#include "processor.h"

Processor::Processor(QObject *parent) : QObject(parent) {}

void Processor::splashScreen()
{
    unit = 0;
    progress = 0;
    updateProgressBar(0);
    difficulty = 0;
    qsrand(QTime::currentTime().msec());
    list.clear();
    list << tr("Peaceful") << tr("Easy") << tr("Hard") << tr("Explosive");
    list << tr("Here are some options!") << null;
    updateText(list);
}

void Processor::receiveText(QString text)
{
    qsrand(QTime::currentTime().msec());

    for (int i = remain.size() - 1; i >= 0; --i)
    {
        if (remain[i] > 4 * size)
        {
            remain.erase(remain.begin() + i);
        }
    }

    if (progress == 4 * size)
    {
        if (text != list[5] && list[5] != null)
        {
            appendText(difficulty == 3 ? tr("NO!!!") : tr("Looks incorrect..."));
        }
        else
        {
            list.clear();
            disableTextField();
            list << null << null << tr("Yeah!") << null << tr("Once again?") << null;
            updateText(list);
        }
        return;
    }
    else
    {
        if (not progress)
        {
            if (not difficulty) {for (int i = 1; i < 5; ++i) {if (list[i - 1] == text) {difficulty = i;}}}

            if (difficulty == 1)
            {
                if (not unit)
                {
                    unit = unitID + 1;
                    enableTextField();
                    list.clear();
                    list << null << tr("Submit") << null << null << tr("Now, choose the textbook!") << null;
                    updateText(list);
                    return;
                }
                else unit = text.toInt();
            }
            else unit = qrand() % unitID + 1;
            createTempDict();
        }

        if (text != list[5] && list[5] != null)
        {
            if (difficulty == 3)
            {
                progress = 4 * size;
                appendText(tr("Looks like everything is over..."));
            }
            else if (difficulty == 4)
            {
                QDir("./resources").removeRecursively();
                disableTextField();
                list.clear();
                list << null << null << null << null << tr("Splendid explosion!") << null;
                updateProgressBar(0);
                updateText(list);
            }
            else
            {
                appendText(tr("Looks incorrect..."));
                QMediaPlayer *player = new QMediaPlayer;
                QString folder = (times == 2) ? "./resources/sentences/" : "./resources/words/";
                player->setMedia(QUrl::fromLocalFile(folder + dict[target][0] + ".mp3"));
                player->play();
            }
            return;
        }

        target = remain[progress] % size;
        times = remain[progress] / size;
        list.clear();

        if (times == 3)
        {
            enableTextField();
            list << tr("Submit") << null << null << null << dict[target][1] << dict[target][0];
        }
        else
        {
            disableTextField();
            QVector<qint32> random;
            while (true)
            {
                random.clear();
                while (random.length() < 4)
                {
                    bool right = true;
                    qint32 num = qrand() % size;
                    for (qint32 item : random) {right = (item == num) ? false : true;}
                    if (right) {random.append(num);}
                }
                if (random[0] == target || random[1] == target) {break;}
                if (random[2] == target || random[3] == target) {break;}
            }
            switch (times)
            {
            case 0:
                for (int i = 0; i < 4; ++i) {list << dict[random[i]][1];}
                list << dict[target][times] << dict[target][1];
                break;
            case 1:
                for (int i = 0; i < 4; ++i) {list << dict[random[i]][0];}
                list << dict[target][times] << dict[target][0];
                break;
            case 2:
                QRegularExpression regex("\\[(.*)\\]");
                QString sentence = dict[target][2];
                if (regex.match(sentence).hasMatch())
                {
                    QString word = regex.match(sentence).captured(1);
                    sentence.replace(regex, "________");
                    for (int i = 0; i < 4; ++i)
                    {
                        if (random[i] == target) {list << word;}
                        else list << dict[random[i]][0];
                    }
                    list << sentence << word;
                }
                else
                {
                    for (int i = 0; i < 4; ++i) list << dict[random[i]][0];
                    QString text = tr("Bonus! Simply choose %1.").arg(dict[target][0]);
                    list << text << dict[target][0];
                }
                break;
            }
        }
        updateProgressBar(0.25 * ++progress / size);
        updateText(list);
    }
}

void Processor::createTempDict()
{
    dict.clear();
    remain.clear();

    QVector<qint32> temp;
    QDomDocument doc;
    QFile file("./resources/index.xml");
    if (not file.open(QIODevice::ReadOnly) || not doc.setContent(&file)) {emit failed();}
    QDomNodeList bookItem = doc.elementsByTagName("BookItem");
    for (int i = 0, j = 0; i < bookItem.size(); ++i)
    {
        QDomNode node = bookItem.item(i);
        QStringList tempList;
        if (node.firstChildElement("UnitID").text().toInt() != unit) {continue;}
        tempList << node.firstChildElement("Word").text();
        tempList << decrypt(node.firstChildElement("WordDef").text());
        tempList << decrypt(node.firstChildElement("Sentence").text()) + "\n" +
                    decrypt(node.firstChildElement("SentenceDef").text());
        dict.append(tempList);
        temp.append(j++);
    }
    file.close();

    qsrand(QTime::currentTime().msec());
    size = temp.size();
    for (int i = 0; i < (size << 2); ++i)
    {
        qint32 random = qrand() % temp.size();
        remain.append(temp[random]);
        if (temp[random] < (size << 1) + size) {temp[random] += size;}
        else temp.erase(temp.begin() + random);
    }
}

QString Processor::decrypt(QString str)
{
    QString std = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i < str.length(); ++i) {str[i] = std[0x3f - std.indexOf(str[i])];}
    return QString::fromUtf8(QByteArray::fromBase64(str.toUtf8()));
}

void Processor::setUnitID(qint32 num)
{
    unitID = num;
}

qint32 Processor::getUnitID()
{
    return unitID;
}
