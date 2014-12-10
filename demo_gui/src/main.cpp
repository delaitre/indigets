
#include <QGuiApplication>
#include <QQuickView>
#include <QDir>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QDir dir(QStringLiteral("../libqt/plugins"));
    QStringList dirs;

    dirs << QCoreApplication::libraryPaths();
    dirs << dir.absolutePath();

    dirs << QDir::currentPath() + "/plugins";
    dirs << QDir::currentPath() ;
    dirs << "../";


    QCoreApplication::setLibraryPaths(dirs);
    QGuiApplication app(argc, argv);

    QQuickView view;
    for(const auto& path : dirs)
        {
            view.engine()->addPluginPath(path);
            view.engine()->addImportPath(path);
        }

    view.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
