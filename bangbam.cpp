#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#define MAXSIZE 29
#define TRUE 1
#define FALSE 0
using namespace std;
//Khai báo cấu trúc thông tin học phần
struct hocphan
{
	char mahp[10];
	char tenhp[25];
	int sotc;
	char loaihp[20];
	char chunhiemhp[25];
	char chuyennganh[25];
};
typedef hocphan ItemType;
//Khai báo cấu trúc cho bảng băm
struct HashNode
{
	ItemType Key;
	HashNode* Next;
};

//Con trỏ đến cấu trúc một HashNode
typedef HashNode *NodePtr;
//bucket là con trỏ dến NodePtr
NodePtr* bucket;

//Hàm băm
int HashFuntion(int key)
{
	return key%MAXSIZE;
}

//phép toán khởi tạo
void initBucket()
{
	bucket = new NodePtr[MAXSIZE];
	for (int i = 0; i<MAXSIZE; i++)
		bucket[i] = NULL;
}

//kiểm tra bucket rỗng
int isEmptyBucket(int b)
{
	return (bucket[b] == NULL ? 1 : 0);
}

//kiểm tra bảng băm rỗng
int isEmpty()
{
	for (int i = 0; i<MAXSIZE; i++)
	{
		if (bucket[i] != NULL)
			return FALSE;
	}
	return TRUE;
}

//Thêm một node vào đầu bucket
void Push(int b, ItemType x)
{
	HashNode* p = new HashNode;
	p->Key = x;
	p->Next = bucket[b];
	bucket[b] = p;
}

//thêm vào bucket một node mới sau p
void insertAfter(HashNode* p, ItemType k)
{
	if (p == NULL)
		printf("Khong them vao node moi");
	else
	{
		HashNode* q = new HashNode;
		q->Key = k;
		q->Next = p->Next;
		p->Next = q;
	}
}
//phép toán chèn khóa k vào danh sách liên kết
void place(int b, ItemType k)
{
	HashNode* p, *q;
	q = NULL;
	for (p = bucket[b]; (p != NULL) && (_strcmpi(k.mahp, p->Key.mahp)>0); p = p->Next)
		q = p;
	if (q == NULL)
		Push(b, k);
	else
		insertAfter(q, k);

}
//chèn phần tử có khóa k vào bảng băm
void Insert(ItemType k)
{
	int b = HashFuntion(k.sotc);
	place(b, k);
}

void xuat1hp(hocphan x)
{
	printf("%-10s %-25s %-4d \t%-15s %-25s %-25s\n", x.mahp, x.tenhp, x.sotc, x.loaihp, x.chunhiemhp, x.chuyennganh);
}
//duyệt các phần tử trong bucket
void TableBucket(int b)
{
	HashNode* p = bucket[b];
	while (p != NULL)
	{
		xuat1hp(p->Key);
		p = p->Next;
	}
}
//Tác vụ duyệt toàn bộ bảng băm
void viewTable()
{
	printf("\t\t\t\t\tDANH SACH HOC PHAN\n");
	printf("Ma\t\tTen\t\t Tin chi\tLoai\t\t\tChu nhiem\tChuyen Nganh\n");
	for (int b = 0; b<MAXSIZE; b++)
	{
		if (bucket[b] != NULL)
		{
			TableBucket(b);
		}
	}

}

void nhap1hp(hocphan &x)
{
	printf("\nNhap ma hoc phan:");
	rewind(stdin);
	gets(x.mahp);
	printf("Nhap ten hoc phan:");
	rewind(stdin);
	gets(x.tenhp);
	printf("Nhap so tin chi:");
	scanf("%d", &x.sotc);
	printf("Nhap loai hoc phan:");
	rewind(stdin);
	gets(x.loaihp);
	printf("Nhap chu nhiem hoc phan:");
	rewind(stdin);
	gets(x.chunhiemhp);
	printf("Nhap chuyen nganh:");
	rewind(stdin);
	gets(x.chuyennganh);
}

