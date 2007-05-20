// checkers.cpp
//
#include "stdafx.h"
#include "SkypeCheckers.h"
#include <cassert>

SkypeCheckers::SkypeCheckers(void)
{
	//Skype�I�u�W�F�N�g�̍쐬
	pSkype = ISkypePtr(__uuidof(Skype));
	//IApplicationPtr pApp = IApplicationPtr("ec163200-44eb-483b-907f-a8c1cf56b8ee");//�ޔ�
	pApp = 
	pApp = IApplicationPtr(__uuidof(Application));
	pStream = IApplicationStreamPtr(__uuidof(ApplicationStream));
	//Checkers�Q�[���̍쐬
	pGame = new Checkers;
	hThread = NULL;
	hExect = NULL;
	//�N���e�B�J���Z�N�V������݂���(SkypeCheckersThread�Ƃ̔r������p)
	pCritSec = new CRITICAL_SECTION;
	InitializeCriticalSection(pCritSec);
	running = false;
	attaching = false;
	connecting = false;
	RunSkypeCheckersThread();
}

SkypeCheckers::~SkypeCheckers(void)
{
	StopSkypeCheckersThread();
	WaitForSingleObject(hThread, INFINITE);
	pSkype = NULL;
	delete pGame;
	::CloseHandle(hThread);
	::CloseHandle(hExect);
	DeleteCriticalSection(pCritSec);
	delete pCritSec;
}

bool SkypeCheckers::RunSkypeCheckersThread()
{
	hThread = (HANDLE)::_beginthreadex(NULL, 0, SkypeCheckersThread, this, 0, NULL);
	return (hThread != NULL);
}

bool SkypeCheckers::StopSkypeCheckersThread()
{
	::EnterCriticalSection(pCritSec);
	if(!running)
		return false;
	for(;!tasks.empty();tasks.pop())
	::SetEvent(hExect);
	::LeaveCriticalSection(pCritSec);
	return true;
}

static unsigned int __stdcall SkypeCheckersThread(void* param)
{
	SkypeCheckers* psc = (SkypeCheckers*)param;

	::EnterCriticalSection(psc->pCritSec);
	psc->running = true;
	::LeaveCriticalSection(psc->pCritSec);

	::CoInitialize(0);//���̃X���b�h��COM�̏�����

	::SetEvent(psc->hExect);
	for(;;)
	{
		::WaitForSingleObject(psc->hExect, INFINITE);
		::EnterCriticalSection(psc->pCritSec);

		if(psc->attaching && psc->Attached())
		{
			psc->tasks.pop();
			psc->attaching = false;
		}

		if(psc->tasks.empty())
		{
			::ResetEvent(psc->hExect);
		}
		else
		{
			switch(psc->tasks.front().cmd)
			{
			case SkypeCheckers::Task::ATTACH://SkypeAPI�ɐڑ�
				if(psc->attaching == false)
				{
					psc->attaching = true;
					psc->pSkype->Attach(5,VARIANT_FALSE);//blocking
				}
				break;
			case SkypeCheckers::Task::CONNECT://�R���^�N�g�ɐڑ�
				if(psc->Attached())
					break;
				if(psc->connecting == false)
				{
					psc->connecting = true;
					continue;
				}
				break;
			}
		}
		::LeaveCriticalSection(psc->pCritSec);
	}
	::CoUninitialize();//���̃X���b�h��COM�̏I���B

	::EnterCriticalSection(psc->pCritSec);
	psc->running = false;
	::LeaveCriticalSection(psc->pCritSec);

	return 0;
}

void SkypeCheckers::AddTask(Task task)
{
	::EnterCriticalSection(pCritSec);
	tasks.push(task);
	::SetEvent(hExect);
	::LeaveCriticalSection(pCritSec);
}

void SkypeCheckers::Attach()
{
	Task task;
	task.cmd = Task::ATTACH;
	AddTask(task);
}

void SkypeCheckers::Connect(CString username)
{
	Task task;
	task.cmd = Task::CONNECT;
	task.username = username;
	AddTask(task);
}

bool SkypeCheckers::StartGame(bool firstMove, bool forceFirst)
{
	bool ret;
	ret = pGame->Start(forceFirst ? (firstMove ? pGame->ally : pGame->enemy) : (rand()%2 ? pGame->ally : pGame->enemy));
	if(ret == false)
		return false;

	char text[100] = {0};
	//sprintf(text, ":%d [SCMes]StartGame, turn:%s", streamId, (this->getTurn() == pGame->ally ? "me" : "you"));

	//return SendSkypeA2AMessage(text);
	return true;
}

bool SkypeCheckers::SendMove(int xf, int yf, int xt, int yt, bool changeTurn)
{
	char text[100] = {0};
//	sprintf(text, ":%d [SCMes]Move:%d,%d,%d,%d", streamId, xf, yf, xt, yt);
	if(pGame->Finished())
	{
		if(pGame->getWinner() == pGame->ally)
			AfxMessageBox(TEXT("���Ȃ��̏����ł��B"));
		else if(pGame->getWinner() == pGame->enemy)
			AfxMessageBox(TEXT("���Ȃ��̕����ł��B"));
	}

//	return SendSkypeA2AMessage(text);
	return true;
}
