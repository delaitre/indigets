#include <tools.hpp>
#include <QLineF>

Tools::Tools(QObject* parent) :
    QObject(parent)
{
}

double Tools::angle(const QPointF& p1, const QPointF& p2) const
{
    return -QLineF(p1, p2).angle();
}
