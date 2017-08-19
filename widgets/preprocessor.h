#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <QObject>
#include <QThread>
#include "downloadmanager.h"
#include "deobfuscator.h"

class Preprocessor : public QObject
{
    Q_OBJECT
public:
    explicit Preprocessor(QObject *parent = nullptr);

public slots:
    void preload();

private slots:
    void preloadFirstPart();
    void preloadMidPart();
    void preloadLastPart();
    void printHeader();
    void progress(qint64 received, qint64 total);
    void debug(QString str);
    void pause();

signals:
    void updateDebugBar(double);
    void appendDebugText(QString);
    void finished();
    void failed();

private:
    double status = 0;
};

#endif // PREPROCESSOR_H
