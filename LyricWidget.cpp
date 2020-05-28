#include "LyricWidget.h"
#include <QtGui>

LyricWidget::LyricWidget(QWidget* parent)
   : QWidget(parent),
     timer(new QTimer(this))
{
    // 绘制频率
    timer->setInterval(interval);
    // 超时时绘制, 超过时长时停止
    connect(timer, &QTimer::timeout, [=]() {
        if(position <= duration) {
            repaint();
            position += interval;
        }
    });

}



void LyricWidget::paintEvent(QPaintEvent* event) {
    if(not duration or not lyric.length()) {
        int areaBottom = height()-lineHeight;
        int areaMiddle = areaBottom / 2 + bias;
        QPainter p(this);
        // 绘制无歌词消息
        QString strLyric = "没有找到歌词";
        QPainter pTmp;
        QFont m_ftLyric(QString::fromLocal8Bit("微软雅黑"), 10, QFont::Bold);QFontMetrics fm(m_ftLyric);
        QSize textSize = fm.size(Qt::TextSingleLine, strLyric);
        QRect rtText(QPoint(0, 0), textSize), rt(0, areaMiddle, width(), lineHeight);
        // 文字
        QImage pmMask(rtText.width(), rtText.height(), QImage::Format_ARGB32);
        pmMask.fill(Qt::transparent);
        if (pTmp.begin(&pmMask))
        {
            pTmp.setFont(m_ftLyric);
            pTmp.setPen(QColor(128,128,128));
            pTmp.drawText(pmMask.rect(), strLyric);
        }
        pTmp.end();
        // 绘制到画布
        p.drawImage(rt.left() + (rt.width() - rtText.width()) / 2, rt.top() +  (rt.height() - rtText.height()) / 2, pmMask);
    }
    else {
        // 对currentIndex进行位移, 找到合适的句子
        int index = currentIndex;
        while(currentIndex > 0
              and lyric[currentIndex].time > position)
            --currentIndex;
        while(currentIndex < lyric.size() - 1
              and lyric[currentIndex + 1].time <= position)
            ++currentIndex;
        // 使用bias产生一个动画效果
        if(index != currentIndex) bias = lineHeight;
        if(bias) --bias;
        int areaBottom = height()-lineHeight;
        int areaMiddle = areaBottom / 2 + bias;
        QPainter p(this);
        // 绘制带动画的歌词
        paintLine(p, currentIndex, QRect(0, areaMiddle, width(), lineHeight));
        // 绘制前后的歌词
        int tmpIndex = currentIndex;
        for (int y = areaMiddle - lineHeight; y > 0; y -= lineHeight)
            paintLine(p, --tmpIndex, QRect(0, y, width(), lineHeight));
        tmpIndex = currentIndex;
        for (int y = areaMiddle + lineHeight; y < height() - lineHeight; y += lineHeight)
            paintLine(p, ++tmpIndex, QRect(0, y, width(), lineHeight));
    }
    QWidget::paintEvent(event);
}



