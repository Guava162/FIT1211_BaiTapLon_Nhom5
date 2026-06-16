#include "QuanLy.h"

using namespace std;

// ==================== ChiTietHoaDon ====================

ChiTietHoaDon::ChiTietHoaDon() {
    strcpy(maHang, "");
    soLuong = 0;
}

ChiTietHoaDon::ChiTietHoaDon(const char* ma, int sl) {
    strcpy(maHang, ma);
    soLuong = sl;
}

const char* ChiTietHoaDon::getMaHang() const { return maHang; }
int ChiTietHoaDon::getSoLuong() const { return soLuong; }

void ChiTietHoaDon::setSoLuong(int sl) {
    if (sl > 0)
        soLuong = sl;
    else
        cout << "  So luong phai lon hon 0!\n";
}

void ChiTietHoaDon::xuat() const {
    cout << "  - Ma Hang: " << left << setw(20) << maHang
         << "| So luong: " << soLuong << "\n";
}

// ==================== HoaDonXuat ====================

HoaDonXuat::HoaDonXuat() {
    strcpy(maHDX, "");
    soLuongMatHang = 0;
}

// Hàm tiện ích nội bộ: kiểm tra mã hàng có trong kho không
static bool timTrongKho(const char* ma, const MatHang* kho, int nKho) {
    for (int i = 0; i < nKho; i++)
        if (strcmp(kho[i].getMaHang(), ma) == 0) return true;
    return false;
}

void HoaDonXuat::nhap(const MatHang* kho, int nKho) {
    // Xóa buffer trước khi nhập maHDX
    cout << "Nhap ma don hang: ";
    cin.width(21);
    cin >> maHDX;
    cin.ignore(10000, '\n');

    cout << "Nhap so luong mat hang trong don: ";
    while (!(cin >> soLuongMatHang) || soLuongMatHang < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Gia tri khong hop le, nhap lai: ";
    }
    if (soLuongMatHang > 100) soLuongMatHang = 100;
    cin.ignore(10000, '\n');

    int nhapDuoc = 0;
    for (int i = 0; i < soLuongMatHang; i++) {
        char ma[21];
        int sl;

        cout << "  Ma mat hang " << i + 1 << ": ";
        cin.width(21);
        cin >> ma;
        cin.ignore(10000, '\n');

        // Validate mã hàng có tồn tại trong kho
        if (!timTrongKho(ma, kho, nKho)) {
            cout << "  [!] Ma hang '" << ma << "' khong ton tai trong kho. Bo qua.\n";
            soLuongMatHang--; // Bù lại vòng lặp
            i--;
            continue;
        }

        // Validate không trùng mã trong đơn hàng hiện tại
        if (chuaMatHang(ma)) {
            cout << "  [!] Ma hang '" << ma << "' da co trong don hang nay. Bo qua.\n";
            soLuongMatHang--;
            i--;
            continue;
        }

        cout << "  So luong: ";
        while (!(cin >> sl) || sl <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  So luong phai lon hon 0, nhap lai: ";
        }
        cin.ignore(10000, '\n');

        danhSachBan[nhapDuoc++] = ChiTietHoaDon(ma, sl);
    }
    soLuongMatHang = nhapDuoc;
}

void HoaDonXuat::xuat() const {
    cout << "\nMa Don Hang: " << maHDX << "\n";
    if (soLuongMatHang == 0) {
        cout << "  (Don hang trong)\n";
        return;
    }
    for (int i = 0; i < soLuongMatHang; i++)
        danhSachBan[i].xuat();
}

void HoaDonXuat::xuat(const MatHang* kho, int nKho) const {
    double tongTien = 0;
    cout << "\n+--------------------------------------------------+\n";
    cout << "| Ma Don Hang: " << left << setw(36) << maHDX << "|\n";
    cout << "+--------------------------------------------------+\n";
    if (soLuongMatHang == 0) {
        cout << "| (Don hang trong)                                 |\n";
        cout << "+--------------------------------------------------+\n";
        return;
    }
    cout << "| " << left << setw(12) << "Ma Hang" << setw(20) << "Ten Hang" << setw(10) << "Don Gia" << setw(6)  << "SL" << setw(12) << "Thanh Tien" << "|\n";
    cout << "+--------------------------------------------------+\n";
    for (int i = 0; i < soLuongMatHang; i++) {
        const char* ma = danhSachBan[i].getMaHang();
        int sl = danhSachBan[i].getSoLuong();
        double donGia = 0;
        const char* tenHang = "(?)";

        // Tra kho lấy tên và giá
        for (int j = 0; j < nKho; j++) {
            if (strcmp(kho[j].getMaHang(), ma) == 0) {
                donGia  = kho[j].getGiaBan();
                tenHang = kho[j].getTenHang();
                break;
            }
        }
        double thanhTien = donGia * sl;
        tongTien += thanhTien;

        cout << "| " << left  << setw(12) << ma << setw(20) << tenHang << fixed << setprecision(0) << setw(10) << donGia << defaultfloat << setw(6) << sl << fixed << setprecision(0) << setw(12) << thanhTien << "|\n";
    }
    cout << "+--------------------------------------------------+\n";
    cout << "| " << right << setw(47) << "TONG TIEN: "
         << fixed << setprecision(0) << setw(0) << tongTien << "VND |\n";
    cout << "+--------------------------------------------------+\n";
}

const char* HoaDonXuat::getMaHDX() const { return maHDX; }

bool HoaDonXuat::chuaMatHang(const char* ma) const {
    for (int i = 0; i < soLuongMatHang; i++)
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) return true;
    return false;
}

void HoaDonXuat::themMatHang(const char* ma, int sl, const MatHang* kho, int nKho) {
    // Validate mã hàng có trong kho
    if (!timTrongKho(ma, kho, nKho)) {
        cout << "  [!] Ma hang '" << ma << "' khong ton tai trong kho!\n";
        return;
    }
    // Validate không trùng trong đơn hàng
    if (chuaMatHang(ma)) {
        cout << "  [!] Ma hang '" << ma << "' da co trong don hang nay!\n";
        return;
    }
    // Validate số lượng
    if (sl <= 0) {
        cout << "  [!] So luong phai lon hon 0!\n";
        return;
    }
    if (soLuongMatHang >= 100) {
        cout << "  [!] Don hang da day (toi da 100 mat hang)!\n";
        return;
    }
    danhSachBan[soLuongMatHang++] = ChiTietHoaDon(ma, sl);
    cout << "  Da them mat hang thanh cong.\n";
}

void HoaDonXuat::suaSoLuong(const char* ma, int slMoi) {
    if (slMoi <= 0) {
        cout << "  [!] So luong phai lon hon 0!\n";
        return;
    }
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            danhSachBan[i].setSoLuong(slMoi);
            cout << "  Da cap nhat so luong.\n";
            return;
        }
    }
    cout << "  [!] Khong tim thay mat hang '" << ma << "' trong don hang.\n";
}

void HoaDonXuat::xoaMatHang(const char* ma) {
    for (int i = 0; i < soLuongMatHang; i++) {
        if (strcmp(danhSachBan[i].getMaHang(), ma) == 0) {
            for (int j = i; j < soLuongMatHang - 1; j++)
                danhSachBan[j] = danhSachBan[j + 1];
            soLuongMatHang--;
            cout << "  Da xoa mat hang '" << ma << "' khoi don hang.\n";
            return;
        }
    }
    cout << "  [!] Khong tim thay mat hang '" << ma << "' trong don hang.\n";
}
