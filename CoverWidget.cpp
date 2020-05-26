#include "CoverWidget.h"

#include <QTimer>
#include <QPainter>
#include <QDebug>

CoverWidget::CoverWidget(QWidget* parent) : QWidget(parent), rotateAngle(0) {
}

void CoverWidget::startRotateAnimation(qreal speedRotate, qreal deltaAngle) {
	if (nullptr == timer) {
		// 通过定时器去旋转图片
		timer = new QTimer(this);
        timer->setInterval(static_cast<int>(round(speedRotate)));
		connect(timer, &QTimer::timeout, [=]() {
            rotateAngle += deltaAngle;
			if (rotateAngle > 360.0) {
				rotateAngle = deltaAngle;
			}
			repaint();
			});
	}
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
        int round = qMin(width(), height()) - 100;
        path.addEllipse(50, 50, round, round);
		painter.setClipPath(path);

		// 设置中心点为起点
		painter.translate(centerPosW, centerPosH);
		// 开始旋转
		painter.rotate(rotateAngle);
		// 恢复起点位置，即左上角(0，0)
		painter.translate(-centerPosW, -centerPosH);

		// 绘制图片
        painter.drawPixmap(49, 49, width() - 98, height() - 98, backgroundImage);
        QPainter painter2(this);
        painter2.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter2.setPen(QPen(QColor(22, 22, 22), 32));
        painter2.drawEllipse(QRectF(40, 40, 320, 320));
        painter2.drawPixmap(0, 0, width(), height(), QPixmap::fromImage(QImage(":img/coverPin")));
	}
}


void CoverWidget::loadImage(QImage image) {
	backgroundImage = QPixmap::fromImage(image);
}
