#include <linearvaluemapper.hpp>

LinearValueMapper::LinearValueMapper(QObject* parent)
    : ValueMapper(parent)
{

}

double LinearValueMapper::percentAtValue(double value) const
{
    return (value - minimum()) / (maximum() - minimum());
}

double LinearValueMapper::valueAtPercent(double percent) const
{
    return  percent * (maximum() - minimum()) + minimum();
}
