#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#define MAX 20

void XuatBanCo(char a[MAX][MAX], int n)
{
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			printf("%4c", a[i][j]);
		}
		printf("\n");
	}
}

void KetQua(char kiemtra, FILE *&FileIn, clock_t start, clock_t &end)
{
	if(kiemtra != '.')
	{
		if(kiemtra == 'x')
		{
			printf("\nTi wins");
		}
		else
		{
			printf("\nTeo wins");
		}

		end = clock(); // Lấy thời gian tại thời điểm kết thúc

		printf("\nChuong trinh chay mat %lf giay", (double)(end - start) / CLOCKS_PER_SEC);

		// Đóng file lại
		fclose(FileIn);
		getch();
		exit(0); // Dừng toàn bộ chương trình
	}
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraHangNgang(char a[MAX][MAX], int n, int vitridong, int vitricot)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống

	// Xét qua bên trái trước (ngang trái)
	for(int j = vitricot - 1; j >= 0; --j)
	{
		if(a[vitridong][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nHang ngang");
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}
	}

	// Xét qua bên phải (ngang phải)
	for(int j = vitricot + 1; j < n; ++j)
	{
		if(a[vitridong][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nHang ngang");
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}
	}
	return '.'; // chưa thắng
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraHangDoc(char a[MAX][MAX], int n, int vitridong, int vitricot)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống

	// Xét lên trên trước (dọc trên)
	for(int i = vitridong - 1; i >= 0; --i)
	{
		if(a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nHang doc");
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}
	}

	// Xét xuống dưới (dọc dưới)
	for(int i = vitridong + 1; i < n; ++i)
	{
		if(a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nHang doc");
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}
	}
	return '.'; // chưa thắng
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraCheoChinh(char a[MAX][MAX], int n, int vitridong, int vitricot)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống

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

			if(dem == 5)
			{
				printf("\nCheo chinh");
				return a[vitridong][vitricot];
			}
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
	i = vitridong + 1;
	j = vitricot + 1;
	while(true)
	{
		if(i == n || j == n)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nCheo chinh");
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}

		// Xét qua lần lặp mới
		i++;
		j++;
	}
	return '.'; // chưa thắng
}

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraCheoPhu(char a[MAX][MAX], int n, int vitridong, int vitricot)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống

	// Kiểm tra chéo phụ trên: Dòng giảm - cột tăng. Dòng giảm tối đa tới 0, Cột tăng tối đa nới n - 1
	int i = vitridong - 1;
	int j = vitricot + 1;
	while(true)
	{
		if(i < 0 || j == n)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nCheo phu");
				return a[vitridong][vitricot];
			}
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
	i = vitridong + 1;
	j = vitricot - 1;
	while(true)
	{
		if(i == n || j < 0)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				printf("\nCheo phu");
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}

		// Xét qua lần lặp mới
		i++;
		j--;
	}
	return '.'; // chưa thắng
}

int main()
{
	char a[MAX][MAX];
	char *input = "input2.txt";

	clock_t start = clock(); // Lấy thời gian tại thời điểm bắt đầu
	clock_t end;

	FILE *FileIn = fopen(input, "r");
	if(!FileIn)
	{
		printf("\nKhong tim thay tap tin %s. Xin kiem tra lai!", input);
	}
	else // Có tồn tại tập tin => đi Xử lý
	{
		int n;
		fscanf(FileIn, "%d", &n);
		
		/*Note: Khi đọc file chứa các ký tự thì nhớ phải đọc ký tự xuống dòng kèm theo nếu không sẽ tùm lum */

		char c;
		fprintf(FileIn, "%c", &c); // ký tự xuống dòng đằng sau số 5 phải đọc vào

		// Sau khi có kích thước bàn cờ rồi thì chúng ta sẽ tiến hành khởi tạo bàn cờ
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				a[i][j] = '.';

				fscanf(FileIn, "%c", &a[i][j]);

				if(a[i][j] != '.') // có thể là x hay o => đi kiểm tra tính thắng/thua
				{
					// Tiến hành kiểm tra xử lý
					
					KetQua(KiemTraHangNgang(a, n, i, j), FileIn, start, end);
					KetQua(KiemTraHangDoc(a, n, i, j), FileIn, start, end);
					KetQua(KiemTraCheoChinh(a, n, i, j), FileIn, start, end);
					KetQua(KiemTraCheoPhu(a, n, i, j), FileIn, start, end);
					
				}
			}
			fprintf(FileIn, "%c", &c); // ký tự xuống dòng ở hàng hiện tại để xuống hàng dưới
		}

		XuatBanCo(a, n);
		printf("\nNot yet");
		end = clock(); // Lấy thời gian tại thời điểm kết thúc

		printf("\nChuong trinh chay mat %lf giay", (double)(end - start) / CLOCKS_PER_SEC);

		// Đóng file lại
		fclose(FileIn);
	}

	getch();
	return 0;
}