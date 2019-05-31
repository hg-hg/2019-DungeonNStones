#include "stdafx.h"
#include "GameLogic.h"

GameLogic::GameLogic(QWidget *parent)
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

void GameLogic::clickedStone(Stone* stone) {
	if (first == nullptr) first = stone;
	if (first->isAnimating) return;
	else if (stone != first) second = stone;
	if (second != nullptr && !second->isAnimating) {
		if (isTwoStonesConnected()) {
			QVector<QVector<bool>> visited(boardSize, QVector<bool>(boardSize, false));
			//TODO: Evaluate the board, using dfs;
			evaluate(Click, visited);
		}
		first = second = nullptr;
	}
}

void GameLogic::deleteStone()
{
	int row = qrand() % boardSize;
	int col = qrand() % boardSize;
	deleteStone(row, col);
}

void GameLogic::deleteStone(int col, int row)
{
	waitForStopAnimation();
	//if (isAnimating) return;
	if (!isPositionValid(col, row)) return;
	if (board[col][row] == nullptr) return;
	stoneToCrush.append(qMakePair(col, row));
	gravity();
}

void GameLogic::endMove() {
	isAnimating = false;
	enableAllStones();
	if (pathOne.size() >= 3) evaluateStonesToCrush(pathOne);
	if (pathTwo.size() >= 3) evaluateStonesToCrush(pathTwo);
	if (es == Click || es == Force) animateCrushingStones();
}

void GameLogic::useSkill(QString skill, QString account)
{
	if (skill == "changeBoard") fillBoard();
	else if (skill == "exchange") forceExchange();
	else if (skill == "Rect") deleteRect();
	else if (skill == "Stone") deleteStone();
	else if (skill == "damage") damage(account);
	else if (skill == "heal") heal(account);
	else if (skill == "BladeSlash") bladeSlash(account);
}

void GameLogic::fillBoard()
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

void GameLogic::setMoveData(int fx, int fy, int sx, int sy)
{
	md = MoveData(fx, fy, sx, sy);
	first = board[fx][fy];
	second = board[sx][sy];
}

bool GameLogic::isTwoStonesConnected()
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

bool GameLogic::evaluate(EvaluateState state, QVector<QVector<bool>>& visited)
{
	es = state;
	bool sameLocation = false;
	if (md.firstX == md.secondX && md.firstY == md.secondY) sameLocation = true;
	initializeVisitedVector(visited);

	if (!isMoveValid()) return false;
	//in Gravity mode, there may be several times of crushing, so DO NOT CLEAR THIS
	if (state != Gravity) stoneToCrush.resize(0);

	//try to exchange two stone and evaluate the result
	auto st1 = first;
	auto st2 = second;
	board[md.firstX][md.firstY] = st2;
	board[md.secondX][md.secondY] = st1;
	pathOne.resize(0);
	pathTwo.resize(0);

	pathOne.append(qMakePair(md.secondX, md.secondY));
	DFS(md.secondX, md.secondY, visited, pathOne);
	evaluatePath(pathOne);
	if (!sameLocation) {
		pathTwo.append(qMakePair(md.firstX, md.firstY));
		DFS(md.firstX, md.firstY, visited, pathTwo);
		evaluatePath(pathTwo);
	}
	if (pathOne.size() >= 3 || pathTwo.size() >= 3) {
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

void GameLogic::initializeVisitedVector(QVector<QVector<bool>>& visited)
{
	if (!visited.isEmpty()) return;
	visited = QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false));
}

bool GameLogic::isPositionValid(int position) const
{
	return (0 <= position && position < boardSize);
}

bool GameLogic::isPositionValid(int col, int row) const
{
	return isPositionValid(col) && isPositionValid(row);
}

bool GameLogic::isMoveValid() const
{
	int fx = md.firstX;
	int fy = md.firstY;
	int sx = md.secondX;
	int sy = md.secondY;
	//if move stones position is illegal
	if (!isPositionValid(fx, fy) || !isPositionValid(sx, sy)) return false;
	if (abs(fx - sx) > 1 || abs(fy - sy) > 1) return false;
	//if stone is null or animating
	if (!first->isValid() || !second->isValid()) return false;
	if (first->isAnimating || second->isAnimating) return false;
	//if stones are the same
	if (first != second && first->match(second)) return false;
	return true;
}