void nhapdulieu()
{
	int n, x;
	printf("Nhap so hoc phan: ");
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		hocphan x;
		printf("\tNhap hoc phan thu %d", i);
		nhap1hp(x);
		Insert(x);
	}
}
void Docfile()
{
	int n;
	ItemType key;
	FILE* f = fopen("DSHP.txt", "r+");
	if (!f)
	{
		printf("Loi doc file");
		return;
	}
	fscanf(f, "%d\n", &n);
	for (int i = 0; i<n; i++)
	{
		fscanf(f, "%9[^#]#%24[^#]#%d#%9[^#]#%24[^#]#%24[^\n]\n", key.mahp, key.tenhp, &key.sotc, key.loaihp, key.chunhiemhp, key.chuyennganh);
		Insert(key);
	}
	fclose(f);
}

int DeleteHocPhan(char* mahp) {
	for (int b = 0; b < MAXSIZE; b++) {
		HashNode* p = bucket[b];
		HashNode* prev = NULL;

		while (p != NULL) {
			if (_strcmpi(p->Key.mahp, mahp) == 0) {
				if (prev == NULL) {
					// Node đầu tiên
					bucket[b] = p->Next;
				}
				else {
					prev->Next = p->Next;
				}
				delete p;
				return 1; // Thành công
			}
			prev = p;
			p = p->Next;
		}
	}
	return 0; // Không tìm thấy
}

void xuatHocPhanTinChiLonHon(int x) {
	int found = 0;
	printf("\nCAC HOC PHAN CO SO TIN CHI LON HON %d:\n", x);
	printf("Ma\t\tTen\t\t Tin chi\tLoai\t\tChu nhiem\tChuyen Nganh\n");

	for (int b = 0; b < MAXSIZE; b++) {
		HashNode* p = bucket[b];
		while (p != NULL) {
			if (p->Key.sotc > x) {
				xuat1hp(p->Key);
				found = 1;
			}
			p = p->Next;
		}
	}

	if (!found)
		printf("Khong co hoc phan nao co so tin chi lon hon %d.\n", x);
}



void Menu()
{
	printf("\t\t-----------------------------------MENU---------------------------------\n");
	printf("\t\t\t1. Tao bang bam tu nhap.\n");
	printf("\t\t\t2. Tao bang bam tu file txt.\n");
	printf("\t\t\t3. Them mot phan tu.\n");
	printf("\t\t\t4. Xoa mot phan tu.\n");
	printf("\t\t\t5. Tim kiem mot phan tu.\n");
	printf("\t\t\t6. Cap nhat thong tin mot phan tu.\n");
	printf("\t\t\t7. Dieu chinh lai kich thuoc khi qua nguong luu tru.\n");
	printf("\t\t\t8. Xuat cac hoc phan co so tin chi lon hon X.\n");
	printf("\t\t\t9. Tinh tong so tin chi cua cac hoc phan.\n");
	printf("\t\t\t10. Dem so luong va tong so tin chi theo tung loai hoc phan.\n");
	printf("\t\t------------------------------------------------------------------------\n");
}
void Process()
{
	int option;
	HashNode *p;
	initBucket();
	do
	{
		Menu();
		printf("Chon chuc nang: ");
		scanf_s("%d", &option);
		switch (option)
		{
		case 1:
			nhapdulieu();
			printf("\nXem bang bam:\n");
			viewTable();
			break;
		case 2:
			Docfile();
			viewTable();
			break;
		case 3:
			break;
		
		case 4: {
					char mahp[10];
					printf("Nhap ma hoc phan can xoa: ");
					rewind(stdin);
					fgets(mahp, sizeof(mahp), stdin);  // dùng gets_s nếu Visual Studio báo lỗi gets

					if (DeleteHocPhan(mahp)) {
						printf("Da xoa hoc phan %s thanh cong.\n", mahp);
						printf("Danh sach hoc phan sau khi xoa:\n");
						viewTable();
					}
					else {
						printf("Khong tim thay hoc phan %s.\n", mahp);
					}
					break;
		}

		
		case 8: {
					int x;
					printf("Nhap so tin chi: ");
					scanf("%d", &x);
					xuatHocPhanTinChiLonHon(x);
					break;
		}


		}
	} while (option != 0);
}
int main()
{
	Process();
}