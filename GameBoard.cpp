#include "stdafx.h"
#include "GameBoard.h"

GameBoard::GameBoard(QWidget *parent)
	: QWidget(parent)
{
	first = second = nullptr;
	exchangeAnimaion = new ExchangeAnimation(this);
	crushAnimation = new CrushAnimation(this);
	gravityAnimation = new GravityAnimation(this);
	fillBoard();
	connect(exchangeAnimaion, SIGNAL(finished()), this, SLOT(endMove()));
	connect(gravityAnimation, SIGNAL(finished()), this, SLOT(gravityFinished()));
	connect(crushAnimation, SIGNAL(finished()), this, SLOT(gravity()));
}

void GameBoard::clickedStone(Stone* stone) {
	if (first == nullptr) first = stone;
	else if (stone != first) second = stone;
	if (second != nullptr) {
		if (isTwoStonesConnected()) {
			QVector<QVector<bool>> visited(boardSize, QVector<bool>(boardSize, false));
			//TODO: Evaluate the board, using dfs;
			evaluate(Click, visited);
		}
		first = second = nullptr;
	}
}

void GameBoard::deleteStone()
{
	int row = qrand() % boardSize;
	int col = qrand() % boardSize;
	deleteStone(row, col);
}

void GameBoard::deleteStone(int col, int row)
{
	waitForStopAnimation();
	//if (isAnimating) return;
	if (!positionExist(col) || !positionExist(row)) return;
	if (board[col][row] == nullptr) return;
	stoneToCrush.append(qMakePair(col, row));
	gravity();
}

void GameBoard::endMove() {
	isAnimating = false;
	for (auto& col : board) for (auto& row : col) row->isAnimating = false;
	if (stOne.size() >= 3) evaluateStonesToCrush(stOne);
	if (stTwo.size() >= 3) evaluateStonesToCrush(stTwo);
	if (es == Click || es == Force) animateCrushingStones();
}

void GameBoard::fillBoard()
{
	/*this check if the board is alreay filled.
		If filled, delete this.*/
	if (!board.isEmpty()) 
		for (auto& col : board) for (auto& row : col) delete row;
	else board.resize(boardSize);
	
	int stoneSize = Stone::size;
	/*remember: board[col][row]
		because first x then y*/
	for (int col = 0; col < boardSize; col++) {
		/*MUST USE & reference, or nothing changed at all!!!*/
		auto& r = board[col];
 		r.resize(boardSize);
		for (int row = 0; row < boardSize; row++) {
			r[row] = stoneManager.getStone(this);
			r[row]->show();
			r[row]->move(col * stoneSize, row * stoneSize);
		}
	}

	/*prevent 3 or more linked stones before the game start*/
	for (int col = 0; col < boardSize; col++) {
		for (int row = 0; row < boardSize; row++) {
			setMoveData(col, row, col, row);
			for (int type = NORMAL_STONE; type <= DM_STONE && evaluate(); type++) {
				stoneManager.changeStone(board[col][row], type, this);
			}
		}
	}

	first = second = nullptr;
}

void GameBoard::setMoveData(int fx, int fy, int sx, int sy)
{
	md = MoveData(fx, fy, sx, sy);
	first = board[fx][fy];
	second = board[sx][sy];
}

bool GameBoard::isTwoStonesConnected()
{
	for (int col = 0; col < boardSize; col++) {
		auto r = board[col];
		for (int row = 0; row < boardSize; row++) {
			if (r[row] == first) firstPos = QPoint(col, row);
			if (r[row] == second) secondPos = QPoint(col, row);
		}
	}
	md = MoveData(firstPos.x(), firstPos.y(), secondPos.x(), secondPos.y());
	if (abs(md.firstX - md.secondX) == 1 && md.firstY == md.secondY) return true;	//Horizental
	if (abs(md.firstY - md.secondY) == 1 && md.firstX == md.secondX) return true;	//Vertical
	return false;
}

