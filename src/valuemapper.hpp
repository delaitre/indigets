#ifndef VALUEMAPPER_HPP
#define VALUEMAPPER_HPP

#include <QObject>

class ValueMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)

public:
    ValueMapper(QObject* parent = 0);

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

    Q_INVOKABLE virtual double percentAtValue(double value) const = 0;
    Q_INVOKABLE virtual double valueAtPercent(double percent) const = 0;

signals:
    void minimumChanged(double minimum);
    void maximumChanged(double maximum);

private:
    double m_minimum;
    double m_maximum;
};

#endif // VALUEMAPPER_HPP
