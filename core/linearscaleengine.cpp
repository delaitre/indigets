#include "linearscaleengine.hpp"

LinearScaleEngine::LinearScaleEngine(QObject* parent)
    : AbstractScaleEngine(parent)
{

}

double LinearScaleEngine::percentAtValue(double value) const
{
    return (value - minimum()) / (maximum() - minimum());
}

double LinearScaleEngine::valueAtPercent(double percent) const
{
    return  percent * (maximum() - minimum()) + minimum();
}
