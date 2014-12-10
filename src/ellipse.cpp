#include "ellipse.hpp"
#include <QPainter>

Ellipse::Ellipse(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_borderWidth(0.)
{
    //FIXME: diasble flags settings ?
    // need to disable this flag to draw inside a QQuickItem
    //setFlag(QGraphicsItem::ItemHasNoContents, false);

    // need to disable this flag to receive geometry change events (used to discard the path cache)
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QColor Ellipse::color() const
{
    return m_color;
}

void Ellipse::setColor(const QColor& color)
{
    if (color != m_color)
    {
        m_color = color;
        update();
        emit colorChanged(m_color);
    }
}

QColor Ellipse::borderColor() const
{
    return m_borderColor;
}

void Ellipse::setBorderColor(const QColor& color)
{
    if (color != m_borderColor)
    {
        m_borderColor = color;
        update();
        emit borderColorChanged(m_borderColor);
    }
}

double Ellipse::borderWidth() const
{
    return m_borderWidth;
}

void Ellipse::setBorderWidth(double width)
{
    if (width != m_borderWidth)
    {
        m_borderWidth = width;
        update();
        emit borderWidthChanged(m_borderWidth);
    }
}

void Ellipse::paint(QPainter* painter)
{
    // Rebuild the path if necessary
    if (m_path.isEmpty())
    {
        QRectF rect = boundingRect();
        m_path.arcMoveTo(rect, 0);
        m_path.arcTo(rect, 0, 360);
    }

    QPen outline(m_borderColor, m_borderWidth);
    painter->setPen(outline);

    QBrush fill(m_color);
    painter->setBrush(fill);

    painter->setRenderHints(QPainter::Antialiasing, smooth());
    painter->drawPath(m_path);
}

void Ellipse::itemChange(ItemChange change, const ItemChangeData& value)
{
    // Discard the path on geometry change
    m_path = QPainterPath();
    QQuickItem::itemChange(change, value);
}
