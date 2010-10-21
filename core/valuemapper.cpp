#include <valuemapper.hpp>

ValueMapper::ValueMapper(QObject* parent)
    : QObject(parent)
    , m_minimum(0)
    , m_maximum(100)
{

}

double ValueMapper::minimum() const
{
    return m_minimum;
}

void ValueMapper::setMinimum(double minimum)
{
    if (minimum != m_minimum)
    {
        m_minimum = minimum;
        emit minimumChanged(m_minimum);
    }
}

double ValueMapper::maximum() const
{
    return m_maximum;
}

void ValueMapper::setMaximum(double maximum)
{
    if (maximum != m_maximum)
    {
        m_maximum = maximum;
        emit maximumChanged(m_maximum);
    }
}
