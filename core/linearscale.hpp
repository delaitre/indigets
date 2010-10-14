#ifndef LINEARSCALE_HPP
#define LINEARSCALE_HPP

#include <abstractscale.hpp>

class LinearScale : public AbstractScale
{
    Q_OBJECT
    Q_ENUMS(Orientation)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

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

signals:
    void orientationChanged(Orientation orientation);

protected:
    virtual QSizeF implicitSize() const;
    virtual QPainterPath buildPath(const QRectF& rect) const;

private:
    Orientation m_orientation;
};

#endif // LINEARSCALE_HPP
