#include <iostream>
#include <Windows.h>
#include <string>
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

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle

(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , 

Cursor_an_Pos);
}

void VeHinh(int x, int y, string str, int color)
{
	gotoxy(x, y); // Cho con trỏ nhảy đến tọa độ x, y.
	textcolor(color); // Tô màu.
	cout << str;
	textcolor(7); // Những dòng ở dưới sẽ trở về như bình thường.
}

int main()
{
	// In danh sách bảng màu.
	/*for(int i = 1; i <= 200; i++)
	{
		textcolor(i);
		cout << "\n=> i = " << i;
	}*/

	VeHinh(10, 10, "\t\t\t\t\t", 176);
	VeHinh(10, 11, "\t\t\t\t\t", 176);
	VeHinh(10, 12, "\t\t\t\t\t", 176);
	VeHinh(10, 13, "\t\t\t\t\t", 176);
	VeHinh(10, 14, "\t\t\t\t\t", 176);
	VeHinh(10, 15, "\t\t\t\t\t", 176);
	VeHinh(10, 16, "\t\t\t\t\t", 176);
	VeHinh(10, 17, "\t\t\t\t\t", 176);

	VeHinh(13, 14, "Ban co muon choi lai ?", 190);
	VeHinh(15, 16, "YES\tNO", 190);
	
	while(true)
	{
		// Cách 1.

		//if(kbhit())
		//{
		//	char c = getch();
		//	//printf("\nKy tu la %c", c);
		//	if(c == 'a' || c == 'A')
		//	{
		//		printf("\nBan chon YES");
		//	}

		//	else if(c == 'd' || c == 'D')
		//	{
		//		printf("\nBan chon NO");
		//	}
		//}

		if(GetAsyncKeyState(VK_LEFT))
		{
			//cout << "\nBan chon YES";
			VeHinh(15, 16, "YES", 185);
			VeHinh(15, 16, "\tNO", 190);
		}

		if(GetAsyncKeyState(VK_RIGHT))
		{
			//cout << "\nBan chon YES";
			VeHinh(15, 16, "YES", 190);
			VeHinh(15, 16, "   \tNO", 185);
		}
	}

	cout << "\n\n\n\n\n";
	system("pause");
	return 0;
}
