#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include <QWidget>
#include <QFileInfo>

struct LyricLine {
    qint64 time;
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

    QVector<LyricLine> lyric;
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
    // 总时长
    qint64 duration = 0;

    void parseLine(QString &line);

public:
    bool loadFile(QString path);
};

#endif // LYRICWIDGET_H
