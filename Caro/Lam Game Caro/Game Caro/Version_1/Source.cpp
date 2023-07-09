#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <stack>
#include <time.h>
#include <fstream>
#pragma comment(lib, "user32") // Thư viện hỗ trợ chức năng hàm full screen khung cmd
using namespace std;

#define MAX 100

struct ToaDo
{
	int toado_dong, toado_cot;
};
typedef struct ToaDo TOADO;

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

/* Hàm trả về vị trí tọa độ con trỏ đang đứng trên khung cmd */
// trả về vị trí x (cột)
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.X;
}

// trả về vị trí y (dòng)
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}
/* ====================================================== */

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

void VeBanCo_CoBan(int sodong, int socot, int doronggiua2cot, int doronggiua2dong)
{
	for(int i = 0; i < sodong; ++i)
	{
		cout << "+";
		for(int j = 0; j < socot; ++j)
		{
			for(int k = 1; k <= doronggiua2cot; ++k)
			{
				cout << "-";
			}
			cout << "+";
		}
		cout << "\n";
		for(int l = 1; l <= doronggiua2dong; ++l)
		{
			cout << "|";
			for(int j = 0; j < socot; ++j)
			{
				for(int k = 1; k <= doronggiua2cot; ++k)
				{
					cout << " ";
				}
				cout << "|";
			}
			cout << "\n";
		}
	}
	cout << "+";
	for(int j = 0; j < socot; ++j)
	{
		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << "-";
		}
		cout << "+";
	}
}

void VeBanCo_NangCao(int sodong, int socot, int doronggiua2cot, int doronggiua2dong, int vitriXbandau, int vitriYbandau)
{
	gotoxy(vitriXbandau, vitriYbandau);

	/* Phần 1: In ra hàng ngang đầu tiên */ 
	cout << (char)218; // ┌
	for(int j = 1; j <= socot - 1; ++j)
	{
		//cout << (char)196 << (char)196 << (char)196; // ─

		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << (char)196; // ─
		}

		cout << (char)194; // ┬
	}
	//cout << (char)196 << (char)196 << (char)196; // ─
	for(int k = 1; k <= doronggiua2cot; ++k)
	{
		cout << (char)196; // ─
	}
	cout << (char)191; // ┐
	//cout << endl; // Nếu dùng endl thì sẽ bị sai trong tình huống chúng ta tùy biến vị trí xuất hiện của bàn cờ tại vitriXbandau, vitriYbandau do khi xuống dòng thì mặc định cơ chế của nó sẽ là bắt đầu tại cột đầu tiên của dòng mới
	vitriYbandau++;
	gotoxy(vitriXbandau, vitriYbandau);

	/* Phần 2: In ra những dòng bên trong */
	for(int i = 1; i <= sodong - 1; ++i)
	{
		for(int l = 1; l <= doronggiua2dong; ++l)
		{
			for(int j = 1; j <= socot; ++j)
			{
				cout << (char)179; // │
				//cout << "   ";
				for(int k = 1; k <= doronggiua2cot; ++k)
				{
					cout << " ";
				}
			}
			cout << (char)179; // │
			//cout << endl; // Nếu dùng endl thì sẽ bị sai trong tình huống chúng ta tùy biến vị trí xuất hiện của bàn cờ tại vitriXbandau, vitriYbandau do khi xuống dòng thì mặc định cơ chế của nó sẽ là bắt đầu tại cột đầu tiên của dòng mới
			vitriYbandau++;
			gotoxy(vitriXbandau, vitriYbandau);
		}
		cout << (char)195; // ├
		for(int j = 1; j <= socot - 1; ++j)
		{
			//cout << (char)196 << (char)196 << (char)196; // ─
			for(int k = 1; k <= doronggiua2cot; ++k)
			{
				cout << (char)196; // ─
			}
			cout << (char)197; // ┼
		}
		//cout << (char)196 << (char)196 << (char)196; // ─
		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << (char)196; // ─
		}
		cout << (char)180; // ┤
		//cout << endl; // Nếu dùng endl thì sẽ bị sai trong tình huống chúng ta tùy biến vị trí xuất hiện của bàn cờ tại vitriXbandau, vitriYbandau do khi xuống dòng thì mặc định cơ chế của nó sẽ là bắt đầu tại cột đầu tiên của dòng mới
		vitriYbandau++;
		gotoxy(vitriXbandau, vitriYbandau);
	}
	for(int l = 1; l <= doronggiua2dong; ++l)
	{
		for(int j = 1; j <= socot; ++j)
		{
			cout << (char)179; // │
			//cout << "   ";
			for(int k = 1; k <= doronggiua2cot; ++k)
			{
				cout << " ";
			}
		}
		cout << (char)179; // │
		//cout << endl; // Nếu dùng endl thì sẽ bị sai trong tình huống chúng ta tùy biến vị trí xuất hiện của bàn cờ tại vitriXbandau, vitriYbandau do khi xuống dòng thì mặc định cơ chế của nó sẽ là bắt đầu tại cột đầu tiên của dòng mới
		vitriYbandau++;
		gotoxy(vitriXbandau, vitriYbandau);
	}

	/* Phần 3: In ra hàng ngang cuối cùng */ 
	cout << (char)192; // └
	for(int j = 1; j <= socot - 1; ++j)
	{
		//cout << (char)196 << (char)196 << (char)196; // ─
		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << (char)196; // ─
		}
		cout << (char)193; // ┴
	}
	//cout << (char)196 << (char)196 << (char)196; // ─
	for(int k = 1; k <= doronggiua2cot; ++k)
	{
		cout << (char)196; // ─
	}
	cout << (char)217; // ┘
}

void VeBanCo_NangCao_CoChiSo(int sodong, int socot, int doronggiua2cot, int doronggiua2dong, char a[20][20], bool DungGotoxy = true)
{
	int SoKhoangCachLuiVoSoVoiLeTrai = log10(sodong) + 1;
	/* In ra chỉ số cột ứng với từng cột */ 
	cout << setw((doronggiua2cot + 2) / 2 + 1 + SoKhoangCachLuiVoSoVoiLeTrai);
	for(int j = 0; j < socot - 1; ++j)
	{
		cout << j;
		cout << setw(doronggiua2cot + 1);
	}
	cout << socot - 1;
	cout << endl;
	/* =================================== */

	/* Phần 1: In ra hàng ngang đầu tiên */ 

	cout << setw(SoKhoangCachLuiVoSoVoiLeTrai + 1);

	cout << (char)218; // ┌
	for(int j = 1; j <= socot - 1; ++j)
	{
		//cout << (char)196 << (char)196 << (char)196; // ─

		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << (char)196; // ─
		}

		cout << (char)194; // ┬
	}
	//cout << (char)196 << (char)196 << (char)196; // ─
	for(int k = 1; k <= doronggiua2cot; ++k)
	{
		cout << (char)196; // ─
	}
	cout << (char)191; // ┐
	cout << endl;

	/* Phần 2: In ra những dòng bên trong */
	for(int i = 1; i <= sodong - 1; ++i)
	{
		for(int l = 1; l <= doronggiua2dong; ++l)
		{
			if(l != doronggiua2dong / 2 + 1)
			{
				cout << setw(SoKhoangCachLuiVoSoVoiLeTrai + 1);
			}
			else
			{
				int sochuso = (i - 1) == 0 ? 1 : log10(i - 1) + 1;
				cout << setw(SoKhoangCachLuiVoSoVoiLeTrai);
				cout << i - 1;
			}

			for(int j = 1; j <= socot; ++j)
			{
				cout << (char)179; // │

				for(int k = 1; k <= doronggiua2cot; ++k)
				{
					if(DungGotoxy == true)
					{
						cout << " ";
					}
					else // dùng theo kiểu xóa màn hình rồi vẽ lại
					{
						if(k != doronggiua2cot / 2 + 1 || l != doronggiua2dong / 2 + 1)
						{
							cout << " ";
						}
						else // k == doronggiua2cot / 2 + 1 && l == doronggiua2dong / 2 + 1
						{
							if(a[i - 1][j - 1] == 'X')
								textcolor(14); // màu vàng
							else if(a[i - 1][j - 1] == 'O')
								textcolor(12); // màu đỏ

							cout << a[i - 1][j - 1]; // in ra quân cờ ở vị trí tương ứng: Hoặc là ký tự rỗng, hoặc là quân cờ X hay O

							textcolor(7); // trở về màu trắng ban đầu
						}
					}

				}
			}
			cout << (char)179; // │
			cout << endl;
		}
		cout << setw(SoKhoangCachLuiVoSoVoiLeTrai + 1);
		cout << (char)195; // ├
		for(int j = 1; j <= socot - 1; ++j)
		{
			//cout << (char)196 << (char)196 << (char)196; // ─
			for(int k = 1; k <= doronggiua2cot; ++k)
			{
				cout << (char)196; // ─
			}
			cout << (char)197; // ┼
		}
		//cout << (char)196 << (char)196 << (char)196; // ─
		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << (char)196; // ─
		}
		cout << (char)180; // ┤
		cout << endl;
	}

	for(int l = 1; l <= doronggiua2dong; ++l)
	{
		if(l != doronggiua2dong / 2 + 1)
		{
			cout << setw(SoKhoangCachLuiVoSoVoiLeTrai + 1);
		}
		else
		{
			int sochuso = (sodong - 1) == 0 ? 1 : log10(sodong - 1) + 1;
			cout << setw(SoKhoangCachLuiVoSoVoiLeTrai);
			cout << sodong - 1;
		}

		for(int j = 1; j <= socot; ++j)
		{
			cout << (char)179; // │

			for(int k = 1; k <= doronggiua2cot; ++k)
			{
				if(DungGotoxy == true)
				{
					cout << " ";
				}
				else // dùng theo kiểu xóa màn hình rồi vẽ lại
				{
					if(k != doronggiua2cot / 2 + 1 || l != doronggiua2dong / 2 + 1)
					{
						cout << " ";
					}
					else
					{
						if(a[sodong - 1][j - 1] == 'X')
							textcolor(14); // màu vàng
						else if(a[sodong - 1][j - 1] == 'O')
							textcolor(12); // màu đỏ

						cout << a[sodong - 1][j - 1]; // in ra quân cờ ở vị trí tương ứng: Hoặc là ký tự rỗng, hoặc là quân cờ X hay O

						textcolor(7); // trở về màu bình thường ban đầu
					}
				}


			}
		}
		cout << (char)179; // │
		cout << endl;
	}

	/* Phần 3: In ra hàng ngang cuối cùng */ 
	cout << setw(SoKhoangCachLuiVoSoVoiLeTrai + 1);
	cout << (char)192; // └
	for(int j = 1; j <= socot - 1; ++j)
	{
		//cout << (char)196 << (char)196 << (char)196; // ─
		for(int k = 1; k <= doronggiua2cot; ++k)
		{
			cout << (char)196; // ─
		}
		cout << (char)193; // ┴
	}
	//cout << (char)196 << (char)196 << (char)196; // ─
	for(int k = 1; k <= doronggiua2cot; ++k)
	{
		cout << (char)196; // ─
	}
	cout << (char)217; // ┘
}

