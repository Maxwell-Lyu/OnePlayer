#ifndef CoverWidget_H
#define CoverWidget_H

#include <QWidget>

class QTimer;

class CoverWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CoverWidget(QWidget* parent = nullptr);
	void startRotateAnimation(int speedRotate, int deltaAngle);
	void loadImage(QImage image);

protected:
	virtual void paintEvent(QPaintEvent* event) override;

private:
	int rotateAngle;
	QPixmap backgroundImage;
	QTimer* timer = nullptr;
};

#endif // CoverWidget_H
