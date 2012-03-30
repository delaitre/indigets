#include "fixedtickengine.hpp"

FixedTickEngine::FixedTickEngine(QObject* parent)
    : TickEngine(parent)
{

}

QVariant FixedTickEngine::data() const
{
    return m_data;
}

void FixedTickEngine::setData(const QVariant& data)
{
    if (data != m_data)
    {
        if (data.type() == QVariant::List || data.type() == QVariant::StringList)
        {
            m_data = data;
            emit dataChanged(m_data);
        }
    }
}

QMap<double, QString> FixedTickEngine::ticks(double minimum, double maximum) const
{
    QMap<double, QString> ticks;

    // Try to convert the data into a QVariantList
    QVariantList list = m_data.toList();
    if (list.isEmpty())
        return ticks;

    // Browse the data
    foreach (const QVariant& tick, list)
    {
        double value = 0;
        QString label;

        if (tick.canConvert(QVariant::Double))
        {
            // Single value, use it as tick value and label
            bool ok = false;
            value = tick.toDouble(&ok);
            if (!ok)
                continue;
            label = QString::number(value);
        }
        else
        {
            // Try to get a value -> label pair
            QVariantList pair = tick.toList();
            int size = pair.size();
            if (size == 0)
                continue;

            // Tick value
            if (size >= 1)
            {
                QVariant v = pair[0];
                bool ok = false;
                value = v.toDouble(&ok);
                if (!ok)
                    continue;
            }

            // Tick label
            if (size >= 2)
                label = pair[1].toString();
            else
                label = QString::number(value);
        }

        // Add the tick to the ticks list
        if (value >= minimum || value <= maximum)
            ticks[value] = label;
    }

    return ticks;
}
