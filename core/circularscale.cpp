#include <circularscale.hpp>
#include <abstractscaleengine.hpp>

CircularScale::CircularScale(QDeclarativeItem* parent)
    : AbstractScale(parent)
    , m_startAngle(215)
    , m_spanAngle(250)
{

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
    hOffset += baselineOffset;
    vOffset += baselineOffset;

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

    double size = qMax(hOffset, vOffset);

    return QSizeF(size, size);
}

QPainterPath CircularScale::buildPath(const QRectF& rect) const
{
    int start = 360 - qRound(m_startAngle);
    int span = qRound(-m_spanAngle);

    double offset = baselineVisible() ? thickness() * 0.5 : 0.;
    if (!flipTicks())
        offset = implicitWidth() - offset;

    QRectF adjustedRect = rect.adjusted(offset, offset, -offset, -offset);

    QPainterPath path;
    path.arcMoveTo(adjustedRect, start);
    path.arcTo(adjustedRect, start, span);

    return path;
}
