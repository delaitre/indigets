#ifndef STEPTICKENGINE_HPP
#define STEPTICKENGINE_HPP

#include "tickengine.hpp"

class StepTickEngine : public TickEngine
{
    Q_OBJECT
    Q_PROPERTY(double step READ step WRITE setStep NOTIFY stepChanged)

public:
    StepTickEngine(QObject* parent = 0);

    double step() const;
    void setStep(double step);

    virtual QMap<double, QString> ticks(double minimum, double maximum) const;

signals:
    void stepChanged(double step);

protected:
    virtual QString label(double value) const;

private:
    double m_step;
};

#endif // STEPTICKENGINE_HPP
