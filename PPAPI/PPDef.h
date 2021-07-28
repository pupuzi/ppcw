#pragma once
#include <stdio.h>

//¶ÏÑÔ
#ifdef _DEBUG
#define ASSERT(p) if(!(p)){ printf("Assertion failed:%s\nFile:%s\nLine:%d \n", #p, __FILE__, __LINE__); __asm {int 3}  }
#else
#define ASSERT(p) 0;
#endif

//ÄÚ´æÐ¹Â©¼ì²â
#ifdef _DEBUG
#define CrtDumpMemoryLeaks {int nFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ); nFlag |= _CRTDBG_LEAK_CHECK_DF; _CrtSetDbgFlag(nFlag); }
#else
#define CrtDumpMemoryLeaks() 0;
#endif

#define TRUE 1;
#define FALSE 0;

typedef unsigned int uint;
typedef long BOOL;