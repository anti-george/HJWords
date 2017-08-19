#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QFile>
#include <QObject>
#include <QQueue>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>

class DownloadManager: public QObject
{
    Q_OBJECT

public:
    explicit DownloadManager(QObject *parent = nullptr);

    void append(const QUrl &url);
    void append(const QStringList &urlList);
    QString saveFileName(const QUrl &url);

signals:
    void finished();
    void failed();
    void progress(qint64, qint64);

private slots:
    void startNextDownload();
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager manager;
    QQueue<QUrl> downloadQueue;
    QNetworkReply *currentDownload;
    QFile output;

    int downloadedCount = 0;
    int totalCount = 0;
};

#endif
