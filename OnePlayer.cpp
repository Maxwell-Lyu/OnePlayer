#include "OnePlayer.h"

OnePlayer::OnePlayer(QWidget* parent)
	: QMainWindow(parent),
	mediaPlayer(nullptr),
	mediaPlaylist(nullptr),
	tabWidget(nullptr),
	buttonGroupTab(nullptr)
{
	ui.setupUi(this);
	mediaPlayer = new QMediaPlayer(this);
	mediaPlaylist = new QMediaPlaylist(this);
	tabWidget = ui.tabWidget;
	buttonGroupTab = ui.buttonGroupTab;
	tabWidget->tabBar()->hide();
}

void OnePlayer::on_btnList_clicked() { tabWidget->setCurrentIndex(0); }
void OnePlayer::on_btnPlayer_clicked() { tabWidget->setCurrentIndex(1); }
void OnePlayer::on_btnLyric_clicked() { tabWidget->setCurrentIndex(2); }
