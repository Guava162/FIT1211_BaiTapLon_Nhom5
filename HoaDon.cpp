#include "QuanLy.h"

using namespace std;

// ==================== ChiTietHoaDon ====================

ChiTietHoaDon::ChiTietHoaDon() {
    strcpy(maHang, ""); strcpy(tenHang, "");
    donGia = 0; soLuong = 0;
}

ChiTietHoaDon::ChiTietHoaDon(const char* ma, const char* ten, double gia, int sl) {
    strcpy(maHang, ma); strcpy(tenHang, ten);
    donGia = gia; soLuong = sl;
}

const char* ChiTietHoaDon::getMaHang() const { return maHang; }
int ChiTietHoaDon::getSoLuong() const { return soLuong; }
void ChiTietHoaDon::setSoLuong(int sl) { if (sl > 0) soLuong = sl; }
void ChiTietHoaDon::congThemSoLuong(int slThem) { soLuong += slThem; }

void ChiTietHoaDon::xuatNgan() const {
    cout << "  - Ma: " << left << setw(15) << maHang 
         << "| Ten: " << setw(20) << tenHang 
         << "| SL: " << soLuong << "\n";
}

double ChiTietHoaDon::tinhThanhTien() const { return donGia * soLuong; }

void ChiTietHoaDon::inChiTietFormat() const {
    cout << "| " << left << setw(12) << maHang << setw(20) << tenHang 
         << fixed << setprecision(0) << setw(10) << donGia << defaultfloat 
         << setw(6) << soLuong << fixed << setprecision(0) << setw(12) 
         << tinhThanhTien() << "|\n";
}

// ==================== HoaDon ====================

HoaDon::HoaDon() {
    strcpy(maHD, ""); soLuongMatHang = 0; 
}

void HoaDon::setMaHD(const char* ma) { strcpy(maHD, ma); }
const char* HoaDon::getMaHD() const { return maHD; }

bool HoaDon::chuaMatHang(const char* ma) const {
    for (int i = 0; i < soLuongMatHang; i++)
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) return true;
    return false;
}

int HoaDon::getSoLuongCacLoaiHang() const { return soLuongMatHang; }
const ChiTietHoaDon& HoaDon::getChiTiet(int index) const { return danhSachBan[index]; }

// Lấy số lượng của 1 mặt hàng cụ thể đang có trong đơn (dùng để tính hoàn kho)
int HoaDon::laySoLuongCuaMatHang(const char* ma) const {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) return danhSachBan[i].getSoLuong();
    }
    return 0;
}

void HoaDon::themMatHang(const char* ma, const char* ten, double gia, int sl) {
    if (sl <= 0) return; 
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            danhSachBan[i].congThemSoLuong(sl);
            cout << "  [+] Da cong don them so luong vao mat hang hien co.\n";
            return;
        }
    }
    
    if (soLuongMatHang >= maxSpDon) {
        cout << "  [!] Don hang da day (toi da 100 loai mat hang).\n"; return;
    }

    danhSachBan[soLuongMatHang++] = ChiTietHoaDon(ma, ten, gia, sl);
    cout << "  Da them mat hang vao don.\n";
}

void HoaDon::suaSoLuong(const char* ma, int slMoi) {
    if (slMoi <= 0) { cout << "  [!] So luong phai > 0.\n"; return; }
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            danhSachBan[i].setSoLuong(slMoi);
            cout << "  Da cap nhat so luong.\n"; return;
        }
    }
    cout << "  [!] Khong tim thay mat hang trong don.\n";
}

void HoaDon::xoaMatHang(const char* ma) {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            for (int j = i; j < soLuongMatHang - 1; j++) {
                danhSachBan[j] = danhSachBan[j + 1];
            }
            soLuongMatHang--; 
            cout << "  Da xoa mat hang khoi don.\n";
            if (soLuongMatHang == 0) cout << "  [!] Canh bao: Don hang hien dang trong.\n";
            return;
        }
    }
    cout << "  [!] Khong tim thay mat hang trong don.\n";
}

void HoaDon::xuatNgan() const {
    cout << "\nMa Don: " << maHD << "\n";
    if (soLuongMatHang == 0) { cout << "  (Don hang trong)\n"; return; }
    for (int i = 0; i < soLuongMatHang; i++) danhSachBan[i].xuatNgan();
}

void HoaDon::xuatChiTiet() const {
    double tongTien = 0;
    cout << "\n+--------------------------------------------------+\n";
    cout << "| Ma Don Hang: " << left << setw(36) << maHD << "|\n";
    cout << "+--------------------------------------------------+\n";
    if (soLuongMatHang == 0) {
        cout << "| (Don hang trong)                                 |\n+--------------------------------------------------+\n";
        return;
    }
    cout << "| " << left << setw(12) << "Ma Hang" << setw(20) << "Ten Hang (Snapshot)" << setw(10) << "Don Gia" << setw(6)  << "SL" << setw(12) << "Thanh Tien" << "|\n";
    cout << "+--------------------------------------------------+\n";
    
    for (int i = 0; i < soLuongMatHang; i++) {
        danhSachBan[i].inChiTietFormat();
        tongTien += danhSachBan[i].tinhThanhTien();
    }
    
    cout << "+--------------------------------------------------+\n";
    cout << "| " << right << setw(47) << "TONG TIEN: " << fixed << setprecision(0) << setw(0) << tongTien << " VND |\n+--------------------------------------------------+\n";
}