bool GameBoard::evaluate(EvaluateState state, QVector<QVector<bool>>& visited)
{
	es = state;
	bool sameLocation = false;
	if (md.firstX == md.secondX && md.firstY == md.secondY) sameLocation = true;
	initializeVisitedVector(visited);

	//if move stones position is illegal
	if (!positionExist(md)) return false;
	//if move length is more than one stone
	if ((abs(md.firstX - md.secondX) > 1)
		|| (abs(md.firstY - md.secondY) > 1)) return false;
	//if stone doesn't exist
	if (!board[md.firstX][md.firstY]->isValid() || !board[md.secondX][md.secondY]->isValid()) return false;
	//if two stones are the same
	if (first != second && first->match(second)) return false;
	//in Gravity mode, there may be several times of crushing, so DO NOT CLEAR THIS
	if (state != Gravity) stoneToCrush.resize(0);

	//try to exchange two stone and evaluate the result
	Stone* st1 = first;
	Stone* st2 = second;
	board[md.firstX][md.firstY] = st2;
	board[md.secondX][md.secondY] = st1;
	stOne.resize(0);
	stTwo.resize(0);

	stOne.append(qMakePair(md.secondX, md.secondY));
	DFS(md.secondX, md.secondY, visited, stOne);
	evaluatePath(stOne);
	if (!sameLocation) {
		stTwo.append(qMakePair(md.firstX, md.firstY));
		DFS(md.firstX, md.firstY, visited, stTwo);
		evaluatePath(stTwo);
	}
	if (stOne.size() >= 3 || stTwo.size() >= 3) {
		if (!sameLocation && (state == Click || state == Force)) {
			isAnimating = true;
			exchangeAnimaion->legalExchange(st1, st2);
		}
		else if (state == Gravity) {
			endMove();
		}
		else if (!sameLocation && state == Normal) {
			endMove();
			board[md.firstX][md.firstY] = st1;
			board[md.secondX][md.secondY] = st2;
		}
		return true;
	}
	else if (state == Force) {
		isAnimating = true;
		exchangeAnimaion->legalExchange(st1, st2);
	}
	else {
		/*move is illegal, so we move two stones back*/
		if (!sameLocation && state == Click)
			exchangeAnimaion->illegalExchange(st1, st2);
		board[md.firstX][md.firstY] = st1;
		board[md.secondX][md.secondY] = st2;
		return false;
	}
	return true;
}

void GameBoard::initializeVisitedVector(QVector<QVector<bool>>& visited)
{
	if (!visited.isEmpty()) return;
	visited = QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false));
}

bool GameBoard::positionExist(const int pos) const
{
	return pos >= 0 && pos < boardSize;
}

bool GameBoard::positionExist(const MoveData mv) const
{
	if (!positionExist(mv.firstX) || !positionExist(mv.firstY)
		|| !positionExist(mv.secondX) || !positionExist(mv.secondY)) return false;
	return true;
}

void GameBoard::DFS(int x, int y, QVector<QVector<bool>>& visited, QVector<QPair<int, int>>& stones)
{
	Stone* stone = board[x][y];
	visited[x][y] = true;
	//North
	if (positionExist(y - 1) && !visited[x][y - 1] && stone->match(board[x][y - 1])) {
		stones.append(qMakePair(x, y - 1));
		DFS(x, y - 1, visited, stones);
	}
	//South
	if (positionExist(y + 1) && !visited[x][y + 1] && stone->match(board[x][y + 1])) {
		stones.append(qMakePair(x, y + 1));
		DFS(x, y + 1, visited, stones);
	}
	//East
	if (positionExist(x + 1) && !visited[x + 1][y] && stone->match(board[x + 1][y])) {
		stones.append(qMakePair(x + 1, y));
		DFS(x + 1, y, visited, stones);
	}
	//West
	if (positionExist(x - 1) && !visited[x - 1][y] && stone->match(board[x - 1][y])) {
		stones.append(qMakePair(x - 1, y));
		DFS(x - 1, y, visited, stones);
	}
}

void GameBoard::evaluatePath(QVector<QPair<int, int>>& stones)
{
	/*after dfs, we may get a path containning more than 2 stones;
		however, it may be zig-zag style, 
		so we move stones without two friends both in horizen and vertical.*/
	for (auto it = stones.begin(); it != stones.end(); ) {
		int x = 0, y = 0;
		for (const auto p : stones) {
			if (p.first == it->first) x++;
			if (p.second == it->second) y++;
		}
		/*My(yuri's) preffered way to remove element while iterating ;D*/
		if (x < 3 && y < 3) it = stones.erase(it);
		else it++;
	}
}

void GameBoard::evaluateStonesToCrush(QVector<QPair<int, int>>& stones)
{
	int hp = 0, damage = 0, mp = 0;
	for (auto stone : stones) {
		stoneToCrush.append(stone);
		auto st = board[stone.first][stone.second];
		hp += st->HP;
		damage += st->DAMAGE;
		mp += st->MP;
	}
	int bouns = stones.size();
	hp *= bouns;
	damage *= bouns;
	mp *= bouns;
	emit stonesCrushing(hp, damage, mp);
}