void LyricWidget::paintLine(QPainter &painter, int index, const QRect &rt) {
    // 过滤下标
    if(index < 0 or index >= lyric.size()) return;
    // 空串直接不绘制
    const QString strLyric = lyric[index].text;
    if(strLyric.isEmpty()) return;
    if(index == currentIndex) {
        // 动画歌词
        qint64 beginTime = lyric[index].time;
        qint64 endTime = index == lyric.size() - 1 ? duration : lyric[index + 1].time;
        QPainter pTmp;
        // 设定字体和绘制区域
        QFont m_ftLyric(QString::fromLocal8Bit("微软雅黑"), 14, QFont::Bold);QFontMetrics fm(m_ftLyric);
        QSize textSize = fm.size(Qt::TextSingleLine, strLyric);
        QRect rtText(QPoint(0, 0), textSize);
        int mPrecent = rtText.width() * (position - beginTime) / (endTime - beginTime);

        // 文字遮罩
        QImage pmMask(rtText.width(), rtText.height(), QImage::Format_ARGB32);
        pmMask.fill(Qt::transparent);
        if (pTmp.begin(&pmMask))
        {
            pTmp.setFont(m_ftLyric);
            pTmp.setPen(Qt::black);
            pTmp.drawText(pmMask.rect(), strLyric);
        }
        pTmp.end();
        // 文字填充
        QImage pmFG(rtText.width(), rtText.height(), QImage::Format_ARGB32);
        if (pTmp.begin(&pmFG))
        {
            pTmp.setCompositionMode(QPainter::CompositionMode_Source);
            // 绘制底色
            pTmp.fillRect(QRect(0, 0, rtText.width(), rtText.height()), QBrush(Qt::white));
            // 绘制进度
            pTmp.fillRect(QRect(0, 0, mPrecent, rtText.height()), QBrush(QColor(30, 136, 229)));
            // 应用遮罩
            pTmp.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            pTmp.drawImage(0, 0, pmMask);
            pTmp.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        }
        pTmp.end();
        // 绘制到画布
        painter.drawImage(rt.left() + (rt.width() - rtText.width()) / 2, rt.top() +  (rt.height() - rtText.height()) / 2, pmFG);
    }
    else {
        // 静态歌词
        QPainter pTmp;
        QFont m_ftLyric(QString::fromLocal8Bit("微软雅黑"), 10, QFont::Bold);QFontMetrics fm(m_ftLyric);
        QSize textSize = fm.size(Qt::TextSingleLine, strLyric);
        QRect rtText(QPoint(0, 0), textSize);
        // 文字
        QImage pmMask(rtText.width(), rtText.height(), QImage::Format_ARGB32);
        pmMask.fill(Qt::transparent);
        if (pTmp.begin(&pmMask))
        {
            pTmp.setFont(m_ftLyric);
            pTmp.setPen(QColor(238,238,238));
            pTmp.drawText(pmMask.rect(), strLyric);
        }
        pTmp.end();
        // 绘制到画布
        painter.drawImage(rt.left() + (rt.width() - rtText.width()) / 2, rt.top() +  (rt.height() - rtText.height()) / 2, pmMask);
    }
    return;
}


bool LyricWidget::loadFile(QString path) {
    // 初始化
    lyric.clear();
    album = artist = author = by = re = title = ve = "";
    currentIndex = bias = 0;
    position = duration = 0;
    // 无文件, 相当于进行重置
    if(path.isEmpty()) return false;
    // 有文件, 成功打开时处理
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
    return true;
}


void LyricWidget::parseLine(QString &line) {
    // 空行
    if (line.isEmpty()) {
        return;
    }
    QString lineLow = line.toLower();
    if (lineLow.startsWith("[al:")) {
        // 唱片集
        album = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[ar:")) {
        // 演唱者
        artist = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[au:")) {
        // 歌词作者
        author = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[by:")) {
        // LRC制作者
        by = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[re:")) {
        // 此LRC文件的创建者或编辑器
        re = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[ti:")) {
        // 歌词标题
        title = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else if (lineLow.startsWith("[ve:")) {
        // 程序的版本
        ve = QString::fromStdWString(line.toStdWString().substr(4, static_cast<size_t>(line.length() - 5)));
    } else {
        // 歌词行
        int delimiterIndex = line.indexOf("]");
        QString time = QString::fromStdString(line.toStdString().substr(1, static_cast<size_t>(delimiterIndex - 1)));
        LyricLine ll;
        // 处理时间戳
        ll.time = QTime::fromString(time, QString("mm:ss.z")).msecsSinceStartOfDay();
        // 处理文字
        line.remove(0, delimiterIndex + 1);
        ll.text = line;
        if (lyric.empty() || lyric.last().time < ll.time)
        {
            // 正常顺序
            lyric.append(ll);
        }
        else
        {
            // 乱序修正
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


