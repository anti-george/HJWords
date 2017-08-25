#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "widgets/preprocessor.h"
#include "widgets/processor.h"
#include "layer.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale::system().name(), ":/"))
        app.installTranslator(&translator);

    Layer layer;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("compatibility", &layer);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;

    Processor processor;
    Preprocessor preprocessor;

    QObject::connect(&preprocessor, SIGNAL(finished()), &processor, SLOT(splashScreen()));

    QObject::connect(&preprocessor, SIGNAL(appendDebugText(QString)), &layer, SIGNAL(appendDebugText(QString)));
    QObject::connect(&preprocessor, SIGNAL(updateDebugBar(double)), &layer, SIGNAL(updateDebugBar(double)));

    QObject::connect(&processor, SIGNAL(appendText(QString)), &layer, SIGNAL(appendText(QString)));
    QObject::connect(&processor, SIGNAL(updateText(QStringList)), &layer, SIGNAL(updateText(QStringList)));
    QObject::connect(&processor, SIGNAL(enableTextField()), &layer, SIGNAL(enableTextField()));
    QObject::connect(&processor, SIGNAL(disableTextField()), &layer, SIGNAL(disableTextField()));
    QObject::connect(&processor, SIGNAL(updateProgressBar(double)), &layer, SIGNAL(updateProgressBar(double)));

    QObject::connect(&layer, SIGNAL(sendBackText(QString)), &processor, SLOT(receiveText(QString)));
    QObject::connect(&layer, SIGNAL(splashScreen()), &processor, SLOT(splashScreen()));
    QObject::connect(&layer, SIGNAL(setUnitID(qint32)), &processor, SLOT(setUnitID(qint32)));
    QObject::connect(&layer, SIGNAL(getUnitID()), &processor, SLOT(getUnitID()));
    QObject::connect(&layer, SIGNAL(load(qint32, qint32, qint32)), &preprocessor, SLOT(load(qint32, qint32, qint32)));

    return app.exec();
}
