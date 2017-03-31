#include "main.h"

//http://phongvu.vn/
#define INP "Text.txt"
#define OUT "Result.txt"

int main()
{
	GetWebpageSource();
	FILE *f = fopen(INP, "rb");
	if (f == NULL) return 0;
	fseek(f, 0, SEEK_END);
	int fSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char*text = (char*)malloc(sizeof(char)*(fSize + 1));
	fread(text, sizeof(char), fSize, f);
	text[fSize] = '\0';
	fclose(f);
	//pattern01 = title
	char pattern01[] = { 116,105,116,108,101,0 };
	int listResult01[128], numResult01;
	DFAsearch(listResult01, numResult01, pattern01, text);
	//pattern02 = VND
	char pattern02[] = { 86,78,196,144,0 }; 
	int listResult02[128], numResult02;
	DFAsearch(listResult02, numResult02, pattern02, text);
	f = fopen(OUT, "wb");
	if (f != NULL)
	{
		fwrite(text, sizeof(char), 3, f);
		for (int i = 0; i < numResult02; i += 2)
		{
			int l = 0, r = numResult01 - 1;
			while (l < r)
			{
				int m = (l + r + 1) / 2;
				if (listResult01[m] < listResult02[i]) l = m;
				else r = m - 1;
			}
			//34 = '"'
			for (l = listResult01[l]; text[l - 1] != 34; l++);
			for (r = l; text[r] != 34; r++);
			//13 10 = '\n'
			text[r++] = 13;
			text[r++] = 10;
			fwrite(text + l, sizeof(char), r - l, f);
			//62 = '>'
			for (l = listResult02[i]; text[l - 1] != 62; l--);
			//60 = '<'
			for (r = listResult02[i]; text[r + 1] != 60; r++);
			text[r++] = 13;
			text[r++] = 10;
			fwrite(text + l, sizeof(char), r - l, f);
		}
		fclose(f);
	}
	free(text);
	return 0;
}