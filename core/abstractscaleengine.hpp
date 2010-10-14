#ifndef ABSTRACTSCALEENGINE_HPP
#define ABSTRACTSCALEENGINE_HPP

#include <QObject>
#include <QMap>

class AbstractScaleEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)

public:

    AbstractScaleEngine(QObject* parent = 0);

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

    QMap<double, QString> ticks() const;
    QString longestLabel() const;

    Q_INVOKABLE virtual double percentAtValue(double value) const = 0;
    Q_INVOKABLE virtual double valueAtPercent(double percent) const = 0;

signals:
    void minimumChanged(double minimum);
    void maximumChanged(double maximum);

protected:
    virtual QMap<double, QString> buildTicks() const = 0;
    void clearTicks();

private:
    double m_minimum;
    double m_maximum;
    mutable QMap<double, QString> m_ticks;
    mutable QString m_longestLabel;
};

#endif // ABSTRACTSCALEENGINE_HPP
