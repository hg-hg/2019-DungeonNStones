#pragma once

#include <QWidget>
#include "StoneManager.h"
#include "ExchangeAnimation.h"
#include "CrushAnimation.h"
#include "GravityAnimation.h"

struct MoveData
{
	int firstX, firstY, secondX, secondY;
	MoveData() = default;
	MoveData(int fx, int fy, int sx, int sy) {
		firstY = fy;
		firstX = fx;
		secondX = sx;
		secondY = sy;
	}
};

class GameLogic : public QWidget
{
	Q_OBJECT

/*fuctions*/
public:
	GameLogic(QWidget *parent = Q_NULLPTR);
	
	void setMoveData(int fx, int fy, int sx, int sy);
private:
	bool isTwoStonesConnected();
	bool evaluate(EvaluateState state = Normal, QVector<QVector<bool>>& visited = QVector<QVector<bool>>(0));
	void initializeVisitedVector(QVector<QVector<bool>>& visited);
	bool isPositionValid(int position) const;
	bool isPositionValid(int col, int row) const;
	bool isMoveValid() const;
	void DFS(int x, int y, QVector<QVector<bool>>& visited, QVector<QPair<int, int>>& path);
	void evaluatePath(QVector<QPair<int, int>>& stones);
	void evaluateStonesToCrush(QVector<QPair<int, int>>& path);
	void animateCrushingStones();
	void waitForStopAnimation();
	void enableAllStones();
signals:
	void stonesCrushing(int hp, int damage, int mp, QString account);

public slots:
	void useSkill(QString skill, QString account);
	void fillBoard();
	void clickedStone(Stone* stone);//invoke by Stone::clicked()
	void deleteStone();
	void deleteStone(int col, int row);
	void changeStone(int row, int col, int type);
	void deleteRect();
	void deleteRect(int col, int row, int width, int height);
	void forceExchange();
	void forceExchange(int x1, int y1, int x2, int y2);
	void damage(QString account);
	void heal(QString account);
protected slots:
	void endMove();
	void gravity();
	void gravityFinished();
/*members*/
public:
	const int boardSize = 8;
	QVector<QVector<Stone*>> board;
	QString account;
private:
	bool isAnimating = false;
	Stone* first;
	Stone* second;
	QPoint firstPos;
	QPoint secondPos;
	MoveData md;
	EvaluateState es;
	QVector<QPair<int, int>> pathOne, pathTwo;
	QVector<QPair<int, int>> stoneToCrush;
	ExchangeAnimation* exchangeAnimaion;
	CrushAnimation* crushAnimation;
	GravityAnimation* gravityAnimation;
	StoneManager stoneManager;
	
};
