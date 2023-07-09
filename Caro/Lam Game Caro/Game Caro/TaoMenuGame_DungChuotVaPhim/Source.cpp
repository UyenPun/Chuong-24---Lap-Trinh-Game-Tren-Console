#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

struct NutNhan
{
	string ChucNang; // Nội dung chức năng hiển thị ra
	int MaMau; // mã màu in ra
	int x, y; // Tọa độ xuất hiện của nút tính theo góc trên cùng bên trái
	int DoRong; // độ rộng bề ngang của nút nhấn
};
typedef struct NutNhan NUTNHAN;

HANDLE hStdin; 
DWORD fdwSaveOldMode;

void textcolor(int x);
void TaoNutNhanChucNang(NUTNHAN nut);

int SoLuongCacNutNhan = 4;
NUTNHAN *DanhSachNutNhan = new NUTNHAN[SoLuongCacNutNhan];
int indexCuaMenuDangDuocChon = 0;

VOID ErrorExit (LPSTR lpszMessage) 
{ 
	fprintf(stderr, "%s\n", lpszMessage); 

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0); 
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void XuatThongBao(string NoiDungThongBao)
{
	gotoxy(1, 5);
	for(int k = 1; k <= 15; ++k)
	{
		textcolor(k);
		gotoxy(1, 5);
		//cout << "Vi tri click chuot khong hop le";
		cout << NoiDungThongBao;
		Sleep(100);
	}
	gotoxy(1, 5);
	int length = NoiDungThongBao.length();
	for(int i = 1; i <= length; ++i)
	{
		cout << " ";
	}
}

// Hàm này nhận 3 tham số x, y là tọa độ của chuột và khoảng cách giữa 2 menu rồi kiểm tra nếu đang ở trong phạm vi của 1 Menu nào đó thì trả về index của Menu đó, nếu không ở trong phạm vi của Menu nào cả thì trả về -1
int KiemTraToaDoChuotHopLe(int x, int y, int khoangcachgiua2menu)
{
	if(x < DanhSachNutNhan[0].x || x > DanhSachNutNhan[0].x + DanhSachNutNhan[0].DoRong - 1)
		return -1;
	else // x hợp lệ
	{
		if(y < DanhSachNutNhan[0].y || y > DanhSachNutNhan[0].y + (SoLuongCacNutNhan - 1) * (khoangcachgiua2menu + 1))
			return -1;
		else // y hợp lệ nhưng coi chừng nó nằm vào những vị trí khoảng trắng ngăn cách giữa 2 nút thì cũng không phải hợp lệ
		{
			if((y - DanhSachNutNhan[0].y) % (khoangcachgiua2menu + 1) != 0)
				return -1;
		}
	}
	return (y - DanhSachNutNhan[0].y) / (khoangcachgiua2menu + 1); // trả về index của nút đang đứng
}