void NhapToaDoQuanCoCanDanh(int &luotdi, char a[20][20], int sodong, int socot, int doronggiua2dong, int doronggiua2cot, bool DungGotoxy = true)
{
	int toado_dong = -1, toado_cot = -1; // Tọa độ vị trí người dùng muốn đánh cờ
	char quanco; // X hoặc O

	quanco = luotdi == 0 ? 'X' : 'O'; // toán tử 3 ngôi

	int DoDaiLonNhat = -1;
	int DoDaiNoiDungThongBao;

	cout << "Luot di hien tai la cua quan co: ";
	//string NoiDungXuatRaManHinh = "Luot di hien tai la cua quan co: ";
	//cout << NoiDungXuatRaManHinh;

	/*if(DungGotoxy == true)
	{
	DoDaiNoiDungThongBao = NoiDungXuatRaManHinh.length();
	if(DoDaiNoiDungThongBao > DoDaiLonNhat)
	DoDaiLonNhat = DoDaiNoiDungThongBao;
	}*/


	quanco == 'X' ? textcolor(14) : textcolor(12);
	cout << quanco;
	textcolor(7); // trở lại màu bình thường

	int vitridongthongbaodautien = doronggiua2dong * sodong + sodong + 1 + 2;

	do{
		cout << "\nNhap vao toa do [dong, cot] can danh: ";
		vitridongthongbaodautien++;
		//NoiDungXuatRaManHinh = "\nNhap vao toa do [dong, cot] can danh: ";
		//cout << NoiDungXuatRaManHinh;

		// Cách làm hiện tại vẫn còn sẽ bị lỗi nếu người dùng cố tình nhấn phím space để đưa con trỏ sang ô kế cận bên phải liên tục sau đó mới nhập hay enter xuống nhiều dòng rồi mới nhập dữ liệu thì cách tính độ dài lớn nhất của nội dung thông báo hay vị trí các dòng thông báo đều sẽ bị sai sót không xóa hết được 2 chỉ số dòng cột người dùng đã nhập
		// Giải pháp:
		// Tìm hiểu cách để tính xem khi nhấn Enter xác nhận nhập xong thì lúc đó con trỏ chuột đang nằm ở vị trí x = ? y = ?
		// Google dịch từ: Làm thế nào để lấy vị trí con trỏ trên màn hình console khi nhấn enter để nhập dữ liệu xong trong visual studio c/c++ sang tiến Anh rồi copy từ tiếng Anh đó tra cứu google
		// Khi đã có được cách làm và test ok thì từ đó tính ra độ dài lớn nhất so sánh với x để nếu x lớn hơn thì cập nhật lại độ dài lớn nhất là x
		// và so sánh nếu y mà lớn hơn vitridongthongbaodautien tức là đã bị enter xuống dòng thì phải cộng bù thêm phần dòng còn thiếu đó
		// sau cùng thì áp dụng cho vòng lặp chạy đủ các dòng và với mỗi dòng sẽ đi lấp đầy bằng khoảng trống với độ dài lớn nhất tìm được
		cin >> toado_dong >> toado_cot;

		if(DungGotoxy == true)
		{
			// Tính ra vị trí dòng y sau khi nhập xong 2 tọa độ để xem nó cách biệt bao nhiêu so với vị trí trước đó mà cộng bù thêm
			vitridongthongbaodautien = wherey(); // lấy ngay vị trí chính là y

			//DoDaiNoiDungThongBao = NoiDungXuatRaManHinh.length() + 10; // 10 chính là dự trù khoảng cách mà người dùng nhập chỉ số dòng , cột
			//if(DoDaiNoiDungThongBao > DoDaiLonNhat)
			//	DoDaiLonNhat = DoDaiNoiDungThongBao;
		}


		if(toado_dong < 0 || toado_dong >= sodong)
		{
			cout << "\nToa do dong khong hop le. Xin kiem tra lai!";
			//NoiDungXuatRaManHinh = "\nToa do dong khong hop le. Xin kiem tra lai!";
			//cout << NoiDungXuatRaManHinh;

			if(DungGotoxy == true)
			{
				/*DoDaiNoiDungThongBao = NoiDungXuatRaManHinh.length();
				if(DoDaiNoiDungThongBao > DoDaiLonNhat)
				DoDaiLonNhat = DoDaiNoiDungThongBao;*/

				vitridongthongbaodautien += 2;
			}
		}

		if(toado_cot < 0 || toado_cot >= socot)
		{
			cout << "\nToa do cot khong hop le. Xin kiem tra lai!";
			//NoiDungXuatRaManHinh = "\nToa do cot khong hop le. Xin kiem tra lai!";
			//cout << NoiDungXuatRaManHinh;
			if(DungGotoxy == true)
			{
				/*DoDaiNoiDungThongBao = NoiDungXuatRaManHinh.length();
				if(DoDaiNoiDungThongBao > DoDaiLonNhat)
				DoDaiLonNhat = DoDaiNoiDungThongBao;*/

				vitridongthongbaodautien += 2;
			}
		}

	}while(toado_dong < 0 || toado_dong >= sodong || toado_cot < 0 || toado_cot >= socot);

	a[toado_dong][toado_cot] = quanco; // lưu trữ quân cờ vừa đánh vào vị trí tọa độ tương ứng trong mảng a

	luotdi = luotdi == 0 ? 1 : 0; // toán tử 3 ngôi

	if(DungGotoxy == true)
	{
		int x = (log10(sodong) + 1) + 1, y = 2; // vị trí ban đầu của góc trên cùng bên trái của bàn cờ

		// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ
		gotoxy(x + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), y + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1));

		quanco == 'X' ? textcolor(14) : textcolor(12);
		cout << quanco;
		textcolor(7); // trở lại màu bình thường

		// Vòng lặp này có tác dụng điều hướng con trỏ chuột đến từng dòng nội dung được in ra màn hình bắt đầu từ dòng đầu tiên ở dưới bàn cờ cho đến dòng thông báo cuối cùng được in ra trên màn hình: Mục đích là để xóa đi hết tất cả những dòng thông báo đó
		for(int y = doronggiua2dong * sodong + sodong + 1 + 2; y <= vitridongthongbaodautien; ++y)
		{
			gotoxy(1, y); // Điều hướng con trỏ chuột nhảy đến vị trí cột đầu tiên dòng thứ y

			// Trong số tất cả những nội dung thông báo được in ra màn hình thì nó có được nội dung thông báo dài nhất và giờ đây sẽ chạy từ đầu đến cuối cái dài nhất đó để xóa đi hết lấp bằng khoảng trống

			// Lấy kích thước bề ngang của khung cmd ngay thời điểm hiện tại
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

			// Chạy từ đầu dòng đến cuối dòng (cuối bề ngang của khung cmd) và lấp bằng khoảng trống
			for(int i = 1; i <= columns; ++i) 
				cout << " ";
		}
		// Sau khi vòng lặp đã xóa đi hết các dòng thông báo thì lại cho nó nhảy về vị trí tọa độ dòng đầu tiên bên dưới bàn cờ để chuẩn bị lại hiện lại câu thông báo nhập quân cờ cần đánh ...
		gotoxy(1, doronggiua2dong * sodong + sodong + 1 + 2);

		// Đây là đoạn code trước đó chưa xử lý được chuyện xóa đi các dòng thông báo lỗi tọa độ dòng cột mà chỉ xóa đi đúng 2 dòng Luot di hien tai ... và dòng Nhap toa do ...
		//// Nhảy đến ngay vị trí đầu chữ "Luot di hien tai ..." để lấp đi dòng nó
		//gotoxy(1, doronggiua2dong * sodong + sodong + 1 + 2); // công thức để nhảy đến ngay dòng đầu tiên ở dưới cùng của bàn cờ
		//cout << "                                                                                  "; // khoảng trắng dài thứ 1 này là tượng trưng cho chữ "Luot di hien tai ..."

		//// Nhảy đến ngay vị trí đầu chử "Nhap vao toa do [dong, cot] ..." để lấp đi chữ đó
		//gotoxy(1, doronggiua2dong * sodong + sodong + 1 + 2 + 1);
		//cout << "                                                                                            "; // Khoảng trắng dài thứ 2 này là tượng trưng cho chữ "Nhap vao toa do [dong, cot] can danh ...";

		//// Sau đó lại cho nó nhảy về lại vị trí ban đầu của chữ "Luot di hien tai ..." để mà vòng lặp tiếp tục lặp in ra màn hình dòng chữ đó đúng ngay vị trí đó
		//gotoxy(1, doronggiua2dong * sodong + sodong + 1 + 2);
	}
}

void XuLyGameTheoHuongNhapToaDoCanDanh(char a[20][20], int sodong, int socot, int doronggiua2cot, int doronggiua2dong, bool DungGotoxy = true)
{
	int luotdi = 0; // Cứ luân phiên 0 - 1 - 0 - 1 ... và có thể quy tắc tùy ý 0 là X, 1 là O hay 0 là O, 1 là X

	if(DungGotoxy == true)
	{
		VeBanCo_NangCao_CoChiSo(sodong, socot, doronggiua2cot, doronggiua2dong, a, DungGotoxy); // tham số cuối có thể không cần để cũng được vì khi khởi tạo trong tham số hàm đã mặc định nó là true rồi
		cout << endl;
	}

	// vòng lặp vô tận
	while(true)
	{
		if(DungGotoxy == false)
		{
			VeBanCo_NangCao_CoChiSo(sodong, socot, doronggiua2cot, doronggiua2dong, a, DungGotoxy);
			cout << endl;
		}

		NhapToaDoQuanCoCanDanh(luotdi, a, sodong, socot, doronggiua2dong, doronggiua2cot, DungGotoxy);

		if(DungGotoxy == false)
		{
			system("cls"); // xóa màn hình
		}
	}
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraHangNgang(char a[MAX][MAX], int sodong, int socot, int vitridong, int vitricot, int SoQuanCoGiongNhauLienTiepToiThieuDeThang, bool KichHoatCheDoChan2DauLaKhongChoThang)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống
	int dem_bichan2dau = 0;

	// Xét qua bên trái trước (ngang trái)
	for(int j = vitricot - 1; j >= 0; --j)
	{
		if(a[vitridong][j] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[vitridong][j] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}
	}

	// Xét qua bên phải (ngang phải)
	for(int j = vitricot + 1; j < socot; ++j)
	{
		if(a[vitridong][j] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[vitridong][j] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}
	}

	if(dem >= SoQuanCoGiongNhauLienTiepToiThieuDeThang)
	{
		if(KichHoatCheDoChan2DauLaKhongChoThang == true && dem_bichan2dau == 2)
			return ' '; // chưa thắng

		return a[vitridong][vitricot]; // đã thắng
	}
	return ' '; // chưa thắng
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraHangDoc(char a[MAX][MAX], int sodong, int socot, int vitridong, int vitricot, int SoQuanCoGiongNhauLienTiepToiThieuDeThang, bool KichHoatCheDoChan2DauLaKhongChoThang)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống
	int dem_bichan2dau = 0;

	// Xét lên trên trước (dọc trên)
	for(int i = vitridong - 1; i >= 0; --i)
	{
		if(a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[i][vitricot] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}
	}

	// Xét xuống dưới (dọc dưới)
	for(int i = vitridong + 1; i < sodong; ++i)
	{
		if(a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[i][vitricot] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}
	}
	if(dem >= SoQuanCoGiongNhauLienTiepToiThieuDeThang)
	{
		if(KichHoatCheDoChan2DauLaKhongChoThang == true && dem_bichan2dau == 2)
			return ' '; // chưa thắng

		return a[vitridong][vitricot]; // đã thắng
	}
	return ' '; // chưa thắng
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraCheoChinh(char a[MAX][MAX], int sodong, int socot, int vitridong, int vitricot, int SoQuanCoGiongNhauLienTiepToiThieuDeThang, bool KichHoatCheDoChan2DauLaKhongChoThang)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống
	int dem_bichan2dau = 0;

	// Kiểm tra chéo chính trên: Các phần tử dòng - cột luôn giảm 1 đơn vị và giảm đến khi nào 1 trong 2 thằng xuất hiện 0
	int i = vitridong - 1;
	int j = vitricot - 1;
	while(true)
	{
		if(i < 0 || j < 0)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[i][j] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}

		// Xét qua lần lặp mới
		i--;
		j--;
	}

	//	Kiểm tra chéo chính dưới: Các phần tử dòng - cột đều tăng lên 1 đơn vị và tăng đến khi nào 1 trong 2 thằng bằng n - 1 thì dừng lại
	i = vitridong + 1;
	j = vitricot + 1;
	while(true)
	{
		if(i == sodong || j == socot)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[i][j] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}

		// Xét qua lần lặp mới
		i++;
		j++;
	}
	if(dem >= SoQuanCoGiongNhauLienTiepToiThieuDeThang)
	{
		if(KichHoatCheDoChan2DauLaKhongChoThang == true && dem_bichan2dau == 2)
			return ' '; // chưa thắng

		return a[vitridong][vitricot]; // đã thắng
	}
	return ' '; // chưa thắng
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraCheoPhu(char a[MAX][MAX], int sodong, int socot, int vitridong, int vitricot, int SoQuanCoGiongNhauLienTiepToiThieuDeThang, bool KichHoatCheDoChan2DauLaKhongChoThang)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống
	int dem_bichan2dau = 0;

	// Kiểm tra chéo phụ trên: Dòng giảm - cột tăng. Dòng giảm tối đa tới 0, Cột tăng tối đa nới n - 1
	int i = vitridong - 1;
	int j = vitricot + 1;
	while(true)
	{
		if(i < 0 || j == socot)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[i][j] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}

		// Xét qua lần lặp mới
		i--;
		j++;
	}

	//	Kiểm tra chéo phụ dưới: Dòng tăng - cột giảm. Dòng tăng tới tối đa là n - 1 và cột giảm tới tối đa là 0
	i = vitridong + 1;
	j = vitricot - 1;
	while(true)
	{
		if(i == sodong || j < 0)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			/* Rơi vào cái else này có nghĩa là tại vị trí này ký tự đó không trùng với quân cờ vừa đánh xuống, thì chỉ có 2 trường hợp xảy ra: 
			hoặc đó là ô rỗng không có cờ, hoặc đó là ô có quân cờ của đối thủ 
			=> chỉ cần xét nếu đó không phải là ô rỗng thì nghĩa là nó chính là ô cờ của đối thủ tức là bị chặn lại ngay ở đầu */
			if(a[i][j] != ' ') 
			{
				dem_bichan2dau++;
			}
			break;
		}

		// Xét qua lần lặp mới
		i++;
		j--;
	}
	if(dem >= SoQuanCoGiongNhauLienTiepToiThieuDeThang)
	{
		if(KichHoatCheDoChan2DauLaKhongChoThang == true && dem_bichan2dau == 2)
			return ' '; // chưa thắng

		return a[vitridong][vitricot]; // đã thắng
	}
	return ' '; // chưa thắng
}

