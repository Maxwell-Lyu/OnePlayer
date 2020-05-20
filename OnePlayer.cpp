#include "OnePlayer.h"

OnePlayer::OnePlayer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tabWidget->tabBar()->hide();
    connect(ui.buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
        [=](int id) { ui.tabWidget->setCurrentIndex(id + 4); });
}
