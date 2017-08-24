#ifndef DEOBFUSCATOR_H
#define DEOBFUSCATOR_H

#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QObject>
#include <QtXml>
#include <quazip.h>
#include <quazipfile.h>
#include <quazipfileinfo.h>

class Deobfuscator: public QObject
{
    Q_OBJECT

public:
    explicit Deobfuscator(qint32 first, qint32 mid, qint32 last, QObject *parent = nullptr);

    QStringList getFileList();
    QStringList getUrlList();

public slots:
    bool extractFileList();
    void setVersion(qint32 first, qint32 mid, qint32 last);
    void clean();

signals:
    void finished();
    void failed();

private:
    bool copyData(QIODevice &inFile, QIODevice &outFile);
    bool extractAll(QString fileCompressed, QString dir);
    bool extractAll(QuaZip &zip, const QString &dir, QString filePwd);
    QString extractFile(QuaZip &zip, QString fileName, QString fileDest, QString filePwd);
    bool extractFile(QuaZip* zip, QString fileName, QString fileDest, QString filePwd);
    bool removeFile(QStringList listFile);

    qint32 zipVersion, zipNewVersion, bookID;
};

#endif // DEOBFUSCATOR_H
