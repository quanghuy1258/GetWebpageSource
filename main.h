#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <wininet.h>
#pragma comment ( lib, "Wininet.lib" )

void DFAsearch(int* listResult, int &numResult, char* pattern, char* text);
void GetWebpageSource();