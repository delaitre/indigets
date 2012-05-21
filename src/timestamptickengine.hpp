#ifndef TIMESTAMPTICKENGINE_HPP
#define TIMESTAMPTICKENGINE_HPP

#include "steptickengine.hpp"
#include <QDateTime>

class TimestampTickEngine : public StepTickEngine
{
    Q_OBJECT
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QDateTime origin READ origin WRITE setOrigin NOTIFY originChanged)

public:
    TimestampTickEngine(QObject* parent = 0);

    QString format() const;

    void setFormat(QString format);

    QDateTime origin() const;

    void setOrigin(QDateTime origin);

signals:
    void formatChanged();
    void originChanged();

protected:
    virtual QString label(double value) const;

private:
    QString m_format;
    QDateTime m_origin;
};

#endif // TIMESTAMPTICKENGINE_HPP
