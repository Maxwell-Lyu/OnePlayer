//#pragma once

#include <QtWidgets/QMainWindow>
#include <QTabBar>
#include <QFile>
#include <QtCore>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <QFileDialog>
#include <QPainter>
#include <QBitmap>
#include <QSize>
#include <taglib/taglib.h>
#include <taglib/tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/attachedpictureframe.h>
#include "ui_OnePlayer.h"

class OnePlayer : public QMainWindow
{
	Q_OBJECT

public:
	OnePlayer(QWidget* parent = Q_NULLPTR);
private slots:

    //自定义槽函数
	void onStateChanged(QMediaPlayer::State state);
	void onPlaylistChanged(int position);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

    // 内部命名槽函数
    //-- 切换tab
    void on_btnList_clicked();
    void on_btnPlayer_clicked();
    void on_btnLyric_clicked();
    //-- 播放控制
    void on_btnPlay_clicked();
    void on_btnStop_clicked();
    void on_btnRand_clicked();
    void on_btnPrev_clicked();
    void on_btnNext_clicked();
    void on_sliderVolume_valueChanged(int value);
    void on_sliderProgress_valueChanged(int value);
    //-- 歌曲列表
    void on_btnAdd_clicked();
    void on_btnClear_clicked();
    void on_btnRemove_clicked();
    void on_listMusic_doubleClicked(const QModelIndex& index);

private:
	Ui::OnePlayerClass ui;
	QMediaPlayer* mediaPlayer;      // 播放器
	QMediaPlaylist* mediaPlaylist;  // 播放列表
    QList<QFileInfo> mediaList;     // 文件信息列表

    void resetPlayer();
};
