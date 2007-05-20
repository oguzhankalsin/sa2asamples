// checkers.cpp
//
#include "stdafx.h"
#include "checkers.h"
#include <cassert>

//class Board

Checkers::Board::Board()
{
	for(int i=1;i<size-1;i++)
	{		
		for(int j=1;i+j<size-1;j+=2)
		{
			cell[i][i+j].available = true;
			cell[i+j][i].available = true;
		}
	}
}

bool Checkers::Board::IsOnBoard(int x, int y)const
{
	return (0 <= x && x < size && 0 <= y && y < size);
}

bool Checkers::Board::IsAvailable(int x, int y)const
{
	if(IsOnBoard(x, y) == false)
		return false;
	return cell[x][y].available;
}

bool Checkers::Board::HasPiece(int x, int y)const
{
	if(IsAvailable(x, y) == false)
		return false;
	return (cell[x][y].piece != 0);
}

bool Checkers::Board::IsEmpty(int x, int y)const
{
	if(IsAvailable(x, y) == false)
		return false;
	return (cell[x][y].piece == 0);
}



//class Player

bool Checkers::Player::Move(int xf, int yf, int xt, int yt)
{
	if(this->game->Started() == false)return false;
	int size = game->board.getSize();
	bool ret = false;
	if(this->side == ally)
		ret = game->Move(this, xf, yf, xt, yt);
	if(this->side == enemy)
		ret = game->Move(this, size-1-xf, size-1-yf, size-1-xt, size-1-yt);
	return ret;
}



//class Checkers

Checkers::~Checkers(void)
{
	for(int i=0;i<10;i++)for(int j=0;j<10;j++)
		delete board.getAt(i, j)->piece;
	delete ally_player;
	delete enemy_player;
}

bool Checkers::CreatePlayer(Side side, Color color)
{
	if(side == ally && ally_player == 0)
	{
		ally_player = new Player(this, side, color);
		for(int i=0+1;i<board.getSize()-2+1;i++)for(int j=board.getSize()-1-3;j<board.getSize()-1;j++)
		{
			if(board.getAt(i, j)->available)
				board.getAt(i, j)->piece = new Piece(side, i, j);
		}
		return ally_player != 0;
	}
	if(side == enemy && enemy_player == 0)
	{
		enemy_player = new Player(this, side, color);
		for(int i=0+1;i<board.getSize()-2+1;i++)for(int j=0+1;j<3+1;j++)
		{
			if(board.getAt(i, j)->available)
				board.getAt(i, j)->piece = new Piece(side, i, j);
		}
		return enemy_player != 0;
	}
	return false;
}

bool Checkers::Start(Side first)
{
	assert(first != blank);
	if(started)
		return false;

	CreatePlayer(ally, first == ally ? dark : light);
	CreatePlayer(enemy, first == enemy ? dark : light);

	turn = first;
	started = true;
	return true;
}

