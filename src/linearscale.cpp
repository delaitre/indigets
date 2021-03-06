#include "linearscale.hpp"

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

/*QSizeF LinearScale::implicitSize() const
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
        width = m_baselineLength + labelOffset.width();
        height = baselineOffset + tickOffset + labelOffset.height();
    }
    else
    {
        width = baselineOffset + tickOffset + labelOffset.width();
        height = m_baselineLength + labelOffset.height();
    }

    return QSizeF(width, height);
}*/

/*QPainterPath LinearScale::buildPath() const
{
    QRectF rect = boundingRect();

    QPainterPath path;
    if (m_orientation == Horizontal)
    {
        double xOffset = (rect.width() - m_baselineLength) * 0.5;
        double yOffset = thickness() * 0.5;
        if (!flipTicks())
            yOffset = implicitHeight() - yOffset;

        QPointF start = rect.topLeft() + QPointF(xOffset, yOffset);
        QPointF end = rect.topRight() + QPointF(-xOffset, yOffset);

        path.moveTo(start);
        path.lineTo(end);
    }
    else
    {
        double xOffset = thickness() * 0.5;
        double yOffset = (rect.height() - m_baselineLength) * 0.5;
        if (!flipTicks())
            xOffset = implicitWidth() - xOffset;

        QPointF start = rect.bottomLeft() + QPointF(xOffset, -yOffset);
        QPointF end = rect.topLeft() + QPointF(xOffset, yOffset);

        path.moveTo(start);
        path.lineTo(end);
    }

    return path;
}*/

QPainterPath LinearScale::buildPath() const
{
    QRectF rect = boundingRect();
    QPainterPath path;

    if (m_orientation == Horizontal)
    {
        path.moveTo(rect.topLeft());
        path.lineTo(rect.topRight());
    }
    else
    {
        path.moveTo(rect.bottomLeft());
        path.lineTo(rect.topLeft());
    }

    return path;
}

QPainterPath LinearScale::subpath(double from, double to) const
{
    QPainterPath subpath;
    const QPainterPath& path = this->path();

    subpath.moveTo(path.pointAtPercent(from));
    subpath.lineTo(path.pointAtPercent(to));

    return subpath;
}
