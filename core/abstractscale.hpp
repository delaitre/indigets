#ifndef ABSTRACTSCALE_HPP
#define ABSTRACTSCALE_HPP

#include <QDeclarativeItem>
#include <QPointer>

class AbstractScaleEngine;

class AbstractScale : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(AbstractScaleEngine* engine READ engine WRITE setEngine NOTIFY engineChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool baselineVisible READ baselineVisible WRITE setBaselineVisible NOTIFY baselineVisibleChanged)
    Q_PROPERTY(bool ticksVisible READ ticksVisible WRITE setTicksVisible NOTIFY ticksVisibleChanged)
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)
    Q_PROPERTY(bool beginningTickVisible READ beginningTickVisible WRITE setBeginningTickVisible NOTIFY beginningTickVisibleChanged)
    Q_PROPERTY(bool endingTickVisible READ endingTickVisible WRITE setEndingTickVisible NOTIFY endingTickVisibleChanged)
    Q_PROPERTY(double thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
    Q_PROPERTY(double tickLength READ tickLength WRITE setTickLength NOTIFY thickLengthChanged)
    Q_PROPERTY(bool flipTicks READ flipTicks WRITE setFlipTicks NOTIFY flipTicksChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(double minimumWidth READ implicitWidth NOTIFY implicitWidthChanged)
    Q_PROPERTY(double minimumHeight READ implicitHeight NOTIFY implicitHeightChanged)

public:
    AbstractScale(QDeclarativeItem* parent = 0);

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

    AbstractScaleEngine* engine() const;
    void setEngine(AbstractScaleEngine* engine);

    QColor color() const;
    void setColor(const QColor& color);

    bool baselineVisible() const;
    void setBaselineVisible(bool visible);

    bool ticksVisible() const;
    void setTicksVisible(bool visible);

    bool labelsVisible() const;
    void setLabelsVisible(bool visible);

    bool beginningTickVisible() const;
    void setBeginningTickVisible(bool visible);

    bool endingTickVisible() const;
    void setEndingTickVisible(bool visible);

    double thickness() const;
    void setThickness(double thickness);

    double tickLength() const;
    void setTickLength(double length);

    bool flipTicks() const;
    void setFlipTicks(bool flipTicks);

    QFont font() const;
    void setFont(const QFont& font);

    Q_INVOKABLE double percentAtValue(double value) const;
    Q_INVOKABLE QPointF pointAtPercent(double percent) const;
    Q_INVOKABLE QPointF pointAtValue(double value) const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    const QPainterPath& path() const;

signals:
    void minimumChanged(double minimum);
    void maximumChanged(double maximum);
    void engineChanged(AbstractScaleEngine* engine);
    void colorChanged(const QColor& color);
    void baselineVisibleChanged(bool visible);
    void ticksVisibleChanged(bool visible);
    void labelsVisibleChanged(bool visible);
    void beginningTickVisibleChanged(bool visible);
    void endingTickVisibleChanged(bool visible);
    void thicknessChanged(double thickness);
    void tickLengthChanged(double length);
    void flipTicksChanged(bool flipTicks);
    void fontChanged(const QFont& font);
    void implicitWidthChanged(double width);
    void implicitHeightChanged(double height);

protected:
    virtual void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry);
    void rebuild();
    virtual QSizeF implicitSize() const = 0;
    virtual QPainterPath buildPath(const QRectF& rect) const = 0;
    virtual QPainterPath subpath(double from, double to) const = 0;

private:
    void drawTick(double percent, const QString& label, QPainter* painter);

private:
    double m_minimum;
    double m_maximum;
    QPointer<AbstractScaleEngine> m_engine;
    QColor m_color;
    bool m_baselineVisible;
    bool m_ticksVisible;
    bool m_labelsVisible;
    bool m_beginningTickVisible;
    bool m_endingTickVisible;
    double m_thickness;
    double m_tickLength;
    bool m_flipTicks;
    QFont m_font;
    mutable QPainterPath m_path;
};

#endif // ABSTRACTSCALE_HPP
