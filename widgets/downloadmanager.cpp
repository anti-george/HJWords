#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
}

void DownloadManager::append(const QStringList &urlList)
{
    foreach (QString url, urlList) append(QUrl::fromEncoded(url.toLocal8Bit()));
}

void DownloadManager::append(const QUrl &url)
{
    if (downloadQueue.isEmpty()) QTimer::singleShot(0, this, SLOT(startNextDownload()));
    downloadQueue.enqueue(url);
    ++totalCount;
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    return QFileInfo(url.path()).fileName();
}

void DownloadManager::startNextDownload()
{
    if (downloadQueue.isEmpty())
    {
        if (downloadedCount == totalCount) emit finished();
        else emit failed();
        return;
    }

    QUrl url = downloadQueue.dequeue();
    QString filename = saveFileName(url);
    output.setFileName(filename);
    if (!output.open(QIODevice::WriteOnly))
    {
        emit failed();
        return;
    }

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

    if (currentDownload->error())
    {
        currentDownload->deleteLater();
        emit failed();
    }
    else
    {
        ++downloadedCount;
        currentDownload->deleteLater();
        startNextDownload();
    }
}

void DownloadManager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
