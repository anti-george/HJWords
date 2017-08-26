#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QVector>
#include <QtXml>
#include <QTime>

class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(QObject *parent = nullptr);

signals:
    void appendText(QString);
    void updateText(QStringList);
    void enableTextField();
    void disableTextField();
    void updateProgressBar(double);
    void playAudio(QString);
    void failed();

public slots:
    void splashScreen();
    void receiveText(QString text);
    void setUnitID(qint32 num);
    qint32 getUnitID();

private slots:
    void createTempDict();
    QString decrypt(QString str);

private:
    const QString null = "";
    qint32 unitID, progress, unit, difficulty, target, times, size = 10;
    QStringList list;
    QVector<qint32> remain;
    QVector<QStringList> dict;
};

#endif // PROCESSOR_H
