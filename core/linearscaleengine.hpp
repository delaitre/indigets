#ifndef LINEARSCALEENGINE_HPP
#define LINEARSCALEENGINE_HPP

#include <abstractscaleengine.hpp>

class LinearScaleEngine : public AbstractScaleEngine
{
    Q_OBJECT

public:
    LinearScaleEngine(QObject *parent = 0);

    Q_INVOKABLE virtual double percentAtValue(double value) const;
    Q_INVOKABLE virtual double valueAtPercent(double percent) const;
};

#endif // LINEARSCALEENGINE_HPP
