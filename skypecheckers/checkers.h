// checkers.h
//
#pragma once

class Checkers
{
//Definition
public:
	enum Color
	{
		dark = 1, 
		light = 2, 
	};
	enum Side
	{
		blank = 0, 
		ally, 
		enemy, 
	};

//Class
private:
	struct Piece
	{
	//Field
	private:
		Side side;
		bool crowned;

	// Constructor
	public:
		Piece(Side side, int x, int y) : side(side), crowned(false){}
		virtual ~Piece(void){}

	// Accessor
	public:
		Side getSide(void){return side;}
		bool isCrowned(void){return crowned;}

	// Method
	public:
		bool Crown(void){return (crowned = true);}
	};

private:
	struct Cell
	{
	//Field
	public:
		Piece* piece;
		bool available;

	// Constructor
	public:
		Cell(int x = 0, int y = 0) : piece(0), available(false){}
		virtual ~Cell(void){}
	};

public:
	class Board
	{
	//Field
	private:
		static const int size = 10;
		Cell cell[size][size];

	// Constructor
	public:
		Board();

	// Accessor
	public:
		int getSize()const{return size;}
		Cell* getAt(int x, int y){return (IsOnBoard(x, y) ? &cell[x][y] : 0);}

	// Method
	public:
		bool IsOnBoard(int x, int y)const;
		bool IsAvailable(int x, int y)const;
		bool HasPiece(int x, int y)const;
		bool IsEmpty(int x, int y)const;
	};

public:
	class Player
	{
	//Field
	public:
		Checkers* game;
		Side side;
		Color color;

	// Constructor
	public:
		Player(Checkers* game, Side side, Color color):game(game), side(side), color(color){}
		virtual ~Player(void){}

	// Method
	public:
		bool Move(int xf, int yf, int xt, int yt);
	};

//Field
public:
	Board board;
private:
	Player* ally_player;
	Player* enemy_player;
	Side turn;
	bool started;
	Side winner;

// Constructor
public:
	Checkers(void):ally_player(0), enemy_player(0), turn(blank), started(false){}
	virtual ~Checkers(void);

// Accessor
public:
	Player* getAlly()const{return ally_player;}
	Player* getEnemy()const{return enemy_player;}
	Side getTurn()const{return turn;}
	bool Started()const{return started;}
	Side getWinner(){if(winner == blank)winner = CheckEndOfGame(); return winner;}
	bool Finished(){return (getWinner() != blank);}

// Method
private:
	bool CreatePlayer(Side side, Color color);
public:
	bool Start(Side first);
private:
	bool Move(Player* player, int xf, int yf, int xt, int yt);// called by Player::Move
	void ChangeTurn(void);
public:
	bool DutyJump(Side side);
private:
	Side CheckEndOfGame();
};
