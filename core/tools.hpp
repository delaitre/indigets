#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <QObject>

class QPointF;

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = 0);

    Q_INVOKABLE double angle(const QPointF& p1, const QPointF& p2) const;
};

#endif // TOOLS_HPP
