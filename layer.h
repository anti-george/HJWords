#ifndef LAYER_H
#define LAYER_H

#include <QObject>

class Layer : public QObject
{
    Q_OBJECT
public:
    explicit Layer(QObject *parent = nullptr);

signals:
    void appendDebugText(QString text);
    void updateDebugBar(double value);
};

#endif // LAYER_H
