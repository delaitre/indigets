#include "stepscaleengine.hpp"
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

StepScaleEngine::StepScaleEngine(QObject* parent)
    : LinearScaleEngine(parent)
    , m_step(10)
{

}

double StepScaleEngine::step() const
{
    return m_step;
}

void StepScaleEngine::setStep(double step)
{
    if (step != m_step)
    {
        m_step = step;
        clearTicks();
        emit stepChanged(m_step);
    }
}

QMap<double, QString> StepScaleEngine::buildTicks() const
{
    double minTick = ceilEps(minimum(), m_step);
    double maxTick = floorEps(maximum(), m_step);

    QMap<double, QString> ticks;
    for (double i = minTick; i <= maxTick; i += m_step)
    {
        double percent = percentAtValue(i);
        QString label("0");
        if (qAbs(i) > _eps)
            label = QString::number(i);
        ticks[percent] = label;
    }

    return ticks;
}