// Hàm này nhận 3 tham số x, y là tọa độ của chuột và khoảng cách giữa 2 menu rồi kiểm tra nếu đang ở trong phạm vi của 1 Menu nào đó thì trả về index của Menu đó, nếu không ở trong phạm vi của Menu nào cả thì trả về -1
// Version 2 này khác trước đó: Lúc này nó sẽ không quy chuẩn tất cả các Menu có cùng bề ngang giống nhau, mà tùy Menu sẽ có bề ngang khác nhau (nó phụ thuộc vào độ dài chức năng của Menu tương ứng) => buộc người điều khiển phải đưa hẳn con chuột vào bên trong phạm vi nội dung của nút
// Hoặc là nếu áp dụng độ rộng của tất cả các Menu quy chuẩn theo 1 độ rộng lớn nhất thì hàm này vẫn đáp ứng chạy ngon lành cành đào
int KiemTraToaDoChuotHopLe_Ver2(int x, int y, int khoangcachgiua2menu)
{
	// Xét tính hợp lệ của y
	if(y < DanhSachNutNhan[0].y || y > DanhSachNutNhan[0].y + (SoLuongCacNutNhan - 1) * (khoangcachgiua2menu + 1))
		return -1;

	// Chạy được xuống dòng này tức là điều kiện if ở trên không thỏa tức là y hợp lệ nhưng coi chừng nó nằm vào những vị trí khoảng trắng ngăn cách giữa 2 nút thì cũng không phải hợp lệ
	if((y - DanhSachNutNhan[0].y) % (khoangcachgiua2menu + 1) != 0)
		return -1;

	// Lúc này chạy xuống đây được tức là y đã là y hợp lệ hoàn toàn và thuộc về y của 1 Menu cụ thể. Lúc này ta sẽ xét xem vị trí x có nằm trong đoạn của nút nhấn đó hay không?
	int index_Menu = (y - DanhSachNutNhan[0].y) / (khoangcachgiua2menu + 1);

	if(x < DanhSachNutNhan[index_Menu].x || x > DanhSachNutNhan[index_Menu].x + DanhSachNutNhan[index_Menu].DoRong - 1)
		return -1;

	return index_Menu; // trả về index của nút đang đứng và nó đang nằm trong phạm vi nội dung của nút đó và hợp lệ
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer, int khoangcachgiua2menu)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");

	switch(mer.dwEventFlags)
	{
	case 0:
		if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			int x = mer.dwMousePosition.X + 1;
			int y = mer.dwMousePosition.Y + 1;

			//int index_Menu = KiemTraToaDoChuotHopLe(x, y, khoangcachgiua2menu);
			int index_Menu = KiemTraToaDoChuotHopLe_Ver2(x, y, khoangcachgiua2menu);

			if(index_Menu != -1)
			{
				// Tô màu đỏ cho nó
				//indexCuaMenuDangDuocChon = (y - DanhSachNutNhan[0].y) / 2;


				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 12; // màu đỏ
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]);

				gotoxy(1, 1);
				cout << "                                                      ";

				gotoxy(1, 1);
				cout << "Dang click vao nut " + DanhSachNutNhan[indexCuaMenuDangDuocChon].ChucNang;
			}
			else
			{
				
			}

		}
		else // Xảy ra sự kiện này khi thả chuột ra (Trước đó nhấn vào)
		{
			DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 14; // màu vàng
			TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]);
		}
		break;
	case MOUSE_MOVED:
		int x = mer.dwMousePosition.X + 1;
		int y = mer.dwMousePosition.Y + 1;

		//int index_Menu = KiemTraToaDoChuotHopLe(x, y, khoangcachgiua2menu);
		int index_Menu = KiemTraToaDoChuotHopLe_Ver2(x, y, khoangcachgiua2menu);

		if(index_Menu != -1) // chuột di chuyển vào trong phạm vi của 1 nút nào đó
		{

			//int idx = (y - DanhSachNutNhan[0].y) / 2;

			if(index_Menu != indexCuaMenuDangDuocChon) // Tức là chuột di chuyển vào 1 Menu mới khác Menu đang được chọn ban đầu
			{
				// Xóa màu vàng ở Menu cũ
				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 15; // trở lại thành màu trắng
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]); // Vẽ lại nó với màu trắng

				// Tô màu vàng ở Menu mới
				indexCuaMenuDangDuocChon = index_Menu; // Cập nhật index của Menu đang được di chuyển chuột vào sang biến index đang xử lý
				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 14; // Cập nhật mã màu vàng cho nó
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]); // Vẽ lại nó với màu vàng

			}

		}
		break;
	}
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

void TaoNutNhanChucNang(NUTNHAN nut)
{
	int length = nut.ChucNang.length();
	gotoxy(nut.x, nut.y);
	textcolor(nut.MaMau);
	//cout << " " << nut.ChucNang;
	//for(int i = 1; i <= nut.DoRong - length - 1; ++i)
		//cout << " ";
	cout << nut.ChucNang;
	textcolor(7); // Trở lại màu bình thường
}

// Hàm ẩn hiện dấu nháy trên khung cmd
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    //printf("Key event: ");

    if(ker.bKeyDown)
	{
		if(ker.wVirtualKeyCode == VK_UP)
		{
			if(indexCuaMenuDangDuocChon > 0)
			{
				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 15; // Reset nút hiện tại trở lại thành màu trắng
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]); // Vẽ lại nút để nút có màu mới

				indexCuaMenuDangDuocChon--; // Thay đổi index qua nút tiếp theo

				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 14; // Cập nhật nút tiếp theo sẽ có màu vàng
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]); // Vẽ lại nút để nút có màu mới
			}
		}
		else if(ker.wVirtualKeyCode == VK_DOWN)
		{
			if(indexCuaMenuDangDuocChon < SoLuongCacNutNhan - 1)
			{
				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 15; // Reset nút hiện tại trở lại thành màu trắng
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]); // Vẽ lại nút để nút có màu mới

				indexCuaMenuDangDuocChon++;

				DanhSachNutNhan[indexCuaMenuDangDuocChon].MaMau = 14; // Cập nhật nút tiếp theo sẽ có màu vàng
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaMenuDangDuocChon]); // Vẽ lại nút để nút có màu mới
			}
		}
		else if(ker.wVirtualKeyCode == VK_SPACE || ker.wVirtualKeyCode == VK_RETURN)
		{
			gotoxy(1, 1);
			cout << "                                                      ";

			gotoxy(1, 1);
			cout << "Dang chon vao nut " + DanhSachNutNhan[indexCuaMenuDangDuocChon].ChucNang;
		}
        //printf("key pressed\n");
	}
    //else printf("key released\n");
}

