#include <standardscalezone.hpp>
#include <abstractscale.hpp>
#include <tickengine.hpp>
#include <QPainter>
#include <cmath>

#ifndef PI
#define PI (3.14159265)
#endif // PI

#ifndef GICS_EPSILON
#define GICS_EPSILON (1.0e-6)
#endif // GICS_EPSILON

namespace
{

QPointF pointOnRect(const QRectF& rect, double angle)
{
    QPointF center = rect.center();
    QSizeF halfSize = rect.size() * 0.5;

    // Make sure the angle is in range [0, 360[
    angle = std::fmod(angle, 360);
    if (angle < 0)    angle += 360;

    double hyp = std::sqrt(halfSize.width() * halfSize.width() + halfSize.height() * halfSize.height());
    double theta = std::asin(halfSize.height() / hyp);
    double thetaDeg = 180 * theta / PI;
    double angleRad = angle * PI / 180;

    QPointF pos;
    if (angle >= 0 && angle < thetaDeg)
        pos = QPointF(halfSize.width(), std::sin(angleRad) * halfSize.height());
    else if (angle >= thetaDeg && angle < 180 - thetaDeg)
        pos = QPointF(std::cos(angleRad) * halfSize.width(), halfSize.height());
    else if (angle >= 180 - thetaDeg && angle < 180 + thetaDeg)
        pos = QPointF(-halfSize.width(), std::sin(angleRad) * halfSize.height());
    else if (angle >= 180 + thetaDeg && angle < 360 - thetaDeg)
        pos = QPointF(std::cos(angleRad) * halfSize.width(), -halfSize.height());
    else if (angle >= 360 - thetaDeg && angle < 360)
        pos = QPointF(halfSize.width(), std::sin(angleRad) * halfSize.height());

    return pos + center;
}

} // anonymous namespace

