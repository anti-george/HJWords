#include "preprocessor.h"

Preprocessor::Preprocessor(QObject *parent) : QObject(parent) {}

void Preprocessor::load(qint32 zipVersion, qint32 zipNewVersion, qint32 bookID)
{
    first = zipVersion; mid = zipNewVersion; last = bookID;
    if (QFileInfo("./resources/index.xml").exists())
    {
        QDomDocument doc;
        QFile file("./resources/index.xml");
        if (not file.open(QIODevice::ReadOnly) || not doc.setContent(&file)) {emit failed();}
        QDomNodeList bookItem = doc.elementsByTagName("BookItem");
        if (bookItem.item(0).firstChildElement("BookID").text().toInt() != bookID)
        {
            file.close();
            QDir("./resources").removeRecursively();
            QTimer::singleShot(0, this, SLOT(loadFirstPart()));
        }
        else
        {
            file.close();
            QTimer::singleShot(0, this, SIGNAL(printHeader()));
        }
    }
    else if ((QDir("./audio")).exists())
    {
        QDir("./audio").removeRecursively();
        QTimer::singleShot(0, this, SLOT(loadFirstPart()));
    }
    else QTimer::singleShot(0, this, SLOT(loadFirstPart()));
}

void Preprocessor::loadFirstPart()
{
    appendDebugText(tr("HJWords - Resources Exploded :(") + "\n" + tr("Downloading..."));
    DownloadManager *manager = new DownloadManager;
    Deobfuscator *deobfs = new Deobfuscator(first, mid, last);
    connect(manager, SIGNAL(progress(qint64, qint64)), this, SLOT(progress(qint64, qint64)));
    connect(manager, SIGNAL(failed()), this, SLOT(pause()));
    connect(manager, SIGNAL(failed()), deobfs, SLOT(deleteLater()));
    connect(manager, SIGNAL(failed()), manager, SLOT(deleteLater()));
    connect(manager, SIGNAL(finished()), this, SLOT(loadMidPart()));
    connect(manager, SIGNAL(finished()), deobfs, SLOT(deleteLater()));
    connect(manager, SIGNAL(finished()), manager, SLOT(deleteLater()));
    manager->append(deobfs->getUrlList());
}

void Preprocessor::loadMidPart()
{
    appendDebugText(tr("Configuring...") + "\n");
    QThread *thread = new QThread;
    Deobfuscator *deobfs = new Deobfuscator(first, mid, last);
    deobfs->moveToThread(thread);
    connect(thread, SIGNAL(started()), deobfs, SLOT(extractFileList()));
    connect(deobfs, SIGNAL(failed()), this, SLOT(pause()));
    connect(deobfs, SIGNAL(failed()), deobfs, SLOT(deleteLater()));
    connect(deobfs, SIGNAL(finished()), this, SLOT(loadLastPart()));
    connect(deobfs, SIGNAL(finished()), deobfs, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void Preprocessor::loadLastPart()
{
    QThread *thread = new QThread;
    Deobfuscator *deobfs = new Deobfuscator(first, mid, last);
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
    if (status < 0.05) {status = percentage * 0.05;}
    else if (status < 0.25) {status = 0.05 + percentage * 0.2;}
    else status = 0.25 + percentage * 0.75;
    emit updateDebugBar(status);
}

void Preprocessor::printHeader()
{
    appendDebugText(tr("HJWords - Excited Word Tank") + "\n" +
                    tr("Copyright (C) 2017 Weijia WANG") + "\n" +
                    tr("Released under GNU LGPL version 3.") + "\n\n");
    emit finished();
}

void Preprocessor::pause()
{
    appendDebugText(tr("An error has occurred..."));
    return;
}
