#include "main.h"

//http://phongvu.vn/
#define INP "phongvu.vn"
#define OUT "Text.txt"

void GetWebpageSource()
{
	FILE *f = fopen(OUT, "wb");
	if (f == NULL) return;
	HINTERNET hInternet = InternetOpenA("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnection = InternetConnectA(hInternet, INP, 80, " ", " ", INTERNET_SERVICE_HTTP, 0, 0);
	HINTERNET hData = HttpOpenRequestA(hConnection, "GET", "/", NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0);
	HttpSendRequestA(hData, NULL, 0, NULL, 0);
	//239 187 191 = 0xEF 0xBB 0xBF = UTF-8
	char buf[2048] = { 239,187,191 };
	fwrite(buf, sizeof(char), 3, f);
	DWORD bytesRead = 0;
	while (InternetReadFile(hData, buf, 2000, &bytesRead) && bytesRead != 0)
		fwrite(buf, sizeof(char), bytesRead, f);
	InternetCloseHandle(hData);
	InternetCloseHandle(hConnection);
	InternetCloseHandle(hInternet);
	fclose(f);
}