bool Checkers::Move(Player* player, int xf, int yf, int xt, int yt)
{
	// ＊ 着手に関する確認 ＊
	// プレイヤーが実在するか確認
	if(player != ally_player && player != enemy_player)
		return 0;
	// プレイヤーが手番者か確認
	if(turn != player->side)
		return false;
	// 盤上での着手をしているか確認
	if(board.IsAvailable(xf, yf) == 0 || board.IsAvailable(xt, yt) == 0)
		return false;
	// 移動するコマの存在を確認
	if(board.getAt(xf, yf)->piece == 0)
		return false;
	// 移動先のセルの状態を確認
	if(board.getAt(xt, yt)->piece != 0)
		return false;

	// ＊ 着手の解釈 ＊
	if(!DutyJump(player->side))
	{
		if(player->side == ally)
		{
			// 周囲１マス（進行）
			if((xt == xf-1 || xt == xf+1) && (yt == yf-1 || yt == yf+1))
			{
				if(yt == yf-1)
				{
					board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
					board.getAt(xf, yf)->piece = 0;
					if(board.IsAvailable(xt-1, yt-1) == false)
						board.getAt(xt, yt)->piece->Crown();
					ChangeTurn();
					return true;
				}
				if(yt == yf+1 && board.getAt(xf, yf)->piece->isCrowned())
				{
					board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
					board.getAt(xf, yf)->piece = 0;
					ChangeTurn();
					return true;
				}
			}
		}
		else if(player->side == enemy)
		{	
			// 周囲１マス（進行）
			if((xt == xf-1 || xt == xf+1) && (yt == yf-1 || yt == yf+1))
			{
				if(yt == yf-1 && board.getAt(xf, yf)->piece->isCrowned())
				{
					board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
					board.getAt(xf, yf)->piece = 0;
					ChangeTurn();
					return true;
				}
				if(yt == yf+1)
				{
					board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
					board.getAt(xf, yf)->piece = 0;
					if(board.IsAvailable(xt+1, yt+1) == false)
						board.getAt(xt, yt)->piece->Crown();
					ChangeTurn();
					return true;
				}
			}
		}
		return false;
	}
			
	// 周囲２マス（ジャンプ）
	if(player->side == ally)
	{
		if((xt == xf-2 || xt == xf+2) && (yt == yf-2 || yt == yf+2))
		{
			if(yt == yf-2)
			{
				board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
				board.getAt(xf, yf)->piece = 0;
				if(board.IsAvailable(xt-1, yt-1) == false)
					board.getAt(xt, yt)->piece->Crown();
				if(xt == xf-2)
				{
					delete board.getAt(xf-1, yf-1)->piece;
					board.getAt(xf-1, yf-1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
				if(xt == xf+2)
				{
					delete board.getAt(xf+1, yf-1)->piece;
					board.getAt(xf+1, yf-1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
			}
			if(yt == yf+2 && board.getAt(xf, yf)->piece->isCrowned())
			{
				board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
				board.getAt(xf, yf)->piece = 0;
				if(xt == xf-2)
				{
					delete board.getAt(xf-1, yf+1)->piece;
					board.getAt(xf-1, yf+1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
				if(xt == xf+2)
				{
					delete board.getAt(xf+1, yf+1)->piece;
					board.getAt(xf+1, yf+1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
			}
		}
	}
	else if(player->side == enemy)
	{	
		if((xt == xf-2 || xt == xf+2) && (yt == yf-2 || yt == yf+2))
		{
			if(yt == yf-2 && board.getAt(xf, yf)->piece->isCrowned())
			{
				board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
				board.getAt(xf, yf)->piece = 0;
				if(xt == xf-2)
				{
					delete board.getAt(xf-1, yf-1)->piece;
					board.getAt(xf-1, yf-1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
				if(xt == xf+2)
				{
					delete board.getAt(xf+1, yf-1)->piece;
					board.getAt(xf+1, yf-1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
			}
			if(yt == yf+2)
			{
				board.getAt(xt, yt)->piece = board.getAt(xf, yf)->piece;
				board.getAt(xf, yf)->piece = 0;
				if(board.IsAvailable(xt+1, yt+1) == false)
					board.getAt(xt, yt)->piece->Crown();
				if(xt == xf-2)
				{
					delete board.getAt(xf-1, yf+1)->piece;
					board.getAt(xf-1, yf+1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
				if(xt == xf+2)
				{
					delete board.getAt(xf+1, yf+1)->piece;
					board.getAt(xf+1, yf+1)->piece = 0;
					if(!DutyJump(player->side))
						ChangeTurn();
					return true;
				}
			}
		}
	}
	return false;
}

bool Checkers::DutyJump(Side side)
{
	if(side == ally)
	{
		for(int i=0;i<board.getSize();i++)for(int j=0;j<board.getSize();j++)
		{
			if(board.HasPiece(i, j))
			{
				if(board.getAt(i, j)->piece->getSide() == ally)
				{
					if(board.HasPiece(i-1, j-1) && board.IsEmpty(i-2, j-2))
						if(board.getAt(i-1, j-1)->piece->getSide() == enemy && board.getAt(i-2, j-2)->piece == 0)
							return true;
					if(board.HasPiece(i+1, j-1) && board.IsEmpty(i+2, j-2))
						if(board.getAt(i+1, j-1)->piece->getSide() == enemy && board.getAt(i+2, j-2)->piece == 0)
							return true;
					if(board.HasPiece(i-1, j+1) && board.IsEmpty(i-2, j+2))
						if(board.getAt(i-1, j+1)->piece->getSide() == enemy && board.getAt(i-2, j+2)->piece == 0)
							if(board.getAt(i, j)->piece->isCrowned())
								return true;
					if(board.HasPiece(i+1, j+1) && board.IsEmpty(i+2, j+2))
						if(board.getAt(i+1, j+1)->piece->getSide() == enemy && board.getAt(i+2, j+2)->piece == 0)
							if(board.getAt(i, j)->piece->isCrowned())
								return true;
				}
			}
		}
		return false;
	}
	else if(side == enemy)
	{
		for(int i=0;i<board.getSize();i++)for(int j=0;j<board.getSize();j++)
		{
			if(board.HasPiece(i, j))
			{
				if(board.getAt(i, j)->piece->getSide() == enemy)
				{
					if(board.HasPiece(i-1, j-1) && board.IsEmpty(i-2, j-2))
						if(board.getAt(i-1, j-1)->piece->getSide() == ally && board.getAt(i-2, j-2)->piece == 0)
							if(board.getAt(i, j)->piece->isCrowned())
								return true;
					if(board.HasPiece(i+1, j-1) && board.IsEmpty(i+2, j-2))
						if(board.getAt(i+1, j-1)->piece->getSide() == ally && board.getAt(i+2, j-2)->piece == 0)
							if(board.getAt(i, j)->piece->isCrowned())
								return true;
					if(board.HasPiece(i-1, j+1) && board.IsEmpty(i-2, j+2))
						if(board.getAt(i-1, j+1)->piece->getSide() == ally && board.getAt(i-2, j+2)->piece == 0)
								return true;
					if(board.HasPiece(i+1, j+1) && board.IsEmpty(i+2, j+2))
						if(board.getAt(i+1, j+1)->piece->getSide() == ally && board.getAt(i+2, j+2)->piece == 0)
								return true;
				}
			}
		}
		return false;
	}
	return false;
}

Checkers::Side Checkers::CheckEndOfGame()
{
	int count_ally = 0;
	int count_enemy = 0;
	for(int i=0;i<board.getSize();i++)for(int j=0;j<board.getSize();j++)
	{
		if(board.HasPiece(i, j))
		{
			if(board.getAt(i, j)->piece->getSide() == ally)
				count_ally++;
			if(board.getAt(i, j)->piece->getSide() == enemy)
				count_enemy++;
		}
	}
	if(count_ally != 0 && count_enemy == 0)
	{
		started = false;
		return ally;
	}
	if(count_ally == 0 && count_enemy != 0)
	{
		started = false;
		return enemy;
	}
	return blank;
}

void Checkers::ChangeTurn(void)
{
	switch(turn)
	{
	case ally:	turn = enemy;	break;
	case enemy:	turn = ally;	break;
	default: assert(turn == ally || turn == enemy);
	}
}
