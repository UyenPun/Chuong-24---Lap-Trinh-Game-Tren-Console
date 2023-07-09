#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	while(true)
	{

		if(GetAsyncKeyState(VK_LEFT))
		{
			cout << "LEFT" << endl;
		}
		if(GetAsyncKeyState(VK_RIGHT))
		{
			cout << "RIGHT" << endl;
		}
		if(GetAsyncKeyState(VK_UP))
		{
			keybd_event(VK_LEFT, 0, 0, 0); 
			keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		}
	}

	system("pause");
	return 0;
}