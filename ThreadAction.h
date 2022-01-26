#ifndef THREAD_ACTION_H
#define THREAD_ACTION_H

#ifdef WIN32
    #include <process.h>
#else
    #include <unistd.h>
    #include <pthread.h>
#endif

#include "h/wintypes.h"
#include "Tool.h"
#include <stdlib.h> 
#include <iostream>
#include <string>
using namespace std;


//Definitions
//////////////////////////////////////////////////////////////////////////
typedef struct tag_TestCaseCounterData
{
    long long nPassed;
    long long nCheckDiskFailed;
    long long nCopyFileFailed;
    long long nCheckFileHashFailed;
    long long nDeleteFileFailed;

    //For Copy Rate
    long long nCopiedFileBytes;
    double nConstSeconsdForFileCopy;

    tag_TestCaseCounterData()
    {
        nPassed = 0;//INT64->MAXINT = 0x7fffffffffffffff = 9223372036854775807
        nCheckDiskFailed = 0;
        nCopyFileFailed = 0;
        nCheckFileHashFailed = 0;
        nDeleteFileFailed = 0;
        nCopiedFileBytes = 0;
        nConstSeconsdForFileCopy = 0;
    }
}TestCaseCounterData, *PTestCaseCounterData;

static DWORD   ACTION_DELAY_FOR_ERROR = 5; //Seconds


//static string ROOT_HD1_NAME = "/home/jacky/Desktop/HD1";
//static string ROOT_HD2_NAME = "/home/jacky/Desktop/HD2";
//static string ROOT_HD3_NAME = "/home/jacky/Desktop/HD3";
//static string ROOT_HD4_NAME = "/home/jacky/Desktop/HD4";
//static string ROOT_FLASH_NAME = "/home/jacky/Desktop/FLASH";
static string ROOT_HD1_NAME = "/mnt/sda1/HD1";
static string ROOT_HD2_NAME = "/mnt/sda1/HD2";
static string ROOT_HD3_NAME = "/mnt/sda1/HD3";
static string ROOT_HD4_NAME = "/mnt/sda1/HD4";
static string ROOT_FLASH_NAME = "/FLASH";

//////////////////////////////////////////////////////////////////////////
static string FLASH_DEPLOY_DATA_SRC_FOLDER = "/UsbTressTestData";

//////////////////////////////////////////////////////////////////////////
static string FLASH_TO_HD1_SRC_FOLDER = "/UsbTressTestDataToHD1";
static string FLASH_TO_HD2_SRC_FOLDER = "/UsbTressTestDataToHD2";
static string FLASH_TO_HD3_SRC_FOLDER = "/UsbTressTestDataToHD3";
static string FLASH_TO_HD4_SRC_FOLDER = "/UsbTressTestDataToHD4";


static string FLASH_TO_HD1_DST_FOLDER = "/FlashToDisk1";
static string FLASH_TO_HD2_DST_FOLDER = "/FlashToDisk2";
static string FLASH_TO_HD3_DST_FOLDER = "/FlashToDisk3";
static string FLASH_TO_HD4_DST_FOLDER = "/FlashToDisk4";

//////////////////////////////////////////////////////////////////////////
static string HD_TO_FLASH_SRC_FOLDER = "/UsbTressTestDataToFlash";

static string HD1_TO_FLASH_DST_FOLDER = "/DiskToFlash";
static string HD2_TO_FLASH_DST_FOLDER = "/Disk2ToFlash";
static string HD3_TO_FLASH_DST_FOLDER = "/Disk3ToFlash";
static string HD4_TO_FLASH_DST_FOLDER = "/Disk4ToFlash";

//////////////////////////////////////////////////////////////////////////
static string SELT_COPY_SRC_FOLDER = "/UsbTressTestData";
static string SELT_COPY_DST_FOLDER = "/SelfCopy";


//////////////////////////////////////////////////////////////////////////
//For Loop Copy Action
//////////////////////////////////////////////////////////////////////////
BOOL CreateDirectory(string strName, void*);
DWORD UsbLoopCopyAction(string strThreadName, string strSource, string strDestnation);

//Thread Actions
//////////////////////////////////////////////////////////////////////////

//Cycle Copy Thread Method

//Loop Copy Thread Methods
//Scenario 1:FLASH
void* UsbStressTest_Flash_SelfCopy_Task(void *lpData);
void* UsbStressTest_Flash_TO_HardDisk1_Task(void *lpData);
void* UsbStressTest_Flash_TO_HardDisk2_Task(void *lpData);
void* UsbStressTest_Flash_TO_HardDisk3_Task(void *lpData);
void* UsbStressTest_Flash_TO_HardDisk4_Task(void *lpData);

//Scenario 2:Hard Disk1
void* UsbStressTest_HardDisk1_SelfCopy_Task(void *lpData);
void* UsbStressTest_HardDisk1_To_Flash_Task(void *lpData);

//Scenario 3:Hard Disk2
void* UsbStressTest_HardDisk2_SelfCopy_Task(void *lpData);
void* UsbStressTest_HardDisk2_To_Flash_Task(void *lpData);

//Scenario 4:Hard Disk3
void* UsbStressTest_HardDisk3_SelfCopy_Task(void *lpData);
void* UsbStressTest_HardDisk3_To_Flash_Task(void *lpData);

//Scenario 5:Hard Disk4
void* UsbStressTest_HardDisk4_SelfCopy_Task(void *lpData);
void* UsbStressTest_HardDisk4_To_Flash_Task(void *lpData);

void RunUsbTesterThreads();

#endif//THREAD_ACTION_H