void ChucNang_Undo(stack<TOADO> &stack_undo, stack<TOADO> &stack_redo, int &toado_dong, int &toado_cot, int &temp_toado_dong, int &temp_toado_cot, bool DanhTheoDuongGiaoDiemDongCot, int vitriXbandau, int vitriYbandau, int doronggiua2cot, int doronggiua2dong, char a[MAX][MAX], int &DemSoLuongQuanCoDaDanh, bool &luotdi, int DoDaiNoiDungThongBao, int sodong, char &quanco)
{
	if(stack_undo.empty() == false) // Kiểm tra stack còn phần tử thì mới đi xử lý chứ nếu không sẽ bị lỗi (vì phải còn phần tử tức là còn có thể Undo được)
	{
		TOADO td;
		td = stack_undo.top(); // Gán phần tử đầu stack qua biến cấu trúc td
		stack_undo.pop(); // Loại bỏ phần tử đầu stack ra khỏi stack

		stack_redo.push(td); // Tọa độ vừa lấy ra khỏi Stack_Undo sẽ được đưa vào trong Stack_REDO

		// Cập nhật lại biến tọa độ dòng - cột để mà khi đánh tiếp theo nó sẽ đánh ngay tại vị trí dấu nháy đang đứng chứ không phải lại đánh ngay vị trí quân cờ cuối cùng đứng trước đó
		toado_dong = td.toado_dong;
		toado_cot = td.toado_cot;

		// Cập nhật lại biến temp_toado_dong, temp_toado_cot là -1 để khi đánh quân cờ mới thì nó sẽ không chạy đến xóa viền background rồi in lại quân cờ bỏ viền background các thứ sẽ bị lung tung
		temp_toado_dong = -1;
		temp_toado_cot = -1;

		// Sau khi đã có được vị trí tọa độ của nước cờ vừa đánh gần nhất được lưu trữ trong biến cấu trúc td (đã gán qua cho luôn biến toado_dong, toado_cot) thì:

		// Cho dấu nháy nhảy đến ô tương ứng tọa độ đó và xóa quân cờ đi
		// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
		DanhTheoDuongGiaoDiemDongCot == false ? 
			// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
			gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

			// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
			gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

		cout << " "; // Lấp quân cờ cuối cùng vừa đánh bằng khoảng trống (cũng là xóa đi viền background mà nó đang có)

		// Xóa quân cờ đó bên mảng a
		a[toado_dong][toado_cot] = ' ';

		DemSoLuongQuanCoDaDanh--; // Giảm đi số lượng quân cờ đã đánh

		// Cập nhật lại lượt đi để câu thông báo lượt đi hiện tại là của quân cờ nào và quân cờ sẽ đánh xuống tiếp tục chính là quân cờ vừa bị Undo xóa đi
		luotdi = !luotdi;

		// Không cần phải xuất lại nội dung "Luot di hien tai la cua quan co: " mà chỉ cần nhảy đến cột x tương ứng để xuất ra quân cờ mới thôi.
		gotoxy(vitriXbandau + DoDaiNoiDungThongBao, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 1); // Nhảy đến dòng dưới cùng của bàn cờ
		if(luotdi == true)
		{
			quanco = 'X';
			textcolor(14); // màu vàng
		}
		else
		{
			quanco = 'O';
			textcolor(12); // màu đỏ
		}
		cout << quanco;
		textcolor(7); // trả lại màu bình thường

		// Nếu ngăn xếp vẫn còn phần tử nghĩa là nước tiếp theo trong ngăn xếp chính là nước cuối cùng hiện tại vừa đánh trên bàn cờ => nhảy đến nước đó và tô viền background cho nó
		if(stack_undo.empty() == false)
		{
			td = stack_undo.top(); // Lấy vị trí tọa độ của nước áp cuối vừa xóa đi để cho dấu nháy nhảy đến ô đó mà tô viền background tương ứng để đại ý nước đó là nước cuối cùng vừa đánh (vì nước cuối cùng trước đó đã bị Undo)

			// để cập nhật lại temp_toado_dong là nước cuối cùng để nếu có đánh nước mới nó sẽ nhảy đến nước cuối cùng này xóa viền background đi, nếu không có 2 dòng gán này thì sẽ có tồn tại 2 viền background của nước hiện tại và nước mới đánh
			temp_toado_dong = td.toado_dong;
			temp_toado_cot = td.toado_cot;

			// Để dấu nháy chính xác là nằm ngay ở ô nó đang đứng (ô ở nước áp cuối trước khi Undo hoặc hiểu là nước cuối cùng sau khi Undo) chứ không phải là ô cuối cùng vừa bị Undo
			toado_dong = td.toado_dong;
			toado_cot = td.toado_cot;

			// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
			DanhTheoDuongGiaoDiemDongCot == false ? 
				// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
				gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + td.toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + td.toado_dong * (doronggiua2dong + 1)) :

				// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
				gotoxy(td.toado_cot * (doronggiua2cot + 1) + vitriXbandau, td.toado_dong * (doronggiua2dong + 1) + vitriYbandau);

			if(quanco == 'X') // Nếu quân cờ mà nó thông báo lượt đánh hiện tại là X thì nghĩa là quân cờ gần nhất trước đó đang là O
			{
				textcolor(12 + 32); // màu viền background đại ý cho quân cờ trước đó chính là quân cờ vừa đánh
				cout << "O"; // In ra quân cờ gần nhất trước đó là O
				textcolor(7); // trở lại màu bình thường
			}
			else // Nếu quân cờ mà nó thông báo lượt đánh hiện tại là O thì nghĩa là quân cờ gần nhất trước đó đang là X
			{
				textcolor(14 + 32); // màu viền background đại ý cho quân cờ trước đó chính là quân cờ vừa đánh
				cout << "X"; // In ra quân cờ gần nhất trước đó là X
				textcolor(7); // trở lại màu bình thường
			}
		}
		else // khi stack đã rỗng thì cho dấu nháy nhảy đến ngay ô cuối cùng vừa xóa đi đó chứ không để dấu nháy nằm ngay dòng thông báo lượt đi hiện tại ...
		{
			// Cho dấu nháy nhảy lại đến ô mà ta vừa Undo đi để đứng ở đó
			// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
			DanhTheoDuongGiaoDiemDongCot == false ? 
				// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
				gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

				// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
				gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);
		}
	}
}

void ChucNang_Redo(stack<TOADO> &stack_redo, stack<TOADO> &stack_undo, int &toado_dong, int &toado_cot, char &quanco, bool DanhTheoDuongGiaoDiemDongCot, bool &luotdi, int vitriXbandau, int vitriYbandau, int doronggiua2dong, int doronggiua2cot, char a[MAX][MAX], int &DemSoLuongQuanCoDaDanh, int &temp_toado_dong, int &temp_toado_cot, int sodong, int DoDaiNoiDungThongBao)
{
	if(!stack_redo.empty()) // stack_redo.empty() == false
	{
		TOADO td = stack_redo.top();
		stack_redo.pop();

		// Gán luôn tọa độ lấy ra từ ngăn xếp stack_redo qua cho 2 biến tọa độ dòng - cột để bất kỳ lúc nào chúng ta muốn điều hướng phím di chuyển dấu nháy thì nó đều di chuyển đúng từ vị trí hiện tại đang đứng
		toado_dong = td.toado_dong;
		toado_cot = td.toado_cot;

		// Đánh quân cờ xuống vị trí td.toado_dong, td.toado_cot => có nghĩa là làm công việc giống như khi chúng ta nhấn vào phím space hay enter để đánh cờ
		// => mượn lại 1 số đoạn code có liên quan của việc đánh cờ khi nhấn phím space hay enter
		quanco = luotdi == true ? 'X' : 'O'; // toán tử 3 ngôi dùng thay vì viết if

		// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
		DanhTheoDuongGiaoDiemDongCot == false ? 
			// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
			gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

			// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
			gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

		luotdi == true ? textcolor(14 + 32) : textcolor(12 + 32); // 14 là màu vàng, 12 là màu đỏ. Và cứ cách 16 đơn vị sẽ là 1 background màu khác
		cout << quanco;
		textcolor(7); // trả lại màu bình thường

		a[toado_dong][toado_cot] = quanco; // cập nhật lại trên mảng a

		// Đưa vị trí tọa độ quân cờ vừa đánh đó vào trong stack_undo để lưu trữ lại
		stack_undo.push(td);

		DemSoLuongQuanCoDaDanh++; // Đếm tổng số lượng quân cờ đã đánh xuống để biết có hết bàn cờ chưa?

		// Cho nó nhảy đến ô tương ứng với tọa độ vừa đánh trước đó để xóa đi viền background nổi bật quân cờ cho trở lại như thường
		if(temp_toado_dong != -1 && temp_toado_cot != -1)
		{
			// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
			DanhTheoDuongGiaoDiemDongCot == false ? 
				// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
				gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + temp_toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + temp_toado_dong * (doronggiua2dong + 1)) :

				// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
				gotoxy(temp_toado_cot * (doronggiua2cot + 1) + vitriXbandau, temp_toado_dong * (doronggiua2dong + 1) + vitriYbandau);

			if(quanco == 'X') // Nếu nước hiện tại vừa đánh xong là X thì nước trước đó phải là O
			{
				textcolor(12); // màu đỏ
				cout << "O";
			}
			else // Nếu nước hiện tại vừa đánh xong là O thì nước trước đó phải là X
			{
				textcolor(14); // màu vàng
				cout << "X"; 
			}
			textcolor(7); // cho trở lại màu bình thường
		}

		// Sau khi đã bỏ viền background nổi bật của nước trước đó thì cập nhật lại biến temp_toado_dong, temp_toado_cot theo tọa độ của nước vừa được đánh để tiếp tục nước đánh tiếp theo lại có dữ kiện để mà xét
		temp_toado_dong = toado_dong;
		temp_toado_cot = toado_cot;

		luotdi = !luotdi; // phủ định của chính nó rồi gán lại cho nó để cứ luân phiên: true - false - true - false

		// Xuất lại câu thông báo về lượt đi tiếp theo là của quân cờ nào
		//gotoxy(vitriXbandau, (doronggiua2dong + 1) * sodong + vitriYbandau + 1); // Nhảy đến dòng dưới cùng của bàn cờ
		//gotoxy((doronggiua2cot + 1) * socot + vitriXbandau + 1, vitriYbandau); // Dấu nháy sẽ nằm ở dòng đầu tiên bên cạnh cột cuối cùng của bàn cờ
		//cout << "Luot di hien tai la cua quan co: ";

		// Không cần phải xuất lại nội dung "Luot di hien tai la cua quan co: " mà chỉ cần nhảy đến cột x tương ứng để xuất ra quân cờ mới thôi.
		gotoxy(vitriXbandau + DoDaiNoiDungThongBao, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 1); // Nhảy đến dòng dưới cùng của bàn cờ
		if(luotdi == true)
		{
			quanco = 'X';
			textcolor(14); // màu vàng
		}
		else
		{
			quanco = 'O';
			textcolor(12); // màu đỏ
		}
		cout << quanco;
		textcolor(7); // trả lại màu bình thường

		// Nhảy lại đứng ngay vị trí ô vừa đánh
		// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
		DanhTheoDuongGiaoDiemDongCot == false ? 
			// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
			gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

			// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
			gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);
	}
}

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit (LPSTR lpszMessage) 
{ 
    fprintf(stderr, "%s\n", lpszMessage); 

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0); 
}

