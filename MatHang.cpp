#include "QuanLy.h"

using namespace std;

MatHang::MatHang() {
    strcpy(maHang, "");
    strcpy(tenHang, "");
    giaBan = 0;
}

void MatHang::nhap() {
    // Đọc maHang bằng cin >>, sau đó ignore '\n' còn trong buffer
    cout << "  Nhap ma mat hang (toi da 20 ky tu): ";
    cin.width(21);
    cin >> maHang;
    cin.ignore(10000, '\n'); // Xóa '\n' sau cin >> để getline hoạt động đúng

    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, 51);

    cout << "  Nhap gia ban: ";
    while (!(cin >> giaBan) || giaBan < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Gia ban khong hop le, nhap lai: ";
    }
    cin.ignore(10000, '\n'); // Xóa '\n' sau cin >> giaBan
}

void MatHang::xuat() const {
    cout << left << setw(20) << maHang << setw(35) << tenHang << fixed << setprecision(0) << giaBan << defaultfloat << "VND\n";
}

const char* MatHang::getMaHang() const { return maHang; }
const char* MatHang::getTenHang() const { return tenHang; }
double MatHang::getGiaBan() const { return giaBan; }
void MatHang::setTenHang(const char* ten) { strcpy(tenHang, ten); }
void MatHang::setGiaBan(double gia) { giaBan = gia; }
