#include <linearscale.hpp>
#include <abstractscaleengine.hpp>

LinearScale::LinearScale(QDeclarativeItem* parent)
    : AbstractScale(parent)
    , m_orientation(LinearScale::Vertical)
{

}

LinearScale::Orientation LinearScale::orientation() const
{
    return m_orientation;
}

void LinearScale::setOrientation(LinearScale::Orientation orientation)
{
    if (orientation != m_orientation)
    {
        m_orientation = orientation;
        rebuild();
        emit orientationChanged(m_orientation);
    }
}

QSizeF LinearScale::implicitSize() const
{
    double baselineOffset = baselineVisible() ? thickness() : 0.;
    QSizeF labelOffset(0, 0);
    double tickOffset = 0;

    if (labelsVisible())
    {
        if (engine())
        {
            QFontMetricsF metrics(font());
            QString longestLabel = engine()->longestLabel();
            labelOffset = metrics.boundingRect(longestLabel).size();
        }

        tickOffset = baselineOffset * 0.5 + tickLength() + 5;
    }
    else if (ticksVisible())
    {
        tickOffset = baselineOffset * 0.5 + tickLength();
    }

    double width = 0;
    double height = 0;
    if (m_orientation == Horizontal)
    {
        width = labelOffset.width();
        height = baselineOffset + tickOffset + labelOffset.height();
    }
    else
    {
        width = baselineOffset + tickOffset + labelOffset.width();
        height = labelOffset.height();
    }

    return QSizeF(width, height);
}

QPainterPath LinearScale::buildPath(const QRectF& rect) const
{
    QPainterPath path;

    if (m_orientation == Horizontal)
    {
        double xOffset = implicitWidth() * 0.5;
        double yOffset = thickness() * 0.5;
        if (!flipTicks())
            yOffset = implicitHeight() - yOffset;

        path.moveTo(rect.topLeft() + QPointF(xOffset, yOffset));
        path.lineTo(rect.topRight() + QPointF(-xOffset, yOffset));
    }
    else
    {
        double xOffset = thickness() * 0.5;
        double yOffset = implicitHeight() * 0.5;
        if (!flipTicks())
            xOffset = implicitWidth() - xOffset;

        path.moveTo(rect.bottomLeft() + QPointF(xOffset, -yOffset));
        path.lineTo(rect.topLeft() + QPointF(xOffset, yOffset));
    }

    return path;
}
