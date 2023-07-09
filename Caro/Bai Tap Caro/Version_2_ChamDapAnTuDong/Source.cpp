#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#define MAX 20
bool KetQua = true;

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

// vitridong: Là vị trí dòng của quân vừa đánh xuống
// vitricot: Là vị trí cột của quân vừa đánh xuống
char KiemTraHangNgang(char a[MAX][MAX], int n, int vitridong, int vitricot)
{
	//printf("\nDANG XET HANG NGANG");
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
	//printf("\nDANG XET HANG DOC");
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
	//printf("\nDANG XET CHEO CHINH");
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
	//printf("\nDANG XET CHEO PHU");
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

char* KetQuaThuatToan(char a[MAX][MAX], char *input)
{
	FILE *FileIn = fopen(input, "r");
	if(!FileIn)
		return "loi";

	// Còn chạy xuống dưới đây tức là tập tin có tồn tại nhưng chúng ta không viết là else nhìn nó lúa lắm
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

				if(KiemTraHangNgang(a, n, i, j) != '.' || KiemTraHangDoc(a, n, i, j) != '.' 
					|| KiemTraCheoChinh(a, n, i, j) != '.' || KiemTraCheoPhu(a, n, i, j) != '.')
				{
					// Đóng file lại
					fclose(FileIn);

					if(a[i][j] == 'x')
						return "Ti wins";
					
					return "Teo wins";
				}

			}
		}
		fprintf(FileIn, "%c", &c); // ký tự xuống dòng ở hàng hiện tại để xuống hàng dưới
	}

	// Đóng file lại
	fclose(FileIn);
	return "Not yet";
}

char* KetQuaBoTest(char* output)
{
	FILE* FileOut = fopen(output, "r");

	if(!FileOut)
		return "loi";

	char ketquadung[10];
	fgets(ketquadung, sizeof(ketquadung), FileOut);

	fclose(FileOut);

	return ketquadung;
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

void XuatKetQuaVoiMotBoTest(char a[MAX][MAX], char *input, char *output)
{
	char ketquathuattoan[10];

	clock_t start = clock();
	strcpy(ketquathuattoan, KetQuaThuatToan(a, input));
	clock_t end = clock();
	bool Check = true;

	if(strcmp(ketquathuattoan, "loi") == 0)
	{
		printf("\nKhong tim thay tap tin %s. Xin kiem tra lai!", input);
		Check = false;
	}
	else
		printf("\nVoi Input: %s => Ket qua thuat toan: %s", input, ketquathuattoan);

	if(Check == true) // có tồn tại tập tin input thì mới tiếp tục làm
	{
		char ketquabotest[10];
		strcpy(ketquabotest, KetQuaBoTest(output));

		if(strcmp(ketquabotest, "loi") == 0)
		{
			printf("\nKhong tim thay tap tin %s. Xin kiem tra lai!", output);
		}
		else // có tồn tại tập tin output thì mới tiếp tục làm
		{
			printf("\nVoi Output: %s => Ket qua bo test: %s", output, ketquabotest);

			if(strcmp(ketquathuattoan, ketquabotest) == 0)
			{
				textcolor(9); // tô màu xanh
				printf("\n=> 2 ket qua giong nhau");
				textcolor(7); // trở lại màu trắng ban đầu
			}
			else
			{
				textcolor(12); // tô màu đỏ
				printf("\n=> 2 ket qua khac nhau");
				textcolor(7); // trở lại màu trắng ban đầu
				KetQua = false;
			}

			double thoigianchay = (double)(end - start) / CLOCKS_PER_SEC;
			printf("\nChuong trinh chay mat %lf giay", thoigianchay);

			if(thoigianchay <= 1)
			{
				textcolor(9); // tô màu xanh
				printf("\n=> Thoi gian chay thoa yeu cau bai toan");
				textcolor(7); // trở lại màu trắng ban đầu
			}
			else
			{
				textcolor(12); // tô màu đỏ
				printf("\n=> Thoi gian chay khong thoa yeu cau bai toan");
				textcolor(7); // trở lại màu trắng ban đầu
				KetQua = false;
			}
		}

	}

}

int main()
{
	// Cách test danh sách bảng màu
	/*for(int i = 1; i <= 200; ++i)
	{
	textcolor(i);
	printf("\ni = %d", i);
	}*/

	char a[MAX][MAX];
	char input[30];
	char output[30];

	for(int i = 1; i <= 12; ++i) // có 12 bộ test thì để con số 12
	{
		strcpy(input, "input");
		strcpy(output, "output");
		char value[10];
		strcat(input, itoa(i, value, 10));
		strcat(input, ".txt");
		strcat(output, itoa(i, value, 10));
		strcat(output, ".txt");

		XuatKetQuaVoiMotBoTest(a, input, output);
		printf("\n--------------------------\n");

		if(KetQua == false) // Bị sai ở bộ test nào thì dừng lại luôn không xét các bộ test sau nữa
			break;

		// Qua mỗi một bộ test thì phải reset lại bàn cờ nếu không sẽ bị lỗi
		for(int i = 0; i < MAX; ++i)
		{
			for(int j = 0; j < MAX; ++j)
				a[i][j] = '.';
		}
	}

	if(KetQua == true)
	{
		textcolor(14); // tô màu vàng
		printf("\n\nACCEPT");
		textcolor(7); // Trở lại màu bình thường
	}
	else
	{
		textcolor(14); // tô màu vàng
		printf("\n\nWRONG");
		textcolor(7); // Trở lại màu bình thường
	}

	getch();
	return 0;
}