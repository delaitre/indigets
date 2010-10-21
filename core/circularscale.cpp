#include <circularscale.hpp>

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

/*QSizeF CircularScale::implicitSize() const
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
*/
QPainterPath CircularScale::buildPath() const
{
    QRectF rect = boundingRect();
    int start = 360 - qRound(m_startAngle);
    int span = qRound(-m_spanAngle);

    QPainterPath path;
    path.arcMoveTo(rect, start);
    path.arcTo(rect, start, span);

    return path;
}

QPainterPath CircularScale::subpath(double from, double to) const
{
    QPainterPath subpath;

    QRectF rect = boundingRect();

    double ratio = to - from;
    int start = 360 - qRound(m_startAngle + m_spanAngle * from);
    int span = qRound(-m_spanAngle * ratio);

    subpath.arcMoveTo(rect, start);
    subpath.arcTo(rect, start, span);

    return subpath;
}
