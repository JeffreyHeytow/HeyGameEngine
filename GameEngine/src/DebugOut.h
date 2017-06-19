#ifndef DEBUG_OUT_H
#define DEBUG_OUT_H

#include <Windows.h>
#include <stdio.h>

//needs a big enough buffer
extern char buff[256];

#define out(A,...) sprintf_s(buff,A,##__VA_ARGS__); OutputDebugString(buff);
#endif // !DEBUG_OUT_H
