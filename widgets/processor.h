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
    void failed();

public slots:
    void splashScreen();
    void receiveText(QString text);

private slots:
    void createTempDict();
    QString decrypt(QString str);

private:
    const QString null = "";
    qint32 progress = 0;
    qint32 unit = 0;
    qint32 difficulty = 4;
    qint32 size = 10;
    QStringList list;
    QVector<qint32> remain;
    QVector<QStringList> dict;
};

#endif // PROCESSOR_H
