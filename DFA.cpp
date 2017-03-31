#include "main.h"

int checkSuffix(char* pattern, char* text)
{
	int m = strlen(pattern), n = strlen(text);
	if (m > n) return 0;
	for (int i = m - 1; i >= 0; i--)
		if (pattern[i] != text[i - m + n]) return 0;
	return 1;
}

void buildDFA(int** dfaTable, char* pattern)
{
	int m = strlen(pattern);
	char *pattern01 = (char*)malloc(sizeof(char)*(m + 1)), *pattern02 = (char*)malloc(sizeof(char)*(m + 1));
	strcpy(pattern01, pattern); strcpy(pattern02, pattern);
	for (int q = 0; q <= m; q++)
	{
		for (int i = 1; i < 256; i++)
		{
			int tst = 1, k = (m + 1 < q + 2) ? (m + 1) : (q + 2);
			while (tst)
			{
				k--;
				char tmp01 = pattern01[k], tmp02 = pattern02[q], tmp03 = pattern02[q + 1];
				pattern01[k] = '\0'; pattern02[q] = i; pattern02[q + 1] = '\0';
				if (checkSuffix(pattern01, pattern02)) tst = 0;
				pattern01[k] = tmp01; pattern02[q] = tmp02; pattern02[q + 1] = tmp03;
			}
			dfaTable[q][i] = k;
		}
	}
	free(pattern01); free(pattern02);
}

void DFAsearch(int* listResult, int &numResult, char* pattern, char* text)
{
	int m = strlen(pattern), n = strlen(text);
	int**dfaTable = (int**)malloc(sizeof(int*)*(m + 1));
	for (int i = 0; i <= m; i++) dfaTable[i] = (int*)malloc(sizeof(int)*256);
	buildDFA(dfaTable, pattern);
	numResult = 0;
	int q = 0;
	for (int i = 0; i < n; i++)
	{
		q = dfaTable[q][((text[i] < 0) ? 256 : 0) + text[i]];
		if (q == m) listResult[numResult++] = i - m + 1;
	} 
	for (int i = 0; i <= m; i++) free(dfaTable[i]);
	free(dfaTable);
}