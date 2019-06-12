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

	MoveData(const int fx, const int fy, const int sx, const int sy)
	{
		firstY = fy;
		firstX = fx;
		secondX = sx;
		secondY = sy;
	}
};

class GameLogic : public QWidget
{
Q_OBJECT

	/*functions*/
public:
	GameLogic(QWidget* parent = Q_NULLPTR);
	~GameLogic();
	void waitForStopAnimation() const;
	void setMoveData(int fx, int fy, int sx, int sy);
	void fillBoard();
	void makeBoardFilledAgain();
private:
	QPoint getPosition(const Stone* stone) const;
	bool willDrop(QPoint location) const;
	bool isTwoStonesConnected();
	bool evaluate(EvaluateState state = Normal, QVector<QVector<bool>>& visited = QVector<QVector<bool>>(0));
	void initializeVisitedVector(QVector<QVector<bool>>& visited) const;
	bool isPositionValid(int position) const;
	bool isPositionValid(int col, int row) const;
	bool isMoveValid() const;
	void dfs(int col, int row, QVector<QVector<bool>>& visited, QVector<QPair<int, int>>& path);
	void evaluatePath(QVector<QPair<int, int>>& path) const;
	void animateCrushingStones();
	void enableAllStones();

	/**skills**/
	void deleteStone();
	void deleteStone(int col, int row);
	void changeStone(int col, int row, int type);
	void deleteRect();
	void deleteRect(int col, int row, int width, int height);
	void forceExchange();
	void forceExchange(int x1, int y1, int x2, int y2);
	void damage(const QString& account, int dam = 20 + qrand() % 100);
	void heal(const QString& account, int hp = 50);
	void recover(const QString& account, int mp = 50);
	void bladeSlash(const QString& account);
	void lightning(const QString& account);
	void meteor(const QString& account);
	void greedy(const QString& account);
	void sinisterStrike(const QString& account);
	void forceOfNature(const QString& account);
signals:
	void stonesCrushing(int hp, int damage, int mp, QString account);

public slots:
	void useSkill(const QString& skill, const QString& account);

private slots:
	void endMove();
	void gravity();
	void gravityFinished();
	
	void clickedStone(Stone* stone); //invoke by Stone::clicked()
	/*members*/
public:
	const int boardSize = 8;
	QVector<QVector<Stone*>> board;
	QString account;
private:
	bool isAnimating = false;
	bool countEffect = true;
	int extraBonus = 0;
	Stone* first;
	Stone* second;
	QPoint firstPos;
	QPoint secondPos;
	MoveData md = {0, 0, 0, 0};
	EvaluateState es;
	QVector<QPair<int, int>> pathOne, pathTwo;
	QVector<QPair<int, int>> stoneToCrush;
	ExchangeAnimation* exchangeAnimation;
	CrushAnimation* crushAnimation;
	GravityAnimation* gravityAnimation;
	StoneManager stoneManager;
};
