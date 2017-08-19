#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "widgets/preprocessor.h"
#include "layer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Layer layer;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("compatibility", &layer);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    Preprocessor *preload = new Preprocessor;
    QObject::connect(preload, SIGNAL(appendDebugText(QString)), &layer, SIGNAL(appendDebugText(QString)));
    QObject::connect(preload, SIGNAL(updateDebugBar(double)), &layer, SIGNAL(updateDebugBar(double)));
    QTimer::singleShot(0, preload, SLOT(preload()));

    return app.exec();
}
