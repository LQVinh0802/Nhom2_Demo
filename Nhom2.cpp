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
int currentSize = MAXSIZE;
int elementCount = 0;
const float threshold = 0.6;
void resizeHashTable();
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
	if ((float)(elementCount + 1) / currentSize > threshold)
	{
		printf("Dang vuot nguong luu tru, dang mo rong bang bam...\n");
		resizeHashTable();
	}

	int b = HashFuntion(k.sotc);
	place(b, k);
	elementCount++;
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
	printf("\t\t\t\t\tDANH SACH HOC PHAN KHOA CNTT\n");
	printf(" Ma\t\tTen hoc phan\t Tin chi\t  Loai\t\t  Chu nhiem\t\t    Chuyen Nganh\n");
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

//Câu 4
int DeleteHocPhan(char* mahp) {
	for (int i = 0; i < MAXSIZE; i++) {
		HashNode* p = bucket[i];
		HashNode* q = NULL;
		while (p != NULL) {
			if (_strcmpi(p->Key.mahp, mahp) == 0) {
				HashNode*t = p;
				p = p->Next;
				q->Next = p;
				delete t;
				return 1; // Thành công
			}
			else
			{
				q = p;
				p = p->Next;
			}	
		}
	}
	return 0; // Không tìm thấy
}

//Câu 5
NodePtr search(const char* mahp)
{
	for (int b = 0; b < MAXSIZE; b++)
	{
		NodePtr p = bucket[b];
		while (p != NULL)
		{
			if (_strcmpi(p->Key.mahp, mahp) == 0) // So sánh không phân biệt hoa thường
				return p; // Tìm thấy
			p = p->Next;
		}
	}
	return NULL; // Không tìm thấy
}

//Câu 6
void CapNhatHocPhan()
{
	char mahp[10];
	printf("Nhap ma hoc phan can cap nhat: ");
	rewind(stdin);
	gets_s(mahp, sizeof(mahp));

	NodePtr p = search(mahp);
	if (p != NULL)
	{
		printf("Thong tin cu:\n");
		printf(" Ma\t\tTen hoc phan\t Tin chi\t  Loai\t\t  Chu nhiem\t\t    Chuyen Nganh\n");
		xuat1hp(p->Key);

		printf("\n\tNhap thong tin moi");
		printf("\nMa hoc phan duoc giu nguyen\n");
		hocphan newData;
		strcpy(newData.mahp, p->Key.mahp);  // Giữ nguyên khóa chính
		printf("Nhap ten hoc phan: ");
		rewind(stdin); gets_s(newData.tenhp, sizeof(newData.tenhp));

		printf("Nhap so tin chi: ");
		scanf("%d", &newData.sotc);

		printf("Nhap loai hoc phan: ");
		rewind(stdin); gets_s(newData.loaihp, sizeof(newData.loaihp));

		printf("Nhap chu nhiem hoc phan: ");
		rewind(stdin); gets_s(newData.chunhiemhp, sizeof(newData.chunhiemhp));

		printf("Nhap chuyen nganh: ");
		rewind(stdin); gets_s(newData.chuyennganh, sizeof(newData.chuyennganh));

		// Ghi đè dữ liệu
		p->Key = newData;

		printf("\nCap nhat thanh cong!\n");
	}
	else
	{
		printf("Khong tim thay hoc phan co ma %s.\n", mahp);
	}
}
//Câu7
void resizeHashTable()
{
	int oldSize = currentSize;
	currentSize *= 2;
	NodePtr* newBucket = new NodePtr[currentSize];

	for (int i = 0; i < currentSize; i++)
		newBucket[i] = NULL;

	for (int i = 0; i < oldSize; i++)
	{
		NodePtr p = bucket[i];
		while (p != NULL)
		{
			int newIndex = p->Key.sotc % currentSize;
			NodePtr temp = p;
			p = p->Next;

			temp->Next = newBucket[newIndex];
			newBucket[newIndex] = temp;
		}
	}

	delete[] bucket;
	bucket = newBucket;
}

//Câu 8
void xuatHocPhanTinChiLonHon(int x) {
	int dem = 0;
	printf("\n\t\t\t\tCAC HOC PHAN CO SO TIN CHI LON HON %d\n", x);
	printf(" Ma\t\tTen hoc phan\t Tin chi\t  Loai\t\t  Chu nhiem\t\t    Chuyen Nganh\n");
	for (int b = 0; b < MAXSIZE; b++) {
		HashNode* p = bucket[b];
		while (p != NULL) {
			if (p->Key.sotc > x) {
				xuat1hp(p->Key);
				dem++;
			}
			p = p->Next;
		}
	}

	if (!dem)
		printf("\nKhong co hoc phan nao co so tin chi lon hon %d.\n", x);
}

