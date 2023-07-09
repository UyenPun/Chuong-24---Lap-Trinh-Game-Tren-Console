#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

struct NutNhan
{
	string ChucNang; // Nội dung chức năng hiển thị ra
	int MauNen; // Màu nền background
	int MauChu; // Màu chữ nội dung
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
int indexCuaNutDiChuyenChuotVao = -1;
int indexCuaNutClickChuotXuong = -1;
bool ChoPhepMouseMoveHoatDong = true;

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


VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
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

			bool KiemTraViTriChuotHopLe = true;

			if(y < DanhSachNutNhan[0].y || y > 3 + DanhSachNutNhan[0].y - 1)
			{
				//XuatThongBao("Vi tri click chuot y khong hop le");
				KiemTraViTriChuotHopLe = false;
			}
			else // y hợp lệ
			{
				if(x < DanhSachNutNhan[0].x || x > DanhSachNutNhan[SoLuongCacNutNhan - 1].x + DanhSachNutNhan[SoLuongCacNutNhan - 1].DoRong - 1)
				{
					//XuatThongBao("Vi tri click chuot x khong hop le");
					KiemTraViTriChuotHopLe = false;
				}
				else // x hợp lệ nhưng coi chừng nó nằm vào những vị trí khoảng trắng ngăn cách giữa 2 nút thì cũng không phải hợp lệ
				{
					// Công thức này là công thức tổng quát dù cho độ rộng giữa các nút có không bằng nhau thì vẫn xài được tuy nhiên phải chấp nhận dùng vòng lặp để duyệt và nếu số lượng nút có nhiều thì sẽ dẫn tới hiệu suất kém
					/*bool Check = false;
					for(int i = 0; i < SoLuongCacNutNhan; ++i)
					{
					if(x >= DanhSachNutNhan[i].x && x <= DanhSachNutNhan[i].x + DanhSachNutNhan[i].DoRong - 1)
					{
					Check = true;
					XuatThongBao("Dang click vao nut " + DanhSachNutNhan[i].ChucNang);
					break;
					}
					}
					if(Check == false)
					{
					XuatThongBao("Vi tri click chuot x khong hop le");
					}*/

					// Lưu ý: Công thức này chỉ đúng với khi độ rộng giữa các nút là bằng nhau, còn nếu độ rộng của các nút không bằng nhau thì phải dùng công thức tổng quát ở trên đi xét duyệt qua tất cả các nút đang có
					int vitriXcuaKhoangTrongNganCachGiua2NutDauTien = DanhSachNutNhan[0].x + DanhSachNutNhan[0].DoRong;
					if((x - vitriXcuaKhoangTrongNganCachGiua2NutDauTien) % (DanhSachNutNhan[0].DoRong + 1) == 0)
					{
						//XuatThongBao("Vi tri click chuot x la khoang trong ngan cach giua 2 nut");
						KiemTraViTriChuotHopLe = false;
					}
					else
					{
						// Bản chất ở đây mình cũng không cần phải cập nhật cờ hiệu = true bởi vì từ đầu nó đã là true rồi
						KiemTraViTriChuotHopLe = true;

						//int idx = (x - DanhSachNutNhan[0].x) / (DanhSachNutNhan[0].DoRong + 1);
						//XuatThongBao("Dang click vao nut co idx = " + to_string(idx));
						//XuatThongBao("Dang click vao nut " + DanhSachNutNhan[idx].ChucNang);
					}
				}
			}

