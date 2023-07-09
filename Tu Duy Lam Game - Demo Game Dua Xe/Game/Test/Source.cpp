#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>

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

void InRaSoX(int x)
{
	int soluongchuso = x >= 0 ? log10((double)x) + 1 : log10((double)-x) + 2;

	int chieudai = soluongchuso * 2;

	printf("%c", 218); // ┌

	// chiều dài
	for(int i = 1; i <= chieudai; ++i)
	{
		printf("%c", 196); // ─
	}

	printf("%c", 191); // ┐

	// chiều rộng

	printf("\n%c", 179); // │

	for(int j = 1; j <= soluongchuso / 2; ++j)
	{
		printf(" ");
	}
	printf("%d", x);
	for(int j = 1; j <= soluongchuso - (soluongchuso / 2); ++j)
	{
		printf(" ");
	}

	printf("%c", 179); // │

	printf("\n%c", 192); // └

	// chiều dài
	for(int i = 1; i <= chieudai; ++i)
	{
		printf("%c", 196); // ─
	}

	printf("%c", 217); // ┘
}

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	int n = sizeof(a) / sizeof(a[0]);

	for(int i = 0; i < n; ++i)
	{
		InRaSoX(a[i]);

		int soluongchuso = a[i] >= 0 ? log10((double)a[i]) + 1 : log10((double)-a[i]) + 2;
		int chieudai = soluongchuso * 2;

		gotoxy((i + 1) * chieudai + 1, 1);
	}

	getch();
	return 0;
}