// Nếu hàm trả về true thì mình sẽ cho nó break trong vòng lặp diễn hoạt game, còn mặc định hàm sẽ trả về false
bool ThongBaoViTriDanhKhongHopLe(string NoiDungThongBao, int vitriXbandau, int doronggiua2dong, bool DanhTheoDuongGiaoDiemDongCot, int sodong, int socot, int vitriYbandau, int ThoiGianQuyDinhChoMoiNuocDanh, int &temp_ThoiGianQuyDinhChoMoiNuocDanh, int doronggiua2cot, int DoDaiNoiDungThongBaoThoiGianConLai, int toado_dong, int toado_cot, char quanco)
{
	// Hiện câu thông báo vị trí đánh không hợp lệ do đã có quân cờ và được nhấp nháy
	for(int i = 1; i <= 15; ++i)
	{
		gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
		textcolor(i);
		//cout << "Vi tri nay da co quan co ton tai nen khong danh duoc"; // In ra câu thông báo lỗi
		cout << NoiDungThongBao;
		Sleep(100); // Dừng 1/10 giây

		/* Để đề phòng trường hợp người chơi lợi dụng vô tính năng thông báo vị trí này đã có quân cờ được đánh để cứ giam cầm trong vòng lặp này mãi 
		dẫn đến thời gian bị đứng lại không giảm đi được => có 2 giải pháp sau
		Giải pháp 1: Tách biệt luồng chạy của việc tính thời gian ra 1 luồng riêng chứ không chạy chung trong luồng xử lý game 
		=> nghiên cứu từ khóa: Đa luồng trong C/C++ (tiếng Anh là: Multi Threading in C/C++)

		Giải pháp 2: Bản chất quân cờ nó nằm lồ lộ ra đó có thằng đui mới đánh vào ô đã có quân cờ, mà đui nặng mới đánh nhiều lần liên 
		=> thằng này tính chơi gian lận => quy định nếu cố tình đánh vào ô đã có quân cờ liên tục kéo dài thời gian nếu vi phạm 5 lần sẽ bị xử thua luôn
		=> game mình tạo cho nên luật mình đưa ra có gì phải ngại

		Giải pháp 3: Vẫn có cách để kể cả nó có liên tục hiện ra thông báo chỗ này đã có quân cờ thì thời gian vẫn cứ thế giảm xuống. 
		=> Cách này này được trình bày ở dưới đây:
		*/
		if(i == 10) // Khi i = 10 tức là đã 10 lần Sleep(100) <=> Sleep(1000) => đủ 1 giây chờ => giảm thời gian xuống 1 giây
		{
			if(ThoiGianQuyDinhChoMoiNuocDanh > 0) // Nếu có tính thời gian thì mới đi xử lý
			{
				temp_ThoiGianQuyDinhChoMoiNuocDanh--; // sau đó giảm thời gian đi 1 đơn vị


				// In ra lại thời gian còn lại
				gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1 + DoDaiNoiDungThongBaoThoiGianConLai, vitriYbandau + 3);
				textcolor(12);
				cout << temp_ThoiGianQuyDinhChoMoiNuocDanh << " "; // Luôn in ra thêm 1 khoảng trắng để bù đi phần chênh lệch giữa số đã in ra trước đó vd: trước đó là 10, sau đó là 9 thì phải in ra 1 khoảng trắng như vậy để xóa đi ký tự 0
				textcolor(7);

				// Nếu thời gian về 0 thì thoát ra khỏi vòng lặp in màu báo vị trí đánh đã có quân cờ vì lúc này nó đã thua rồi nên thoát ra không cần in ra thông báo đó nữa để chạy ra ngoài vòng lặp gặp cái if tương tự sẽ kết thúc game
				if(temp_ThoiGianQuyDinhChoMoiNuocDanh == 0)
				{
					break;
				}
			}
		}
	}

	// 1 giây rưỡi sau sẽ tự động mất đi
	//Sleep(1000);
	gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
	textcolor(7); // trở lại màu bình thường
	//cout << "                                                              ";
	int length = NoiDungThongBao.length();
	for(int i = 1; i <= length; ++i)
		cout << " ";

	// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
	DanhTheoDuongGiaoDiemDongCot == false ? 
		// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
		gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

		// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
		gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

	// Đã hết thời gian và kết luận người chơi ở lần đánh hiện tại đã bị thua và người chơi đối thủ thắng
	if(temp_ThoiGianQuyDinhChoMoiNuocDanh == 0)
	{
		for(int k = 1; k <= 15; ++k)
		{
			/* Đoạn code để cho chữ chạy từ lề trái qua phải in ra màn hình nội dung thông báo chiến thắng */
			// Nhảy đến vị trí x bắt đầu xuất ra chữ của lần trước đó để lấp đi nội dung bằng khoảng trống để không bị in ra dư
			gotoxy(vitriXbandau + (k - 1) * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
			cout << "                                 "; // lấp đi bằng khoảng trống

			// Với mỗi mã màu k chạy từ 1 tới 15 thì nó dựa theo mã màu k tương ứng trong mỗi lần lặp để tạo ra 1 vị trí xuất hiện x mới của chữ nội dung xuất ra màn hình từ đó chữ sẽ chạy từ lề trái qua lề phải
			gotoxy(vitriXbandau + k * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
			textcolor(k);
			//cout << quanco << " da chien thang";
			cout << "Vi da het thoi gian nen " << quanco << " da thua va " << (quanco == 'X' ? "O" : "X") << " da chien thang";

			// Để mỗi lần lặp qua đơn vị màu mới nó có 1 khoảng độ dừng lại để còn tạo ra hiệu ứng nhấp nháy chứ nếu không nó chạy 1 cái lèo là xong
			Sleep(200);
		}
		return true; // Thoát khỏi vòng lặp diễn hoạt game
	}
	return false; // Game vẫn tiếp tục
}


void XuLyGameTheoHuongDungPhim(char a[MAX][MAX], stack<TOADO> &stack_undo, stack<TOADO> &stack_redo, int sodong, int socot, int doronggiua2cot, int doronggiua2dong, int vitriXbandau, int vitriYbandau, bool DanhTheoDuongGiaoDiemDongCot, int SoQuanCoGiongNhauLienTiepToiThieuDeThang, bool KichHoatCheDoChan2DauLaKhongChoThang, int ThoiGianQuyDinhChoMoiNuocDanh, bool KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi, int TongThoiGianDanhCoCuaNguoiChoiQuanCoX, int TongThoiGianDanhCoCuaNguoiChoiQuanCoO, bool LuotDiBanDau, bool KichHoatCheDoLoapMap)
{
	// Nếu muốn đánh quân cờ nằm bên trong từng ô thì độ rộng giữa 2 cột và độ rộng giữa 2 dòng tối thiểu phải là 1. 
	// Và tốt nhất nên là số lẻ để quân cờ khi đánh được cách đều 2 bên (trái - phải) - (trên - dưới)
	if(DanhTheoDuongGiaoDiemDongCot == false) // đánh trong ô
	{
		if(doronggiua2dong < 1)
			doronggiua2dong = 1;

		if(doronggiua2cot < 1)
			doronggiua2cot = 1;

		if(doronggiua2dong % 2 == 0)
			doronggiua2dong++; // lẻ

		if(doronggiua2cot % 2 == 0)
			doronggiua2cot++; // lẻ
	}
	else // đánh theo giao điểm dòng cột: độ rộng giữa 2 dòng, 2 cột miễn từ 0 trở lên là được hết và có là số lẻ hay số chẵn cũng không quan tâm
	{
		if(doronggiua2dong < 0)
			doronggiua2dong = 0;

		if(doronggiua2cot < 0)
			doronggiua2cot = 0;
	}


	// Lường trước tình huống có thể xảy ra nếu như chọn đánh theo chế độ giao điểm dòng cột thì nếu số dòng hay số cột chạm đến mức tối đa khai báo của mảng thì ta chủ động giảm số dòng, giảm số cột xuống 1 đơn vị
	if(DanhTheoDuongGiaoDiemDongCot == true)
	{
		if(sodong == MAX)
			sodong--;

		if(socot == MAX)
			socot--;
	}

	bool luotdi = LuotDiBanDau; // Nếu là true tức là X đi trước, false tức là O đi trước

	// Xác định lượt đi tiếp theo nếu là số chẵn thì phải là phủ định lại của lượt đi ban đầu
	//if((DemSoLuongQuanCoDaDanh + 1) % 2 == 0)
		//luotdi = !LuotDiBanDau;


	char quanco;


	VeBanCo_NangCao(sodong, socot, doronggiua2cot, doronggiua2dong, vitriXbandau, vitriYbandau);

	// Công thức này phải để nằm sau hàm vẽ bàn cờ bởi vì bàn cờ yêu cầu kích thước bao nhiêu ban đầu thì sẽ vẽ ra đúng như vậy, chẳng qua là nếu xét đánh theo các đường giao điểm dòng - cột thì sẽ phát sinh thêm 1 đường dòng, thêm 1 đường cột cho nên ta chủ động tăng số dòng, tăng số cột thêm 1 đơn vị để thỏa mãn
	if(DanhTheoDuongGiaoDiemDongCot == true)
	{
		sodong++;
		socot++;
	}

	
	// Trước khi đi vào vòng lặp chơi game thì mình sẽ in ra luật chơi đã chọn từ đầu ở bên hông của bàn cờ để người chơi nhìn vào mà nhớ
	gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau); // Dấu nháy sẽ nằm ở dòng đầu tiên bên cạnh cột cuối cùng của bàn cờ
	cout << "So luong quan co lien tiep toi thieu de chien thang: ";
	textcolor(12);
	cout << SoQuanCoGiongNhauLienTiepToiThieuDeThang;
	textcolor(7);

	gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 1); // Dấu nháy sẽ nằm ở dòng dưới dòng thông báo trước đó
	cout << SoQuanCoGiongNhauLienTiepToiThieuDeThang << " quan co lien tiep nhung bi chan 2 dau thi co thang khong: ";
	textcolor(12);
	cout << (KichHoatCheDoChan2DauLaKhongChoThang == true ? "Khong" : "Co"); 
	textcolor(7);

	string NoiDungThongBaoThoiGianConLai;
	int DoDaiNoiDungThongBaoThoiGianConLai = 0;
	int dem_Sleep = 0; // Mục đích để đếm số lần Sleep xảy ra đạt bao nhiêu lần thì mới giảm đi 1 giây (vd: Nếu để Sleep(250) thì 4 lần như vậy thì mới giảm 1 giây)
	int temp_ThoiGianQuyDinhChoMoiNuocDanh = ThoiGianQuyDinhChoMoiNuocDanh; // Biến này lưu thời gian quy định cho mỗi nước đánh và cứ liên tục giảm đi 1 giây. Mục đích lưu ra 1 biến phụ là để giữ nguyên được giá trị ban đầu của biến thời gian quy định
	
	// Biến này là 1 số dương => Có tính thời gian cho mỗi nước đánh => in ra dòng thông báo là có tính thời gian cho mỗi nước đánh và có nói cụ thể là bao nhiêu luôn
	if(ThoiGianQuyDinhChoMoiNuocDanh > 0)
	{
		gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 2);
		cout << "Thoi gian toi da cho moi nuoc danh la: ";

		textcolor(12);
		cout << ThoiGianQuyDinhChoMoiNuocDanh;
		textcolor(7);
		cout << " giay";

		gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 3);
		NoiDungThongBaoThoiGianConLai = "Thoi gian con lai la: ";
		DoDaiNoiDungThongBaoThoiGianConLai = NoiDungThongBaoThoiGianConLai.length();
		cout << NoiDungThongBaoThoiGianConLai;
		textcolor(12);
		cout << ThoiGianQuyDinhChoMoiNuocDanh;
		textcolor(7);

		temp_ThoiGianQuyDinhChoMoiNuocDanh = ThoiGianQuyDinhChoMoiNuocDanh;

		gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 4);
		cout << "Co tinh tong thoi gian danh ra co cua moi nguoi choi khong? ";
		textcolor(12);
		cout << (KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi == true ? "Co" : "Khong");
		textcolor(7);
	}

	//int vitrixbandaucuabanco = 1, vitriybandaucuabanco = 1; // vị trí ban đầu của góc trên cùng bên trái của bàn cờ

	bool Play = true; // Mặc định là true tức là chế độ Play, nếu nó là false tức là chế độ Pause => Chỉ áp dụng khi có tính thời gian
	
	int DemSoLuongQuanCoDaDanh = 0; // Để biết được khi nào đã hết bàn cờ. Nếu là New Game thì biến này = 0, nếu là Load Map thì biến sẽ có giá trị khác tuy nhiên nó vẫn cứ khởi tạo ban đầu là 0 để rồi đi vào bước mà tái hiện lại quân cờ trên bàn cờ nhờ vào tính năng Redo thì trong hàm Redo đó nó đã có tăng biến này lên. // Đếm số lượng các quân cờ hợp lệ đánh xuống. Mục đích là để đi kiểm tra xem khi nào bàn cờ đã hết không còn chỗ để đánh nữa và cũng chưa có ai thắng thì kết luận ván cờ hòa
	
	// Mặc định khi New Game thì nó có giá trị thế này, tuy nhiên nếu là Load Map thì nó sẽ có giá trị khác. Và nó có giá trị khác là khi đi vào trong hàm chức năng redo nó sẽ cập nhật lại giá trị các biến này
	int toado_dong = 0, toado_cot = 0; // Mục đích để khi bắt đầu quá trình diễn hoạt game thì dấu nháy đầu tiên sẽ nằm ở tọa độ này
	int temp_toado_dong = -1, temp_toado_cot = -1; // Mục đích để lưu lại tọa độ của nước vừa đánh để khi đánh sang nước mới nó sẽ đi xóa viền background của nước vừa đánh trước đó
	

	// Dấu nháy sẽ nhảy đến vị trí tọa độ thích hợp để in ra câu thông báo
	gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 1); // Dấu nháy sẽ nằm ở dòng dưới cùng của bàn cờ
	//gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau); // Dấu nháy sẽ nằm ở dòng đầu tiên bên cạnh cột cuối cùng của bàn cờ
	cout << "Luot di hien tai la cua quan co: ";
	string NoiDungThongBao = "Luot di hien tai la cua quan co: ";
	int DoDaiNoiDungThongBao = NoiDungThongBao.length();

	quanco = luotdi == true ? 'X' : 'O'; // toán tử 3 ngôi dùng thay vì viết if
	luotdi == true ? textcolor(14) : textcolor(12); // 14 là màu vàng, 12 là màu đỏ. Và cứ cách 16 đơn vị sẽ là 1 background màu khác
	cout << quanco;
	textcolor(7); // trả lại màu bình thường
	
	// Nếu là chế độ Load Map thì chúng ta sẽ đi in ra hết tất cả các quân cờ mà người dùng đã đánh và đã được lưu lại => Nhờ vào tính năng Redo để làm điều này (giống như chế độ Play/Pause mà chúng ta đã tận dụng trước đó)
	if(KichHoatCheDoLoapMap == true)
	{
		while(!stack_redo.empty())
		{
			ChucNang_Redo(stack_redo, stack_undo, toado_dong, toado_cot, quanco, DanhTheoDuongGiaoDiemDongCot, luotdi, vitriXbandau, vitriYbandau, doronggiua2dong, doronggiua2cot, a, DemSoLuongQuanCoDaDanh, temp_toado_dong, temp_toado_cot, sodong, DoDaiNoiDungThongBao);
		}

		// Kiểm tra xem là có đang tính thời gian cho mỗi nước đánh cờ hay không? Nếu có thì tạm cho bàn cờ dừng lại khoảng tầm 10 giây để người đánh ở lượt đó có thời gian chiêm nghiệm lại ván cờ trước đó
		int ThoiGianChoPhepXemLaiBanCoTruocKhiBatDauTinhThoiGianMoiNuocDanh = 5; // tính theo giây

		gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 6);
		cout << "Ngay khi nao Ban muon danh co thi nhan Enter hay Space de choi";
		for(int t = ThoiGianChoPhepXemLaiBanCoTruocKhiBatDauTinhThoiGianMoiNuocDanh; t > 0; --t)
		{
			gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 5);
			cout << "Ban co thoi gian la ";
			textcolor(12);
			cout << t;
			textcolor(7);
			cout << " giay de xem lai ban co truoc khi bat dau.";
			Sleep(1000); // Dừng lại 1 giây

			if(kbhit())
			{
				char x = getch();
				if(x == 32 || x == 13)
					break;
			}
		}
		// Nhảy lại vị trí dòng thông báo để xóa đi
		gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 5);
		cout << "                                                               ";
		gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 6);
		cout << "                                                              ";
	}

	

	// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
	DanhTheoDuongGiaoDiemDongCot == false ? 
		// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
		gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

		// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
		gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

	INPUT_RECORD InputRecord;
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events, fdwMode;

	// Tự động tắt chế độ Quick Edit Mode nếu đang được bật để từ đó có thể bắt sự kiện chuột được
	/* 
       Step-1:
       Disable 'Quick Edit Mode' option
    */
	fdwMode = ENABLE_EXTENDED_FLAGS;
       if (! SetConsoleMode(hin, fdwMode) )
           ErrorExit("SetConsoleMode");

	    /* 
       Step-2:
       Enable the window and mouse input events,
       after you have already applied that 'ENABLE_EXTENDED_FLAGS'
       to disable 'Quick Edit Mode'
    */
    // Enable the window and mouse input events. 
 
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT; 
    if (! SetConsoleMode(hin, fdwMode) ) 
        ErrorExit("SetConsoleMode");

	while(true) // vòng lặp vô tận tạo diễn hoạt cho game
	{
		// Phải có if này để lồng tất cả xử lý chuột vô bên trong để chương trình không bị dừng lại ngay dòng lệnh ReadConsoleInput mà nó sẽ chạy các dòng lệnh đang có trong while(true) để đi tính thời gian hay có thể đi xử lý bắt key từ bàn phím với kbhit hay sau này có 1 số tác vụ gì đó khác nữa ...
		if(GetAsyncKeyState(VK_LBUTTON)) // Left mouse button
		{
			//cout << "HELLO WORLD!";
			ReadConsoleInput(hin, &InputRecord, 1, &Events);

			//if(InputRecord.EventType == MOUSE_EVENT) // Nhận biết được có thao tác gì đó với chuột => có thể bỏ đi vì đã xét sự kiện if đầu tiên rồi
			if(InputRecord.Event.MouseEvent.dwEventFlags == 0) // Để tránh trường hợp người dùng nhấn chuột xuống sau đó kéo di chuyển thì nó sẽ phát sinh sự kiện liên tục thì không đúng. Mình chỉ muốn nhấn xuống 1 cái thì phát sinh sự kiện sau đó có làm gì đi nữa thì cũng không có gì xảy ra thêm. Chỉ mỗi lần nhấn xuống thì mới xảy ra sự kiện
			{
				// Lẽ ra theo logic thì ta có thể bỏ qua cái if này do cái if(GetAsyncKeyState(VK_LBUTTON)) vốn dĩ đã thỏa rồi tuy nhiên trong quá trình vận hành ta thấy nếu bỏ dòng if này đi thì ở lần click đầu tiên nó bị in ra đến 3 lần tọa độ khác nhau => giữ lại cái if này
				if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					// Tọa độ x, y của con trỏ chuột khi click xuống
					int x = InputRecord.Event.MouseEvent.dwMousePosition.X + 1;
					int y = InputRecord.Event.MouseEvent.dwMousePosition.Y + 1;

					// Xét tính hợp lệ của vị trí click chuột xem có nằm trong bàn cờ không?
					if((x >= vitriXbandau && x <= (DanhTheoDuongGiaoDiemDongCot == true ? socot - 1 : socot) * (doronggiua2cot + 1) + vitriXbandau)
						&& (y >= vitriYbandau && y <= (DanhTheoDuongGiaoDiemDongCot == true ? sodong - 1 : sodong) * (doronggiua2dong + 1) + vitriYbandau))
					{
						// Nếu click trong phạm vi bàn cờ thì tùy theo chế độ đánh mà sẽ có tính hợp lệ khác nhau:
						
						// Nếu đang là chế độ đánh trong từng ô: Thì hợp lệ là khi click trong phạm vi của từng ô, còn các vị trí khác đều không hợp lệ
						if(DanhTheoDuongGiaoDiemDongCot == false)
						{
							// vị trí x - 1 nếu không chia hết cho (doronggiua2cot + 1) thì vị trí đó thỏa mãn là nằm bên trong của ô
							// tương tự như vậy với y: nếu vị trí y - 1 không chia hết cho (doronggiua2dong + 1) thì vị trí đó thỏa mãn là nằm bên trong của ô
							if(((x - vitriXbandau) % (doronggiua2cot + 1) != 0) && ((y - vitriYbandau) % (doronggiua2dong + 1) != 0))
							{
								// Công thức tự nhận ra và kiểm nghiệm qua các trường hợp ví dụ đều đúng và đem áp dụng
								toado_cot = (x - vitriXbandau) / (doronggiua2cot + 1);
								toado_dong = (y - vitriYbandau) / (doronggiua2dong + 1);

								goto DanhCoXuongBanCo; // Function(abc)

								// Tự động nhấn đến phím Enter để từ đó chương trình tự động chạy đến đoạn code xử lý khi nhấn Enter mà ta đã có sẵn
								/*keybd_event(VK_RETURN, 0, 0, 0); 
								keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);*/

							}
							else
							{
								// Vị trí đánh không nằm trong 1 ô
								string ThongBao = "Vi tri danh co khong hop le do khong nam trong o";
								bool KetThuc = ThongBaoViTriDanhKhongHopLe(ThongBao, vitriXbandau, doronggiua2dong, DanhTheoDuongGiaoDiemDongCot, sodong, socot, vitriYbandau, ThoiGianQuyDinhChoMoiNuocDanh, temp_ThoiGianQuyDinhChoMoiNuocDanh, doronggiua2cot, DoDaiNoiDungThongBaoThoiGianConLai, toado_dong, toado_cot, quanco);
					
								if(KetThuc == true)
									break; // Thoát khỏi vòng lặp diễn hoạt game
							}
						}
						// Nếu đang là chế độ đánh theo giao điểm dòng cột: Thì hợp lệ là khi click vào 4 góc trái trên, phải trên, trái dưới, phải dưới của 1 ô, còn các vị trí khác đều không hợp lệ
						else // Chế độ đánh theo giao điểm dòng cột
						{
							if(((x - vitriXbandau) % (doronggiua2cot + 1) == 0) && ((y - vitriYbandau) % (doronggiua2dong + 1) == 0))
							{
								// Công thức tự nhận ra và kiểm nghiệm qua các trường hợp ví dụ đều đúng và đem áp dụng
								toado_cot = (x - vitriXbandau) / (doronggiua2cot + 1);
								toado_dong = (y - vitriYbandau) / (doronggiua2dong + 1);

								goto DanhCoXuongBanCo;

								// Tự động nhấn đến phím Enter để từ đó chương trình tự động chạy đến đoạn code xử lý khi nhấn Enter mà ta đã có sẵn
								/*keybd_event(VK_RETURN, 0, 0, 0); 
								keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);*/
							}
							else
							{
								// Vị trí đánh không nằm trong 1 ô
								string ThongBao = "Vi tri danh co khong hop le do khong nam ngay giao diem dong cot";
								bool KetThuc = ThongBaoViTriDanhKhongHopLe(ThongBao, vitriXbandau, doronggiua2dong, DanhTheoDuongGiaoDiemDongCot, sodong, socot, vitriYbandau, ThoiGianQuyDinhChoMoiNuocDanh, temp_ThoiGianQuyDinhChoMoiNuocDanh, doronggiua2cot, DoDaiNoiDungThongBaoThoiGianConLai, toado_dong, toado_cot, quanco);
					
								if(KetThuc == true)
									break; // Thoát khỏi vòng lặp diễn hoạt game
							}
						}
					}
					else
					{
						// Vị trí đánh ngoài bàn cờ
						string ThongBao = "Vi tri danh co khong hop le do nam ngoai ban co";
						bool KetThuc = ThongBaoViTriDanhKhongHopLe(ThongBao, vitriXbandau, doronggiua2dong, DanhTheoDuongGiaoDiemDongCot, sodong, socot, vitriYbandau, ThoiGianQuyDinhChoMoiNuocDanh, temp_ThoiGianQuyDinhChoMoiNuocDanh, doronggiua2cot, DoDaiNoiDungThongBaoThoiGianConLai, toado_dong, toado_cot, quanco);
					
						if(KetThuc == true)
							break; // Thoát khỏi vòng lặp diễn hoạt game
					}
				}
			}
			// Lưu ý: Dòng này chỉ gọi tới khi sử dụng chuột nên phải để nó ở bên trong cái if này chứ nếu để ra bên ngoài vòng lặp while(true) thì lại không dùng phím được
			FlushConsoleInputBuffer(hin); // Phải có dòng lệnh này để nó xóa đi bộ đệm chỉ tính ở ngay lần nhấn hiện tại tránh trường hợp nhấn chuột liên tục lúc thông báo lỗi để rồi hết bị lỗi thì nhấn lại vào 1 vị trí khác nó lại đem dữ liệu vị trí cũ trước đó đã nhấn trong lúc thông báo lỗi
		}

		/* So sánh giữa 2 cách bắt key từ bàn phím thì ta thấy cách dùng getch nó không bị độ trễ và không bị quá nhạy như hàm GetAsyncKeyState
		=> Nên dùng getch */
		if(kbhit()) // nhận biết được có tương tác từ bàn phím
		{
			char c = getch(); // chờ nhận vào 1 phím từ bàn phím

			if(c == -32) // Đối với các phím chức năng nó sẽ xử lý ra -32 trước thì mính bắt theo điều kiện này để phân biệt được với phím in ra được
			{
				c = getch();
				if(c == 77) // Right
				//if(GetAsyncKeyState(VK_RIGHT))
				{
					if(toado_cot < socot - 1)
						toado_cot++;
				}
				else if(c == 75) // Left
				//else if(GetAsyncKeyState(VK_LEFT))
				{
					if(toado_cot > 0)
						toado_cot--;
				}
				else if(c == 72) // Up
				//else if(GetAsyncKeyState(VK_UP))
				{
					if(toado_dong > 0)
						toado_dong--;
				}
				else if(c == 80) // Down
				//else if(GetAsyncKeyState(VK_DOWN))
				{
					if(toado_dong < sodong - 1)
						toado_dong++;
				}
				// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
				DanhTheoDuongGiaoDiemDongCot == false ? 
					// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
					gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

					// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
					gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);
			}
			else if(c == 'a' || c == 'A' || c == 'd' || c == 'D' || c == 'w' || c == 'W' || c == 's' || c == 'S') // Đây là những phím điều hướng con trỏ chuột
			//if(GetAsyncKeyState(0x41) || GetAsyncKeyState(0x44) || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x53))
			{
				if(c == 'a' || c == 'A') // Left
				//if(GetAsyncKeyState(0x41))
				{
					if(toado_cot > 0)
						toado_cot--;
				}
				else if(c == 'd' || c == 'D') // Right
				//else if(GetAsyncKeyState(0x44))
				{
					if(toado_cot < socot - 1)
						toado_cot++;
				}
				else if(c == 'w' || c == 'W') // Up
				//else if(GetAsyncKeyState(0x57))
				{
					if(toado_dong > 0)
						toado_dong--;
				}
				else if(c == 's' || c == 'S') // Down
				//else if(GetAsyncKeyState(0x53))
				{
					if(toado_dong < sodong - 1)
						toado_dong++;
				}
				// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
				DanhTheoDuongGiaoDiemDongCot == false ? 
					// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
					gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

					// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
					gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);
			}
			else if(c == 32 || c == 13) // Space & Enter để đánh cờ
			//else if(GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_RETURN))
			{
DanhCoXuongBanCo: // Nhãn để khi sử dụng chuột đánh cờ thì sẽ nhảy đến nhãn này và bắt đầu thực hiện nội dung từ đây trở xuống
				quanco = luotdi == true ? 'X' : 'O'; // toán tử 3 ngôi dùng thay vì viết if

				if(a[toado_dong][toado_cot] == ' ') // vị trí này chưa có quân cờ nên có thể đánh được
				{
					// Tính năng redo chỉ sử dụng nếu trước đó người dùng chọn tính năng Undo thì ngay lập tức có thể Redo lại được, tuy nhiên để tránh trường hợp nếu trước đó người dùng chọn tính năng Undo thì dữ liệu các nước vừa bị Undo sẽ được đưa qua stack_redo và lưu lại rồi nếu người dùng lại đánh cờ ở 1 vị trí khác hay chính vị trí mà người dùng đã undo trước đó rồi sau đó lại gọi đến tính năng Redo thì như vậy nó sẽ bị rối loạn chương trình hết lên. Cho nên chúng ta quy tắc rằng nếu người dùng vừa chọn tính năng Undo mà sau đó chọn liền tính năng Redo thì cho phép chứ nếu người dùng đã đánh ra cờ thì toàn bộ dữ liệu lưu trong Redo sẽ bị xóa hết để tránh lỗi xảy ra
					while(!stack_redo.empty())
					{
						stack_redo.pop();
					}

					if(ThoiGianQuyDinhChoMoiNuocDanh > 0) // Phải có kích hoạt chế độ tính thời gian cho mỗi nước đánh thì mới có thể sử dụng tính năng tính tổng thời gian để đánh ra cờ của mỗi người chơi
					{
						if(KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi == true)
						{
							int ThoiGianDanhCo = ThoiGianQuyDinhChoMoiNuocDanh - temp_ThoiGianQuyDinhChoMoiNuocDanh;

							// Bởi vì để thời gian bắt đầu tính lại từ ban đầu trở về thì biến temp_ThoiGianQuyDinhChoMoiNuocDanh mình cho nó = ThoiGianQuyDinhChoMoiNuocDanh cộng thêm 1 dẫn tới nếu người chơi đánh liên tục sát nhau thì khi trừ nhau giữa ThoiGianQuyDinhChoMoiNuocDanh và temp_ThoiGianQuyDinhChoMoiNuocDanh sẽ bị ra -1 => xét nếu là số âm thì cho nó = 0 luôn
							if(ThoiGianDanhCo < 0)
								ThoiGianDanhCo = 0;

							// Xử lý lấy thời gian mà quân cờ vừa đánh ra trước dòng bên dưới nó bị reset lại về ban đầu
							if(quanco == 'X')
							{
								TongThoiGianDanhCoCuaNguoiChoiQuanCoX += ThoiGianDanhCo;
								//gotoxy(vitriXbandau, (doronggiua2dong + 1) * sodong + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
								//cout << "Quan co X vua danh mat " << ThoiGianDanhCo << " giay";
							}
							else
							{
								TongThoiGianDanhCoCuaNguoiChoiQuanCoO += ThoiGianDanhCo;
								//gotoxy(vitriXbandau, (doronggiua2dong + 1) * sodong + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
								//cout << "Quan co O vua danh mat " << ThoiGianDanhCo << " giay";
							}
						}

						temp_ThoiGianQuyDinhChoMoiNuocDanh = ThoiGianQuyDinhChoMoiNuocDanh + 1; // Cứ với mỗi nước đánh cờ mới thì lại cập nhật lại biến temp_ThoiGianQuyDinhChoMoiNuocDanh thành giá trị mặc định ban đầu để chuẩn bị tiếp tục giảm 1 giây. Lý do cộng thêm 1 là bởi vì sau đó xét xuống nó lại giảm đi 1 và in ra bắt đầu từ 30
					}
				

					//gotoxy(vitriXbandau, (doronggiua2dong + 1) * sodong + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
					//cout << "                                                                      "; // In ra câu thông báo lỗi

					// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
					DanhTheoDuongGiaoDiemDongCot == false ? 
						// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
						gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

						// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
						gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

					luotdi == true ? textcolor(14 + 32) : textcolor(12 + 32); // 14 là màu vàng, 12 là màu đỏ. Và cứ cách 16 đơn vị sẽ là 1 background màu khác
					cout << quanco;
					textcolor(7); // trả lại màu bình thường

					a[toado_dong][toado_cot] = quanco; // cập nhật lại trên mảng a
					
					// Đưa vị trí tọa độ quân cờ vừa đánh đó vào trong stack_undo để lưu trữ lại
					TOADO td;
					td.toado_dong = toado_dong;
					td.toado_cot = toado_cot;
					stack_undo.push(td);
					
					DemSoLuongQuanCoDaDanh++; // Đếm tổng số lượng quân cờ đã đánh xuống để biết có hết bàn cờ chưa?

					// Cho nó nhảy đến ô tương ứng với tọa độ vừa đánh trước đó để xóa đi viền background nổi bật quân cờ cho trở lại như thường
					if(temp_toado_dong != -1 && temp_toado_cot != -1)
					{
						// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
						DanhTheoDuongGiaoDiemDongCot == false ? 
							// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
							gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + temp_toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + temp_toado_dong * (doronggiua2dong + 1)) :

							// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
							gotoxy(temp_toado_cot * (doronggiua2cot + 1) + vitriXbandau, temp_toado_dong * (doronggiua2dong + 1) + vitriYbandau);

						if(quanco == 'X') // Nếu nước hiện tại vừa đánh xong là X thì nước trước đó phải là O
						{
							textcolor(12); // màu đỏ
							cout << "O";
						}
						else // Nếu nước hiện tại vừa đánh xong là O thì nước trước đó phải là X
						{
							textcolor(14); // màu vàng
							cout << "X"; 
						}
						textcolor(7); // cho trở lại màu bình thường
					}

					// Đi kiểm tra xem quân cờ vừa đánh có chiến thắng chưa?

					if(KiemTraHangNgang(a, sodong, socot, toado_dong, toado_cot, SoQuanCoGiongNhauLienTiepToiThieuDeThang, KichHoatCheDoChan2DauLaKhongChoThang) != ' ')
					{
						for(int k = 1; k <= 15; ++k)
						{
							// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
							DanhTheoDuongGiaoDiemDongCot == false ? 
								// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
								gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1))
								:
								// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
								gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

							textcolor(k);
							cout << quanco;

							// Xét qua bên trái trước (ngang trái)
							for(int j = toado_cot - 1; j >= 0; --j)
							{
								if(a[toado_dong][j] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + j * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(j * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}
							}

							// Xét qua bên phải (ngang phải)
							for(int j = toado_cot + 1; j < socot; ++j)
							{
								if(a[toado_dong][j] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + j * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(j * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}
							}

							/* Đoạn code để cho chữ chạy từ lề trái qua phải in ra màn hình nội dung thông báo chiến thắng */
							// Nhảy đến vị trí x bắt đầu xuất ra chữ của lần trước đó để lấp đi nội dung bằng khoảng trống để không bị in ra dư
							gotoxy(vitriXbandau + (k - 1) * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							cout << "                                 "; // lấp đi bằng khoảng trống

							// Với mỗi mã màu k chạy từ 1 tới 15 thì nó dựa theo mã màu k tương ứng trong mỗi lần lặp để tạo ra 1 vị trí xuất hiện x mới của chữ nội dung xuất ra màn hình từ đó chữ sẽ chạy từ lề trái qua lề phải
							gotoxy(vitriXbandau + k * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							textcolor(k);
							cout << quanco << " da chien thang";

							// Để mỗi lần lặp qua đơn vị màu mới nó có 1 khoảng độ dừng lại để còn tạo ra hiệu ứng nhấp nháy chứ nếu không nó chạy 1 cái lèo là xong
							Sleep(200);
						}

						gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 3); // Nhảy đến dòng dưới dòng thông báo chiến thắng
						textcolor(7); // trả lại màu như bình thường

						break; // thoát ra khỏi vòng lặp diễn hoạt game
					}

					if(KiemTraHangDoc(a, sodong, socot, toado_dong, toado_cot, SoQuanCoGiongNhauLienTiepToiThieuDeThang, KichHoatCheDoChan2DauLaKhongChoThang) != ' ')
					{
						for(int k = 1; k <= 15; ++k)
						{
							// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
							DanhTheoDuongGiaoDiemDongCot == false ? 
								// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
								gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1))
								:
								// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
								gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

							textcolor(k);
							cout << quanco;

							// Xét lên trên trước (dọc trên)
							for(int i = toado_dong - 1; i >= 0; --i)
							{
								if(a[i][toado_cot] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + i * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, i * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}
							}

							// Xét xuống dưới (dọc dưới)
							for(int i = toado_dong + 1; i < sodong; ++i)
							{
								if(a[i][toado_cot] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + i * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, i * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}
							}

							/* Đoạn code để cho chữ chạy từ lề trái qua phải in ra màn hình nội dung thông báo chiến thắng */
							// Nhảy đến vị trí x bắt đầu xuất ra chữ của lần trước đó để lấp đi nội dung bằng khoảng trống để không bị in ra dư
							gotoxy(vitriXbandau + (k - 1) * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							cout << "                                 "; // lấp đi bằng khoảng trống

							// Với mỗi mã màu k chạy từ 1 tới 15 thì nó dựa theo mã màu k tương ứng trong mỗi lần lặp để tạo ra 1 vị trí xuất hiện x mới của chữ nội dung xuất ra màn hình từ đó chữ sẽ chạy từ lề trái qua lề phải
							gotoxy(vitriXbandau + k * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							textcolor(k);
							cout << quanco << " da chien thang";

							// Để mỗi lần lặp qua đơn vị màu mới nó có 1 khoảng độ dừng lại để còn tạo ra hiệu ứng nhấp nháy chứ nếu không nó chạy 1 cái lèo là xong
							Sleep(200);
						}

						gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 3); // Nhảy đến dòng dưới dòng thông báo chiến thắng
						textcolor(7); // trả lại màu như bình thường

						break; // thoát ra khỏi vòng lặp diễn hoạt game
					}

					if(KiemTraCheoChinh(a, sodong, socot, toado_dong, toado_cot, SoQuanCoGiongNhauLienTiepToiThieuDeThang, KichHoatCheDoChan2DauLaKhongChoThang) != ' ')
					{
						for(int k = 1; k <= 15; ++k)
						{
							// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
							DanhTheoDuongGiaoDiemDongCot == false ? 
								// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
								gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1))
								:
								// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
								gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

							textcolor(k);
							cout << quanco;

							// Kiểm tra chéo chính trên: Các phần tử dòng - cột luôn giảm 1 đơn vị và giảm đến khi nào 1 trong 2 thằng xuất hiện 0
							int i = toado_dong - 1;
							int j = toado_cot - 1;
							while(true)
							{
								if(i < 0 || j < 0)
								{
									break; // vị trí xét không hợp lệ
								}


								// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
								if(a[i][j] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + j * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + i * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(j * (doronggiua2cot + 1) + vitriXbandau, i * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}

								// Xét qua lần lặp mới
								i--;
								j--;
							}

							//	Kiểm tra chéo chính dưới: Các phần tử dòng - cột đều tăng lên 1 đơn vị và tăng đến khi nào 1 trong 2 thằng bằng n - 1 thì dừng lại
							i = toado_dong + 1;
							j = toado_cot + 1;
							while(true)
							{
								if(i == sodong || j == socot)
								{
									break; // vị trí xét không hợp lệ
								}

								// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
								if(a[i][j] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + j * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + i * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(j * (doronggiua2cot + 1) + vitriXbandau, i * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}

								// Xét qua lần lặp mới
								i++;
								j++;
							}

							/* Đoạn code để cho chữ chạy từ lề trái qua phải in ra màn hình nội dung thông báo chiến thắng */
							// Nhảy đến vị trí x bắt đầu xuất ra chữ của lần trước đó để lấp đi nội dung bằng khoảng trống để không bị in ra dư
							gotoxy(vitriXbandau + (k - 1) * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							cout << "                                 "; // lấp đi bằng khoảng trống

							// Với mỗi mã màu k chạy từ 1 tới 15 thì nó dựa theo mã màu k tương ứng trong mỗi lần lặp để tạo ra 1 vị trí xuất hiện x mới của chữ nội dung xuất ra màn hình từ đó chữ sẽ chạy từ lề trái qua lề phải
							gotoxy(vitriXbandau + k * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							textcolor(k);
							cout << quanco << " da chien thang";

							// Để mỗi lần lặp qua đơn vị màu mới nó có 1 khoảng độ dừng lại để còn tạo ra hiệu ứng nhấp nháy chứ nếu không nó chạy 1 cái lèo là xong
							Sleep(200);
						}

						gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 3); // Nhảy đến dòng dưới dòng thông báo chiến thắng
						textcolor(7); // trả lại màu như bình thường

						break; // thoát ra khỏi vòng lặp diễn hoạt game
					}

					if(KiemTraCheoPhu(a, sodong, socot, toado_dong, toado_cot, SoQuanCoGiongNhauLienTiepToiThieuDeThang, KichHoatCheDoChan2DauLaKhongChoThang) != ' ')
					{
						for(int k = 1; k <= 15; ++k)
						{
							// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
							DanhTheoDuongGiaoDiemDongCot == false ? 
								// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
								gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1))
								:
								// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
								gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);

							textcolor(k);
							cout << quanco;

							// Kiểm tra chéo phụ trên: Dòng giảm - cột tăng. Dòng giảm tối đa tới 0, Cột tăng tối đa nới n - 1
							int i = toado_dong - 1;
							int j = toado_cot + 1;
							while(true)
							{
								if(i < 0 || j == socot)
								{
									break; // vị trí xét không hợp lệ
								}


								// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
								if(a[i][j] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + j * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + i * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(j * (doronggiua2cot + 1) + vitriXbandau, i * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}

								// Xét qua lần lặp mới
								i--;
								j++;
							}

							//	Kiểm tra chéo phụ dưới: Dòng tăng - cột giảm. Dòng tăng tới tối đa là n - 1 và cột giảm tới tối đa là 0
							i = toado_dong + 1;
							j = toado_cot - 1;
							while(true)
							{
								if(i == sodong || j < 0)
								{
									break; // vị trí xét không hợp lệ
								}

								// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
								if(a[i][j] == a[toado_dong][toado_cot])
								{
									// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
									DanhTheoDuongGiaoDiemDongCot == false ? 
										// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
										gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + j * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + i * (doronggiua2dong + 1))
										:
										// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
										gotoxy(j * (doronggiua2cot + 1) + vitriXbandau, i * (doronggiua2dong + 1) + vitriYbandau);

									textcolor(k);
									cout << quanco;
								}
								else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
								{
									break;
								}

								// Xét qua lần lặp mới
								i++;
								j--;
							}

							/* Đoạn code để cho chữ chạy từ lề trái qua phải in ra màn hình nội dung thông báo chiến thắng */
							// Nhảy đến vị trí x bắt đầu xuất ra chữ của lần trước đó để lấp đi nội dung bằng khoảng trống để không bị in ra dư
							gotoxy(vitriXbandau + (k - 1) * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							cout << "                                 "; // lấp đi bằng khoảng trống

							// Với mỗi mã màu k chạy từ 1 tới 15 thì nó dựa theo mã màu k tương ứng trong mỗi lần lặp để tạo ra 1 vị trí xuất hiện x mới của chữ nội dung xuất ra màn hình từ đó chữ sẽ chạy từ lề trái qua lề phải
							gotoxy(vitriXbandau + k * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							textcolor(k);
							cout << quanco << " da chien thang";

							// Để mỗi lần lặp qua đơn vị màu mới nó có 1 khoảng độ dừng lại để còn tạo ra hiệu ứng nhấp nháy chứ nếu không nó chạy 1 cái lèo là xong
							Sleep(200);
						}

						gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 3); // Nhảy đến dòng dưới dòng thông báo chiến thắng
						textcolor(7); // trả lại màu như bình thường

						break; // thoát ra khỏi vòng lặp diễn hoạt game
					}

					// Cái điều kiện if này phải để nằm sau điều kiện if xét chiến thắng, bởi vì lỡ nước đi cuối cùng cũng là nước đi chiến thắng thì như vậy nó sẽ kết luận là chiến thắng chứ không phải hòa
					if(DemSoLuongQuanCoDaDanh == sodong * socot)
					{
						string KetLuan = "Van co hoa nhau do ban co da het cho de danh";
						
						if(ThoiGianQuyDinhChoMoiNuocDanh > 0) // Phải có kích hoạt chế độ tính thời gian cho mỗi nước đánh thì mới có thể sử dụng tính năng tính tổng thời gian để đánh ra cờ của mỗi người chơi
						{
							if(KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi == true) // Nếu áp dụng luật này thì bàn cờ phải có tổng số lượng ô là số chẵn vd: 10 x 10, 20 x 20 chứ nếu tổng số ô là số lẻ thì như vậy người đi quân cờ đầu tiên sẽ được đánh nhiều hơn 1 quân dẫn đến khi tính thời gian sẽ phải tính thời gian dư ra 1 quân so với người kia và từ đó lại bị thua thiệt do có thời gian nhiều hơn. Tuy nhiên thực tế thì xét theo góc độ công bằng thì người được đánh đầu tiên là đã có ưu thế riêng rồi cho nên hay là xem như bù trừ
							{
								if(TongThoiGianDanhCoCuaNguoiChoiQuanCoX < TongThoiGianDanhCoCuaNguoiChoiQuanCoO)
								{
									KetLuan = "X da chien thang do co tong thoi gian danh co it hon O";
								}
								else if(TongThoiGianDanhCoCuaNguoiChoiQuanCoX > TongThoiGianDanhCoCuaNguoiChoiQuanCoO)
								{
									KetLuan = "O da chien thang do co tong thoi gian danh co it hon X";
								}
								else 
								{
									KetLuan = "X va O hoa nhau do co tong thoi gian danh co bang nhau";
								}
							}
						}
						

						// Hiện câu thông báo và được nhấp nháy
						for(int i = 1; i <= 15; ++i)
						{
							gotoxy(vitriXbandau, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
							textcolor(i);
							cout << KetLuan;
							Sleep(100);
						}
						//cout << "\nTong thoi gian quan co X danh ra: " << TongThoiGianDanhCoCuaNguoiChoiQuanCoX;
						//cout << "\nTong thoi gian quan co O danh ra: " << TongThoiGianDanhCoCuaNguoiChoiQuanCoO;
						break; // thoát ra khỏi vòng lặp diễn hoạt game
					}

					// Sau khi đã bỏ viền background nổi bật của nước trước đó thì cập nhật lại biến temp_toado_dong, temp_toado_cot theo tọa độ của nước vừa được đánh để tiếp tục nước đánh tiếp theo lại có dữ kiện để mà xét
					temp_toado_dong = toado_dong;
					temp_toado_cot = toado_cot;

					luotdi = !luotdi; // phủ định của chính nó rồi gán lại cho nó để cứ luân phiên: true - false - true - false

					// Xuất lại câu thông báo về lượt đi tiếp theo là của quân cờ nào
					//gotoxy(vitriXbandau, (doronggiua2dong + 1) * sodong + vitriYbandau + 1); // Nhảy đến dòng dưới cùng của bàn cờ
					//gotoxy((doronggiua2cot + 1) * socot + vitriXbandau + 1, vitriYbandau); // Dấu nháy sẽ nằm ở dòng đầu tiên bên cạnh cột cuối cùng của bàn cờ
					//cout << "Luot di hien tai la cua quan co: ";

					// Không cần phải xuất lại nội dung "Luot di hien tai la cua quan co: " mà chỉ cần nhảy đến cột x tương ứng để xuất ra quân cờ mới thôi.
					gotoxy(vitriXbandau + DoDaiNoiDungThongBao, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 1); // Nhảy đến dòng dưới cùng của bàn cờ
					if(luotdi == true)
					{
						quanco = 'X';
						textcolor(14); // màu vàng
					}
					else
					{
						quanco = 'O';
						textcolor(12); // màu đỏ
					}
					cout << quanco;
					textcolor(7); // trả lại màu bình thường

					/* Sau khi đánh cờ xong ở 1 ô bất kỳ thì ta chủ động cho nó nhảy dấu nháy sang ô bên cạnh, 
					nếu ô bên cạnh không có thì nhảy xuống ô đầu tiên của hàng bên dưới,
					nếu hàng bên dưới cũng không có thì nhảy về ô đầu tiên của hàng đầu tiên */

					// Ta có thể đổi ý sau khi đánh tại 1 ô thì dấu nháy vẫn sẽ nằm ở ô đó chứ không nhảy sang ô bên cạnh vì giờ đây ta đã có thể kiểm tra được vị trí đánh bị trùng thì không cho đánh nên yên tâm
					/*
					toado_cot++;
					if(toado_cot == socot)
					{
					toado_cot = 0;
					toado_dong++;
					if(toado_dong == sodong)
					{
					toado_dong = 0;
					}
					}
					*/

					// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ
					// Vẫn phải có dòng này thì dấu nháy nó mới vẫn nằm ngay tọa độ ô vừa đánh
					// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
					DanhTheoDuongGiaoDiemDongCot == false ? 
						// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
						gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

						// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
						gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);
				}
				else
				{
					string ThongBao = "Vi tri nay da co quan co ton tai nen khong danh duoc";
					bool KetThuc = ThongBaoViTriDanhKhongHopLe(ThongBao, vitriXbandau, doronggiua2dong, DanhTheoDuongGiaoDiemDongCot, sodong, socot, vitriYbandau, ThoiGianQuyDinhChoMoiNuocDanh, temp_ThoiGianQuyDinhChoMoiNuocDanh, doronggiua2cot, DoDaiNoiDungThongBaoThoiGianConLai, toado_dong, toado_cot, quanco);
					
					if(KetThuc == true)
						break; // Thoát khỏi vòng lặp diễn hoạt game
				}
			}
			else if(c == 'u' || c == 'U') // Undo: Quay trở lại 1 nước trước đó
			{
				ChucNang_Undo(stack_undo, stack_redo, toado_dong, toado_cot, temp_toado_dong, temp_toado_cot, DanhTheoDuongGiaoDiemDongCot, vitriXbandau, vitriYbandau, doronggiua2cot, doronggiua2dong, a,  DemSoLuongQuanCoDaDanh, luotdi, DoDaiNoiDungThongBao, sodong, quanco);
			}
			else if(c == 'r' || c == 'R') // Redo
			{
				ChucNang_Redo(stack_redo, stack_undo, toado_dong, toado_cot, quanco, DanhTheoDuongGiaoDiemDongCot, luotdi, vitriXbandau, vitriYbandau, doronggiua2dong, doronggiua2cot, a, DemSoLuongQuanCoDaDanh, temp_toado_dong, temp_toado_cot, sodong, DoDaiNoiDungThongBao);
			}
			else if(c == 'p' || c == 'P') // Play/Pause
			{
				if(ThoiGianQuyDinhChoMoiNuocDanh > 0) // Tính năng Play/Pause chỉ áp dụng khi có tính thời gian cho mỗi nước đánh
				{
					Play = !Play; // Phủ định lại của nó: Nếu đang là true thì biến thành false, đang là false thì biến thành true

					if(Play == false) // Pause => đóng băng tất cả mọi thứ lại: Bao gồm việc tính thời gian, việc di chuyển trên bàn cờ, việc đánh cờ ...
					{
						// In ra 1 câu thông báo là bàn cờ đang ở tình trạng pause
						gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 5); // Nằm ngay dưới dòng thông báo Thời gian còn lại ...
						cout << "Ban co dang tam dung. Nhan phim ";
						textcolor(12);
						cout << "P";
						textcolor(7);
						cout << " de tiep tuc choi";

						// Trước khi đi vô vòng lặp vô tận chúng ta sẽ ẩn toàn bộ quân cờ đang có trên bàn cờ bằng tính năng Undo chúng ta đã làm => cho Undo đến tận cùng để xóa hết toàn bộ quân cờ trên bàn cờ
						while(!stack_undo.empty())
						{
							ChucNang_Undo(stack_undo, stack_redo, toado_dong, toado_cot, temp_toado_dong, temp_toado_cot, DanhTheoDuongGiaoDiemDongCot, vitriXbandau, vitriYbandau, doronggiua2cot, doronggiua2dong, a,  DemSoLuongQuanCoDaDanh, luotdi, DoDaiNoiDungThongBao, sodong, quanco);
						}

						// Giam nó vào trong 1 luồng vòng lặp vô tận con khác nằm bên trong vòng lặp vô tận diễn hoạt game
						while(true)
						{
							if(kbhit()) // Hàm nhận biết có tương tác phím
							{
								char c1 = getch();

								// Xử lý với những trường hợp phím chức năng
								if(c1 == -32)
								{
									c1 = getch(); // Nếu nhấn mũi tên đi xuống thì chỗ này sẽ tự động nhận vào mã ascii 80 và không xử lý gì hết còn nếu không có dòng này thì vòng lặp while(true) tiếp tục lặp lại và ở lần sau đó mã ascii 80 được đưa vào và nó thỏa cái else sau đó thỏa trùng với mã ascii của P => thoát khỏi vòng lặp con => không như mong muốn của chúng ta
								}
								else
								{
									// Nếu nhấn thêm phím P lần nữa thì nghĩa là Play lại => Cho nó thoát ra khỏi vòng lặp vô tận con để trở về vòng lặp vô tận cha (vòng lặp diễn hoạt game)
									if(c1 == 'p' || c1 == 'P')
									{
										// Xóa dòng thông báo bàn cờ đang tạm dừng
										gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1, vitriYbandau + 5); // Nằm ngay dưới dòng thông báo Thời gian còn lại ...
										cout << "                                                   "; // Không nên dài quá kẻo bị xuống dòng xóa mất bàn cờ ở bên lề trái bởi vì khung cmd nó không có gia tăng bề ngang mà chỉ có con lăn bề dọc thôi

										Play = !Play; // Phủ định lại của nó: Nếu đang là true thì biến thành false, đang là false thì biến thành true

										// Trước khi thoát ra thì sẽ cho hiển thị lại toàn bộ quân cờ đã bị ẩn trước đó nhờ vào tính năng Redo
										while(!stack_redo.empty())
										{
											ChucNang_Redo(stack_redo, stack_undo, toado_dong, toado_cot, quanco, DanhTheoDuongGiaoDiemDongCot, luotdi, vitriXbandau, vitriYbandau, doronggiua2dong, doronggiua2cot, a, DemSoLuongQuanCoDaDanh, temp_toado_dong, temp_toado_cot, sodong, DoDaiNoiDungThongBao);
										}

										break; // Cho nó thoát ra khỏi vòng lặp vô tận con để trở về vòng lặp vô tận cha (vòng lặp diễn hoạt game)
									}
								}
							}
						}
					}
				}
			}
			else if(c == 19) // Nhấn phím Ctrl S để Save lại bàn cờ
			{
				// Cần phải đặt cho nó 1 cái tên để lưu trữ lại xuống tập tin và mặc định nó sẽ lưu ở đường dẫn nào?
				// Đối với đường dẫn lưu tập tin thì chúng ta nên dùng đường dẫn tương đối chứ không nên gán cứng cố định đường dẫn tuyệt đối vì bên máy người dùng khác chưa chắc có đường dẫn đó (vd: Bạn để đường dẫn lưu trữ là: E:/abc/xyz thì chắc gì máy tính người chạy chương trình đã có ổ E, nếu có ổ E chắc gì có thư mục abc, xyz?
				// Đối với tên tập tin thì Bạn có thể cho nó 1 cái tên bất kỳ nào đó tùy ý Bạn tuy nhiên cẩn thận có thể bị trùng tên và phải mất công gõ thì có thể lựa chọn cho nó tạo ra 1 cái tên tự động lưu trữ theo kiểu cú pháp: <ngày tháng năm><giờ phút giây> (vd: 9_11_2019_16_05_30.txt)
				
				// Lấy thời gian hiện tại từ hệ thống máy tính
				time_t t = time(0);
				struct tm *Now = localtime(&t);

				// Tạo tên tập tin tự động được ghép thành từ ngày_tháng_năm_giờ_phút_giây ngay thời điểm được tạo ra
				string FileName;
				FileName = to_string(Now->tm_mday) + "_" + to_string(Now->tm_mon + 1) + "_" + to_string(Now->tm_year + 1900) + "_" + to_string(Now->tm_hour) + "_" + to_string(Now->tm_min) + "_" + to_string(Now->tm_sec);

				// Mở file để ghi dữ liệu vào
				ofstream FileOut;
				FileOut.open(FileName + ".txt", ios_base::out);

				// Xử lý ghi dữ liệu vào file ...
				FileOut << "sodong: " << (DanhTheoDuongGiaoDiemDongCot == true ? sodong - 1 : sodong) << endl;
				FileOut << "socot: " << (DanhTheoDuongGiaoDiemDongCot == true ? socot - 1 : socot) << endl;
				FileOut << "doronggiua2cot: " << doronggiua2cot << endl;
				FileOut << "doronggiua2dong: " << doronggiua2dong << endl;
				FileOut << "vitriXbandau: " << vitriXbandau << endl;
				FileOut << "vitriYbandau: " << vitriYbandau << endl;
				FileOut << "DanhTheoDuongGiaoDiemDongCot: " << DanhTheoDuongGiaoDiemDongCot << endl;
				FileOut << "stack_undo" << endl;
				FileOut << stack_undo.size() << endl;

				// Nếu lấy dữ liệu trong stack_undo ra ghi vào file thế này thì sau cùng stack_undo sẽ không còn dữ liệu gì nữa và nếu giả sử người dùng có muốn chơi tiếp mà chưa tắt game thì không dùng được tính năng Undo nữa => sẽ tạo 1 biến phụ cho stack_undo để lưu trữ stack_undo qua biến phụ này sau đó xét trên biến phụ để đảm bảo biến chính vẫn được giữ nguyên giá trị
				stack<TOADO> temp_stack_undo = stack_undo;
				while(!temp_stack_undo.empty())
				{
					TOADO td = temp_stack_undo.top();
					temp_stack_undo.pop();

					FileOut << td.toado_dong << " " << td.toado_cot << endl;
				}

				FileOut << "SoQuanCoGiongNhauLienTiepToiThieuDeThang: " << SoQuanCoGiongNhauLienTiepToiThieuDeThang << endl;
				FileOut << "KichHoatCheDoChan2DauLaKhongChoThang: " << KichHoatCheDoChan2DauLaKhongChoThang << endl;
				FileOut << "ThoiGianQuyDinhChoMoiNuocDanh: " << ThoiGianQuyDinhChoMoiNuocDanh << endl;
				FileOut << "KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi: " << KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi << endl;
				FileOut << "LuotDiBanDau: " << LuotDiBanDau << endl;
				FileOut << "TongThoiGianDanhCoCuaNguoiChoiQuanCoX: " << TongThoiGianDanhCoCuaNguoiChoiQuanCoX << endl;
				FileOut << "TongThoiGianDanhCoCuaNguoiChoiQuanCoO: " << TongThoiGianDanhCoCuaNguoiChoiQuanCoO << endl;

				FileOut.close(); // Đóng file lại

				cout << "Du lieu ban co da duoc ghi vao tap tin co ten: " << FileName + ".txt";

			}
			else if(c == 27) // Esc
			{
				exit(0); // Tắt luôn chương trình
			}
		}

		if(temp_ThoiGianQuyDinhChoMoiNuocDanh > 0) 
		{
			Sleep(1); // Tối thiểu nó phải là 1 thì mới có Sleep chứ nếu là Sleep(0) nghĩa là không có Sleep rồi
			dem_Sleep++;

			// Lẽ ra Sleep(1000) sẽ tương ứng là 1000 cái Sleep(1) tuy nhiên thực tế cho thấy nó bị chậm hơn 1 nửa. Nguyên nhân vì bản chất việc gọi hàm là chương trình có tốn thời gian để gọi và những cái xử lý ở bên trong của hàm cũng bị lặp đi lặp lại dẫn tới mất thời gian => đo thực tế thấy rằng chỉ 500 Sleep(1) thì mới tương đương 1 cái Sleep(1000)
			if(dem_Sleep == 500) // đó là lý do chỗ này để 500
			{
				dem_Sleep = 0; // Nhớ là phải reset lại là 0 để còn đếm cho lần tiếp theo

				temp_ThoiGianQuyDinhChoMoiNuocDanh--; // sau đó giảm thời gian đi 1 đơn vị

				// In ra lại thời gian còn lại
				gotoxy((doronggiua2cot + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? socot : socot - 1) + vitriXbandau + 1 + DoDaiNoiDungThongBaoThoiGianConLai, vitriYbandau + 3);
				textcolor(12);
				cout << temp_ThoiGianQuyDinhChoMoiNuocDanh << " "; // Luôn in ra thêm 1 khoảng trắng để bù đi phần chênh lệch giữa số đã in ra trước đó vd: trước đó là 10, sau đó là 9 thì phải in ra 1 khoảng trắng như vậy để xóa đi ký tự 0
				textcolor(7);
				
				// Đã hết thời gian và kết luận người chơi ở lần đánh hiện tại đã bị thua và người chơi đối thủ thắng
				if(temp_ThoiGianQuyDinhChoMoiNuocDanh == 0)
				{
					for(int k = 1; k <= 15; ++k)
					{
						/* Đoạn code để cho chữ chạy từ lề trái qua phải in ra màn hình nội dung thông báo chiến thắng */
						// Nhảy đến vị trí x bắt đầu xuất ra chữ của lần trước đó để lấp đi nội dung bằng khoảng trống để không bị in ra dư
						gotoxy(vitriXbandau + (k - 1) * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
						cout << "                                 "; // lấp đi bằng khoảng trống

						// Với mỗi mã màu k chạy từ 1 tới 15 thì nó dựa theo mã màu k tương ứng trong mỗi lần lặp để tạo ra 1 vị trí xuất hiện x mới của chữ nội dung xuất ra màn hình từ đó chữ sẽ chạy từ lề trái qua lề phải
						gotoxy(vitriXbandau + k * 3, (doronggiua2dong + 1) * (DanhTheoDuongGiaoDiemDongCot == false ? sodong : sodong - 1) + vitriYbandau + 2); // Nhảy đến dòng dưới dòng thông báo Lượt đi hiện tại ...
						textcolor(k);
						//cout << quanco << " da chien thang";
						cout << "Vi da het thoi gian nen " << quanco << " da thua va " << (quanco == 'X' ? "O" : "X") << " da chien thang";

						// Để mỗi lần lặp qua đơn vị màu mới nó có 1 khoảng độ dừng lại để còn tạo ra hiệu ứng nhấp nháy chứ nếu không nó chạy 1 cái lèo là xong
						Sleep(200);
					}
					break; // Thoát khỏi vòng lặp diễn hoạt game
				}

				// công thức để nhảy đến 1 ô có vị trí tọa độ dòng, cột bất kỳ và đánh theo kiểu giao điểm dòng cột hoặc đánh trong từng ô
				DanhTheoDuongGiaoDiemDongCot == false ? 
					// Công thức để con trỏ nhảy vào bên trong của 1 ô có tọa độ dòng - cột bất kỳ
					gotoxy(vitriXbandau + doronggiua2cot / 2 + 1 + toado_cot * (doronggiua2cot + 1), vitriYbandau + doronggiua2dong / 2 + 1 + toado_dong * (doronggiua2dong + 1)) :

					// Công thức để con trỏ nhảy vào giao điểm của dòng - cột bất kỳ
					gotoxy(toado_cot * (doronggiua2cot + 1) + vitriXbandau, toado_dong * (doronggiua2dong + 1) + vitriYbandau);
			}

			
		}
	}
	SetConsoleMode(hin, fdwMode);
}

