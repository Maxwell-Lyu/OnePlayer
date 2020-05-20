#pragma once

#include <QtWidgets/QMainWindow>
#include <QTabBar>
#include <QFile>
#include "ui_OnePlayer.h"

class OnePlayer : public QMainWindow
{
    Q_OBJECT

public:
    OnePlayer(QWidget *parent = Q_NULLPTR);

private:
    Ui::OnePlayerClass ui;
};
