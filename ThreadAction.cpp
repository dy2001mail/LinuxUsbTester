#include "ThreadAction.h"

#include <sys/time.h>

//////////////////////////////////////////////////////////////////////////
//For Loop Copy Action
//////////////////////////////////////////////////////////////////////////
BOOL CreateDirectory(string strName, void*)
{
    string strCmd = "mkdir ";
    strCmd += strName;

    //cout << "[SYSTME][CMD] " << strCmd.c_str() << endl;
    system(strCmd.c_str());

    return TRUE;
}

DWORD UsbLoopCopyAction(string strThreadName, string strSource, string strDestnation)
{
    if (strSource.length()==0
     || strDestnation.length()==0)
    {
        return 1;
    }

    DWORD dwRet = 0;
    string strMsg;
    TestCaseCounterData cTestCaseCounterData;
    string strBegTime = GetCurrentDateTime();

    while (TRUE)
    {
        double fTemp = 0.0f;
        if (0 != cTestCaseCounterData.nConstSeconsdForFileCopy)
        {
            //cout << "nConstSeconsdForFileCopy = " << cTestCaseCounterData.nConstSeconsdForFileCopy << endl;
            //cout << "nCopiedFileBytes = " << cTestCaseCounterData.nCopiedFileBytes << endl;
            fTemp = (double)((double)(cTestCaseCounterData.nCopiedFileBytes/1024.00))/cTestCaseCounterData.nConstSeconsdForFileCopy;
        }

        cout << "-----------------------------------------------\n"
        << "--" << strThreadName << "--"
        << "\nStartTime: " << strBegTime
        << "\n CurrTime: " << GetCurrentDateTime()
        << "\n     Pass: " << cTestCaseCounterData.nPassed
        << "\n DiskFail: " << cTestCaseCounterData.nCheckDiskFailed
        << "\n CopyFail: " << cTestCaseCounterData.nCopyFileFailed
        << "\n HashFail: " << cTestCaseCounterData.nCheckFileHashFailed
        << "\n  DelFail: " << cTestCaseCounterData.nDeleteFileFailed
        << "\nUSB Speed: " << fTemp << "KB/S\n"
        << "-----------------------------------------------\n" << endl;

        //Step 1:Make sure that the source folder is exist.
        //////////////////////////////////////////////////////////////////////////
        if (IsFolderExists(strSource.c_str(), TRUE))
        {
            //Step 2:Clean up all destination folder and files
            //////////////////////////////////////////////////////////////////////////
            if (IsFolderExists(strDestnation.c_str(), FALSE))
            {
                if (!DeleteAllFiles(strDestnation.c_str(), TRUE))
                {
                    ++cTestCaseCounterData.nDeleteFileFailed;
#ifdef WIN32
                    Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
                    usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif

                    if (!DeleteAllFiles(strDestnation.c_str(), TRUE))
                    {
                        ++cTestCaseCounterData.nDeleteFileFailed;
                    }
                }
            }
            else
            {
                //Create a test folder
                //////////////////////////////////////////////////////////////////////////
                if (!CreateDirectory(strDestnation, NULL))
                {
#ifdef WIN32
                    Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
                    usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif

                    if (!CreateDirectory(strDestnation, NULL))
                    {
                        dwRet = 5;

                        ++cTestCaseCounterData.nCheckDiskFailed;

#ifdef WIN32
                        Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
                        usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif

                        continue;
                    }
                }
            }

            //Step 3: Do copying actions
            //////////////////////////////////////////////////////////////////////////
            struct timeval t_start,t_end;
            long cost_time = 0;

            //get start time
            gettimeofday(&t_start, NULL);
            long start = ((long)t_start.tv_sec)*1000+(long)t_start.tv_usec/1000;
            //printf("Start time: %ld ms\n", start);

            if (!CopyAllFiles(strSource.c_str(), strDestnation.c_str()))
            {
                dwRet = 1;

                ++cTestCaseCounterData.nCopyFileFailed;

#ifdef WIN32
                Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
                usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif

                continue;
            }

            //Step 4:Generate Copying speed
            //////////////////////////////////////////////////////////////////////////
            //get end time
            gettimeofday(&t_end, NULL);
            long end = ((long)t_end.tv_sec)*1000+(long)t_end.tv_usec/1000;
            //printf("End time: %ld ms\n", end);

            //calculate time slot
            cost_time = end - start;
            //printf("Cost time: %ld ms\n", cost_time);

            cTestCaseCounterData.nConstSeconsdForFileCopy += (cost_time/1000.00);
            for (int i=0; i < TOTAL_FILES; i++)
            {
                cTestCaseCounterData.nCopiedFileBytes += FILE_SIZE_LIST[i];
            }

            //Step 5: Do checking file hash actions
            //////////////////////////////////////////////////////////////////////////
            if (!CheckAllFilehash(strDestnation))
            {
                dwRet = 2;

                ++cTestCaseCounterData.nCheckFileHashFailed;

#ifdef WIN32
                Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
                usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif

                continue;
            }

            //Step 6: Do deleting file hash actions
            //////////////////////////////////////////////////////////////////////////
            if (!DeleteAllFiles(strDestnation.c_str(), FALSE))
            {
                dwRet = 3;

                ++cTestCaseCounterData.nDeleteFileFailed;

#ifdef WIN32
                Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
                usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif
                continue;
            }
        }
        else
        {
            dwRet = 4;

            ++cTestCaseCounterData.nCheckDiskFailed;

#ifdef WIN32
            Sleep(ACTION_DELAY_FOR_ERROR * 1000);
#else
            usleep(ACTION_DELAY_FOR_ERROR * 1000*1000);
#endif

            continue;
        }

        ++cTestCaseCounterData.nPassed;
    }

    return dwRet;
}

