#include <abstractscaleengine.hpp>

AbstractScaleEngine::AbstractScaleEngine(QObject* parent)
    : QObject(parent)
    , m_minimum(0)
    , m_maximum(100)
{

}

double AbstractScaleEngine::minimum() const
{
    return m_minimum;
}

void AbstractScaleEngine::setMinimum(double minimum)
{
    if (minimum != m_minimum)
    {
        m_minimum = minimum;
        emit minimumChanged(m_minimum);
    }
}

double AbstractScaleEngine::maximum() const
{
    return m_maximum;
}

void AbstractScaleEngine::setMaximum(double maximum)
{
    if (maximum != m_maximum)
    {
        m_maximum = maximum;
        emit maximumChanged(m_maximum);
    }
}

QMap<double, QString> AbstractScaleEngine::ticks() const
{
    if (m_ticks.isEmpty())
        m_ticks = buildTicks();
    return m_ticks;
}

QString AbstractScaleEngine::longestLabel() const
{
    if (m_longestLabel.isEmpty())
    {
        QMap<double, QString> ticks = this->ticks();
        QMap<double, QString>::const_iterator it = ticks.constBegin();
        QMap<double, QString>::const_iterator itEnd = ticks.constEnd();
        while (it != itEnd)
        {
            QString label = it.value();
            if (label.size() > m_longestLabel.size())
                m_longestLabel = label;
            ++it;
        }
    }

    return m_longestLabel;
}

void AbstractScaleEngine::clearTicks()
{
    m_ticks.clear();
    m_longestLabel.clear();
}
