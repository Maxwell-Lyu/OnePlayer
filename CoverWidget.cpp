#include "CoverWidget.h"

#include <QTimer>
#include <QPainter>
#include <QDebug>

CoverWidget::CoverWidget(QWidget* parent) : QWidget(parent), rotateAngle(0) {
}

void CoverWidget::startRotateAnimation(int speedRotate, int deltaAngle) {
	if (nullptr == timer) {
		// 通过定时器去旋转图片
		timer = new QTimer(this);
		timer->setInterval(speedRotate);
		connect(timer, &QTimer::timeout, [=]() {
			rotateAngle += deltaAngle;
			if (rotateAngle > 360.0) {
				rotateAngle = deltaAngle;
			}
			repaint();
			});
	}
	timer->start();
}

void CoverWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);

	if (!backgroundImage.isNull()) {
		// 中心点
		int centerPosW = width() >> 1;
		int centerPosH = height() >> 1;

		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		// 把自身截取为圆形
		QPainterPath path;
		int round = qMin(width(), height());
		path.addEllipse(0, 0, round, round);
		painter.setClipPath(path);

		// 设置中心点为起点
		painter.translate(centerPosW, centerPosH);
		// 开始旋转
		painter.rotate(rotateAngle);
		// 恢复起点位置，即左上角(0，0)
		painter.translate(-centerPosW, -centerPosH);

		// 绘制图片
		painter.drawPixmap(-1, -1, width() + 2, height() + 2, backgroundImage);
	}
}


void CoverWidget::loadImage(QImage image) {
	backgroundImage = QPixmap::fromImage(image);
}
