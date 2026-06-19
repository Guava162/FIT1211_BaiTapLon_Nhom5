#include "QuanLy.h"

using namespace std;

// ==================== LỚP ChiTietDonHang ====================

ChiTietDonHang::ChiTietDonHang() {
    strcpy(maHang, ""); 
    strcpy(tenHang, "");
    donGia = 0; 
    soLuong = 0;
}

// Constructor khởi tạo có truyền tham số. Sao chép thông tin sp từ kho sang hoá đơn, giữ nguyên giá ở thời điểm mua.
ChiTietDonHang::ChiTietDonHang(const char* ma, const char* ten, double gia, int sl) {
    strcpy(maHang, ma); 
    strcpy(tenHang, ten);
    donGia = gia; 
    soLuong = sl;
}


const char* ChiTietDonHang::getMaHang() const { return maHang; }
int ChiTietDonHang::getSoLuong() const { return soLuong; }
void ChiTietDonHang::setSoLuong(int sl) { if (sl > 0) soLuong = sl; }
void ChiTietDonHang::congThemSoLuong(int slThem) { soLuong += slThem; }

// Hiển thị thông tin ngắn
void ChiTietDonHang::xuatNgan() const {
    cout << "  - Ma: " << left << setw(15) << maHang 
         << "| Ten: " << setw(20) << tenHang 
         << "| SL: " << soLuong << "\n";
}

double ChiTietDonHang::tinhThanhTien() const { return donGia * soLuong; }

void ChiTietDonHang::inChiTietFormat() const {
    cout << "| " << left << setw(10) << maHang << setw(22) << tenHang 
         << fixed << setprecision(0) << setw(12) << donGia << defaultfloat 
         << setw(6) << soLuong << fixed << setprecision(0) << setw(14) 
         << tinhThanhTien() << "|\n";
}

// ==================== LỚP DonHang ====================

DonHang::DonHang() {
    strcpy(maHD, ""); 
    soLuongMatHang = 0; 
}


void DonHang::setMaHD(const char* ma) { strcpy(maHD, ma); }
const char* DonHang::getMaHD() const { return maHD; }

// Kiểm tra trùng mã
bool DonHang::chuaMatHang(const char* ma) const {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) return true;
    }
    return false; 
}

int DonHang::getSoLuongLoaiHang() const { return soLuongMatHang; }
const ChiTietDonHang& DonHang::getChiTiet(int index) const { return danhSachBan[index]; }

// Lấy số lượng mua của từng mặt hàng trong hoá đơn 
int DonHang::laySoLuongMatHang(const char* ma) const {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) return danhSachBan[i].getSoLuong();
    }
    return 0; 
}

// Thêm sản phẩm vào đơn, tự động thêm vào số lượng hiện nếu đã tồn tại
void DonHang::themMatHang(const char* ma, const char* ten, double gia, int sl) {
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

    danhSachBan[soLuongMatHang++] = ChiTietDonHang(ma, ten, gia, sl);
    cout << "  Da them mat hang vao don.\n";
}

// Thay đổi số lượng mua của hàng trong đơn
void DonHang::suaSoLuong(const char* ma, int slMoi) {
    if (slMoi <= 0) { cout << "  [!] So luong phai > 0.\n"; return; }
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            danhSachBan[i].setSoLuong(slMoi);
            cout << "  Da cap nhat so luong.\n"; return;
        }
    }
    cout << "  [!] Khong tim thay mat hang trong don.\n";
}

// Xóa 1 mặt hàng khỏi đơn
void DonHang::xoaMatHang(const char* ma) {
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

// In thông tin ngắn gọn
void DonHang::xuatNgan() const {
    cout << "\nMa Don: " << maHD << "\n";
    if (soLuongMatHang == 0) { cout << "  (Don hang trong)\n"; return; }
    for (int i = 0; i < soLuongMatHang; i++) {
        danhSachBan[i].xuatNgan(); 
    }
}

// In phiếu tính tiền dạng bảng
void DonHang::xuatChiTiet() const {
    double tongTien = 0; 
    
    cout << "\n+-----------------------------------------------------------------+\n";
    cout << "| Ma Don Hang: " << left << setw(51) << maHD << "|\n";
    cout << "+-----------------------------------------------------------------+\n";
    
    if (soLuongMatHang == 0) {
        cout << "| " << left << setw(64) << "(Don hang trong)" << "|\n";
        cout << "+-----------------------------------------------------------------+\n";
        return;
    }
    
    cout << "| " << left << setw(10) << "Ma Hang" << setw(22) << "Ten Hang (Snapshot)" 
         << setw(12) << "Don Gia" << setw(6)  << "SL" << setw(14) << "Thanh Tien" << "|\n";
    cout << "+-----------------------------------------------------------------+\n";
    
    for (int i = 0; i < soLuongMatHang; i++) {
        danhSachBan[i].inChiTietFormat(); 
        tongTien += danhSachBan[i].tinhThanhTien(); 
    }
    
    cout << "+-----------------------------------------------------------------+\n";
    
    string tongTienStr = to_string((long long)tongTien) + " VND"; // Gộp tongTien và "VND" thành 1 string
    
    cout << "| " << right << setw(48) << "TONG TIEN: " << left << setw(16) << tongTienStr << "|\n";
    cout << "+-----------------------------------------------------------------+\n";
}