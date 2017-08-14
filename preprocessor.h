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
    void debug(QString str);
    void pause();

signals:
    void appendPlainText(QString);
    void failed();

public slots:
};

#endif // PREPROCESSOR_H
