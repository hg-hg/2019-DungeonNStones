#include "stdafx.h"
#include "GameLogic.h"
#include "Sound.h"

GameLogic::GameLogic(QWidget* parent)
	: QWidget(parent)
{
	es = Normal;
	first = second = nullptr;
	exchangeAnimation = new ExchangeAnimation(this);
	crushAnimation = new CrushAnimation(this);
	gravityAnimation = new GravityAnimation(this);
	fillBoard();
	connect(exchangeAnimation, SIGNAL(finished()), this, SLOT(endMove()));
	connect(gravityAnimation, SIGNAL(finished()), this, SLOT(gravityFinished()));
	connect(crushAnimation, SIGNAL(finished()), this, SLOT(gravity()));
}

GameLogic::~GameLogic()
{
}

void GameLogic::clickedStone(Stone* stone)
{
	//if (isAnimating) return;
	Sound::SEPlayer->setMedia(QUrl("qrc:/sound/Resources/Sound/ClickStone.wav"));
	Sound::SEPlayer->play();
	if (stone->isAnimating) return;
	const auto location = getPosition(stone);
	if (willDrop(location)) return;
	if (first == nullptr)
	{
		first = stone;
		firstPos = location;
	}
	else if (stone != first)
	{
		second = stone;
		secondPos = location;
	}
	if (second != nullptr)
	{
		if (isTwoStonesConnected() && evaluate(Click))
		{
			first = second = nullptr;
		} else
		{
			first = second;
			firstPos = secondPos;
			second = nullptr;
		}
	}
}

void GameLogic::deleteStone()
{
	const auto row = qrand() % boardSize;
	const auto col = qrand() % boardSize;
	deleteStone(row, col);
}

void GameLogic::deleteStone(const int col, const int row)
{
	if (!isPositionValid(col, row)) return;
	if (board[col][row] == nullptr) return;
	if (board[col][row]->isAnimating) return;
	stoneToCrush.append(qMakePair(col, row));
	gravity();
}

void GameLogic::endMove()
{
	isAnimating = false;
	enableAllStones();
	if (pathOne.size() >= 3)
	{
		Sound::SEPlayer->setMedia(QUrl("qrc:/sound/Resources/Sound/Crush.wav"));
		Sound::SEPlayer->play();
		evaluateStonesToCrush(pathOne);
	}
	if (pathTwo.size() >= 3)
	{
		Sound::SEPlayer->setMedia(QUrl("qrc:/sound/Resources/Sound/Crush.wav"));
		Sound::SEPlayer->play();
		evaluateStonesToCrush(pathTwo);
	}
	if (es == Click || es == Force) animateCrushingStones();
}

void GameLogic::useSkill(const QString& skill, const QString& account)
{
	waitForStopAnimation();
	if (skill == "changeBoard") fillBoard();
	else if (skill == "exchange") forceExchange();
	else if (skill == "Rect") deleteRect();
	else if (skill == "Stone") deleteStone();
	else if (skill == "damage") damage(account);
	else if (skill == "heal") heal(account);
	else if (skill == "BladeSlash") bladeSlash(account);
	else if (skill == "lightning") lightning(account);
	else if (skill == "meteor") meteor(account);
	else if (skill == "greedy") greedy(account);
	else if (skill == "SinisterStrike") sinisterStrike(account);
	else if (skill == "ForceOfNature") forceOfNature(account);
}

void GameLogic::fillBoard()
{
	/*this check if the board is already filled.
		If filled, delete this.*/
	if (!board.isEmpty())
		for (auto& col : board) for (auto& row : col) delete row;
	else board.resize(boardSize);

	const auto stoneSize = Stone::size;
	/*remember: board[col][row]
		because first x then y*/
	for (auto col = 0; col < boardSize; col++)
	{
		/*MUST USE & reference, or nothing changed at all!!!*/
		auto& r = board[col];
		r.resize(boardSize);
		for (auto row = 0; row < boardSize; row++)
		{
			r[row] = stoneManager.getStone(this);
			r[row]->show();
			r[row]->move(col * stoneSize, row * stoneSize);
		}
	}

	/*prevent 3 or more linked stones before the game start*/
	for (auto col = 0; col < boardSize; col++)
	{
		for (auto row = 0; row < boardSize; row++)
		{
			setMoveData(col, row, col, row);
			for (int type = NORMAL_STONE; type <= DM_STONE && evaluate(); type++)
			{
				stoneManager.changeStone(board[col][row], type, this);
			}
		}
	}

	first = second = nullptr;
}

