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
    explicit Deobfuscator(QObject *parent = nullptr);

    QStringList getFileList();
    QStringList getUrlList();

public slots:
    bool extractFileList();
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

    const qint32 zipVersion = 1508281615;
    const qint32 zipNewVersion = 1604271249;
    const qint32 bookID = 11852;
};

#endif // DEOBFUSCATOR_H
