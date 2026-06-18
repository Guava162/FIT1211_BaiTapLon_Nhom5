#include "QuanLy.h"

using namespace std;

// Khởi tạo: mã rỗng, số lượng 0
ChiTietHoaDon::ChiTietHoaDon() {
    strcpy(maHang, ""); soLuong = 0;
}

ChiTietHoaDon::ChiTietHoaDon(const char* ma, int sl) {
    strcpy(maHang, ma); soLuong = sl;
}

const char* ChiTietHoaDon::getMaHang() const { return maHang; }
int ChiTietHoaDon::getSoLuong() const { return soLuong; }

// Chỉ chấp nhận số lượng dương
void ChiTietHoaDon::setSoLuong(int sl) {
    if (sl > 0) soLuong = sl;
}

// In ngắn: mã hàng + số lượng (dùng trong submenu sửa đơn)
void ChiTietHoaDon::xuat() const {
    cout << "  - Ma Hang: " << left << setw(20) << maHang << "| So luong: " << soLuong << "\n";
}

// ==================== HoaDonXuat ====================

HoaDonXuat::HoaDonXuat() {
    strcpy(maHDX, ""); soLuongMatHang = 0;
}

// Kiểm tra mã hàng có thực sự tồn tại trong kho hay không
static bool timTrongKho(const char* ma, const MatHang* kho, int nKho) {
    for (int i = 0; i < nKho; i++)
        if (strcmp(kho[i].getMaHang(), ma) == 0) return true;
    return false;
}

// Nhập 1 đơn hàng mới: mã đơn + danh sách mặt hàng (validate tồn tại trong kho, không trùng)
void HoaDonXuat::nhap(const MatHang* kho, int nKho) {
    cout << "Nhap ma don hang: ";
    cin.width(21); cin >> maHDX; cin.ignore(10000, '\n');

    cout << "Nhap so luong mat hang trong don: ";
    soLuongMatHang = nhapSoNguyenDuong("  Gia tri khong hop le, nhap lai: ");
    if (soLuongMatHang > 100) soLuongMatHang = 100;

    int nhapDuoc = 0;
    for (int i = 0; i < soLuongMatHang; i++) {
        char ma[21];
        cout << "  Ma mat hang " << i + 1 << ": ";
        cin.width(21); cin >> ma; cin.ignore(10000, '\n');

        if (!timTrongKho(ma, kho, nKho) || chuaMatHang(ma)) {
            cout << "  [!] Ma hang loi (khong co trong kho hoac trung lap). Bo qua.\n";
            soLuongMatHang--; i--; continue;
        }

        cout << "  So luong: ";
        int sl = nhapSoNguyenDuong("  So luong phai lon hon 0, nhap lai: ");
        danhSachBan[nhapDuoc++] = ChiTietHoaDon(ma, sl);
    }
    soLuongMatHang = nhapDuoc;
}

// In ngắn: chỉ mã đơn + danh sách (mã hàng, số lượng) — dùng trong submenu sửa
void HoaDonXuat::xuat() const {
    cout << "\nMa Don Hang: " << maHDX << "\n";
    if (soLuongMatHang == 0) { cout << "  (Don hang trong)\n"; return; }
    for (int i = 0; i < soLuongMatHang; i++) danhSachBan[i].xuat();
}

// In đầy đủ dạng bảng: mã, tên (tra từ kho), đơn giá, số lượng, thành tiền, tổng tiền
void HoaDonXuat::xuat(const MatHang* kho, int nKho) const {
    double tongTien = 0;
    cout << "\n+--------------------------------------------------+\n";
    cout << "| Ma Don Hang: " << left << setw(36) << maHDX << "|\n";
    cout << "+--------------------------------------------------+\n";
    if (soLuongMatHang == 0) {
        cout << "| (Don hang trong)                                 |\n+--------------------------------------------------+\n";
        return;
    }
    cout << "| " << left << setw(12) << "Ma Hang" << setw(20) << "Ten Hang" << setw(10) << "Don Gia" << setw(6)  << "SL" << setw(12) << "Thanh Tien" << "|\n";
    cout << "+--------------------------------------------------+\n";
    for (int i = 0; i < soLuongMatHang; i++) {
        const char* ma = danhSachBan[i].getMaHang();
        int sl = danhSachBan[i].getSoLuong();
        double donGia = 0; const char* tenHang = "(?)";

        // Tra kho để lấy tên và giá tương ứng với mã hàng
        for (int j = 0; j < nKho; j++) {
            if (strcmp(kho[j].getMaHang(), ma) == 0) {
                donGia  = kho[j].getGiaBan(); tenHang = kho[j].getTenHang(); break;
            }
        }
        double thanhTien = donGia * sl; tongTien += thanhTien;
        cout << "| " << left  << setw(12) << ma << setw(20) << tenHang << fixed << setprecision(0) << setw(10) << donGia << defaultfloat << setw(6) << sl << fixed << setprecision(0) << setw(12) << thanhTien << "|\n";
    }
    cout << "+--------------------------------------------------+\n";
    cout << "| " << right << setw(47) << "TONG TIEN: " << fixed << setprecision(0) << setw(0) << tongTien << "VND |\n+--------------------------------------------------+\n";
}

const char* HoaDonXuat::getMaHDX() const { return maHDX; }

// Kiểm tra mã hàng có nằm trong đơn hàng hiện tại không
bool HoaDonXuat::chuaMatHang(const char* ma) const {
    for (int i = 0; i < soLuongMatHang; i++)
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) return true;
    return false;
}

// Thêm 1 mặt hàng vào đơn: validate tồn tại trong kho, không trùng, số lượng hợp lệ, đơn chưa đầy
void HoaDonXuat::themMatHang(const char* ma, int sl, const MatHang* kho, int nKho) {
    if (!timTrongKho(ma, kho, nKho) || chuaMatHang(ma) || sl <= 0 || soLuongMatHang >= 100) {
        cout << "  [!] Thao tac khong hop le hoac don hang da day!\n"; return;
    }
    danhSachBan[soLuongMatHang++] = ChiTietHoaDon(ma, sl);
    cout << "  Da them mat hang thanh cong.\n";
}

// Sửa số lượng của 1 mặt hàng đã có trong đơn
void HoaDonXuat::suaSoLuong(const char* ma, int slMoi) {
    if (slMoi <= 0) return;
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            danhSachBan[i].setSoLuong(slMoi);
            cout << "  Da cap nhat so luong.\n"; return;
        }
    }
    cout << "  [!] Khong tim thay mat hang.\n";
}

// Xóa 1 mặt hàng khỏi đơn, dồn các phần tử phía sau lên
void HoaDonXuat::xoaMatHang(const char* ma) {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            for (int j = i; j < soLuongMatHang - 1; j++) danhSachBan[j] = danhSachBan[j + 1];
            soLuongMatHang--;
            cout << "  Da xoa mat hang.\n"; return;
        }
    }
    cout << "  [!] Khong tim thay mat hang.\n";
}
