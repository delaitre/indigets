#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <QQmlExtensionPlugin>

class Tools;

class Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    virtual void initializeEngine(QQmlEngine * engine, const char * uri);
    virtual void registerTypes(const char* uri);
private:
    Tools* m_tools;
};

#endif // PLUGIN_HPP
