#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include <QWidget>
#include <QtCore>

struct LyricLine {
    // 开始时间
    qint64 time;
    // 内容
    QString text;
};

class LyricWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LyricWidget(QWidget* parent);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:

    const int interval = 30;
    const int lineHeight = 30;
    // 歌词列表
    QVector<LyricLine> lyric;
    // 当前正在进行动画的行
    int currentIndex = 0;
    // 当前进度
    qint64 position = 0;
    // 总时长
    qint64 duration = 0;

    // 计时控制动画
    QTimer *timer;



    // 唱片集
    QString album;
    // 演唱者
    QString artist;
    // 歌词作者
    QString author;
    // 此LRC文件的创建者
    QString by;
    // 创建此LRC文件的播放器或编辑器
    QString re;
    // 歌词标题
    QString title;
    // 程序的版本
    QString ve;

    //
    void parseLine(QString &line);
    void paintLine(QPainter &painter, int index, const QRect &rt);
public:
    bool loadFile(QString path);
    void setDuration(qint64 dur) { duration = dur; }
    void setPosition(qint64 pos) { position = pos; }
    void stop() { timer->stop(); }
    void start() { timer->start(); }
};

#endif // LYRICWIDGET_H
