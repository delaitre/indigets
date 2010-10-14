#ifndef FIXEDSCALEENGINE_HPP
#define FIXEDSCALEENGINE_HPP

#include <linearscaleengine.hpp>
#include <QVariant>

class FixedScaleEngine : public LinearScaleEngine
{
    Q_OBJECT
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)

public:
    FixedScaleEngine(QObject* parent = 0);

    QVariant data() const;
    void setData(const QVariant& data);

signals:
    void dataChanged(const QVariant& data);

protected:
    virtual QMap<double, QString> buildTicks() const;

private:
    QVariant m_data;
};

#endif // FIXEDSCALEENGINE_HPP
