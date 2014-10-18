#ifndef STANDARDSCALEZONE_HPP
#define STANDARDSCALEZONE_HPP

#include "scalezone.hpp"
#include <QPainterPath>

class TickEngine;

class StandardScaleZone : public ScaleZone
{
    Q_OBJECT
    Q_PROPERTY(TickEngine* tickEngine READ tickEngine WRITE setTickEngine NOTIFY tickEngineChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool baselineVisible READ baselineVisible WRITE setBaselineVisible NOTIFY baselineVisibleChanged)
    Q_PROPERTY(bool ticksVisible READ ticksVisible WRITE setTicksVisible NOTIFY ticksVisibleChanged)
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)
    Q_PROPERTY(bool beginningTickVisible READ beginningTickVisible WRITE setBeginningTickVisible NOTIFY beginningTickVisibleChanged)
    Q_PROPERTY(bool endingTickVisible READ endingTickVisible WRITE setEndingTickVisible NOTIFY endingTickVisibleChanged)
    Q_PROPERTY(double thickness READ thickness WRITE setThickness NOTIFY thicknessChanged)
    Q_PROPERTY(double tickLength READ tickLength WRITE setTickLength NOTIFY tickLengthChanged)
    Q_PROPERTY(bool flipTicks READ flipTicks WRITE setFlipTicks NOTIFY flipTicksChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)

public:
    StandardScaleZone(QQuickItem* parent = 0);

    TickEngine* tickEngine() const;
    void setTickEngine(TickEngine* engine);

    QMap<double, QString> ticks() const;

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

    void paint(QPainter* painter);

signals:
    void tickEngineChanged(TickEngine* engine);
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

protected slots:
    virtual void rebuild();

private:
    void drawTick(const QPointF& position, double angle, const QString& label, QPainter* painter);

private:
    QPointer<TickEngine> m_tickEngine;
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
    QPainterPath m_path;
};

#endif // STANDARDSCALEZONE_HPP
