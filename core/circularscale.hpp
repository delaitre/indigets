#ifndef CIRCULARSCALE_HPP
#define CIRCULARSCALE_HPP

#include <abstractscale.hpp>

class CircularScale : public AbstractScale
{
    Q_OBJECT
    Q_PROPERTY(double startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(double spanAngle READ spanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)

public:
    CircularScale(QDeclarativeItem* parent = 0);

    double startAngle() const;
    void setStartAngle(double angle);

    double spanAngle() const;
    void setSpanAngle(double span);

signals:
    void startAngleChanged(double angle);
    void spanAngleChanged(double span);

protected:
    virtual QSizeF implicitSize() const;
    virtual QPainterPath buildPath(const QRectF& rect) const;

private:
    double m_startAngle;
    double m_spanAngle;
};

#endif // CIRCULARSCALE_HPP
