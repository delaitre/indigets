#include "scalezone.hpp"
#include "abstractscale.hpp"

ScaleZone::ScaleZone(QDeclarativeItem* parent)
    : QDeclarativeItem(parent)
    , m_minimum(0)
    , m_maximum(0)
{

}

AbstractScale* ScaleZone::scale() const
{
    return m_scale;
}

void ScaleZone::setScale(AbstractScale* scale)
{
    if (scale != m_scale)
    {
        if (m_scale)
            disconnect(m_scale, SIGNAL(pathChanged(const QPainterPath&)), this, SLOT(rebuild()));

        m_scale = scale;

        if (m_scale)
            connect(m_scale.data(), SIGNAL(pathChanged(const QPainterPath&)), this, SLOT(rebuild()));

        rebuild();
        emit scaleChanged(m_scale);
    }
}

double ScaleZone::minimum() const
{
    return m_minimum;
}

void ScaleZone::setMinimum(double minimum)
{
    if (minimum != m_minimum)
    {
        m_minimum = minimum;
        rebuild();
        emit minimumChanged(m_minimum);
    }
}

double ScaleZone::maximum() const
{
    return m_maximum;
}

void ScaleZone::setMaximum(double maximum)
{
    if (maximum != m_maximum)
    {
        m_maximum = maximum;
        rebuild();
        emit maximumChanged(m_maximum);
    }
}
