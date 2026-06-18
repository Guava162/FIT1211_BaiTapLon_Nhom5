#include "QuanLy.h"

using namespace std;

// Khởi tạo mặc định: rỗng và giá 0
MatHang::MatHang() {
    strcpy(maHang, "");
    strcpy(tenHang, "");
    giaBan = 0;
}

// Nhập đầy đủ mã, tên, giá từ bàn phím (dùng khi gọi độc lập, không qua bước validate riêng)
void MatHang::nhap() {
    cout << "  Nhap ma mat hang (toi da 20 ky tu): ";
    cin.width(21); cin >> maHang; cin.ignore(10000, '\n');

    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, 51);

    cout << "  Nhap gia ban: ";
    giaBan = nhapSoThucDuong("  Gia ban khong hop le, nhap lai: ");
}

// Gán mã đã có (đã được kiểm tra không trùng từ trước), chỉ còn nhập tên + giá
void MatHang::nhapConMa(const char* ma) {
    strcpy(maHang, ma);
    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, 51);
    cout << "  Nhap gia ban: ";
    giaBan = nhapSoThucDuong("  Gia ban khong hop le, nhap lai: ");
}

// In 1 dòng: mã | tên | giá bán (VND)
void MatHang::xuat() const {
    cout << left << setw(20) << maHang << setw(35) << tenHang
         << fixed << setprecision(0) << giaBan << defaultfloat << "VND\n";
}

const char* MatHang::getMaHang()  const { return maHang; }
const char* MatHang::getTenHang() const { return tenHang; }
double      MatHang::getGiaBan()  const { return giaBan; }
void MatHang::setTenHang(const char* ten) { strcpy(tenHang, ten); }
void MatHang::setGiaBan(double gia)       { giaBan = gia; }
