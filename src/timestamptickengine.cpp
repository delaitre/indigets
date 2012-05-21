#include "timestamptickengine.hpp"
#include <QDateTime>

TimestampTickEngine::TimestampTickEngine(QObject* parent)
    : StepTickEngine(parent)
    , m_format("hh:mm:ss")
    , m_origin(QDateTime::currentDateTimeUtc())
{

}

QString TimestampTickEngine::format() const
{
    return m_format;
}

void TimestampTickEngine::setFormat(QString format)
{
    if (m_format != format)
    {
        m_format = format;
        emit formatChanged();
    }
}

QDateTime TimestampTickEngine::origin() const
{
    return m_origin;
}

void TimestampTickEngine::setOrigin(QDateTime origin)
{
    if (m_origin != origin)
    {
        m_origin = origin;
        emit originChanged();
    }
}

QString TimestampTickEngine::label(double value) const
{
    // convert the value back to a timestamp
    QDateTime timestamp = m_origin.addMSecs(static_cast<qint64>(value));

    // format it
    return timestamp.toString(m_format);
}
