#ifdef WIN32
    #include <process.h>
#else
    #include <unistd.h>
    #include <pthread.h>
#endif


#include <iostream>
using namespace std;

#include "ThreadAction.h"

//
//////////////////////////////////////////////////////////////////////////
long g_nCycleCounter = 0;

//////////////////////////////////////////////////////////////////////////
void Test()
{
    cout << "Test" << endl;
}


//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
unsigned __stdcall AllTestThread(void*)
#else
void* AllTestThread(void*)
#endif
{
    for (int i = 0; i<20; i++)
    {
        cout << "----------------Single Thread(" << i+1 << "/" << g_nCycleCounter << ")----------------"<< endl;
        Test();
    }


#ifdef WIN32
    _endthreadex(0);
    return 0;
#else
    return NULL;
#endif
}

void SingleThreadTest()
{
#ifdef WIN32
    _beginthreadex(0, 0, AllTestThread, NULL, 0, NULL);
#else
    pthread_t tid;
    int reqRandCnt = 5;
    pthread_create(&tid, NULL, AllTestThread, &reqRandCnt);
#endif
}

//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
unsigned __stdcall SingleTestThread(void*)
#else
void* SingleTestThread(void*)
#endif
{
    for (int i = 0; i<100; i++)
    {
        Test();
    }

#ifdef WIN32
    _endthreadex(0);
    return 0;
#else
    return NULL;
#endif
}

void MultiThreadTest()
{
    for (long i=0; i<g_nCycleCounter; i++)
    {
#ifdef WIN32
        _beginthreadex(0, 0, SingleTestThread, NULL, 0, NULL);
#else
        pthread_t tid;
        int reqRandCnt = 5;
        pthread_create(&tid, NULL, SingleTestThread, &reqRandCnt);
#endif
    }
}

int main()
{
/*
    int iModel = 0;
    int nCycle = 0;
    cout << "Please input cycle count" << endl;
    cin >> g_nCycleCounter;

    if (g_nCycleCounter < 100)
    {
        g_nCycleCounter = 1000;
    }

    cout << "Please Choose one Model" << endl;
    cout << "--0:SingleThreadTest" << endl;
    cout << "--Other:MultiThreadTest" << endl;
    cin >> iModel;

    cout << "Cycle Count = " << g_nCycleCounter << endl;

    if (0 == iModel)
    {
        cout << "SingleThreadTest Model" << endl;
        SingleThreadTest();
    }
    else
    {
        cout << "MultiThreadTest Model" << endl;
        g_nCycleCounter /=100;
        MultiThreadTest();
    }

    while(++nCycle < 20000)
    {
        //Do not let me go baby
        cout << nCycle << endl;

#ifdef WIN32
        Sleep(5000);
#else
        usleep(1000*100);
#endif
    }
*/

    //BYTE byHash[20] = {0};
    //GetFileSHA1Hash("/home/jacky/Desktop/FLASH/SelfCopy/1.log", byHash);
    //PrintInfo(byHash, 20);


    RunUsbTesterThreads();

    while(TRUE)
    {
        usleep(5000*1000);
    };
    return 0;
}