//Câu 9
void tinhTongTinChiCNTT() {
	int tong = 0;
	for (int b = 0; b < MAXSIZE; b++) {
		HashNode* p = bucket[b];
		while (p != NULL) {
			tong += p->Key.sotc;
			p = p->Next;
		}
	}
	viewTable();
	printf("\nTong so tin chi cua cac hoc phan cua khoa CNTT: %d\n", tong);
}

//Câu 10
void thongKeTheoLoaiHocPhan() {
	struct ThongKe {
		char loaihp[20];
		int soluong;
		int tongtinchi;
	} ds[50];

	int dem = 0;

	for (int b = 0; b < MAXSIZE; b++) {
		HashNode* p = bucket[b];
		while (p != NULL) {
			int found = 0;
			for (int i = 0; i < dem; i++) {
				if (_stricmp(ds[i].loaihp, p->Key.loaihp) == 0) {
					ds[i].soluong++;
					ds[i].tongtinchi += p->Key.sotc;
					found = 1;
					break;
				}
			}
			if (!found) {
				strcpy(ds[dem].loaihp, p->Key.loaihp);
				ds[dem].soluong = 1;
				ds[dem].tongtinchi = p->Key.sotc;
				dem++;
			}
			p = p->Next;
		}
	}

	if (dem == 0) {
		printf("\nKhong co du lieu de thong ke.\n");
	}
	else {
		viewTable();
		printf("\n\tThong ke theo tung loai hoc phan\n");
		printf("%-17s %-12s  %-15s\n", "Loai hoc phan", "So luong", "Tong tin chi");
		for (int i = 0; i < dem; i++) {
			printf("%-20s %-15d %-15d\n", ds[i].loaihp, ds[i].soluong, ds[i].tongtinchi);
		}
	}
}

void Menu()
{
	printf("\n\t\t-----------------------------------MENU---------------------------------\n");
	printf("\t\t\t0. Thoat chuong trinh.\n");
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
			case 1:{
				nhapdulieu();
				printf("\nXem bang bam:\n");
				viewTable();
				break;
			}
			case 2:{
				Docfile();
				viewTable();
				break;
			}	
			case 3:{
				hocphan x;
				printf("\tNhap thong tin hoc phan can them");
				nhap1hp(x);
				Insert(x);
				printf("Da them thanh cong.\n");
				viewTable();
				break;
			}
			case 4: {
				char mahp[10];
				printf("Nhap ma hoc phan can xoa: ");
				rewind(stdin);
				gets_s(mahp, sizeof(mahp));  // dùng gets_s nếu Visual Studio báo lỗi gets
				if (DeleteHocPhan(mahp)) {
					printf("Da xoa hoc phan %s thanh cong.\n", mahp);
					printf("Danh sach hoc phan sau khi xoa:\n");
					viewTable();
				}
				else {
					viewTable();
					printf("Khong tim thay hoc phan %s.\n", mahp);
				}
				break;
			}
			
			case 5:{
				char mahp[10];
				printf("Nhap ma hoc phan can tim: ");
				rewind(stdin);
				gets_s(mahp, sizeof(mahp));
				NodePtr found = search(mahp);
				printf(" Ma\t\tTen hoc phan\t Tin chi\t  Loai\t\t  Chu nhiem\t\t    Chuyen Nganh\n");
				if (found != NULL) {
					xuat1hp(found->Key);
				}
				else {
					printf("Khong tim thay hoc phan co ma %s.\n", mahp);
				}
				break;
			}

			case 6:{
				CapNhatHocPhan();
				viewTable();
				break;
			}
			case 7:{
				printf("Dang thuc hien mo rong bang bam theo yeu cau.\n");
				resizeHashTable();
				printf("Mo rong thanh cong! Hien tai kich thuoc bang bam la: %d\n", currentSize);
				viewTable();
				break;
			}
			case 8: {
				int x;
				printf("Nhap so tin chi: ");
				scanf("%d", &x);
				xuatHocPhanTinChiLonHon(x);
				break;
			}
			case 9: 
			{
				tinhTongTinChiCNTT();
    			break;
			}
			case 10:
			{
				thongKeTheoLoaiHocPhan();
				break;
			}

		}
	} while (option != 0);
}

int main()
{
	Process();
}