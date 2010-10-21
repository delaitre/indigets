#include <abstractscale.hpp>
#include <valuemapper.hpp>

#include <QPainter>

AbstractScale::AbstractScale(QDeclarativeItem* parent)
    : QDeclarativeItem(parent)
    , m_minimum(0)
    , m_maximum(100)
{

}

double AbstractScale::minimum() const
{
    return m_minimum;
}

void AbstractScale::setMinimum(double minimum)
{
    if (minimum != m_minimum)
    {
        m_minimum = minimum;
        rebuild();
        emit minimumChanged(m_minimum);
    }
}

double AbstractScale::maximum() const
{
    return m_maximum;
}

void AbstractScale::setMaximum(double maximum)
{
    if (maximum != m_maximum)
    {
        m_maximum = maximum;
        rebuild();
        emit maximumChanged(m_maximum);
    }
}

ValueMapper* AbstractScale::mapper() const
{
    return m_mapper;
}

void AbstractScale::setMapper(ValueMapper* mapper)
{
    if (mapper != m_mapper)
    {
        m_mapper = mapper;
        rebuild();
        emit mapperChanged(m_mapper);
    }
}

QDeclarativeListProperty<ScaleZone> AbstractScale::zones()
{
    return QDeclarativeListProperty<ScaleZone>(this, m_zones);
}

int AbstractScale::zoneCount() const
{
    return m_zones.count();
}

ScaleZone* AbstractScale::zone(int index) const
{
    return m_zones.at(index);
}

const QPainterPath& AbstractScale::path() const
{
    return m_path;
}

double AbstractScale::percentAtValue(double value) const
{
    if (!m_mapper || value <= m_minimum)
        return 0.;
    if (value >= m_maximum)
        return 1.;

    return m_mapper->percentAtValue(value);
}

QPointF AbstractScale::pointAtPercent(double percent) const
{
    return m_path.pointAtPercent(percent);
}

QPointF AbstractScale::pointAtValue(double value) const
{
    return m_path.pointAtPercent(percentAtValue(value));
}

double AbstractScale::angleAtPercent(double percent) const
{
    return m_path.angleAtPercent(percent);
}

double AbstractScale::angleAtValue(double value) const
{
    return m_path.angleAtPercent(percentAtValue(value));
}

void AbstractScale::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);

    // Discard the path on geometry change
    rebuild();
}

void AbstractScale::rebuild()
{
    m_path = buildPath();
    emit pathChanged(m_path);
    update();
}
