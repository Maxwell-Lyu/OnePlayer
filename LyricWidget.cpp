#include "LyricWidget.h"
#include <QtGui>

LyricWidget::LyricWidget(QWidget* parent)
   : QWidget(parent)
{

}



void LyricWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
}




bool LyricWidget::loadFile(QString path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;

    QTextStream stream(&file);

    // 读取文本
    while (!stream.atEnd())
    {
        QString strline = stream.readLine();
        parseLine(strline);
    }

    if (duration == 0 and not lyric.isEmpty())
    {
        duration = lyric.last().time;
    }
    return true;
}


void LyricWidget::parseLine(QString &line) {

    if (line.isEmpty()) {
        return;
    }
    QString lineLow = line.toLower();
    if (lineLow.startsWith("[al:")) {
        // 唱片集
        album = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[ar:")) {
        // 演唱者
        artist = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[au:")) {
        // 歌词作者
        author = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[by:")) {
        // LRC制作者
        by = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[re:")) {
        // 此LRC文件的创建者或编辑器
        re = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[ti:")) {
        // 歌词标题
        title = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[ve:")) {
        // 程序的版本
        ve = QString::fromStdString(line.toStdString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else {
        int delimiterIndex = line.indexOf("]");
        QString time = QString::fromStdString(line.toStdString().substr(1, static_cast<size_t>(delimiterIndex - 1)));
        LyricLine ll;
        ll.time = QTime::fromString(time, QString("mm:ss.z")).msecsSinceStartOfDay();
        line.remove(0, delimiterIndex + 1);
        ll.text = line;
        if (lyric.empty() || lyric.last().time < ll.time)
        {
            lyric.append(ll);
        }
        else
        {
            int i = lyric.size() - 1;
            for (; i > 0; i--)
            {
                if (lyric[i].time < ll.time)
                    break;
            }
            lyric.insert(i + 1, ll);
        }
    }
}
