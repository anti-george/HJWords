#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QVector>
#include <QtXml>
#include <QTime>
#include <QMediaPlayer>

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
    void failed();

public slots:
    void splashScreen();
    void receiveText(QString text);

private slots:
    void createTempDict();
    QString decrypt(QString str);

private:
    const QString null = "";
    qint32 progress, unit, difficulty, target, times;
    qint32 size = 10;
    QStringList list;
    QVector<qint32> remain;
    QVector<QStringList> dict;
};

#endif // PROCESSOR_H
