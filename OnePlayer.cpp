#include "OnePlayer.h"

OnePlayer::OnePlayer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tabWidget->tabBar()->hide();
    connect(ui.pushButtonList, &QPushButton::clicked, this, [=] {onSwitchTab(0);});
    connect(ui.pushButtonPlayer, &QPushButton::clicked, this, [=]{onSwitchTab(1);});
    connect(ui.pushButtonLyric, &QPushButton::clicked, this, [=]{onSwitchTab(2);});
}

void OnePlayer::onSwitchTab(int index) {
    ui.tabWidget->setCurrentIndex(index);
}
