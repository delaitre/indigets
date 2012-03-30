#ifndef TICKENGINE_HPP
#define TICKENGINE_HPP

#include <QObject>
#include <QMap>

class TickEngine : public QObject
{
    Q_OBJECT

public:
    TickEngine(QObject* parent = 0);

    virtual QMap<double, QString> ticks(double minimum, double maximum) const = 0;
};

#endif // TICKENGINE_HPP
