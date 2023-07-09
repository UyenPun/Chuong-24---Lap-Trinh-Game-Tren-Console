#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}


int main()
{
	resizeConsole(800, 600);

	textcolor(14); // Màu vàng.
	cout << "HELLO";

	textcolor(12); // Màu đỏ.
	cout << "\nSON DEP TRAI";

	gotoxy(10, 10);
	cout << "ABC";

	// Kiểm tra có sự tương tác vào từ bàn phím.
	while(true)
	{
		fflush(stdin);
		if(kbhit())
		{
			char c = getch();
			//cout << "\nBan dang nhan vao 1 phim !";
			cout << "\nBan dang nhan vao phim " << c;
			break;
		}
	}

	//XoaManHinh();
	//system("cls");

	cout << "Son dep trai";
	Sleep(2000);
	cout << "\nAi cung biet";

	system("pause");
	return 0;
}