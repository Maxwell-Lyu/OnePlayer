#include "OnePlayer.h"

OnePlayer::OnePlayer(QWidget* parent)
	: QMainWindow(parent),
	mediaPlayer(new QMediaPlayer(this)),
	mediaPlaylist(new QMediaPlaylist(this))
	//timerCoverRotate(new QTimer(this))
{

	connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
		this, SLOT(onStateChanged(QMediaPlayer::State)));

	connect(mediaPlayer, SIGNAL(positionChanged(qint64)),
		this, SLOT(onPositionChanged(qint64)));

	connect(mediaPlayer, SIGNAL(durationChanged(qint64)),
		this, SLOT(onDurationChanged(qint64)));

	connect(mediaPlaylist, SIGNAL(currentIndexChanged(int)),
		this, SLOT(onPlaylistChanged(int)));

	//connect(timerCoverRotate, SIGNAL(timeout()),
	//	this, SLOT(onTimerCover()));

	ui.setupUi(this);

	ui.tabWidget->tabBar()->hide();

	mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop); //循环模式
	mediaPlayer->setPlaylist(mediaPlaylist);

	//timerCoverRotate->start(100);
	ui.widgetCover->loadImage(QImage(":/img/testBG"));
	//ui.widgetCover->setGeometry(100, 100, 300, 300);
	ui.widgetCover->startRotateAnimation(100, 1);
}





void OnePlayer::onStateChanged(QMediaPlayer::State state)
{//播放器状态变化，更新按钮状态
	//ui.btnPlay->setEnabled(!(state == QMediaPlayer::PlayingState));
	//ui.btnPause->setEnabled(state == QMediaPlayer::PlayingState);
	ui.btnStop->setEnabled(state == QMediaPlayer::PlayingState);
	ui.widgetCover->setState(state == QMediaPlayer::PlayingState);
}

void OnePlayer::onPlaylistChanged(int position)
{//播放列表变化,更新当前播放文件名显示
	ui.listMusic->setCurrentRow(position);
	QListWidgetItem* item = ui.listMusic->currentItem();
	//if (item)
	//	ui.LabCurMedia->setText(item->text());
}

void OnePlayer::onDurationChanged(qint64 duration)
{//文件时长变化，更新进度显示
	ui.sliderProgress->setMaximum(duration);

	//int   secs = duration / 1000;//秒
	//int   mins = secs / 60; //分钟
	//secs = secs % 60;//余数秒
	//durationTime = QString::asprintf("%d:%d", mins, secs);
	//ui.LabRatio->setText(positionTime + "/" + durationTime);
}

void OnePlayer::onCurrentMediaChanged(const QMediaContent& media) {
	// TODO
}


void OnePlayer::onPositionChanged(qint64 position)
{//当前文件播放位置变化，更新进度显示
	if (ui.sliderProgress->isSliderDown())
		return;

	ui.sliderProgress->setSliderPosition(position);//
}

void OnePlayer::on_btnAdd_clicked()
{//添加文件
	QString curPath = QDir::homePath();//获取系统当前目录
	QString dlgTitle = "选择音频文件"; //对话框标题
	QString filter = "音频文件(*.mp3 *.wav *.wma);;mp3文件(*.mp3);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)"; //文件过滤器
	QStringList fileList = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);

	if (fileList.count() < 1)
		return;

	for (int i = 0; i < fileList.count(); i++)
	{
		QString aFile = fileList.at(i);
		mediaPlaylist->addMedia(QUrl::fromLocalFile(aFile));//添加文件

		QFileInfo   fileInfo(aFile);
		ui.listMusic->addItem(fileInfo.fileName());//添加到界面文件列表
	}

	if (mediaPlayer->state() != QMediaPlayer::PlayingState)
		mediaPlaylist->setCurrentIndex(0);
	//mediaPlayer->play();
}

void OnePlayer::on_btnPlay_clicked()
{//播放
	if (mediaPlayer->state() == QMediaPlayer::PlayingState)
		mediaPlayer->pause();
	else {
		if (mediaPlaylist->currentIndex() < 0)
			mediaPlaylist->setCurrentIndex(0);
		mediaPlayer->play();
	}
}


void OnePlayer::on_btnStop_clicked()
{//停止播放
	mediaPlayer->stop();
}

void OnePlayer::on_listMusic_doubleClicked(const QModelIndex& index)
{//双击时切换播放文件
	int rowNo = index.row();
	mediaPlaylist->setCurrentIndex(rowNo);
	mediaPlayer->play();
}

void OnePlayer::on_btnClear_clicked()
{//清空列表
	mediaPlaylist->clear();
	ui.listMusic->clear();
	mediaPlayer->stop();
}

void OnePlayer::on_sliderVolume_valueChanged(int value)
{//调整音量
	mediaPlayer->setVolume(value);
}


void OnePlayer::on_sliderProgress_valueChanged(int value)
{//文件进度调控
	mediaPlayer->setPosition(value);
}

void OnePlayer::on_btnRemove_clicked()
{//移除一个文件
	int pos = ui.listMusic->currentRow();
	QListWidgetItem* item = ui.listMusic->takeItem(pos);
	delete item;//从listMusic里删除

	if (mediaPlaylist->currentIndex() == pos) //是当前播放的曲目
	{
		int nextPos = 0;
		if (pos >= 1)
			nextPos = pos - 1;

		mediaPlaylist->removeMedia(pos);//从播放列表里移除
		if (ui.listMusic->count() > 0)
		{
			mediaPlaylist->setCurrentIndex(nextPos);
			onPlaylistChanged(nextPos);
		}
		else
		{
			mediaPlayer->stop();
			//ui.LabCurMedia->setText("无曲目");
		}
	}
	else
		mediaPlaylist->removeMedia(pos);
}

void OnePlayer::on_btnPrev_clicked()
{//前一文件
	mediaPlaylist->previous();
}

void OnePlayer::on_btnNext_clicked()
{//下一文件
	mediaPlaylist->next();
}






void OnePlayer::on_btnList_clicked() { ui.tabWidget->setCurrentIndex(0); }
void OnePlayer::on_btnPlayer_clicked() { ui.tabWidget->setCurrentIndex(1); }
void OnePlayer::on_btnLyric_clicked() { ui.tabWidget->setCurrentIndex(2); }