void GameLogic::setMoveData(const int fx, const int fy, const int sx, const int sy)
{
	md = MoveData(fx, fy, sx, sy);
	first = board[fx][fy];
	second = board[sx][sy];
}

QPoint GameLogic::getPosition(const Stone* stone) const
{
	for (auto col = 0; col < boardSize; col++)
	{
		auto r = board[col];
		for (auto row = 0; row < boardSize; row++)
		{
			if (r[row] == stone) return {col, row};
		}
	}
	return {0, 0};
}

bool GameLogic::willDrop(const QPoint location) const
{
	auto col = board[location.x()];
	for (auto i = location.y(); i < boardSize; i++)
	{
		if (col[i]->isAnimating) 
		return true;
	}
	return false;
}

bool GameLogic::isTwoStonesConnected()
{
	md = MoveData(firstPos.x(), firstPos.y(), secondPos.x(), secondPos.y());
	if (abs(md.firstX - md.secondX) == 1 && md.firstY == md.secondY) return true; //Horizental
	if (abs(md.firstY - md.secondY) == 1 && md.firstX == md.secondX) return true; //Vertical
	return false;
}

bool GameLogic::evaluate(const EvaluateState state, QVector<QVector<bool>>& visited)
{
	es = state;
	auto sameLocation = false;
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
	dfs(md.secondX, md.secondY, visited, pathOne);
	evaluatePath(pathOne);
	if (!sameLocation)
	{
		pathTwo.append(qMakePair(md.firstX, md.firstY));
		dfs(md.firstX, md.firstY, visited, pathTwo);
		evaluatePath(pathTwo);
	}
	if (pathOne.size() >= 3 || pathTwo.size() >= 3)
	{
		if (!sameLocation && (state == Click || state == Force))
		{
			isAnimating = true;
			exchangeAnimation->legalExchange(st1, st2);
		}
		else if (state == Gravity)
		{
			endMove();
		}
		else if (!sameLocation && state == Normal)
		{
			endMove();
			board[md.firstX][md.firstY] = st1;
			board[md.secondX][md.secondY] = st2;
		}
		return true;
	}
	if (state == Force)
	{
		isAnimating = true;
		exchangeAnimation->legalExchange(st1, st2);
	}
	else
	{
		/*move is illegal, so we move two stones back*/
		if (!sameLocation && state == Click)
			exchangeAnimation->illegalExchange(st1, st2);
		board[md.firstX][md.firstY] = st1;
		board[md.secondX][md.secondY] = st2;
		return false;
	}
	return true;
}

void GameLogic::initializeVisitedVector(QVector<QVector<bool>>& visited) const
{
	if (!visited.isEmpty()) return;
	visited = QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false));
}

bool GameLogic::isPositionValid(const int position) const
{
	return (0 <= position && position < boardSize);
}

auto GameLogic::isPositionValid(const int col, const int row) const -> bool
{
	return isPositionValid(col) && isPositionValid(row);
}

