#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "widgets/preprocessor.h"
#include "widgets/processor.h"
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

    Processor processor;
    Preprocessor preload;
    QObject::connect(&preload, SIGNAL(finished()), &processor, SLOT(splashScreen()));
    QObject::connect(&preload, SIGNAL(appendDebugText(QString)), &layer, SIGNAL(appendDebugText(QString)));
    QObject::connect(&preload, SIGNAL(updateDebugBar(double)), &layer, SIGNAL(updateDebugBar(double)));
    QObject::connect(&processor, SIGNAL(appendText(QString)), &layer, SIGNAL(appendText(QString)));
    QObject::connect(&processor, SIGNAL(updateText(QStringList)), &layer, SIGNAL(updateText(QStringList)));
    QObject::connect(&processor, SIGNAL(enableTextField()), &layer, SIGNAL(enableTextField()));
    QObject::connect(&processor, SIGNAL(disableTextField()), &layer, SIGNAL(disableTextField()));
    QObject::connect(&processor, SIGNAL(updateProgressBar(double)), &layer, SIGNAL(updateProgressBar(double)));
    QObject::connect(&layer, SIGNAL(sendBackText(QString)), &processor, SLOT(receiveText(QString)));
    QObject::connect(&layer, SIGNAL(splashScreen()), &processor, SLOT(splashScreen()));
    QTimer::singleShot(0, &preload, SLOT(preload()));

    return app.exec();
}
