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
#include <deque>
#include "ui_OnePlayer.h"

class OnePlayer : public QMainWindow
{
	Q_OBJECT

public:
	OnePlayer(QWidget* parent = Q_NULLPTR);
private slots:
	void on_btnList_clicked();
	void on_btnPlayer_clicked();
	void on_btnLyric_clicked();

	void onStateChanged(QMediaPlayer::State state);
	void onPlaylistChanged(int position);
	void onDurationChanged(qint64 duration);
	void onPositionChanged(qint64 position);
	void onCurrentMediaChanged(const QMediaContent& media);
	//void onTimerCover();

	//
	void on_btnAdd_clicked();
	void on_btnPlay_clicked();
	void on_btnStop_clicked();
	void on_listMusic_doubleClicked(const QModelIndex& index);
	void on_btnClear_clicked();
	void on_sliderVolume_valueChanged(int value);
	void on_sliderProgress_valueChanged(int value);
	void on_btnRemove_clicked();
	void on_btnPrev_clicked();
	void on_btnNext_clicked();

private:
	Ui::OnePlayerClass ui;
	QMediaPlayer* mediaPlayer;      // 播放器
	QMediaPlaylist* mediaPlaylist;  // 播放列表

};
