#ifndef LAYER_H
#define LAYER_H

#include <QObject>

class Layer : public QObject
{
    Q_OBJECT
public:
    explicit Layer(QObject *parent = nullptr);

signals:
    void splashScreen();
    void appendDebugText(QString text);
    void updateDebugBar(double value);
    void appendText(QString text);
    void updateText(QStringList list);
    void sendBackText(QString text);
    void updateProgressBar(double value);
    void enableTextField();
    void disableTextField();
    void preload(qint32 zipVersion, qint32 zipNewVersion, qint32 bookID);
};

#endif // LAYER_H


