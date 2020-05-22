//#pragma once

#include <QtWidgets/QMainWindow>
#include <QTabBar>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
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

private:
	Ui::OnePlayerClass ui;
	QMediaPlayer* mediaPlayer;      // 播放器
	QMediaPlaylist* mediaPlaylist;  // 播放列表
	QTabWidget* tabWidget;          // 选项卡区域
	QButtonGroup* buttonGroupTab;   // 选项卡切换按钮

};
