#ifndef FIXEDTICKENGINE_HPP
#define FIXEDTICKENGINE_HPP

#include "tickengine.hpp"
#include <QVariant>

class FixedTickEngine : public TickEngine
{
    Q_OBJECT
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)

public:
    FixedTickEngine(QObject* parent = 0);

    QVariant data() const;
    void setData(const QVariant& data);

    virtual QMap<double, QString> ticks(double minimum, double maximum) const;

signals:
    void dataChanged(const QVariant& data);

private:
    QVariant m_data;
};

#endif // FIXEDTICKENGINE_HPP
