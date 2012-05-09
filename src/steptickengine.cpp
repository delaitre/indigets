#include "steptickengine.hpp"
#include <cmath>

namespace
{

/////////////////////////
// This code is from Qwt

const double _eps = 1.0e-6;

/**
 * Ceil a value, relative to an interval
 *
 * \param value Value to ceil
 * \param intervalSize Interval size
 * \sa floorEps()
 */
double ceilEps(double value, double intervalSize)
{
    const double eps = _eps * intervalSize;

    value = (value - eps) / intervalSize;
    return std::ceil(value) * intervalSize;
}

/**
 * Floor a value, relative to an interval
 *
 * \param value Value to floor
 * \param intervalSize Interval size
 * \sa floorEps()
 */
double floorEps(double value, double intervalSize)
{
    const double eps = _eps * intervalSize;

    value = (value + eps) / intervalSize;
    return std::floor(value) * intervalSize;
}

// End of Qwt's code
/////////////////////////

} // anonymous namespace

StepTickEngine::StepTickEngine(QObject* parent)
    : TickEngine(parent)
    , m_step(10)
{

}

double StepTickEngine::step() const
{
    return m_step;
}

void StepTickEngine::setStep(double step)
{
    if (step != m_step)
    {
        m_step = step;
        emit stepChanged(m_step);
    }
}

QMap<double, QString> StepTickEngine::ticks(double minimum, double maximum) const
{
    double minTick = ceilEps(minimum, m_step);
    double maxTick = floorEps(maximum, m_step);

    QMap<double, QString> ticks;
    for (double value = minTick; value <= maxTick; value += m_step)
    {
        // Add the tick to the list
        ticks[value] = label(value);
    }

    return ticks;
}

QString StepTickEngine::label(double value) const
{
    // Round to 0 if very close
    if (qAbs(value) > _eps)
        return QString::number(value);
    else
        return "0";
}
