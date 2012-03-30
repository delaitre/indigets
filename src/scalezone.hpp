#ifndef SCALEZONE_HPP
#define SCALEZONE_HPP

#include <QDeclarativeItem>
#include <QPointer>

class AbstractScale;

class ScaleZone : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(AbstractScale* scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)

public:
    ScaleZone(QDeclarativeItem* parent = 0);

    AbstractScale* scale() const;
    void setScale(AbstractScale* scale);

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

signals:
    void scaleChanged(AbstractScale* scale);
    void minimumChanged(double minimum);
    void maximumChanged(double maximum);

protected slots:
    virtual void rebuild() = 0;

private:
    QPointer<AbstractScale> m_scale;
    double m_minimum;
    double m_maximum;
};

#endif // SCALEZONE_HPP
