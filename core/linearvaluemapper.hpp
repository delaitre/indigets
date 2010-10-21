#ifndef LINEARVALUEMAPPER_HPP
#define LINEARVALUEMAPPER_HPP

#include <valuemapper.hpp>

class LinearValueMapper : public ValueMapper
{
    Q_OBJECT

public:
    LinearValueMapper(QObject* parent = 0);

    Q_INVOKABLE virtual double percentAtValue(double value) const;
    Q_INVOKABLE virtual double valueAtPercent(double percent) const;
};

#endif // LINEARVALUEMAPPER_HPP
