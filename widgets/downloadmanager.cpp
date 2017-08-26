#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) : QObject(parent) {}

void DownloadManager::append(const QStringList &urlList)
{
    foreach (QString url, urlList) {append(QUrl::fromEncoded(url.toLocal8Bit()));}
}

void DownloadManager::append(const QUrl &url)
{
    if (downloadQueue.isEmpty())
    {QTimer::singleShot(0, this, SLOT(downloadNext()));}
    downloadQueue.enqueue(url);
    ++totalCount;
}

void DownloadManager::downloadNext()
{
    if (downloadQueue.isEmpty())
    {
        if (downloadedCount != totalCount) {emit failed();}
        else emit finished();
        return;
    }

    QUrl url = downloadQueue.dequeue();
    QString filename = QFileInfo(url.path()).fileName();
    output.setFileName(filename);
    if (not output.open(QIODevice::WriteOnly)) {emit failed(); return;}

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(finished()), SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()), SLOT(downloadReadyRead()));
    connect(currentDownload, SIGNAL(downloadProgress(qint64, qint64)),
            SIGNAL(progress(qint64, qint64)));
}

void DownloadManager::downloadFinished()
{
    output.close();
    if (currentDownload->error()) {currentDownload->deleteLater(); failed();}
    else {++downloadedCount; currentDownload->deleteLater(); downloadNext();}
}

void DownloadManager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
