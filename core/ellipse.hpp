#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <QDeclarativeItem>

class Ellipse : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(double borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)

public:
    Ellipse(QDeclarativeItem* parent = 0);

    QColor color() const;
    void setColor(const QColor& color);

    QColor borderColor() const;
    void setBorderColor(const QColor& color);

    double borderWidth() const;
    void setBorderWidth(double width);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

signals:
    void colorChanged(const QColor& color);
    void borderColorChanged(const QColor& color);
    void borderWidthChanged(double width);

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
    QColor m_color;
    QColor m_borderColor;
    double m_borderWidth;
    QPainterPath m_path;
};

#endif // ELLIPSE_HPP
