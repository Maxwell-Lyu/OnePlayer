#include "OnePlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
    QFile qss(":/style/theme");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
	OnePlayer w;
	w.show();
	return a.exec();
}