			if(KiemTraViTriChuotHopLe == true)
			{
				ChoPhepMouseMoveHoatDong = false;

				// Tô màu đỏ cho nó
				indexCuaNutClickChuotXuong = (x - DanhSachNutNhan[0].x) / (DanhSachNutNhan[0].DoRong + 1);
				DanhSachNutNhan[indexCuaNutClickChuotXuong].MauNen = DanhSachNutNhan[indexCuaNutClickChuotXuong].MauChu = 192; // màu nền đỏ, chữ màu đen
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaNutClickChuotXuong]);

				//XuatThongBao("Dang click vao nut " + DanhSachNutNhan[idx].ChucNang);

				gotoxy(DanhSachNutNhan[0].x, DanhSachNutNhan[0].y + 3);
				cout << "                                                      ";

				gotoxy(DanhSachNutNhan[0].x, DanhSachNutNhan[0].y + 3);
				cout << "Dang click vao nut " + DanhSachNutNhan[indexCuaNutClickChuotXuong].ChucNang;
			}
			else
			{
				
			}

		}
		else // Xảy ra sự kiện này khi thả chuột ra (Trước đó nhấn vào)
		{
		    //printf("button press\n");
			ChoPhepMouseMoveHoatDong = true;

			// Vị trí nút click xuống hợp lệ trước đó được tô màu đỏ thì khi thả click ra thì chính nút đó sẽ được reset màu trở lại ban đầu
			if(indexCuaNutClickChuotXuong != -1)
			{
				DanhSachNutNhan[indexCuaNutClickChuotXuong].MauNen = DanhSachNutNhan[indexCuaNutClickChuotXuong].MauChu = 112; // màu nền trắng đục, chữ màu đen
				TaoNutNhanChucNang(DanhSachNutNhan[indexCuaNutClickChuotXuong]);
		
				indexCuaNutClickChuotXuong = -1; // Reset lại idx vì idx chỉ lưu vị trí của nút ở lần click đầu tiên, còn khi thả ra mình reset lại màu cho nó thì phải reset lại luôn

				indexCuaNutDiChuyenChuotVao = -1; // Cho nó là -1 để sau khi thả click xong nó tự động gọi lại sự kiện mouse move và nếu nhận thấy vị trí chuột còn đang nằm bên trong nút thì nhờ index này = -1 mà nó thỏa cái if để rồi đi tô màu xanh, còn nếu sau khi thả click mà vị trí chuột nằm ngoài nút thì nó sẽ không làm gì cả do không thỏa if, nhưng nhờ ngay trong sự kiện thả chuột này mình đã reset lại thành màu trắng nên nó vẫn ổn
			}
		}
		break;
	case MOUSE_MOVED:
		int x = mer.dwMousePosition.X + 1;
		int y = mer.dwMousePosition.Y + 1;

		bool KiemTraViTriChuotHopLe = true;

		if(y < DanhSachNutNhan[0].y || y > 3 + DanhSachNutNhan[0].y - 1)
		{
			//XuatThongBao("Vi tri click chuot y khong hop le");

			KiemTraViTriChuotHopLe = false;
		}
		else // y hợp lệ
		{
			if(x < DanhSachNutNhan[0].x || x > DanhSachNutNhan[SoLuongCacNutNhan - 1].x + DanhSachNutNhan[SoLuongCacNutNhan - 1].DoRong - 1)
			{
				//XuatThongBao("Vi tri click chuot x khong hop le");


				KiemTraViTriChuotHopLe = false;
			}
			else // x hợp lệ nhưng coi chừng nó nằm vào những vị trí khoảng trắng ngăn cách giữa 2 nút thì cũng không phải hợp lệ
			{
				// Công thức này là công thức tổng quát dù cho độ rộng giữa các nút có không bằng nhau thì vẫn xài được tuy nhiên phải chấp nhận dùng vòng lặp để duyệt và nếu số lượng nút có nhiều thì sẽ dẫn tới hiệu suất kém
				/*bool Check = false;
				for(int i = 0; i < SoLuongCacNutNhan; ++i)
				{
				if(x >= DanhSachNutNhan[i].x && x <= DanhSachNutNhan[i].x + DanhSachNutNhan[i].DoRong - 1)
				{
				Check = true;
				XuatThongBao("Dang click vao nut " + DanhSachNutNhan[i].ChucNang);
				break;
				}
				}
				if(Check == false)
				{
				XuatThongBao("Vi tri click chuot x khong hop le");
				}*/

				// Lưu ý: Công thức này chỉ đúng với khi độ rộng giữa các nút là bằng nhau, còn nếu độ rộng của các nút không bằng nhau thì phải dùng công thức tổng quát ở trên đi xét duyệt qua tất cả các nút đang có
				int vitriXcuaKhoangTrongNganCachGiua2NutDauTien = DanhSachNutNhan[0].x + DanhSachNutNhan[0].DoRong;
				if((x - vitriXcuaKhoangTrongNganCachGiua2NutDauTien) % (DanhSachNutNhan[0].DoRong + 1) == 0)
				{
					//XuatThongBao("Vi tri click chuot x la khoang trong ngan cach giua 2 nut");


					KiemTraViTriChuotHopLe = false;
				}
				else // Đang ở trong phạm vi của 1 nút nhấn hợp lệ
				{

					// Bản chất ở đây mình cũng không cần phải cập nhật cờ hiệu = true bởi vì từ đầu nó đã là true rồi
					KiemTraViTriChuotHopLe = true;

				}
			}
		}
	
		if(ChoPhepMouseMoveHoatDong == true) // Để tránh tình trạng nếu đang trong quá trình giữ click chưa thả ra mà lại di chuyển chuột thì nó lại gọi lại sự kiện mouse move và lại biến thành màu xanh => nếu chưa thả click thì không cho phép mouse move hoạt động
		{
			if(KiemTraViTriChuotHopLe == true) // chuột di chuyển vào trong phạm vi của 1 nút nào đó
			{
				if(indexCuaNutDiChuyenChuotVao == -1)
				{
					indexCuaNutDiChuyenChuotVao = (x - DanhSachNutNhan[0].x) / (DanhSachNutNhan[0].DoRong + 1);
					//XuatThongBao("Dang click vao nut co idx = " + to_string(idx));
					//XuatThongBao("Dang click vao nut " + DanhSachNutNhan[idx].ChucNang);

					// Tô màu xanh đậm cho nó
					DanhSachNutNhan[indexCuaNutDiChuyenChuotVao].MauNen = DanhSachNutNhan[indexCuaNutDiChuyenChuotVao].MauChu = 160; // màu nền xanh lá cây, chữ màu đen
					TaoNutNhanChucNang(DanhSachNutNhan[indexCuaNutDiChuyenChuotVao]);
				}
			}
			else // vị trí chuột đã nằm ngoài các nút
			{
				if(indexCuaNutDiChuyenChuotVao >= 0)
				{
					DanhSachNutNhan[indexCuaNutDiChuyenChuotVao].MauNen = DanhSachNutNhan[indexCuaNutDiChuyenChuotVao].MauChu = 112; // màu nền trắng đục, chữ màu đen
					TaoNutNhanChucNang(DanhSachNutNhan[indexCuaNutDiChuyenChuotVao]);
					indexCuaNutDiChuyenChuotVao = -1; // Reset lại
				}
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

void TaoNutChucNang(string ChucNang)
{
	//string ChucNang = "New Game";
	int length = ChucNang.length();


	cout << (char)218; // ┌ 
	for(int i = 1; i <= length; ++i)
	{
		cout << (char)196; // ─
	}
	cout << (char)191; //  ┐
	cout << endl;

	cout << (char)179; // │
	cout << ChucNang;
	cout << (char)179; // │
	cout << endl;

	cout << (char)192; // └
	for(int i = 1; i <= length; ++i)
	{
		cout << (char)196; // ─
	}
	cout << (char)217; // ┘
}

void TaoNutNhanChucNang(NUTNHAN nut)
{
	gotoxy(nut.x, nut.y);
	int length = nut.ChucNang.length();
	textcolor(nut.MauNen); // chữ màu đen, nền màu trắng đục
	for(int i = 1; i <= nut.DoRong; ++i)
		cout << " ";
	gotoxy(nut.x, nut.y + 1);
	textcolor(nut.MauChu);

	int SoLuongKhoangTrangTruoc, SoLuongKhoangTrangSau;

	SoLuongKhoangTrangTruoc = (nut.DoRong - length) % 2 == 0 ? (nut.DoRong - length) / 2 : (nut.DoRong - length) / 2;
	SoLuongKhoangTrangSau = (nut.DoRong - length) % 2 == 0 ? (nut.DoRong - length) / 2 : (nut.DoRong - length) / 2 + 1;

	for(int i = 1; i <= SoLuongKhoangTrangTruoc; ++i)
		cout << " ";
	cout << nut.ChucNang;
	for(int i = 1; i <= SoLuongKhoangTrangSau; ++i)
		cout << " ";

	gotoxy(nut.x, nut.y + 2);
	textcolor(nut.MauNen); // chữ màu đen, nền màu trắng đục
	for(int i = 1; i <= nut.DoRong; ++i)
		cout << " ";
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

int main()
{
	//ShowConsoleCursor(false); // ẩn dấu nháy đi

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
	int vitriXbandau = 2;
	int vitriYbandau = 2;

	for(int i = 0; i < SoLuongCacNutNhan; ++i)
	{
		DanhSachNutNhan[i].ChucNang = DanhSachTenCacNutNhan[i];
		DanhSachNutNhan[i].MauNen = 112; // chữ màu đen, nền màu trắng đục
		DanhSachNutNhan[i].MauChu = 112; // chữ màu đen, nền màu trắng đục
		DanhSachNutNhan[i].DoRong = DoDaiLonNhat;
		DanhSachNutNhan[i].y = vitriYbandau;

		if(i != 0) // i từ 1 trở lên
		{
			DanhSachNutNhan[i].x = DanhSachNutNhan[i - 1].x + DanhSachNutNhan[i - 1].DoRong + 1; // 1 ở đây là khoảng cách giữa 2 nút với nhau
		}
		else // i = 0 => nút đầu tiên
		{
			DanhSachNutNhan[i].x = vitriXbandau;
		}

		//DanhSachNutNhan[3].MauNen = DanhSachNutNhan[3].MauChu = 160;
		//DanhSachNutNhan[2].MauNen = DanhSachNutNhan[2].MauChu = 192;

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
			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent); 
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