int main()
{	
	int sodong = 10, socot = 10;
	int doronggiua2cot = 3, doronggiua2dong = 1; // Nếu muốn đánh quân cờ nằm bên trong từng ô thì độ rộng giữa 2 cột và độ rộng giữa 2 dòng tối thiểu phải là 1. Và tốt nhất nên là số lẻ để quân cờ khi đánh được cách đều 2 bên (trái - phải) - (trên - dưới). Còn nếu đánh theo tọa độ giao điểm dòng cột thì độ rộng giữa 2 dòng, 2 cột miễn từ 0 trở lên là được hết và có là số lẻ hay số chẵn cũng không quan tâm
	int vitriXbandauCuaBanCo = 1, vitriYbandauCuaBanCo = 1; // vị trí xuất hiện ban đầu của bàn cờ
	bool DanhTheoDuongGiaoDiemDongCot = true;  // nếu là true tức là sẽ đánh theo giao điểm dòng - cột, nếu là false tức là đánh trong từng ô
	char a[MAX][MAX];
	stack<TOADO> stack_undo; // Ngăn xếp để lưu trữ vị trí từng quân cờ được đánh xuống bàn cờ để thực hiện tính năng Undo
	stack<TOADO> stack_redo; // Ngăn xếp để lưu trữ vị trí từng quân cờ lấy ra từ ngăn xếp Undo để thực hiện tính năng Redo
	int SoQuanCoGiongNhauLienTiepToiThieuDeThang = 5; // Tùy bàn cờ mà điều chỉnh số này cho hợp lý (vd: Bàn cờ 3 x 3 thì chỉnh 3 quân liên tiếp là thắng)
	bool KichHoatCheDoChan2DauLaKhongChoThang = false; // Nếu là true tức là kích hoạt chế độ chặn 2 đầu là không cho thắng, nếu là false tức là bỏ chế độ đó đi chặn 2 đầu miễn đủ số lượng quân tối thiểu liên tiếp là kết luận thắng
	int ThoiGianQuyDinhChoMoiNuocDanh = 20; // tính theo giây (nếu con số này là giá trị âm vd: -1 thì nghĩa là tính năng tính thời gian cho mỗi nước đánh sẽ không được kích hoạt, còn nếu là giá trị dương thì nghĩa là tính năng đã được kích hoạt)
	bool KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi = true; // Nếu có tính thời gian cho mỗi nước đi thì có thêm chế độ tính tổng thời gian để đánh ra quân cờ của mỗi người chơi, để trong tình huống bàn cờ hết chỗ để đánh thay vì kết luận hòa thì chúng ta sẽ đi xem ai dùng ít thời gian nhất để đánh ra toàn bộ quân cờ thì người đó sẽ chiến thắng, còn nếu cả 2 dùng thời gian như nhau thì chính thức là hòa
	int TongThoiGianDanhCoCuaNguoiChoiQuanCoX = 0;
	int TongThoiGianDanhCoCuaNguoiChoiQuanCoO = 0;
	bool KichHoatCheDoLoapMap = false; // Nếu là true thì sẽ cho dữ liệu bàn cờ đang đánh dở trước đó được load từ tập tin vào, nếu là false thì xem như đánh 1 bàn cờ mới (New Game) 
	bool LuotDiBanDau = true; // Nếu là true thì nghĩa là X đánh trước, nếu là false thì nghĩa là O đánh trước
	
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); // Full Screen
	
	/*
nhaplaithongsokythuat: // nhãn goto nhảy tới
	cout << "Nhap [so dong, so cot] cua ban co: ";
	cin >> sodong >> socot;

	cout << "\nNhap vi tri toa do [x, y] ban dau cua ban co: ";
	cin >> vitriXbandauCuaBanCo >> vitriYbandauCuaBanCo;

	cout << "\nNhap do rong giua 2 cot, 2 dong cua ban co: ";
	cin >> doronggiua2cot >> doronggiua2dong;

	cout << "\nBan co muon danh theo giao diem toa do dong cot khong? Nhap 1 la co, Nhap 0 la khong: ";
	cin >> DanhTheoDuongGiaoDiemDongCot;

	cout << "\nNhap so luong quan co giong nhau lien tiep toi thieu de chien thang: ";
	cin >> SoQuanCoGiongNhauLienTiepToiThieuDeThang;

	cout << "\nBan co muon kich hoat che do neu bi chan 2 dau la khong cho thang khong? Nhap 1 la co, Nhap 0 la khong: ";
	cin >> KichHoatCheDoChan2DauLaKhongChoThang;

	system("cls"); // xóa màn hình tất cả những câu thông báo nhập nãy giờ của chúng ta
	*/
	int choitiep;
	do{
		// Reset các thông số sau đây

		// Khởi tạo tất cả các phần tử trong mảng 2 chiều là ký tự khoảng trắng
		// Dùng hàm hỗ trợ có sẵn trong C++
		fill((char *)a, (char *)a + sizeof(a), ' '); // Cũng nên dùng hàm này luôn để nếu có đánh theo đường giao điểm thì cần tới thêm 1 dòng, thêm 1 cột thì tất cả mảng đều toàn giá trị rỗng => vẫn thỏa mãn

		while(!stack_undo.empty())
		{
			stack_undo.pop();
		}

		while(!stack_redo.empty())
		{
			stack_redo.pop();
		}

		TongThoiGianDanhCoCuaNguoiChoiQuanCoO = TongThoiGianDanhCoCuaNguoiChoiQuanCoX = 0;


		string DuongDanMap;
		ifstream FileIn;
		bool DuongDanHopLe;
		if(KichHoatCheDoLoapMap == true)
		{
			/*do{
				DuongDanHopLe = true;

				cout << "\nNhap vao duong dan den tap tin Map can load: ";
				getline(cin, DuongDanMap);

				FileIn.open(DuongDanMap, ios_base::in);

				if(!FileIn)
				{
					cout << "\nDuong dan den tap tin Map: " << DuongDanMap << " khong ton tai. Xin kiem tra lai!";
					DuongDanHopLe = false;
				}
			}while(DuongDanHopLe == false);*/

			FileIn.open("10_11_2019_12_51_12.txt", ios_base::in);

			// Tiến hành đọc file luôn để lưu dữ liệu tương ứng qua các biến thông số kỹ thuật để đi vào hàm xử lý game nó sẽ dựng được game theo đúng thông số trong tập tin
			string temp;
			FileIn >> temp;
			FileIn >> sodong;

			//cout << temp << " " << sodong << endl;

			FileIn >> temp;
			FileIn >> socot;
			
			//cout << temp << " " << socot << endl;

			
			FileIn >> temp;
			FileIn >> doronggiua2cot;
			
			//cout << temp << " " << doronggiua2cot << endl;

			FileIn >> temp;
			FileIn >> doronggiua2dong;
			
			//cout << temp << " " << doronggiua2dong << endl;

			FileIn >> temp;
			FileIn >> vitriXbandauCuaBanCo;
			
			//cout << temp << " " << vitriXbandauCuaBanCo << endl;

			FileIn >> temp;
			FileIn >> vitriYbandauCuaBanCo;
			
			//cout << temp << " " << vitriYbandauCuaBanCo << endl;

			FileIn >> temp;
			FileIn >> DanhTheoDuongGiaoDiemDongCot;
			
			//cout << temp << " " << DanhTheoDuongGiaoDiemDongCot << endl;

			FileIn >> temp;
			//cout << temp << endl;
			
			int size;
			FileIn >> size;
			//cout << size << endl;
			
			for(int i = 1; i <= size; ++i)
			{
				TOADO td;
				FileIn >> td.toado_dong >> td.toado_cot;
				stack_redo.push(td); // Phải đưa vào trong Stack Redo để chúng ta có thể dùng tính năng Redo để tái hiện lại bàn cờ
				//cout << td.toado_dong << " " << td.toado_cot << endl;
			}

			FileIn >> temp;
			FileIn >> SoQuanCoGiongNhauLienTiepToiThieuDeThang;
			
			//cout << temp << " " << SoQuanCoGiongNhauLienTiepToiThieuDeThang << endl;

			FileIn >> temp;
			FileIn >> KichHoatCheDoChan2DauLaKhongChoThang;
			
			//cout << temp << " " << KichHoatCheDoChan2DauLaKhongChoThang << endl;

			FileIn >> temp;
			FileIn >> ThoiGianQuyDinhChoMoiNuocDanh;
			
			//cout << temp << " " << ThoiGianQuyDinhChoMoiNuocDanh << endl;

			FileIn >> temp;
			FileIn >> KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi;
			
			//cout << temp << " " << KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi << endl;

			FileIn >> temp;
			FileIn >> LuotDiBanDau;
			
			//cout << temp << " " << LuotDiBanDau << endl;

			FileIn >> temp;
			FileIn >> TongThoiGianDanhCoCuaNguoiChoiQuanCoX;
			
			//cout << temp << " " << TongThoiGianDanhCoCuaNguoiChoiQuanCoX << endl;

			FileIn >> temp;
			FileIn >> TongThoiGianDanhCoCuaNguoiChoiQuanCoO;
			
			//cout << temp << " " << TongThoiGianDanhCoCuaNguoiChoiQuanCoO << endl;

			FileIn.close(); // Đóng file lại để giải phóng
		}

		
		
		XuLyGameTheoHuongDungPhim(a, stack_undo, stack_redo, sodong, socot, doronggiua2cot, doronggiua2dong, vitriXbandauCuaBanCo, vitriYbandauCuaBanCo, DanhTheoDuongGiaoDiemDongCot, SoQuanCoGiongNhauLienTiepToiThieuDeThang, KichHoatCheDoChan2DauLaKhongChoThang, ThoiGianQuyDinhChoMoiNuocDanh, KichHoatCheDoTinhTongThoiGianDeDanhRaCoCuaMoiNguoiChoi, TongThoiGianDanhCoCuaNguoiChoiQuanCoX, TongThoiGianDanhCoCuaNguoiChoiQuanCoO, LuotDiBanDau, KichHoatCheDoLoapMap);

		cout << "\nBan co muon choi tiep lai tu dau khong? Neu co nhap so 1, nguoc lai nhap so bat ky de ket thuc: ";
		cin >> choitiep;
		//choitiep = getch(); // chờ nhận key từ bàn phím

		if(choitiep == 1)
		{
			/*
			bool ChoiLaiVoiThongSoKyThuatBanDau;

			
			cout << "\nBan co muon choi lai voi thong so ky thuat ban dau khong? Nhap 1 la co, Nhap 0 la khong: ";
			cin >> ChoiLaiVoiThongSoKyThuatBanDau;

			if(ChoiLaiVoiThongSoKyThuatBanDau == 1) // có => không cần nhập lại thông số kỹ thuật ban đầu, cứ thế vẽ lại bàn cờ rồi chơi thôi
			{
				system("cls"); // Xóa hết màn hình để chơi lại từ đầuKichHoatCheDoLoapMap
			}
			else // không => cho nhập lại thông số sau đó mới vẽ bàn cờ
			{
				goto nhaplaithongsokythuat;
			}
			*/

			system("cls"); // Xóa hết màn hình để chơi lại từ đầu
		}
	}while(choitiep == 1);


	system("pause"); // getch();
	return 0;
}