#include "QuanLy.h"

using namespace std;

int main() {
    MatHang* kho = nullptr; int nKho = 0, sucChuaKho = 0;
    HoaDonXuat* dsHDX = nullptr; int nHDX = 0, sucChuaHDX = 0;
    int choice;

    LoadData(kho, nKho, sucChuaKho, dsHDX, nHDX, sucChuaHDX);

    do {
        cout << "\n=========== QUAN LY DON HANG ===========\n";
        cout << "1. Nhap san pham\n2. Sua thong tin san pham (theo ma)\n3. Xoa san pham\n";
        cout << "4. Nhap thong tin don hang\n5. Sua thong tin don hang (theo ma)\n6. Xoa don hang (theo ma)\n";
        cout << "7. Liet ke toan bo san pham trong he thong\n8. Liet ke toan bo don hang co trong he thong\n9. Thoat khoi he thong\n";
        cout << "========================================\nNhap lua chon: "; 
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
            case 1: themMatHang(kho, nKho, sucChuaKho); break;
            case 2: suaThongTinMatHang(kho, nKho); break;
            case 3: xoaMatHang(kho, nKho, dsHDX, nHDX); break;
            case 4: themHoaDon(dsHDX, nHDX, sucChuaHDX, kho, nKho); break;
            case 5: suaThongTinDonHang(dsHDX, nHDX, kho, nKho); break;
            case 6: xoaHoaDon(dsHDX, nHDX); break;
            case 7: lietKeMatHang(kho, nKho); break;
            case 8: lietKeHoaDon(dsHDX, nHDX, kho, nKho); break;
            case 9: cout << "Da thoat chuong trinh!\n"; break;
            default: cout << "Lua chon khong hop le!\n"; break;
        }

        if (choice >= 1 && choice <= 6) SaveData(kho, nKho, dsHDX, nHDX);

    } while (choice != 9);

    delete[] kho;
    delete[] dsHDX;
    return 0;
}