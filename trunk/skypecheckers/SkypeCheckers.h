// SkypeCheckers.h
//
#pragma once
#include "checkers.h"
#include <process.h>
#include <queue>

//Å¶Vistaè„Ç≈ÇÕSkypeÇä«óùé“å†å¿Ç≈ãNìÆÇ∑ÇÈÇ±Ç∆ÅIÅI

static char g_appname[] = "skypecheckers1.0beta1";

const int mesMax = 1024;

using namespace std;

class SkypeCheckers
{
public:
	Checkers* pGame;
private:
	HANDLE hThread;
	HANDLE hExect;
	LPCRITICAL_SECTION pCritSec;
	struct Task
	{
		enum Command
		{
			ATTACH,
			CONNECT,
			SEND,
		};
		Command cmd;
		CString username;
	};
	//priority_queue<Task> tasks;
	queue<Task> tasks;

private:
	bool running;
	bool attaching;
	bool connecting;

public:
	SkypeCheckers();
	virtual ~SkypeCheckers(void);
	friend unsigned int __stdcall SkypeCheckersThread(void* param);
	bool RunSkypeCheckersThread();
	bool StopSkypeCheckersThread();
	void AddTask(Task task);
	void Attach();
	void Connect(CString username);

	bool Attached(){return false;}

	bool SendMove(int xf, int yf, int xt, int yt, bool changeTurn);
	bool StartGame(bool firstMove = true, bool forceFirst = false);
	void Procedure(void);
};

unsigned int __stdcall SkypeCheckersThread(void* param);