StandardScaleZone::StandardScaleZone(QDeclarativeItem* parent)
    : ScaleZone(parent)
    , m_baselineVisible(true)
    , m_ticksVisible(true)
    , m_labelsVisible(true)
    , m_beginningTickVisible(true)
    , m_endingTickVisible(true)
    , m_thickness(2)
    , m_tickLength(3)
    , m_flipTicks(false)
{
    // need to disable this flag to draw inside a QDeclarativeItem
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

TickEngine* StandardScaleZone::tickEngine() const
{
    return m_tickEngine;
}

void StandardScaleZone::setTickEngine(TickEngine* engine)
{
    if (engine != m_tickEngine)
    {
        m_tickEngine = engine;
        rebuild();
        emit tickEngineChanged(m_tickEngine);
    }
}

QMap<double, QString> StandardScaleZone::ticks() const
{
    QMap<double, QString> ticks;
    if (m_tickEngine)
    {
        ticks = m_tickEngine->ticks(minimum(), maximum());

        // Skip beginning/ending tick if necessary
        if (!ticks.isEmpty() && !m_beginningTickVisible)
        {
            QMap<double, QString>::iterator it = ticks.begin();
            double value = it.key();
            if (qAbs(value - minimum()) < GICS_EPSILON)
                ticks.remove(value);
        }

        if (!ticks.isEmpty() && !m_endingTickVisible)
        {
            QMap<double, QString>::iterator it = --ticks.end();
            double value = it.key();
            if (qAbs(maximum() - value) < GICS_EPSILON)
                ticks.remove(value);
        }
    }

    return ticks;
}

QColor StandardScaleZone::color() const
{
    return m_color;
}

void StandardScaleZone::setColor(const QColor& color)
{
    if (color != m_color)
    {
        m_color = color;
        update();
        emit colorChanged(m_color);
    }
}

bool StandardScaleZone::baselineVisible() const
{
    return m_baselineVisible;
}

void StandardScaleZone::setBaselineVisible(bool visible)
{
    if (visible != m_baselineVisible)
    {
        m_baselineVisible = visible;
        rebuild();
        emit baselineVisibleChanged(m_baselineVisible);
    }
}

bool StandardScaleZone::ticksVisible() const
{
    return m_ticksVisible;
}

void StandardScaleZone::setTicksVisible(bool visible)
{
    if (visible != m_ticksVisible)
    {
        m_ticksVisible = visible;
        rebuild();
        emit ticksVisibleChanged(m_ticksVisible);
    }
}

bool StandardScaleZone::labelsVisible() const
{
    return m_labelsVisible;
}

void StandardScaleZone::setLabelsVisible(bool visible)
{
    if (visible != m_labelsVisible)
    {
        m_labelsVisible = visible;
        rebuild();
        emit labelsVisibleChanged(m_labelsVisible);
    }
}

bool StandardScaleZone::beginningTickVisible() const
{
    return m_beginningTickVisible;
}

void StandardScaleZone::setBeginningTickVisible(bool visible)
{
    if (visible != m_beginningTickVisible)
    {
        m_beginningTickVisible = visible;
        rebuild();
        emit beginningTickVisibleChanged(m_beginningTickVisible);
    }
}

bool StandardScaleZone::endingTickVisible() const
{
    return m_endingTickVisible;
}

void StandardScaleZone::setEndingTickVisible(bool visible)
{
    if (visible != m_endingTickVisible)
    {
        m_endingTickVisible = visible;
        rebuild();
        emit endingTickVisibleChanged(m_endingTickVisible);
    }
}

double StandardScaleZone::thickness() const
{
    return m_thickness;
}

void StandardScaleZone::setThickness(double thickness)
{
    if (thickness != m_thickness)
    {
        m_thickness = thickness;
        rebuild();
        emit thicknessChanged(m_thickness);
    }
}

double StandardScaleZone::tickLength() const
{
    return m_tickLength;
}

void StandardScaleZone::setTickLength(double length)
{
    length = qMax(length, 0.);
    if (length != m_tickLength)
    {
        m_tickLength = length;
        rebuild();
        emit tickLengthChanged(m_tickLength);
    }
}

bool StandardScaleZone::flipTicks() const
{
    return m_flipTicks;
}

void StandardScaleZone::setFlipTicks(bool flipTicks)
{
    if (flipTicks != m_flipTicks)
    {
        m_flipTicks = flipTicks;
        rebuild();
        emit flipTicksChanged(m_flipTicks);
    }
}

QFont StandardScaleZone::font() const
{
    return m_font;
}

void StandardScaleZone::setFont(const QFont& font)
{
    if (font != m_font)
    {
        m_font = font;
        rebuild();
        emit fontChanged(m_font);
    }
}

void StandardScaleZone::rebuild()
{
    // TODO compute implicit width/height more precisely

    m_path = QPainterPath();
    QRectF rect;

    AbstractScale* scale = this->scale();
    if (scale)
    {
        // Compute new zone path
        m_path = scale->subpath(scale->percentAtValue(minimum()), scale->percentAtValue(maximum()));

        // Compute the zone bounding rect according to path, baseline, ticks and labels
        rect = m_path.boundingRect();

        // Baseline
        if (m_baselineVisible)
        {
            double halfThickness = m_thickness / 2;
            rect.adjust(-halfThickness, -halfThickness, halfThickness, halfThickness);
        }

        // Ticks & labels
        if (m_tickEngine)
        {
            if (m_labelsVisible)
            {
                QString longestLabel;
                QMap<double, QString> ticks = this->ticks();
                QMap<double, QString>::const_iterator it = ticks.constBegin();
                QMap<double, QString>::const_iterator itEnd = ticks.constEnd();
                while (it != itEnd)
                {
                    const QString& label = it.value();
                    if (label.size() > longestLabel.size())
                        longestLabel = label;
                    ++it;
                }

                if (!longestLabel.isNull())
                {
                    QFontMetricsF metrics(m_font);
                    QRectF labelRect(QPointF(0, 0), metrics.size(Qt::TextSingleLine, longestLabel));
                    rect.adjust(-labelRect.width(), -labelRect.height(), labelRect.width(), labelRect.height());
                }

                double tickOffset = m_tickLength + 5;
                rect.adjust(-tickOffset, -tickOffset, tickOffset, tickOffset);
            }
            else if (m_ticksVisible)
            {
                rect.adjust(-m_tickLength, -m_tickLength, m_tickLength, m_tickLength);
            }
        }
    }

    // Correct the zone position and size
    setPos(rect.topLeft());
    setImplicitWidth(rect.width());
    setImplicitHeight(rect.height());

    // Correct the zone path according to the new bounding rect
    m_path.translate(rect.topLeft() * -1);

    update();
}

void StandardScaleZone::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    AbstractScale* scale = this->scale();
    if (!scale)
        return;

    QPen pen(m_color, m_thickness);
    painter->setPen(pen);
    painter->setFont(m_font);
    painter->setRenderHints(QPainter::Antialiasing, smooth());

    // Baseline
    if (m_baselineVisible)
        painter->strokePath(m_path, pen);

    // Ticks & labels
    if (m_tickEngine && (m_ticksVisible || m_labelsVisible))
    {
        QMap<double, QString> ticks = this->ticks();
        QMap<double, QString>::const_iterator it = ticks.constBegin();
        QMap<double, QString>::const_iterator itEnd = ticks.constEnd();
        while (it != itEnd)
        {
            // Get the position and angle for the value
            double value = it.key();
            double percent = scale->percentAtValue(value);
            QPointF position = scale->pointAtPercent(percent);
            position += pos() * -1; // Adjust the position from scale pos to zone pos
            qreal angleDeg = scale->angleAtPercent(percent);

            // Render
            drawTick(position, angleDeg, it.value(), painter);
            ++it;
        }
    }
}

void StandardScaleZone::drawTick(const QPointF& position, double angle, const QString& label, QPainter* painter)
{
    QPointF start = position;

    // Get the perpendicular to the path at percent
    qreal angleDeg = angle;
    if (m_flipTicks)
        angleDeg += 180;
    qreal angleRad = angleDeg / 180 * PI;
    QPointF direction(-std::sin(angleRad), -std::cos(angleRad));

    // Adjust the start point position to ensure its visibility if the baseline is visible
    if (m_baselineVisible)
        start += direction * m_thickness * 0.5;

    // Tick
    if (m_ticksVisible)
    {
        QPointF end = start + direction * m_tickLength;
        painter->drawLine(start, end);
    }

    // Label
    if (m_labelsVisible)
    {
        QFontMetrics metrics(m_font);
        QRectF labelRect(QPointF(0, 0), metrics.size(Qt::TextSingleLine, label));
        QPointF labelPos = start + direction * (m_tickLength + 5);
        labelRect.moveTo(labelPos - pointOnRect(labelRect, 90 - angleDeg));
        painter->drawText(labelRect, label);
    }
}

/*
QString StandardScaleZone::longestLabel() const
{
    QString longestLabel;

    QMap<double, QString> ticks = this->ticks();
    QMap<double, QString>::const_iterator it = ticks.constBegin();
    QMap<double, QString>::const_iterator itEnd = ticks.constEnd();
    while (it != itEnd)
    {
        QString label = it.value();
        if (label.size() > longestLabel.size())
            longestLabel = label;
        ++it;
    }

    return longestLabel;
}
*/
