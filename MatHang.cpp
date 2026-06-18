#include "QuanLy.h"

using namespace std;

MatHang::MatHang() {
    strcpy(maHang, "");
    strcpy(tenHang, "");
    giaBan = 0;
    soLuongTon = 0;
}

void MatHang::nhap() {
    cout << "  Nhap ma mat hang (toi da 20 ky tu): ";
    cin.width(maxMa); cin >> maHang; cin.ignore(10000, '\n');

    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, maxTen);
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }

    cout << "  Nhap gia ban: ";
    giaBan = nhapSoThucDuong("  Gia ban khong hop le, nhap lai: ");
    
    cout << "  Nhap so luong ton kho: ";
    soLuongTon = nhapSoNguyenKhongAm("  So luong khong hop le, nhap lai: ");
}

void MatHang::nhapConMa(const char* ma) {
    strcpy(maHang, ma); 
    
    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, maxTen);
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }

    cout << "  Nhap gia ban: ";
    giaBan = nhapSoThucDuong("  Gia ban khong hop le, nhap lai: ");
    
    cout << "  Nhap so luong ton kho: ";
    soLuongTon = nhapSoNguyenKhongAm("  So luong khong hop le, nhap lai: ");
}

void MatHang::xuat() const {
    cout << left << setw(15) << maHang << setw(30) << tenHang 
         << setw(10) << soLuongTon 
         << fixed << setprecision(0) << giaBan << defaultfloat << " VND\n";
}

const char* MatHang::getMaHang()  const { return maHang; }
const char* MatHang::getTenHang() const { return tenHang; }
double      MatHang::getGiaBan()  const { return giaBan; }
int         MatHang::getSoLuongTon() const { return soLuongTon; }

void MatHang::setTenHang(const char* ten) { strcpy(tenHang, ten); }
void MatHang::setGiaBan(double gia)       { giaBan = gia; }

// Cho phép số âm để trừ kho, số dương để nhập thêm
void MatHang::capNhatSoLuongTon(int sl)   { soLuongTon += sl; }