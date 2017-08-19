#include "preprocessor.h"
#include <QDebug>

Preprocessor::Preprocessor(QObject *parent) : QObject(parent)
{
}

void Preprocessor::preload()
{
    if ((QDir("./resources")).exists()) QTimer::singleShot(0, this, SLOT(printHeader()));
    else if ((QDir("./audio")).exists()) QTimer::singleShot(0, this, SLOT(preloadLastPart()));
    else QTimer::singleShot(0, this, SLOT(preloadFirstPart()));
}

void Preprocessor::preloadFirstPart()
{
    debug("HJWords - Resources not found :(");
    debug("Downloading (41.2 M) ...");
    Deobfuscator *deobfs = new Deobfuscator;
    DownloadManager *manager = new DownloadManager;
    connect(manager, SIGNAL(progress(qint64, qint64)), this, SLOT(progress(qint64, qint64)));
    connect(manager, SIGNAL(failed()), this, SLOT(pause()));
    connect(manager, SIGNAL(failed()), deobfs, SLOT(deleteLater()));
    connect(manager, SIGNAL(failed()), manager, SLOT(deleteLater()));
    connect(manager, SIGNAL(finished()), this, SLOT(preloadMidPart()));
    connect(manager, SIGNAL(finished()), deobfs, SLOT(deleteLater()));
    connect(manager, SIGNAL(finished()), manager, SLOT(deleteLater()));
    manager->append(deobfs->getUrlList());
}

void Preprocessor::preloadMidPart()
{
    debug("Extracting (50.6 M) ...");
    QThread *thread = new QThread;
    Deobfuscator *deobfs = new Deobfuscator;
    deobfs->moveToThread(thread);
    connect(thread, SIGNAL(started()), deobfs, SLOT(extractFileList()));
    connect(deobfs, SIGNAL(failed()), this, SLOT(pause()));
    connect(deobfs, SIGNAL(failed()), deobfs, SLOT(deleteLater()));
    connect(deobfs, SIGNAL(finished()), this, SLOT(preloadLastPart()));
    connect(deobfs, SIGNAL(finished()), deobfs, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void Preprocessor::preloadLastPart()
{
    debug("Configuring (54.5 M) ...");
    QThread *thread = new QThread;
    Deobfuscator *deobfs = new Deobfuscator;
    connect(thread, SIGNAL(started()), deobfs, SLOT(clean()));
    connect(deobfs, SIGNAL(failed()), this, SLOT(pause()));
    connect(deobfs, SIGNAL(failed()), deobfs, SLOT(deleteLater()));
    connect(deobfs, SIGNAL(finished()), this, SLOT(printHeader()));
    connect(deobfs, SIGNAL(finished()), deobfs, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void Preprocessor::progress(qint64 received, qint64 total)
{
    double percentage = 1.0 * received / total;
    if (status < 0.04) status = percentage * 0.04;
    else if (status < 0.24) status = 0.04 + percentage * 0.2;
    else status = 0.24 + percentage * 0.72;
    emit updateDebugBar(status);
}

void Preprocessor::printHeader()
{
    debug("");
    debug("HJWords - Excited Word Tank");
    debug("Copyright (C) 2017 Weijia WANG");
    debug("Released under GNU LGPL version 3.");
    debug("");
    emit updateDebugBar(1);
    emit finished();
}

void Preprocessor::pause()
{
    debug("\nFailed.");
    return;
}

void Preprocessor::debug(QString str)
{
    emit appendDebugText(str);
}
