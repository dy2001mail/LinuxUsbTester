/*

 * MUSCLE SmartCard Development ( http://www.linuxnet.com )

 *

 * Copyright (C) 1999

 *  David Corcoran <corcoran@linuxnet.com>

 * Copyright (C) 2002-2011

 *  Ludovic Rousseau <ludovic.rousseau@free.fr>

 *

 * $Id: wintypes.h 5714 2011-05-05 09:26:47Z rousseau $

 */



/**

 * @file

 * @brief This keeps a list of Windows(R) types.

 */



#ifndef __wintypes_h__

#define __wintypes_h__



#ifdef __cplusplus

extern "C"

{

#endif



#ifdef __APPLE__



#include <stdint.h>



#ifndef BYTE

    typedef uint8_t BYTE;

#endif

    typedef uint8_t CHAR;

    typedef uint8_t UCHAR;

    typedef uint8_t *PUCHAR;

    typedef uint16_t USHORT;



#ifndef __COREFOUNDATION_CFPLUGINCOM__

    typedef uint32_t ULONG;

    typedef void *LPVOID;

    typedef int16_t BOOL;

#endif



    typedef uint32_t *PULONG;

    typedef const void *LPCVOID;

    typedef uint32_t DWORD;

    typedef uint32_t *PDWORD;

    typedef uint16_t WORD;

    typedef int32_t LONG;

    typedef const char *LPCSTR;

    typedef const BYTE *LPCBYTE;

    typedef BYTE *LPBYTE;

    typedef DWORD *LPDWORD;

    typedef char *LPSTR;



#else



#include <stdio.h>



#ifndef BYTE

	typedef unsigned char BYTE;

#endif

    typedef char CHAR;

	typedef unsigned char UCHAR;

	typedef unsigned char *PUCHAR;

	typedef unsigned short USHORT;

	typedef	unsigned int UINT;



#ifndef __COREFOUNDATION_CFPLUGINCOM__

	typedef unsigned long ULONG;

	typedef void *LPVOID;

#endif



	typedef const void *LPCVOID;

	typedef unsigned long DWORD;

	typedef unsigned long *PDWORD;

	typedef long LONG;

	typedef const char *LPCSTR;

	typedef const BYTE *LPCBYTE;

	typedef BYTE *LPBYTE;

	typedef DWORD *LPDWORD;

	typedef char *LPSTR;



	/* these types were deprecated but still used by old drivers and

	 * applications. So just declare and use them. */

	typedef LPSTR LPTSTR;

	typedef LPCSTR LPCTSTR;



	/* types unused by pcsc-lite */

	typedef short BOOL;

	typedef unsigned short WORD;

	typedef unsigned long *PULONG;





#endif



typedef void VOID;

typedef int INT;

typedef INT *PINT;

typedef BYTE *PBYTE;

typedef WORD *PWORD;

//typedef FILE* HANDLE;

typedef void* HANDLE;

#define FALSE               0

#define TRUE                1



#ifdef __cplusplus

}

#endif



#endif