#include <plugin.hpp>
#include <tools.hpp>
#include <ellipse.hpp>
#include <linearvaluemapper.hpp>
#include <fixedtickengine.hpp>
#include <steptickengine.hpp>
#include <linearscale.hpp>
#include <circularscale.hpp>
#include <standardscalezone.hpp>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

void Plugin::initializeEngine(QDeclarativeEngine* engine, const char* uri)
{
    Q_UNUSED(uri);

    QDeclarativeContext* context = engine->rootContext();

    m_tools = new Tools(this);
    context->setContextProperty("Gics", m_tools);
}

void Plugin::registerTypes(const char* uri)
{
    qmlRegisterType<Ellipse>(uri, 1, 0, "Ellipse");
    qmlRegisterType<ValueMapper>();
    qmlRegisterType<LinearValueMapper>(uri, 1, 0, "LinearValueMapper");
    qmlRegisterType<TickEngine>();
    qmlRegisterType<FixedTickEngine>(uri, 1, 0, "FixedTickEngine");
    qmlRegisterType<StepTickEngine>(uri, 1, 0, "StepTickEngine");
    qmlRegisterType<AbstractScale>();
    qmlRegisterType<LinearScale>(uri, 1, 0, "LinearScale");
    qmlRegisterType<CircularScale>(uri, 1, 0, "CircularScale");
    qmlRegisterType<ScaleZone>();
    qmlRegisterType<StandardScaleZone>(uri, 1, 0, "StandardScaleZone");
}

Q_EXPORT_PLUGIN2(gics, Plugin);
