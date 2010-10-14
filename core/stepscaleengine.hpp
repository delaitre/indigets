#ifndef STEPSCALEENGINE_HPP
#define STEPSCALEENGINE_HPP

#include <linearscaleengine.hpp>

class StepScaleEngine : public LinearScaleEngine
{
    Q_OBJECT
    Q_PROPERTY(double step READ step WRITE setStep NOTIFY stepChanged)

public:
    StepScaleEngine(QObject* parent = 0);

    double step() const;
    void setStep(double step);

signals:
    void stepChanged(double step);

protected:
    virtual QMap<double, QString> buildTicks() const;

private:
    double m_step;
};

#endif // STEPSCALEENGINE_HPP