void GameBoard::animateCrushingStones()
{
	for (auto pos : stoneToCrush) {
		auto st = board[pos.first][pos.second];
		crushAnimation->add(st);
	}

	/*15 is just a magic number, change it if you want.
		But DO NOT EDIT THIS COMMENT 
		in case I want to change it back but forget the default value*/
	isAnimating = true;
	crushAnimation->animate(15);
}

void GameBoard::waitForStopAnimation()
{
	while (isAnimating) {
		QEventLoop loop;
		QTimer::singleShot(50, &loop, SLOT(quit()));
		loop.exec();
	}
}

void GameBoard::changeStone(int row, int col, int type)
{
	waitForStopAnimation();
	auto stone = board[col][row];
	stoneManager.changeStone(stone, type, this);
}

void GameBoard::deleteRect()
{
	int row = qrand() % boardSize;
	int col = qrand() % boardSize;
	int width = qMin(qrand() % boardSize, boardSize - col - 1);
	int height = qMin(qrand() % boardSize, boardSize - row - 1);
	deleteRect(col, row, width, height);
}

void GameBoard::deleteRect(int col, int row, int width, int height)
{
	waitForStopAnimation();
	if (!positionExist(col) || !positionExist(row)) return;
	int destX = col + width;
	int destY = row + height;
	if (!positionExist(destX) || !positionExist(destY)) return;
	for (int c = col; c <= destX; c++) for (int r = row; r <= destY; r++)
		stoneToCrush.append(qMakePair(c, r));
	gravity();
}

void GameBoard::forceExchange()
{
	int row = qrand() % boardSize;
	int col = qrand() % boardSize;
	if (col < row) {
		if (positionExist(col + 1)) forceExchange(col, row, col + 1, row);
		else forceExchange(col, row, col - 1, row);
	}
	else {
		if (positionExist(row + 1)) forceExchange(col, row, col, row + 1);
		else forceExchange(col, row, col, row - 1);
	}
	
}

void GameBoard::forceExchange(int x1, int y1, int x2, int y2)
{
	waitForStopAnimation();
	setMoveData(x1, y1, x2, y2);
	evaluate(Force);
}

void GameBoard::gravity()
{
	for (auto pos : stoneToCrush) {
		auto st = board[pos.first][pos.second];
		if (st->isValid()) {
			delete st;
			board[pos.first][pos.second] = nullptr;
			//only delete is useless, you must reset it to nullptr explicitly
		}
	}
	stoneToCrush.resize(0);
	int maxDy = 0;

	//if you change the gravity derection, please change this nested loop.
	//for example, if you want to make the stone move from button to top, change the second loop from 0 to max.
	//if you want to change the move from left to right, change the loop order, serach row first.
	//dy indicates the length it moves.
	for (auto& col : board) {
		int dy = 0;
		for (int row = boardSize - 1; row >= 0; row--) {
			auto& stone = col[row];
			if (stone == nullptr) dy++;
			else {
				auto p = stone->pos();
				p.setY(p.y() + dy * stone->size);
				if (dy == 0) continue;
				col[row + dy] = stone;
				col[row] = nullptr;
				gravityAnimation->add(col[row + dy], p);
			}
		}
		if (dy > maxDy) maxDy = dy;
	}

	/*drop from maxDy above*/
	for (int col = 0; col < boardSize; col++) {
		auto& column = board[col];
		int top = 0;
		while (top < boardSize && !column[top]->isValid()) top++;
		int size = Stone::size;
		for (int row = 0; row < top; row++) {
			auto stone = stoneManager.getStone(this);
			stone->show();
			column[row] = stone;
			stone->move(col * size, (row - maxDy) * size);
			QPoint p(col * size, row * size);
			gravityAnimation->add(column[row], p);
		}
	}
	isAnimating = true;
	gravityAnimation->animate();
	
}

void GameBoard::gravityFinished()
{
	isAnimating = false;
	bool flag = false;
	for (int col = 0; col < boardSize; col++) {
		for (int row = 0; row < boardSize; row++) {
			setMoveData(col, row, col, row);
			if (evaluate(Gravity)) flag = true;
		}
	}
	first = second = nullptr;
	
	if (flag) animateCrushingStones();
}
