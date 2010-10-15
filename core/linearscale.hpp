#ifndef LINEARSCALE_HPP
#define LINEARSCALE_HPP

#include <abstractscale.hpp>

class LinearScale : public AbstractScale
{
    Q_OBJECT
    Q_ENUMS(Orientation)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(double baselineLength READ baselineLength WRITE setBaselineLength NOTIFY baselineLengthChanged)

public:
    enum Orientation
    {
        Horizontal = Qt::Horizontal,
        Vertical = Qt::Vertical
    };

public:
    LinearScale(QDeclarativeItem* parent = 0);

    Orientation orientation() const;
    void setOrientation(Orientation orientation);

    double baselineLength() const;
    void setBaselineLength(double length);

signals:
    void orientationChanged(Orientation orientation);
    void baselineLengthChanged(double length);

protected:
    virtual QSizeF implicitSize() const;
    virtual QPainterPath buildPath(const QRectF& rect) const;

private:
    Orientation m_orientation;
    double m_baselineLength;
};

#endif // LINEARSCALE_HPP