void GameLogic::DFS(int col, int row, QVector<QVector<bool>>& visited, QVector<QPair<int, int>>& stones)
{
	Stone* stone = board[col][row];
	visited[col][row] = true;
	//North
	if (isPositionValid(row - 1) && !visited[col][row - 1] && stone->match(board[col][row - 1])) {
		if (stone->isAnimating) return;
		stones.append(qMakePair(col, row - 1));
		DFS(col, row - 1, visited, stones);
	}
	//South
	if (isPositionValid(row + 1) && !visited[col][row + 1] && stone->match(board[col][row + 1])) {
		if (stone->isAnimating) return;
		stones.append(qMakePair(col, row + 1));
		DFS(col, row + 1, visited, stones);
	}
	//East
	if (isPositionValid(col + 1) && !visited[col + 1][row] && stone->match(board[col + 1][row])) {
		if (stone->isAnimating) return;
		stones.append(qMakePair(col + 1, row));
		DFS(col + 1, row, visited, stones);
	}
	//West
	if (isPositionValid(col - 1) && !visited[col - 1][row] && stone->match(board[col - 1][row])) {
		if (stone->isAnimating) return;
		stones.append(qMakePair(col - 1, row));
		DFS(col - 1, row, visited, stones);
	}
}

void GameLogic::evaluatePath(QVector<QPair<int, int>>& path)
{
	/*after dfs, we may get a path containning more than 2 stones;
		however, it may be zig-zag style, 
		so we move stones without two friends both in horizen and vertical.*/
	for (auto it = path.begin(); it != path.end(); ) {
		int col = 0, row = 0;
		for (const auto p : path) {
			if (p.first == it->first) col++;
			if (p.second == it->second) row++;
		}
		/*My(yuri's) preffered way to remove element while iterating ;D*/
		if (col < 3 && row < 3) it = path.erase(it);
		else it++;
	}
}

void GameLogic::evaluateStonesToCrush(QVector<QPair<int, int>>& path)
{
	int hp = 0, damage = 0, mp = 0;
	for (auto stone : path) {
		stoneToCrush.append(stone);
		auto st = board[stone.first][stone.second];
		hp += st->HP;
		damage += st->DAMAGE;
		mp += st->MP;
	}
	int bouns = path.size();
	if (bouns <= 3) bouns = 1;
	else bouns -= 1;
	hp *= bouns;
	damage *= bouns;
	mp *= bouns;
	emit stonesCrushing(hp, damage, mp, account);
}

void GameLogic::animateCrushingStones()
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

void GameLogic::waitForStopAnimation()
{
	while (isAnimating) {
		QEventLoop loop;
		QTimer::singleShot(50, &loop, SLOT(quit()));
		loop.exec();
	}
}

void GameLogic::enableAllStones()
{
	for (auto& col : board) for (auto& row : col) row->isAnimating = false;
}

void GameLogic::changeStone(int row, int col, int type)
{
	waitForStopAnimation();
	auto stone = board[col][row];
	if (stone->TYPE == type) return;
	stoneManager.changeStone(stone, type, this);
}

void GameLogic::deleteRect()
{
	int row = qrand() % boardSize;
	int col = qrand() % boardSize;
	int width = qMin(qrand() % boardSize, boardSize - col - 1);
	int height = qMin(qrand() % boardSize, boardSize - row - 1);
	deleteRect(col, row, width, height);
}

void GameLogic::deleteRect(int col, int row, int width, int height)
{
	waitForStopAnimation();
	if (!isPositionValid(col, row)) return;
	int destX = col + width;
	int destY = row + height;
	if (!isPositionValid(destX, destY)) return;
	for (int c = col; c <= destX; c++) for (int r = row; r <= destY; r++)
		stoneToCrush.append(qMakePair(c, r));
	gravity();
}

void GameLogic::forceExchange()
{
	int row = qrand() % boardSize;
	int col = qrand() % boardSize;
	if (col < row) {
		if (isPositionValid(col + 1)) forceExchange(col, row, col + 1, row);
		else forceExchange(col, row, col - 1, row);
	}
	else {
		if (isPositionValid(row + 1)) forceExchange(col, row, col, row + 1);
		else forceExchange(col, row, col, row - 1);
	}
	
}

void GameLogic::forceExchange(int x1, int y1, int x2, int y2)
{
	waitForStopAnimation();
	setMoveData(x1, y1, x2, y2);
	evaluate(Force);
}

void GameLogic::damage(QString account)
{
	emit stonesCrushing(0, 50, 0, account);
}

void GameLogic::damage(QString account, int dam)
{
	emit stonesCrushing(0, dam, 0, account);
}

void GameLogic::heal(QString account)
{
	emit(stonesCrushing(50, 0, 0, account));
}

void GameLogic::bladeSlash(QString account)
{
	int col = qMin(qrand() % boardSize, boardSize - 2);
	int dam = 0;
	for (int i = col; i <= col + 1; i++) {
		for (auto row : board[col]) {
			dam += row->DAMAGE;
		}
	}
	dam /= 2;
	damage(account, dam);
	deleteRect(col, 0, 1, boardSize - 1);
}

void GameLogic::gravity()
{
	enableAllStones();
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

void GameLogic::gravityFinished()
{
	enableAllStones();
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
