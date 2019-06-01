#include <QWidget>
#include <QPushButton>
class MainSceneButton : public QPushButton
{
	Q_OBJECT

public:
	MainSceneButton(QWidget* parent = Q_NULLPTR);
	void ZoomPush();
	void ZoomPop();
	void setPicture(QString normalImg);
	~MainSceneButton();

public:
	QString normalImg;
	QString pressImg;
	int pressTimes;
};
