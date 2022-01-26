#include "Tool.h"
// #include <io.h> // for _findfirst
// #include <sys/stat.h>

#include <fstream>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include "SHA1.h"


#ifdef WIN32
    #include <direct.h> // for _getcwd()
#else
    #include <unistd.h>
    #define    _getcwd     getcwd
#endif

BOOL IsFileExists(string strileName, BOOL bFlag)
{
    fstream cFileStream;
    cFileStream.open(strileName.c_str(), ios::in);

    if (!cFileStream)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL IsFolderExists(string strFolderName, BOOL bFlag)
{
    if (access(strFolderName.c_str(), F_OK) == 0)
    {
        //cout << "IsFolderExists:[" << __LINE__ << "] " << strFolderName.c_str() <<endl;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

string GetCurrentDateTime()
{
    time_t t;
    struct tm* tm;
    char szBuffer[256] = {0};

    time(&t);
    tm=localtime(&t);

    sprintf(szBuffer,
      "%04d-%02d-%02d %02d:%02d:%02d",
      tm->tm_year-100+2000,
      tm->tm_mon+1,
      tm->tm_mday,
      tm->tm_hour,
      tm->tm_min,
      tm->tm_sec);

    return string(szBuffer);
}


BOOL GetFileSHA1Hash(string strFileName, PBYTE pbyHash)
{
    ifstream cInputFile(strFileName.c_str(), ios::in | ios::binary);
    if(!cInputFile)
    {
        cout<<"File open error!\n";
        return FALSE;
    }

    char buf[2048]={0};
    int nTotalFileLength = 0;

    // get length of file:
    cInputFile.seekg (0, cInputFile.end);
    nTotalFileLength = cInputFile.tellg();
    cInputFile.seekg (0, cInputFile.beg);

    CSHA1 sha1;

    while(!cInputFile.eof())
    {
         cInputFile.read(buf,2048);

         int nGetSize = 2048;
         if (nTotalFileLength > 2048)
         {
             nTotalFileLength -= 2048;
         }
         else
         {
             nGetSize = nTotalFileLength;
         }

         sha1.Update((unsigned char*)buf, nGetSize);
    }

    sha1.Final();
    sha1.GetHash(pbyHash);
    cInputFile.close();

    return TRUE;
}

void CopyFile(string strSrc, string strDst)
{
    string strCmd = "cp -f ";
    strCmd += strSrc;
    strCmd += " ";
    strCmd += strDst;

    system(strCmd.c_str());
}

BOOL CopyAllFiles(string strSrcFolderName, string strDstFolderName)
{
    string strMsg;
    //DWORD dwRet = 0;

    //Step1: Make sure that the destination folder had been created!
    //////////////////////////////////////////////////////////////////////////
    if (IsFolderExists(strDstFolderName.c_str(), TRUE))
    {
        string strSrcFolder = strSrcFolderName;
        string strDstFolder = strDstFolderName;

        for (int i=0; i<TOTAL_FILES; i++)
        {
            //Step2: Make sure that the source file  could be found
            //////////////////////////////////////////////////////////////////////////
            if (IsFileExists(strSrcFolder + FILE_LIST[i], TRUE))
            {
                //Step3: Make sure that the file copying is OK
                //////////////////////////////////////////////////////////////////////////
                CopyFile(strSrcFolder + FILE_LIST[i], strDstFolder + FILE_LIST[i]);
            }
            else
            {
                return FALSE;
            }
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CopyDismissedFiles(string strSrcFolderName, string strDstFolderName)
{
    string strMsg;
    //DWORD dwRet = 0;

    //Step1: Make sure that the destination folder had been created!
    //////////////////////////////////////////////////////////////////////////
    if (IsFolderExists(strDstFolderName, TRUE))
    {
        string strSrcFolder = strSrcFolderName;
        string strDstFolder = strDstFolderName;

        for (int i=0; i<TOTAL_FILES; i++)
        {
            if (IsFileExists(strDstFolder + FILE_LIST[i], TRUE))
            {
                continue;
            }

            //Step2: Make sure that the source file  could be found
            //////////////////////////////////////////////////////////////////////////
            if (IsFileExists(strSrcFolder + FILE_LIST[i], TRUE))
            {
                //Step3: Make sure that the file copying is OK
                //////////////////////////////////////////////////////////////////////////
                CopyFile(strSrcFolder + FILE_LIST[i], strDstFolder + FILE_LIST[i]);
            }
            else
            {
                return FALSE;
            }
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

BOOL DeleteAllFiles(string strFolderName, BOOL bTimeout)
{
    string strCmd = "rm -rf ";
    strCmd += strFolderName;

    system(strCmd.c_str());

    return TRUE;
}

BOOL CheckAllFilehash(string strFolderName)
{
    string strTemp;
    BYTE bySha1Hash[20] = {0};

    for (int i=0; i<TOTAL_FILES; i++)
    {
        strTemp = strFolderName;
        strTemp += FILE_LIST[i];

        //Step 1: Make sure that the file is exist first
        //////////////////////////////////////////////////////////////////////////
        if (IsFileExists(strTemp.c_str(), TRUE))
        {
            if (!GetFileSHA1Hash(strTemp.c_str(), bySha1Hash)
                || memcmp(bySha1Hash, SHA1_HASH_LIST[i], 20)!=0)
            {
                cout << "FileName = " << strTemp << endl;
                cout << "--Generated hash value--" << endl;
                PrintInfo(bySha1Hash, 20);
                cout << "--Expected hash value--" << endl;
                PrintInfo(SHA1_HASH_LIST[i], 20);

                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
    }

    return TRUE;
}

void GetCurrentDirectory(string &strPath)
{
    char buffer[1024] = "";
    _getcwd(buffer, sizeof(buffer) );
    strPath = buffer;

    cout << "Path:" << buffer << endl;
}

BOOL DeployFolderAction(string strSrc, string strDst)
{
    return FALSE;
}

void PrintInfo(BYTE* ptr, int nSize)
{
   if (ptr != NULL)
   {
       string strMsg;
       for (int i=0; i< nSize; i++)
       {
           char szTemp[12] = {0};
           sprintf(szTemp, "%02X ", ptr[i]);
           strMsg += szTemp;
       }

       cout << "Buffer:" << strMsg << endl;
   }
}

