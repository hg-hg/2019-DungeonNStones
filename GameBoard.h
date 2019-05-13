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

class GameBoard : public QWidget
{
	Q_OBJECT

/*fuctions*/
public:
	GameBoard(QWidget *parent = Q_NULLPTR);
	
	void setMoveData(int fx, int fy, int sx, int sy);
private:
	bool isTwoStonesConnected();
	bool evaluate(EvaluateState state = Normal, QVector<QVector<bool>>& visited = QVector<QVector<bool>>(0));
	void initializeVisitedVector(QVector<QVector<bool>>& visited);
	bool positionExist(const int pos) const;
	bool positionExist(const MoveData mv) const;
	void DFS(int x, int y, QVector<QVector<bool>>& visited, QVector<QPair<int, int>>& stones);
	void evaluatePath(QVector<QPair<int, int>>& stones);
	void evaluateStonesToCrush(QVector<QPair<int, int>>& stones);
	void animateCrushingStones();
	void waitForStopAnimation();
signals:
	void stonesCrushing(int hp, int damage, int mp);

public slots:
	void fillBoard();
	void clickedStone(Stone* stone);//invoke by Stone::clicked()
	void deleteStone();
	void deleteStone(int col, int row);
	void changeStone(int row, int col, int type);
	void deleteRect();
	void deleteRect(int col, int row, int width, int height);
	void forceExchange();
	void forceExchange(int x1, int y1, int x2, int y2);
protected slots:
	void endMove();
	void gravity();
	void gravityFinished();
/*members*/
public:
	const int boardSize = 8;
	QVector<QVector<Stone*>> board;
private:
	bool isAnimating = false;
	Stone* first;
	Stone* second;
	QPoint firstPos;
	QPoint secondPos;
	MoveData md;
	EvaluateState es;
	QVector<QPair<int, int>> stOne, stTwo;
	QVector<QPair<int, int>> stoneToCrush;
	ExchangeAnimation* exchangeAnimaion;
	CrushAnimation* crushAnimation;
	GravityAnimation* gravityAnimation;
	StoneManager stoneManager;
};
