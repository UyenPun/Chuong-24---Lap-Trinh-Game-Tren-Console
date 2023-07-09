#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
using namespace std;

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle
(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

int main()
{
	ifstream FileIn;
	FileIn.open("GioiThieu.txt", ios::in);

	while(!FileIn.eof())
	{
		char c;
		FileIn.get(c);
		Sleep(100);
		textcolor(14);
		cout << c;

		// Nếu mà nhận được sự tương tác 1 phím bất kỳ thì sẽ kết thúc lời giới thiệu.
		if(kbhit())
		{
			return 0;
		}
	}

	FileIn.close();

	system("pause");
	return 0;
}