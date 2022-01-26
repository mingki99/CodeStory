#include <iostream>
#include <Windows.h>
//#include <shellapi.h>

using namespace std;


int main (void)
{
	//ShellExecute(NULL, "open", "http://3001ssw.tistory.com", NULL, NULL, SW_SHOW);


	const char* a = "https://www.youtube.com/";

	::ShellExecute(NULL, ("open"), a, NULL, NULL, SW_SHOW);

	
}

