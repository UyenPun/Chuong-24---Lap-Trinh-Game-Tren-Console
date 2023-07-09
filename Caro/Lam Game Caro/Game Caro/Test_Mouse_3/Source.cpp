#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
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

int main()
{
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

	
	// diễn hoạt game
	while(true)
	{
		//cout << "HELLO WORLD!\n";
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if(InputRecord.EventType == MOUSE_EVENT)
		{
			if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				int x = InputRecord.Event.MouseEvent.dwMousePosition.X + 1;
				int y = InputRecord.Event.MouseEvent.dwMousePosition.Y + 1;

				gotoxy(x, y);
				cout<<"Hello world at "<< x <<" x "<< y<<" ";
			}
		}
		
		if(InputRecord.EventType == KEY_EVENT)
		{
			if(InputRecord.Event.KeyEvent.wVirtualKeyCode)
			{
				if(InputRecord.Event.KeyEvent.bKeyDown)
				{
					if(VK_LEFT)
					{
						cout<<"VK_LEFT   = "<<InputRecord.Event.KeyEvent.wVirtualKeyCode <<" \n";
					}
				}
				
			}
		}

	}

	 SetConsoleMode(hin, fdwMode);
	//system("pause");
	return 0;
}