#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <QDeclarativeExtensionPlugin>

class Tools;

class Plugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    virtual void initializeEngine(QDeclarativeEngine* engine, const char* uri);
    virtual void registerTypes(const char* uri);

private:
    Tools* m_tools;
};

#endif // PLUGIN_HPP
