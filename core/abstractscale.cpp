#include <abstractscale.hpp>
#include <abstractscaleengine.hpp>
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

AbstractScale::AbstractScale(QDeclarativeItem* parent)
    : QDeclarativeItem(parent)
    , m_minimum(0)
    , m_maximum(100)
    , m_engine(0)
    , m_color(Qt::black)
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

AbstractScaleEngine* AbstractScale::engine() const
{
    return m_engine;
}

void AbstractScale::setEngine(AbstractScaleEngine* engine)
{
    if (engine != m_engine)
    {
        m_engine = engine;
        rebuild();
        emit engineChanged(m_engine);
    }
}

QColor AbstractScale::color() const
{
    return m_color;
}

void AbstractScale::setColor(const QColor& color)
{
    if (color != m_color)
    {
        m_color = color;
        rebuild();
        emit colorChanged(m_color);
    }
}

bool AbstractScale::baselineVisible() const
{
    return m_baselineVisible;
}

void AbstractScale::setBaselineVisible(bool visible)
{
    if (visible != m_baselineVisible)
    {
        m_baselineVisible = visible;
        rebuild();
        emit baselineVisibleChanged(m_baselineVisible);
    }
}

bool AbstractScale::ticksVisible() const
{
    return m_ticksVisible;
}

void AbstractScale::setTicksVisible(bool visible)
{
    if (visible != m_ticksVisible)
    {
        m_ticksVisible = visible;
        rebuild();
        emit ticksVisibleChanged(m_ticksVisible);
    }
}

bool AbstractScale::labelsVisible() const
{
    return m_labelsVisible;
}

void AbstractScale::setLabelsVisible(bool visible)
{
    if (visible != m_labelsVisible)
    {
        m_labelsVisible = visible;
        rebuild();
        emit labelsVisibleChanged(m_labelsVisible);
    }
}

bool AbstractScale::beginningTickVisible() const
{
    return m_beginningTickVisible;
}

void AbstractScale::setBeginningTickVisible(bool visible)
{
    if (visible != m_beginningTickVisible)
    {
        m_beginningTickVisible = visible;
        emit beginningTickVisibleChanged(m_beginningTickVisible);
    }
}

bool AbstractScale::endingTickVisible() const
{
    return m_endingTickVisible;
}

void AbstractScale::setEndingTickVisible(bool visible)
{
    if (visible != m_endingTickVisible)
    {
        m_endingTickVisible = visible;
        emit endingTickVisibleChanged(m_endingTickVisible);
    }
}

double AbstractScale::thickness() const
{
    return m_thickness;
}

void AbstractScale::setThickness(double thickness)
{
    if (thickness != m_thickness)
    {
        m_thickness = thickness;
        rebuild();
        emit thicknessChanged(m_thickness);
    }
}

double AbstractScale::tickLength() const
{
    return m_tickLength;
}

void AbstractScale::setTickLength(double length)
{
    length = qMax(length, 0.);
    if (length != m_tickLength)
    {
        m_tickLength = length;
        rebuild();
        emit tickLengthChanged(m_tickLength);
    }
}

bool AbstractScale::flipTicks() const
{
    return m_flipTicks;
}

void AbstractScale::setFlipTicks(bool flipTicks)
{
    if (flipTicks != m_flipTicks)
    {
        m_flipTicks = flipTicks;
        rebuild();
        emit flipTicksChanged(m_flipTicks);
    }
}

QFont AbstractScale::font() const
{
    return m_font;
}

void AbstractScale::setFont(const QFont& font)
{
    if (font != m_font)
    {
        m_font = font;
        rebuild();
        emit fontChanged(m_font);
    }
}

double AbstractScale::percentAtValue(double value) const
{
    if (!m_engine || value < m_minimum || value > m_maximum)
        return -1.;

    double percent = m_engine->percentAtValue(value);

    // Adjust the engine percent to the scale percent
    double engineRange = m_engine->maximum() - m_engine->minimum();
    double scaleRange = m_maximum - m_minimum;
    double ratio = scaleRange / engineRange;

    return (percent - m_engine->percentAtValue(m_minimum)) / ratio;
}

QPointF AbstractScale::pointAtPercent(double percent) const
{
    return m_path.pointAtPercent(percent);
}

QPointF AbstractScale::pointAtValue(double value) const
{
    double percent = percentAtValue(value);
    if (percent < 0.)
        return QPointF();

    return m_path.pointAtPercent(percent);
}

const QPainterPath& AbstractScale::path() const
{
    return m_path;
}

void AbstractScale::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(m_color, m_thickness);
    painter->setPen(pen);
    painter->setFont(m_font);
    painter->setRenderHints(QPainter::Antialiasing, smooth());

    // Baseline
    if (m_baselineVisible)
        painter->strokePath(m_path, pen);

    // Ticks & labels
    if (m_engine && (m_ticksVisible || m_labelsVisible))
    {
        QMap<double, QString> ticks = m_engine->ticks();
        QMap<double, QString>::const_iterator it = ticks.constBegin();
        QMap<double, QString>::const_iterator itEnd = ticks.constEnd();
        while (it != itEnd)
        {
            // Get the tick value from the engine percent
            double percent = it.key();
            double value = m_engine->valueAtPercent(percent);

            // Skip beginning/ending tick if necessary
            if ((!m_beginningTickVisible && qAbs(value - m_minimum) < GICS_EPSILON)
                || (!m_endingTickVisible && qAbs(value - m_maximum) < GICS_EPSILON))
            {
                ++it;
                continue;
            }

            // Convert the engine percent in scale percent
            double adjustedPercent = percentAtValue(value);
            if (adjustedPercent < 0.)
            {
                ++it;
                continue;
            }

            // Render the tick
            QString label = it.value();
            drawTick(adjustedPercent, label, painter);

            ++it;
        }
    }
}

void AbstractScale::drawTick(double percent, const QString& label, QPainter* painter)
{
    if (percent < 0. || percent > 1.)
        return;

    // Get the point at percent of the path
    QPointF start = m_path.pointAtPercent(percent);

    // Get the perpendicular to the path at percent
    qreal angleDeg = m_path.angleAtPercent(percent);
    if (m_flipTicks)
        angleDeg += 180;
    qreal angle = angleDeg / 180 * PI;
    QPointF direction(-std::sin(angle), -std::cos(angle));

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

void AbstractScale::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    // Discard the path on geometry change
    rebuild();
    return QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
}

void AbstractScale::rebuild()
{
    QSizeF size = implicitSize();
    setImplicitWidth(size.width());
    setImplicitHeight(size.height());
    emit implicitWidthChanged(size.width());
    emit implicitHeightChanged(size.height());

    m_path = buildPath(boundingRect());

    update();
}
