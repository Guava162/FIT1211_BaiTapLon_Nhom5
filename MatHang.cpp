#include "QuanLy.h"

using namespace std;

MatHang::MatHang() {
    strcpy(maHang, "");
    strcpy(tenHang, "");
    giaBan = 0;
}

void MatHang::nhap() {
    cout << "  Nhap ma mat hang (toi da 20 ky tu): ";
    cin.width(21); cin >> maHang; cin.ignore(10000, '\n');

    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, 51);

    cout << "  Nhap gia ban: ";
    // Sử dụng hàm tiện ích đã viết ở QuanLy.cpp
    giaBan = nhapSoThucDuong("  Gia ban khong hop le, nhap lai: ");
}

void MatHang::xuat() const {
    cout << left << setw(20) << maHang << setw(35) << tenHang << fixed << setprecision(0) << giaBan << defaultfloat << "VND\n";
}

const char* MatHang::getMaHang() const { return maHang; }
const char* MatHang::getTenHang() const { return tenHang; }
double MatHang::getGiaBan() const { return giaBan; }
void MatHang::setTenHang(const char* ten) { strcpy(tenHang, ten); }
void MatHang::setGiaBan(double gia) { giaBan = gia; }