//Thread Actions
//////////////////////////////////////////////////////////////////////////

//Cycle Copy Thread Method

//Loop Copy Thread Methods
//Scenario 1:FLASH
void* UsbStressTest_Flash_SelfCopy_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_FLASH_NAME + SELT_COPY_SRC_FOLDER,
        ROOT_FLASH_NAME + SELT_COPY_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_Flash_TO_HardDisk1_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_FLASH_NAME + FLASH_TO_HD1_SRC_FOLDER,
        ROOT_HD1_NAME + FLASH_TO_HD1_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_Flash_TO_HardDisk2_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_FLASH_NAME + FLASH_TO_HD2_SRC_FOLDER,
        ROOT_HD2_NAME + FLASH_TO_HD2_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_Flash_TO_HardDisk3_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_FLASH_NAME + FLASH_TO_HD3_SRC_FOLDER,
        ROOT_HD3_NAME + FLASH_TO_HD3_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_Flash_TO_HardDisk4_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_FLASH_NAME + FLASH_TO_HD4_SRC_FOLDER,
        ROOT_HD4_NAME + FLASH_TO_HD4_DST_FOLDER);
    return NULL;
}

//Scenario 2:Hard Disk1
void* UsbStressTest_HardDisk1_SelfCopy_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD1_NAME + SELT_COPY_SRC_FOLDER,
        ROOT_HD1_NAME + SELT_COPY_DST_FOLDER);
}
void* UsbStressTest_HardDisk1_To_Flash_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD1_NAME + HD_TO_FLASH_SRC_FOLDER,
        ROOT_FLASH_NAME + HD1_TO_FLASH_DST_FOLDER);
    return NULL;
}

//Scenario 3:Hard Disk2
void* UsbStressTest_HardDisk2_SelfCopy_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD2_NAME + SELT_COPY_SRC_FOLDER,
        ROOT_HD2_NAME + SELT_COPY_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_HardDisk2_To_Flash_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD2_NAME + HD_TO_FLASH_SRC_FOLDER,
        ROOT_FLASH_NAME + HD2_TO_FLASH_DST_FOLDER);
    return NULL;
}

//Scenario 4:Hard Disk3
void* UsbStressTest_HardDisk3_SelfCopy_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD3_NAME + SELT_COPY_SRC_FOLDER,
        ROOT_HD3_NAME + SELT_COPY_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_HardDisk3_To_Flash_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD3_NAME + HD_TO_FLASH_SRC_FOLDER,
        ROOT_FLASH_NAME + HD3_TO_FLASH_DST_FOLDER);
    return NULL;
}

//Scenario 5:Hard Disk4
void* UsbStressTest_HardDisk4_SelfCopy_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD4_NAME + SELT_COPY_SRC_FOLDER,
        ROOT_HD4_NAME + SELT_COPY_DST_FOLDER);
    return NULL;
}
void* UsbStressTest_HardDisk4_To_Flash_Task(void *lpData)
{
    UsbLoopCopyAction(__FUNCTION__,
        ROOT_HD4_NAME + HD_TO_FLASH_SRC_FOLDER,
        ROOT_FLASH_NAME + HD4_TO_FLASH_DST_FOLDER);
    return NULL;
}

void RunUsbTesterThreads()
{
    pthread_t tid;
    int reqRandCnt = 5;

    //Scenario 1:FLASH
    //pthread_create(&tid, NULL, UsbStressTest_Flash_SelfCopy_Task, &reqRandCnt);

    //pthread_create(&tid, NULL, UsbStressTest_Flash_TO_HardDisk1_Task, &reqRandCnt);
    //pthread_create(&tid, NULL, UsbStressTest_Flash_TO_HardDisk2_Task, &reqRandCnt);
    //pthread_create(&tid, NULL, UsbStressTest_Flash_TO_HardDisk3_Task, &reqRandCnt);
    //pthread_create(&tid, NULL, UsbStressTest_Flash_TO_HardDisk4_Task, &reqRandCnt);

    //Scenario 2:Hard Disk1
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk1_SelfCopy_Task, &reqRandCnt);
    pthread_create(&tid, NULL, UsbStressTest_HardDisk1_To_Flash_Task, &reqRandCnt);

    //Scenario 3:Hard Disk2
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk2_SelfCopy_Task, &reqRandCnt);
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk2_To_Flash_Task, &reqRandCnt);

    //Scenario 4:Hard Disk3
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk3_SelfCopy_Task, &reqRandCnt);
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk3_To_Flash_Task, &reqRandCnt);

    //Scenario 5:Hard Disk4
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk4_SelfCopy_Task, &reqRandCnt);
    //pthread_create(&tid, NULL, UsbStressTest_HardDisk4_To_Flash_Task, &reqRandCnt);
}
