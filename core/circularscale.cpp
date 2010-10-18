#include <circularscale.hpp>
#include <abstractscaleengine.hpp>

CircularScale::CircularScale(QDeclarativeItem* parent)
    : AbstractScale(parent)
    , m_baselineRect(QPointF(0, 0), implicitSize())
    , m_startAngle(215)
    , m_spanAngle(250)
{

}

const QRectF& CircularScale::baselineRect() const
{
    return m_baselineRect;
}

void CircularScale::setBaselineRect(const QRectF& rect)
{
    QRectF normalized = rect.normalized();
    if (normalized != m_baselineRect)
    {
        m_baselineRect = normalized;
        rebuild();
        emit baselineRectChanged(m_baselineRect);
    }
}

double CircularScale::startAngle() const
{
    return m_startAngle;
}

void CircularScale::setStartAngle(double angle)
{
    if (angle != m_startAngle)
    {
        m_startAngle = angle;
        rebuild();
        emit startAngleChanged(m_startAngle);
    }
}

double CircularScale::spanAngle() const
{
    return m_spanAngle;
}

void CircularScale::setSpanAngle(double span)
{
    if (span != m_spanAngle)
    {
        m_spanAngle = span;
        rebuild();
        emit spanAngleChanged(m_spanAngle);
    }
}

QSizeF CircularScale::implicitSize() const
{
    double hOffset = 0.;
    double vOffset = 0.;

    double baselineOffset = baselineVisible() ? thickness() : 0.;

    if (!flipTicks())
    {
        if (labelsVisible())
        {
            if (engine())
            {
                QFontMetricsF metrics(font());
                QString longestLabel = engine()->longestLabel();
                QSizeF labelOffset = metrics.boundingRect(longestLabel).size();
                hOffset += labelOffset.width();
                vOffset += labelOffset.height();
            }

            double labelSpacing = baselineOffset * 0.5 + tickLength() + 5;
            hOffset += labelSpacing;
            vOffset += labelSpacing;
        }
        else if (ticksVisible())
        {
            double tickLength = baselineOffset * 0.5 + this->tickLength();
            hOffset += tickLength;
            vOffset += tickLength;
        }
    }

    double width = m_baselineRect.width() + baselineOffset + hOffset * 2;
    double height = m_baselineRect.height() + baselineOffset + vOffset * 2;

    return QSizeF(width, height);
}

QPainterPath CircularScale::buildPath(const QRectF& rect) const
{
    int start = 360 - qRound(m_startAngle);
    int span = qRound(-m_spanAngle);

    QRectF adjustedRect = m_baselineRect;
    adjustedRect.moveCenter(rect.center());
    QPainterPath path;
    path.arcMoveTo(adjustedRect, start);
    path.arcTo(adjustedRect, start, span);

    return path;
}

QPainterPath CircularScale::subpath(double from, double to) const
{
    QPainterPath subpath;

    QRectF rect = m_baselineRect;
    rect.moveCenter(boundingRect().center());
    QPointF fromPoint = path().pointAtPercent(from);
    QPointF toPoint = path().pointAtPercent(to);
    QPointF center = rect.center();

    double fromAngle = QLineF(center, fromPoint).angle();
    double toAngle = QLineF(center, toPoint).angle();

    subpath.arcMoveTo(rect, fromAngle);
    subpath.arcTo(rect, fromAngle, toAngle - fromAngle);

    return subpath;
}
