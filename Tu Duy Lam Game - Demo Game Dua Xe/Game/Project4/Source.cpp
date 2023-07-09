#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
using namespace std;

char map[50][50]; // Mảng 2 chiều các ký tự.


// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, 
height, TRUE);
}

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

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle
(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void VeDuongDua_1()
{
	// Dài 30, rộng 30.
	for(int i = 0; i < 30; i++)
	{
		map[i][0] = '|';
		map[i][29] = '|';
		if(i % 2 == 0)
		{
			map[i][14] = '|';
		}

		for(int j = 1; j < 29 && j != 14; j++)
		{
			map[i][j] = ' ';
		}
	}
}

void VeDuongDua_2()
{
	// Dài 30, rộng 30.
	for(int i = 0; i < 30; i++)
	{
		map[i][0] = '|';
		map[i][29] = '|';
		if(i % 2 != 0)
		{
			map[i][14] = '|';
		}

		for(int j = 1; j < 29 && j != 14; j++)
		{
			map[i][j] = ' ';
		}
	}
}

void InDuongDua()
{
	// Dài 30, rộng 30.
	for(int i = 0; i < 30; i++)
	{
		cout << "\t\t\t";
		for(int j = 0; j < 30; j++)
		{
			/* ============ In Đường Đua ========== */
			if(j == 0 || j == 29)
			{
				textcolor(191);
				map[i][j] = ' ';
				cout << map[i][j];
				textcolor(7);
			}
			else if(j == 14)
			{
				textcolor(15);
				cout << map[i][j];
				textcolor(7);

				map[i][j] = ' '; // Xóa lằn đi.
			}
			
			/* ================================= */

			/* IN XE PLAYER */
			else if(map[i][j] == 'X' || map[i][j] == '@' || map[i][j] == '#')
			{
				textcolor(14); // Màu vàng.
				cout << map[i][j];
				textcolor(7); // Trở lại màu bình thường.
			}

			/* IN XE COMPUTER */
			else if(map[i][j] == '!')
			{
				//map[i][j] = ' '; // Bỏ đi ký tự '!'
				textcolor(200);
				cout << map[i][j];
				textcolor(7);
			}

			// Những ký tự không phải là xe.
			else
			{
				cout << map[i][j];
			}
		}
		cout << endl;
	}
}

void VeXePlayer(int x, int y)
{
	map[x][y] = 'X'; // Thân xe.
	map[x][y - 1] = '#'; // Bên trái thân xe.
	map[x][y + 1] = '#'; // Bên phải thân xe.
	map[x - 1][y - 1] = '@'; // Bánh xe trên bên trái.
	map[x + 1][y - 1] = '@'; // Bánh xe dưới bên trái.
	map[x - 1][y + 1] = '@'; // Bánh xe trên bên phải.
	map[x + 1][y + 1] = '@'; // Bánh xe dưới bên phải.
}

void VeXeChuongNgaiVat(int x, int y)
{
	map[x][y] = '!'; // Thân xe.
	map[x][y - 1] = '!'; // Bên trái thân xe.
	map[x][y + 1] = '!'; // Bên phải thân xe.
	map[x - 1][y - 1] = '!'; // Bánh xe trên bên trái.
	map[x + 1][y - 1] = '!'; // Bánh xe dưới bên trái.
	map[x - 1][y + 1] = '!'; // Bánh xe trên bên phải.
	map[x + 1][y + 1] = '!'; // Bánh xe dưới bên phải.
}

void XoaXeChuongNgai(int x, int y)
{
	map[x][y] = ' '; // Thân xe.
	map[x][y - 1] = ' '; // Bên trái thân xe.
	map[x][y + 1] = ' '; // Bên phải thân xe.
	map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
	map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
	map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
	map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.
}

void DiChuyenXe(int &x, int &y) // x, y là tọa độ hiện tại của xe.
{
	/* 
		
		Trái Trên cùng: 1, 2
		Trái dưới cùng: 28, 2
		phải trên cùng: 1, 27
		phải dưới cùng: 28, 27
		*/

	// qua trái.
	if(GetAsyncKeyState(VK_LEFT))
	{
		if(y > 2)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if(map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				// printf("\a"); // Tiếng beep.
				exit(0); // Kết thúc.
			}

			// Xóa xe đi.
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			y--; // Giảm cột xuống.
			VeXePlayer(x, y); // Vẽ lại xe.

			
		}
		
	}

	// qua phải.
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		if(y <= 26)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if(map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				// printf("\a"); // Tiếng beep.
				exit(0); // Kết thúc.
			}

			// Xóa xe đi.
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			y++; // Tăng cột lên.
			VeXePlayer(x, y); // Vẽ lại xe.

			
		}
	}

	// Đi lên.
	else if(GetAsyncKeyState(VK_UP))
	{
		if(x > 1)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if(map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				// printf("\a"); // Tiếng beep.
				exit(0); // Kết thúc.
			}

			// Xóa xe đi.
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			x--; // Giảm số dòng.
			VeXePlayer(x, y); // Vẽ lại xe.
		}
	}

	// Đi xuống
	else if(GetAsyncKeyState(VK_DOWN))
	{
		if(x <= 27)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if(map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				// printf("\a"); // Tiếng beep.
				exit(0); // Kết thúc.
			}

			// Xóa xe đi.-
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			x++; // Tăng số dòng.
			VeXePlayer(x, y); // Vẽ lại xe.
		}
	}
}



int main()
{
	
	resizeConsole(800, 600);

	int x = 20, y = 15; // Tọa độ của xe Player.
	int x1 = 2, y1; // Tọa độ xe chướng ngại vật động.
	int x2 = 5, y2 = 10; // Tọa độ xe chướng ngại vật tĩnh.

	int a = 0;
	while(true)
	{
		a++;
		if(a % 2 != 0)
		{
			VeDuongDua_1();
		}
		else
		{
			VeDuongDua_2();
		}

		// Random tung độ cho xe computer.
		/* 
		Muốn random 1 số nguyên trong đoạn [a, b]:
		srand(time(0)); // Reset thời gian
		int x = a + rand() % (b - a + 1); // Công thức
		*/

		srand(time(0)); // Reset thời gian
		y1 = 2 + rand() % 26; // [2, 27]

		VeXePlayer(x, y);
		VeXeChuongNgaiVat(x1, y1); // Xe động.
		VeXeChuongNgaiVat(x2, y2); // Xe tĩnh.

		XoaManHinh();
	
		InDuongDua();

		DiChuyenXe(x, y);

		Sleep(0);

		if(a >= 30)
		{
			a = 0;
		}

		// Kiểm tra đụng độ giữa xe player và xe tĩnh
		//map[x][y] = ' '; // Thân xe.
		//map[x][y - 1] = ' '; // Bên trái thân xe.
		//map[x][y + 1] = ' '; // Bên phải thân xe.
		//map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
		//map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
		//map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
		//map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

		// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
		if(map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
		{
			// printf("\a"); // Tiếng beep.
			return 0; // Kết thúc.
		}

		XoaXeChuongNgai(x1, y1);
		x1++; // Tăng dòng lên, tạo hiệu ứng di chuyển.
		if(x1 == 31)
		{
			x1 = 2;
		}

		XoaXeChuongNgai(x2, y2);
		x2++;
		if(x2 == 31)
		{
			x2 = 5;
			y2 = 2 + rand() % 26; // [2, 27]
		}
	}
	
	/*for(int i = 0; i <= 200; i++)
	{
		textcolor(i);
		cout << "\n=> i = " << i;
	}*/

	system("pause");
	return 0;
}