bool GameLogic::isMoveValid() const
{
	const auto fx = md.firstX;
	const auto fy = md.firstY;
	const auto sx = md.secondX;
	const auto sy = md.secondY;
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

void GameLogic::dfs(const int col, const int row, QVector<QVector<bool>>& visited, QVector<QPair<int, int>>& path)
{
	Stone* stone = board[col][row];
	visited[col][row] = true;
	//North
	if (isPositionValid(row - 1) && !visited[col][row - 1] && stone->match(board[col][row - 1]))
	{
		if (stone->isAnimating) return;
		path.append(qMakePair(col, row - 1));
		dfs(col, row - 1, visited, path);
	}
	//South
	if (isPositionValid(row + 1) && !visited[col][row + 1] && stone->match(board[col][row + 1]))
	{
		if (stone->isAnimating) return;
		path.append(qMakePair(col, row + 1));
		dfs(col, row + 1, visited, path);
	}
	//East
	if (isPositionValid(col + 1) && !visited[col + 1][row] && stone->match(board[col + 1][row]))
	{
		if (stone->isAnimating) return;
		path.append(qMakePair(col + 1, row));
		dfs(col + 1, row, visited, path);
	}
	//West
	if (isPositionValid(col - 1) && !visited[col - 1][row] && stone->match(board[col - 1][row]))
	{
		if (stone->isAnimating) return;
		path.append(qMakePair(col - 1, row));
		dfs(col - 1, row, visited, path);
	}
}

void GameLogic::evaluatePath(QVector<QPair<int, int>>& path) const
{
	/*after dfs, we may get a path containing more than 2 stones;
		however, it may be zig-zag style,
		so we move stones without two friends both in horizon and vertical.*/
	for (auto it = path.begin(); it != path.end();)
	{
		auto col = 0, row = 0;
		if (willDrop(QPoint(col, row)))
		{
			it = path.erase(it);
			continue;
		}
		for (const auto p : path)
		{
			if (p.first == it->first) col++;
			if (p.second == it->second) row++;
		}
		/*My(yuri's) preferred way to remove element while iterating ;D*/
		if (col < 3 && row < 3) it = path.erase(it);
		else it++;
	}
}

void GameLogic::evaluateStonesToCrush(QVector<QPair<int, int>>& path)
{
	stoneToCrush.append(path);
	//for (auto stone : path)
	//{
	//	stoneToCrush.append(stone);
	//}
}

void GameLogic::animateCrushingStones()
{
	for (auto& pos : stoneToCrush)
	{
		auto& st = board[pos.first][pos.second];
		crushAnimation->add(st);
	}

	/*15 is just a magic number, change it if you want.
		But DO NOT EDIT THIS COMMENT
		in case I want to change it back but forget the default value*/
	isAnimating = true;
	crushAnimation->animate(15);
}

void GameLogic::waitForStopAnimation() const
{
	while (isAnimating)
	{
		QEventLoop loop;
		QTimer::singleShot(50, &loop, SLOT(quit()));
		loop.exec();
	}
}

void GameLogic::enableAllStones()
{
	for (auto& col : board) for (auto& row : col) row->isAnimating = false;
}

auto GameLogic::changeStone(const int col, const int row, const int type) -> void
{
	auto stone = board[col][row];
	if (stone->TYPE == type) return;
	stoneManager.changeStone(stone, type, this);
}

void GameLogic::deleteRect()
{
	const auto row = qrand() % boardSize;
	const auto col = qrand() % boardSize;
	const auto width = qMin(qrand() % boardSize, boardSize - col - 1);
	const auto height = qMin(qrand() % boardSize, boardSize - row - 1);
	deleteRect(col, row, width, height);
}

void GameLogic::deleteRect(const int col, const int row, const int width, const int height)
{
	countEffect = false;
	if (!isPositionValid(col, row)) return;
	const auto destX = col + width;
	const auto destY = row + height;
	if (!isPositionValid(destX, destY)) return;
	for (auto c = col; c <= destX; c++)
		for (auto r = row; r <= destY; r++)
			stoneToCrush.append(qMakePair(c, r));
	gravity();
	countEffect = true;
}

void GameLogic::forceExchange()
{
	const auto row = qrand() % boardSize;
	const auto col = qrand() % boardSize;
	if (col < row)
	{
		if (isPositionValid(col + 1)) forceExchange(col, row, col + 1, row);
		else forceExchange(col, row, col - 1, row);
	}
	else
	{
		if (isPositionValid(row + 1)) forceExchange(col, row, col, row + 1);
		else forceExchange(col, row, col, row - 1);
	}
}

void GameLogic::forceExchange(const int x1, const int y1, const int x2, const int y2)
{
	setMoveData(x1, y1, x2, y2);
	evaluate(Force);
}

void GameLogic::damage(const QString& account, const int dam)
{
	emit stonesCrushing(0, dam, 0, account);
}

void GameLogic::heal(const QString& account, const int hp)
{
	emit stonesCrushing(hp, 0, 0, account);
}

void GameLogic::recover(const QString& account, const int mp)
{
	emit stonesCrushing(0, 0, mp, account);
}

void GameLogic::bladeSlash(const QString& account)
{
	const auto col = qMin(qrand() % boardSize, boardSize - 2);
	auto dam = 0;
	for (auto i = col; i <= col + 1; i++)
	{
		for (auto row : board[col])
		{
			dam += row->DAMAGE;
		}
	}
	dam /= 2;
	damage(account, dam);
	deleteRect(col, 0, 1, boardSize - 1);
}

void GameLogic::lightning(const QString& account)
{
	countEffect = false;
	auto mp = 0;
	for (auto i = 0; i < boardSize; i++) {
		stoneToCrush.append(qMakePair(i, i));
		stoneToCrush.append(qMakePair(boardSize - i - 1, i));
		mp += board[i][i]->MP;
		mp += board[boardSize - i - 1][i]->MP;
	}
	mp /= 2;
	recover(account, mp);
	gravity();
	countEffect = true;
}

void GameLogic::meteor(const QString& account)
{
	countEffect = false;
	auto dam = 0, mp = 0;
	const auto splitter = boardSize / 2;
	for (auto col = 0; col < splitter; col++)
	{
		const auto another = boardSize - 1 - col;
		for (auto row = splitter - 1 - col; row <= splitter + col; row++)
		{
			stoneToCrush.append(qMakePair(col, row));
			stoneToCrush.append(qMakePair(another, row));
			const auto stone = board[col][row];
			const auto anotherStone = board[another][row];
			dam += stone->DAMAGE + anotherStone->DAMAGE;
			mp += stone->MP + anotherStone->MP;
		}
	}
	emit stonesCrushing(0, dam, mp, account);
	gravity();
	countEffect = true;
}

void GameLogic::greedy(const QString& account)
{
	useSkill("Stone", account);
	const auto random = qrand() % 7;
	if (random < 5) greedy(account);
}

void GameLogic::sinisterStrike(const QString& account)
{
	extraBonus++;
}

void GameLogic::forceOfNature(const QString& account)
{
	const auto col = 3;
	const auto row = 3;
	const auto type = NORMAL_STONE;
	changeStone(col, row, type);
	changeStone(col + 1, row, type);
	changeStone(col, row + 1, type);
	changeStone(col + 1, row + 1, type);
}

void GameLogic::gravity()
{
	enableAllStones();
	auto hp = 0, damage = 0, mp = 0, bonus = 0;
	for (const auto pos : stoneToCrush)
	{
		auto st = board[pos.first][pos.second];
		if (st->isValid())
		{
			if (countEffect)
			{
				hp += st->HP;
				damage += st->DAMAGE;
				mp += st->MP;
				bonus++;
				Sound::SEPlayer->setMedia(QUrl("qrc:/sound/Resources/Sound/Gravity.wav"));
				Sound::SEPlayer->play();
			}
			delete st;
			board[pos.first][pos.second] = nullptr;
			//only delete is useless, you must reset it to nullptr explicitly
		}
	}
	if (countEffect)
	{
		if (bonus <= 3) bonus = 1;
		else bonus -= 2;
		if (extraBonus)
		{
			bonus += extraBonus;
			extraBonus = 0;
		}
		hp *= bonus;
		damage *= bonus;
		mp *= bonus;
		emit stonesCrushing(hp, damage, mp, account);
	}
	//countEffect = true;
	stoneToCrush.resize(0);
	auto maxDy = 0;

	//if you change the gravity direction, please change this nested loop.
	//for example, if you want to make the stone move from button to top, change the second loop from 0 to max.
	//if you want to change the move from left to right, change the loop order, serach row first.
	//dy indicates the length it moves.
	for (auto& col : board)
	{
		auto dy = 0;
		for (auto row = boardSize - 1; row >= 0; row--)
		{
			auto& stone = col[row];
			if (stone == nullptr) dy++;
			else
			{
				auto p = stone->pos();
				p.setY(p.y() + dy * Stone::size);
				if (dy == 0) continue;
				col[row + dy] = stone;
				col[row] = nullptr;
				gravityAnimation->add(col[row + dy], p);
			}
		}
		if (dy > maxDy) maxDy = dy;
	}

	/*drop from maxDy above*/
	isAnimating = true;
	for (auto col = 0; col < boardSize; col++)
	{
		auto& column = board[col];
		auto top = 0;
		while (top < boardSize && !column[top]->isValid()) top++;
		const auto size = Stone::size;
		for (auto row = 0; row < top; row++)
		{
			auto stone = stoneManager.getStone(this);
			stone->show();
			column[row] = stone;
			stone->move(col * size, (row - maxDy) * size);
			const QPoint p(col * size, row * size);
			gravityAnimation->add(column[row], p);
		}
	}
	
	gravityAnimation->animate();
}

void GameLogic::gravityFinished()
{
	enableAllStones();
	isAnimating = false;
	auto flag = false;
	for (auto col = 0; col < boardSize; col++)
	{
		for (auto row = 0; row < boardSize; row++)
		{
			setMoveData(col, row, col, row);
			if (evaluate(Gravity)) flag = true;
		}
	}
	first = second = nullptr;

	if (flag) animateCrushingStones();
}
