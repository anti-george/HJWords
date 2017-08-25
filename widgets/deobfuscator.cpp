#include "deobfuscator.h"

Deobfuscator::Deobfuscator(qint32 first, qint32 mid, qint32 last, QObject *parent) :
    QObject(parent), zipVersion(first), zipNewVersion(mid), bookID(last)
{
}

bool Deobfuscator::copyData(QIODevice &inFile, QIODevice &outFile)
{
    while (!inFile.atEnd())
    {
        char buf[4096];
        qint64 readLen = inFile.read(buf, 4096);
        if (readLen <= 0) return false;
        if (outFile.write(buf, readLen) != readLen) return false;
    }
    return true;
}

bool Deobfuscator::extractFile(QuaZip* zip, QString fileName, QString fileDest, QString filePwd)
{
    if (!zip) return false;
    if (zip->getMode() != QuaZip::mdUnzip) return false;
    if (!fileName.isEmpty()) zip->setCurrentFile(fileName);
    QuaZipFile inFile(zip);
    if(!inFile.open(QIODevice::ReadOnly,
                    filePwd.toLatin1().data()) || inFile.getZipError()) return false;
    QDir curDir;
    if (fileDest.endsWith('/') && !curDir.mkpath(fileDest)) return false;
    else if (!curDir.mkpath(QFileInfo(fileDest).absolutePath())) return false;

    QuaZipFileInfo64 info;
    if (!zip->getCurrentFileInfo(&info)) return false;

    QFile::Permissions srcPerm = info.getPermissions();
    if (fileDest.endsWith('/') && QFileInfo(fileDest).isDir())
    {
        if (srcPerm) QFile(fileDest).setPermissions(srcPerm);
        return true;
    }

    QFile outFile;
    outFile.setFileName(fileDest);
    if(!outFile.open(QIODevice::WriteOnly)) return false;
    if (!copyData(inFile, outFile) || inFile.getZipError()) {outFile.close(); return false;}
    outFile.close();

    inFile.close();
    if (inFile.getZipError()) return false;
    if (srcPerm) outFile.setPermissions(srcPerm);
    return true;
}

QString Deobfuscator::extractFile(QuaZip &zip, QString fileName, QString fileDest, QString filePwd)
{
    if(!zip.open(QuaZip::mdUnzip)) return QString();
    if (fileDest.isEmpty()) fileDest = fileName;
    if (!extractFile(&zip, fileName, fileDest, filePwd)) return QString();

    zip.close();
    if (zip.getZipError()) return QString();
    return QFileInfo(fileDest).absoluteFilePath();
}

bool Deobfuscator::extractAll(QuaZip &zip, const QString &dir, QString filePwd)
{
    if(!zip.open(QuaZip::mdUnzip)) return false;

    QDir directory(dir);
    QStringList extracted;
    if (!zip.goToFirstFile()) return false;
    do
    {
        QString name = zip.getCurrentFileName();
        QString absFilePath = directory.absoluteFilePath(name);
        if (absFilePath.startsWith("/")) absFilePath.replace("\\", "/");
        if (!extractFile(&zip, "", absFilePath, filePwd)) return false;
        extracted.append(absFilePath);
    }
    while (zip.goToNextFile());

    zip.close();
    if (zip.getZipError()) return false;
    return true;
}

bool Deobfuscator::extractAll(QString fileCompressed, QString dir)
{
    QString pwd;
    QuaZip zip(fileCompressed);
    for (int i = 0; i < 10; ++i) pwd += 0xff - fileCompressed[i].toLatin1();
    pwd = QString(pwd.toLatin1().toBase64());
    if (!(extractAll(zip, dir, pwd))) return false;
    return true;
}

QStringList Deobfuscator::getFileList()
{
    return {QString::number(zipNewVersion) + ".xml.zip", QString::number(zipNewVersion) + ".res.zip",
            QString::number(zipVersion) + ".sentence.zip"};
}

QStringList Deobfuscator::getUrlList()
{
    QString base = "https://c2g.hjfile.cn/package/" + QString::number(bookID) + "/";
    QStringList url, list = getFileList();
    foreach (QString file, list) url << base + file;
    return url;
}

bool Deobfuscator::extractFileList()
{
    QStringList args = getFileList(), dir {"./audio", "./", "./audio/sentences"};
    for (int i = 0; i < 3; ++i) if (!extractAll(args.at(i), dir.at(i))) {emit failed(); return false;}
    emit finished(); return true;
}

void Deobfuscator::clean()
{
    QDomDocument doc;
    QFile file("./audio/word.txt");
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) emit failed();
    QDomNodeList bookItem = doc.elementsByTagName("BookItem");
    for (int i = 0; i < bookItem.size(); ++i)
    {
        QDomNode node = bookItem.item(i);
        QDomElement from = node.firstChildElement("WordID");
        QDomElement to = node.firstChildElement("Word");
        if (from.isNull() || to.isNull()) continue;
        QStringList folders {"./audio/words/", "./audio/sentences/"};
        for (QString folder : folders)
        {
            if (QFileInfo::exists(folder + from.text() + ".mp3"))
            {
                if (QFileInfo::exists(folder + to.text() + ".mp3"))
                    if (!QFile::remove(folder + to.text() + ".mp3")) emit failed();
                if (!QFile::rename(folder + from.text() + ".mp3",
                                   folder + to.text() + ".mp3")) emit failed();
            }
        }
    }
    file.close();

    QDir dir; QStringList args = getFileList();
    for (QString file : args) if (!QFile::remove(file)) emit failed();
    if (!QFile::rename("./audio/word.txt", "./audio/index.xml")) emit failed();
    else if (!QFile::remove("./audio/unit.txt")) emit failed();
    else if (!dir.rename("./audio", "./resources")) emit failed();
    else emit finished();
}
