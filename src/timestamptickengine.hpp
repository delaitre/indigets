#ifndef TIMESTAMPTICKENGINE_HPP
#define TIMESTAMPTICKENGINE_HPP

#include "steptickengine.hpp"

class TimestampTickEngine : public StepTickEngine
{
    Q_OBJECT
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)

public:
    TimestampTickEngine(QObject* parent = 0);

    QString format() const;

    void setFormat(QString format);

signals:
    void formatChanged();

protected:
    virtual QString label(double value) const;

private:
    QString m_format;
};

#endif // TIMESTAMPTICKENGINE_HPP
