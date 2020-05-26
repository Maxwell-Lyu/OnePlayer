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
	void startRotateAnimation(qreal speedRotate, qreal deltaAngle);
    void loadImage(QImage image);
    void setState(bool state) { state ? timer->start() : timer->stop(); }
	void resetAngle() { rotateAngle = 0; }

protected:
	virtual void paintEvent(QPaintEvent *event) override;

private:
	qreal rotateAngle;
	QPixmap backgroundImage;
    QTimer *timer = nullptr;
};

#endif // CoverWidget_H
