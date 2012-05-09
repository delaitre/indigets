#include "timestamptickengine.hpp"
#include <QDateTime>

TimestampTickEngine::TimestampTickEngine(QObject* parent)
    : StepTickEngine(parent)
    , m_format("hh:mm:ss")
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

QString TimestampTickEngine::label(double value) const
{
    // convert the value back to a timestamp
    QDateTime timestamp = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(value));

    // format it
    return timestamp.toString(m_format);
}
