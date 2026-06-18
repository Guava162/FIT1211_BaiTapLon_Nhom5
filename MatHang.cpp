#include "QuanLy.h"

using namespace std;

MatHang::MatHang() {
    strcpy(maHang, "");  
    strcpy(tenHang, ""); 
    giaBan = 0;          
    soLuongTon = 0;      
}

// Nhập mới hoàn toàn thông tin mặt hàng
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

// Nhập thông tin bổ sung khi đã biết trước mã mặt hàng
void MatHang::nhapThem(const char* ma) {
    strcpy(maHang, ma); 
    
    cout << "  Nhap ten mat hang: ";
    cin.getline(tenHang, maxTen);
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }

    cout << "  Nhap gia ban: ";
    giaBan = nhapSoThucDuong("  Gia ban khong hop le, nhap lai: ");
    
    cout << "  Nhap so luong ton kho: ";
    soLuongTon = nhapSoNguyenKhongAm("  So luong khong hop le, nhap lai: ");
}

// In thông tin mặt hàng trên 1 dòng
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
void MatHang::capNhatSoLuongTon(int sl)   { soLuongTon += sl; }