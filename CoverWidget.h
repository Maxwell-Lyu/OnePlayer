#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include <QWidget>
#include <QtCore>
class QTimer;

class CoverWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CoverWidget(QWidget *parent = nullptr);
    // 启动动画(初始化)
	void startRotateAnimation(qreal speedRotate, qreal deltaAngle);
    // 加载封面
    void loadImage(QImage image);
    // 设定状态
    void setState(bool state) { state ? timer->start() : timer->stop(); }
    // 回到0度角
    void resetAngle() { rotateAngle = 0; }

protected:
	virtual void paintEvent(QPaintEvent *event) override;
private:
    // 当前旋转角度
	qreal rotateAngle;
    // 专辑封面图片
	QPixmap backgroundImage;
    // 计时器
    QTimer *timer = nullptr;
};

#endif // CoverWidget_H
