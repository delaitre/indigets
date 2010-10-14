#include <plugin.hpp>
#include <tools.hpp>
#include <ellipse.hpp>
#include <stepscaleengine.hpp>
#include <fixedscaleengine.hpp>
#include <linearscale.hpp>
#include <circularscale.hpp>
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
    qmlRegisterType<AbstractScaleEngine>();
    qmlRegisterType<StepScaleEngine>(uri, 1, 0, "StepScaleEngine");
    qmlRegisterType<FixedScaleEngine>(uri, 1, 0, "FixedScaleEngine");
    qmlRegisterType<AbstractScale>();
    qmlRegisterType<LinearScale>(uri, 1, 0, "LinearScale");
    qmlRegisterType<CircularScale>(uri, 1, 0, "CircularScale");
}

Q_EXPORT_PLUGIN2(gics, Plugin);
