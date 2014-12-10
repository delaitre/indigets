#ifndef ABSTRACTSCALE_HPP
#define ABSTRACTSCALE_HPP

#include <QQuickItem>
#include <QPainterPath>
#include <QPointer>

class ValueMapper;
class ScaleZone;

class AbstractScale : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(ValueMapper* mapper READ mapper WRITE setMapper NOTIFY mapperChanged)
    Q_PROPERTY(QQmlListProperty<ScaleZone> zones READ zones)
    Q_PROPERTY(const QPainterPath& path READ path NOTIFY pathChanged)

public:
    AbstractScale(QQuickItem* parent = 0);

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

    ValueMapper* mapper() const;
    void setMapper(ValueMapper* mapper);

    QQmlListProperty<ScaleZone> zones();
    int zoneCount() const;
    ScaleZone* zone(int index) const;

    const QPainterPath& path() const;
    virtual QPainterPath subpath(double from, double to) const; // FIXME should be pure virtual

    Q_INVOKABLE double percentAtValue(double value) const;

    Q_INVOKABLE QPointF pointAtPercent(double percent) const;
    Q_INVOKABLE QPointF pointAtValue(double value) const;

    Q_INVOKABLE double angleAtPercent(double percent) const;
    Q_INVOKABLE double angleAtValue(double value) const;

signals:
    void minimumChanged(double minimum);
    void maximumChanged(double maximum);
    void mapperChanged(ValueMapper* mapper);
    void pathChanged(const QPainterPath& path);

protected:
    virtual void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry);
    void rebuild();
    virtual QPainterPath buildPath() const; // FIXME should be pure virtual

private:
    double m_minimum;
    double m_maximum;
    QPointer<ValueMapper> m_mapper;
    QList<ScaleZone*> m_zones;
    mutable QPainterPath m_path;
};

#endif // ABSTRACTSCALE_HPP