int main()
{
	ShowConsoleCursor(false); // ẩn dấu nháy đi

	/*for(int i = 1; i <= 300; ++i)
	{
	textcolor(i);
	cout << "i = " << i << endl;
	}*/

	//string str[] = {" New Game ", "   Undo   ", "   Redo   ", "   Exit   "};
	vector<string> DanhSachTenCacNutNhan;
	DanhSachTenCacNutNhan.resize(SoLuongCacNutNhan);
	DanhSachTenCacNutNhan[0] = "New Game";
	DanhSachTenCacNutNhan[1] = "Undo";
	DanhSachTenCacNutNhan[2] = "Redo";
	DanhSachTenCacNutNhan[3] = "Exit";

	// Tìm tên nút chức năng có độ dài lớn nhất
	int DoDaiLonNhat = DanhSachTenCacNutNhan[0].length();

	for(int i = 1; i < SoLuongCacNutNhan; ++i)
	{
		int length = DanhSachTenCacNutNhan[i].length();

		if(length > DoDaiLonNhat)
			DoDaiLonNhat = length;
	}
	DoDaiLonNhat += 2; // để trước và sau nó có 1 khoảng trắng cách lề biên trái phải ra

	//string str[] = {"New Game", "Undo", "Redo", "Exit"};

	// Vị trí xuất hiện ban đầu của nút nhấn đầu tiên
	int vitriXbandau = 20;
	int vitriYbandau = 3;
	int KhoangCachGiua2Menu = 1;

	DanhSachNutNhan[0].ChucNang = DanhSachTenCacNutNhan[0];
	DanhSachNutNhan[0].MaMau = 14; // chữ màu vàng, nền màu đen

	// Tùy ý người dùng muốn quy chuẩn tất cả các nút về 1 độ rộng giống nhau hay mỗi nút sẽ có độ rộng tùy biến theo độ dài nội dung chức năng của nút đó
	//DanhSachNutNhan[0].DoRong = DoDaiLonNhat;
	DanhSachNutNhan[0].DoRong = DanhSachNutNhan[0].ChucNang.length();

	DanhSachNutNhan[0].x = vitriXbandau;
	DanhSachNutNhan[0].y = vitriYbandau;
	TaoNutNhanChucNang(DanhSachNutNhan[0]);

	for(int i = 1; i < SoLuongCacNutNhan; ++i)
	{
		DanhSachNutNhan[i].ChucNang = DanhSachTenCacNutNhan[i];
		DanhSachNutNhan[i].MaMau = 15; // chữ màu vàng, nền màu đen
		
		// Tùy ý người dùng muốn quy chuẩn tất cả các nút về 1 độ rộng giống nhau hay mỗi nút sẽ có độ rộng tùy biến theo độ dài nội dung chức năng của nút đó
		//DanhSachNutNhan[i].DoRong = DoDaiLonNhat;
		DanhSachNutNhan[i].DoRong = DanhSachNutNhan[i].ChucNang.length();
		
		DanhSachNutNhan[i].x = vitriXbandau;
		DanhSachNutNhan[i].y = DanhSachNutNhan[i - 1].y + KhoangCachGiua2Menu + 1; // cộng 1 chính là vị trí của nút tiếp theo
		
		TaoNutNhanChucNang(DanhSachNutNhan[i]);
	}

	DWORD cNumRead, fdwMode, i; 
	INPUT_RECORD irInBuf[128]; 

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	if (hStdin == INVALID_HANDLE_VALUE) 
		ErrorExit("GetStdHandle"); 

	// Save the current input mode, to be restored on exit. 

	if (! GetConsoleMode(hStdin, &fdwSaveOldMode) ) 
		ErrorExit("GetConsoleMode"); 

	/* 
	Step-1:
	Disable 'Quick Edit Mode' option
	*/
	// Tự động tắt chế độ Quick Edit Mode nếu đang được bật để từ đó có thể bắt sự kiện chuột được
	fdwMode = ENABLE_EXTENDED_FLAGS;
	if (! SetConsoleMode(hStdin, fdwMode) )
		ErrorExit("SetConsoleMode");

	/* 
	Step-2:
	Enable the window and mouse input events,
	after you have already applied that 'ENABLE_EXTENDED_FLAGS'
	to disable 'Quick Edit Mode'
	*/
	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
	if (! SetConsoleMode(hStdin, fdwMode) ) 
		ErrorExit("SetConsoleMode"); 


	// Loop to read and handle the next 100 input events. 

	while(true)
	{ 
		// Wait for the events. 

		if (! ReadConsoleInput( 
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead) ) // number of records read 
			ErrorExit("ReadConsoleInput"); 

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++) 
		{
			switch(irInBuf[i].EventType) 
			{ 
			case KEY_EVENT: // keyboard input 
                KeyEventProc(irInBuf[i].Event.KeyEvent); 
                break; 
			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent, KhoangCachGiua2Menu); 
				break; 
			} 
		}
		//FlushConsoleInputBuffer(hStdin);
	} 

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	system("pause");
	return 0;
}