﻿#ifndef CoverWidget_H
#define CoverWidget_H

#include <QWidget>

class QTimer;

class CoverWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CoverWidget(QWidget *parent = nullptr);
	void startRotateAnimation(qreal speedRotate, qreal deltaAngle);
	void loadImage(QImage image);
	void setState(bool state) { running = state; }
	void resetAngle() { rotateAngle = 0; }

protected:
	virtual void paintEvent(QPaintEvent *event) override;

private:
	qreal rotateAngle;
	QPixmap backgroundImage;
	QTimer *timer = nullptr;
	bool running = false;
};

#endif // CoverWidget_H
