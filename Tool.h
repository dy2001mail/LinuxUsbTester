#ifndef TOOL_H
#define TOOL_H

#include "h/wintypes.h"
#include <iostream>
using namespace std;

//Definitions
//////////////////////////////////////////////////////////////////////////
 static int TOTAL_FILES = 7;

 static BYTE LOG_FILE_SHA1_HASH[] = "\x10\x23\x05\xBE\xBE\x10\x1D\xE9\x06\x3C\xCE\x33\x33\x09\x38\xF7\xD0\x81\x3F\x7A";
 static BYTE COR_FILE_SHA1_HASH[] = "\xEF\xE3\x79\x1A\xFE\x15\x70\xBD\x2D\x05\x91\x66\xCE\x88\xAD\x45\xD6\xF3\xCC\x6C";
 static BYTE REG_FILE_SHA1_HASH[] = "\xA3\xEF\xF7\xBF\x70\xDB\x5A\xA9\xEA\x42\xFD\x98\xC7\x3B\x67\x6A\x3D\x4C\x0C\x29";
 static BYTE EXE_FILE_SHA1_HASH[] = "\x9B\xBA\xFD\x18\xB7\x31\x1E\xF9\xE6\x8C\xA2\xD2\x4A\x0B\xD9\x65\x30\xF7\x55\x4E";
//static BYTE NB0_FILE_SHA1_HASH[] = "\x97\xDE\xDA\xEE\x71\x3F\xFD\x2F\x63\xFF\x49\x59\xB6\x45\xB5\x86\xB7\x33\x17\x4A";
static  BYTE BIN_FILE_SHA1_HASH[] = "\x30\xF6\xED\xE3\xE1\x97\x95\x88\x8E\xF1\xDF\x85\x4A\x23\x18\x42\xB0\x54\x80\x55";
static BYTE XFA_FILE_SHA1_HASH[] = "\x26\x1E\xBB\x4B\xDA\x11\x73\xF3\x19\x88\x2E\x2D\x13\xC1\x9D\x2C\x90\x52\x1B\xE0";
//static BYTE DLL_FILE_SHA1_HASH[] = "\x22\x77\xC2\xCB\xAF\x3C\xB3\x64\x02\x51\x1D\x1E\x40\xFE\xD0\x5A\xFB\x71\xB1\x33";
static BYTE DLL_FILE_SHA1_HASH[]  = "\x05\xBA\x1A\x70\x3E\xC1\xDD\xEC\x6A\x44\x23\xC1\xC1\xD2\x78\x8A\x10\x9D\xA8\xB1";

static PBYTE SHA1_HASH_LIST[] =
{
    ( PBYTE)&LOG_FILE_SHA1_HASH[0],
    ( PBYTE)&COR_FILE_SHA1_HASH[0],
    ( PBYTE)&REG_FILE_SHA1_HASH[0],
    ( PBYTE)&EXE_FILE_SHA1_HASH[0],
    //( PBYTE)&NB0_FILE_SHA1_HASH[0],
    ( PBYTE)&BIN_FILE_SHA1_HASH[0],
    ( PBYTE)&XFA_FILE_SHA1_HASH[0],
    ( PBYTE)&DLL_FILE_SHA1_HASH[0]
};

static string  FILE_LIST[] =
{
    "/1.log",
    "/T103_2001A063_151015A1_normal_SHA256.COR",
    "/3.reg",
    "/4.exe",
    //"/NK.nb0",
    "/SaioPost.bin",
    "/Sign_PucKey_01.xfa",
    "/test.dll"
};

//How many bytes for each files
static DWORD  FILE_SIZE_LIST[] =
{
   11582,//_T("\\1.log"),
    324480,//_T("\\T103_2001A063_151015A1_normal_SHA256.COR"),
    279,//_T("\\3.reg"),
    93976,//_T("\\4.exe"),
    //18078890,//    _T("\\NK.nb0"),
    126560,//_T("\\SaioPost.bin"),
    1168,//_T("\\Sign_PucKey_01.xfa"),
    4096//_T("\\test.dll")
};

BOOL IsFileExists(string strileName, BOOL bFlag);

BOOL IsFolderExists(string strFolderName, BOOL bFlag);

string GetCurrentDateTime();


BOOL GetFileSHA1Hash(string strFileName, PBYTE pbyHash);
void CopyFile(string strSrc, string strDst);

BOOL CopyAllFiles(string strSrcFolderName, string strDstFolderName);
BOOL CopyDismissedFiles(string strSrcFolderName, string strDstFolderName);

BOOL DeleteAllFiles(string strFolderName, BOOL bTimeout);
BOOL CheckAllFilehash(string strFolderName);
void GetCurrentDirectory(string &strPath);
BOOL DeployFolderAction(string strSrc, string strDst);

void PrintInfo(BYTE* ptr, int nSize);

#endif//TOOL_H

