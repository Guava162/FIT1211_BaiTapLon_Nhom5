#include "QuanLy.h"

using namespace std;

// ==================== HÀM TIỆN ÍCH ====================
double nhapSoThucDuong(const char* thongBaoLoi) {
    double bien;
    while (!(cin >> bien) || bien < 0) {
        cin.clear(); cin.ignore(10000, '\n'); cout << thongBaoLoi;
    }
    cin.ignore(10000, '\n'); return bien;
}

int nhapSoNguyenDuong(const char* thongBaoLoi) {
    int bien;
    while (!(cin >> bien) || bien <= 0) {
        cin.clear(); cin.ignore(10000, '\n'); cout << thongBaoLoi;
    }
    cin.ignore(10000, '\n'); return bien;
}

// Hàm dùng chung để tự động x2 sức chứa cho bất kỳ loại mảng động nào
template <typename T>
void moRongMang(T*& mang, int n, int& sucChua) {
    int newCap = (sucChua == 0) ? 10 : sucChua * 2;
    T* temp = new T[newCap];
    for (int i = 0; i < n; i++) temp[i] = mang[i];
    delete[] mang;
    mang = temp;
    sucChua = newCap;
}

// ==================== FILE I/O ====================
void SaveData(MatHang* kho, int nKho, HoaDonXuat* dsHDX, int nHDX) {
    ofstream fKho("Kho.dat", ios::binary);
    if (fKho) {
        fKho.write(reinterpret_cast<char*>(&nKho), sizeof(nKho));
        for (int i = 0; i < nKho; i++) fKho.write(reinterpret_cast<char*>(&kho[i]), sizeof(MatHang));
        fKho.close();
    }
    ofstream fHDX("HoaDonXuat.dat", ios::binary);
    if (fHDX) {
        fHDX.write(reinterpret_cast<char*>(&nHDX), sizeof(nHDX));
        for (int i = 0; i < nHDX; i++) fHDX.write(reinterpret_cast<char*>(&dsHDX[i]), sizeof(HoaDonXuat));
        fHDX.close();
    }
}

void LoadData(MatHang*& kho, int& nKho, int& sucChuaKho, HoaDonXuat*& dsHDX, int& nHDX, int& sucChuaHDX) {
    kho = nullptr; nKho = 0; sucChuaKho = 0;
    dsHDX = nullptr; nHDX = 0; sucChuaHDX = 0;

    ifstream fKho("Kho.dat", ios::binary);
    if (fKho) {
        fKho.read(reinterpret_cast<char*>(&nKho), sizeof(nKho));
        if (nKho < 0) nKho = 0;
        sucChuaKho = (nKho == 0) ? 10 : nKho;
        kho = new MatHang[sucChuaKho];
        for (int i = 0; i < nKho; i++) fKho.read(reinterpret_cast<char*>(&kho[i]), sizeof(MatHang));
        fKho.close();
    } else { sucChuaKho = 10; kho = new MatHang[sucChuaKho]; }

    ifstream fHDX("HoaDonXuat.dat", ios::binary);
    if (fHDX) {
        fHDX.read(reinterpret_cast<char*>(&nHDX), sizeof(nHDX));
        if (nHDX < 0) nHDX = 0;
        sucChuaHDX = (nHDX == 0) ? 10 : nHDX;
        dsHDX = new HoaDonXuat[sucChuaHDX];
        for (int i = 0; i < nHDX; i++) fHDX.read(reinterpret_cast<char*>(&dsHDX[i]), sizeof(HoaDonXuat));
        fHDX.close();
    } else { sucChuaHDX = 10; dsHDX = new HoaDonXuat[sucChuaHDX]; }
}

// ==================== QUẢN LÝ MẶT HÀNG ====================
void themMatHang(MatHang*& kho, int& nKho, int& sucChuaKho) {
    if (nKho >= sucChuaKho) moRongMang(kho, nKho, sucChuaKho);
    
    cout << "--- NHAP THEM MAT HANG ---\n";
    kho[nKho].nhap();
    nKho++;
    cout << "Da them mat hang thanh cong.\n";
}

void suaThongTinMatHang(MatHang* kho, int nKho) {
    char ma[21];
    cout << "Nhap ma mat hang can sua: ";
    cin.width(21); cin >> ma; cin.ignore(10000, '\n');

    for (int i = 0; i < nKho; i++) {
        if (strcmp(kho[i].getMaHang(), ma) == 0) {
            char tenMoi[51];
            cout << "Nhap ten moi: "; cin.getline(tenMoi, 51);
            cout << "Nhap gia moi: "; 
            double giaMoi = nhapSoThucDuong("Gia khong hop le, nhap lai: ");
            
            kho[i].setTenHang(tenMoi);
            kho[i].setGiaBan(giaMoi);
            cout << "Da sua thong tin thanh cong!\n"; return;
        }
    }
    cout << "[!] Khong tim thay mat hang '" << ma << "'.\n";
}

void xoaMatHang(MatHang*& kho, int& nKho, HoaDonXuat* dsHDX, int nHDX) {
    char ma[21];
    cout << "Nhap ma mat hang can xoa: ";
    cin.width(21); cin >> ma; cin.ignore(10000, '\n');

    for (int i = 0; i < nHDX; i++) {
        if (dsHDX[i].chuaMatHang(ma)) {
            cout << "[!] Mat hang dang ton tai trong don hang '" << dsHDX[i].getMaHDX() << "'. KHONG THE XOA!\n"; return;
        }
    }
    for (int i = 0; i < nKho; i++) {
        if (strcmp(kho[i].getMaHang(), ma) == 0) {
            for (int j = i; j < nKho - 1; j++) kho[j] = kho[j + 1];
            nKho--;
            cout << "Da xoa mat hang '" << ma << "'.\n"; return;
        }
    }
    cout << "[!] Khong tim thay mat hang '" << ma << "'.\n";
}

void lietKeMatHang(MatHang* kho, int nKho) {
    if (nKho == 0) { cout << "Kho hang dang trong.\n"; return; }
    cout << "--- DANH SACH MAT HANG ---\n";
    cout << left << setw(20) << "Ma Hang" << setw(35) << "Ten Hang" << "Gia Ban\n" << string(65, '-') << "\n";
    for (int i = 0; i < nKho; i++) kho[i].xuat();
}

// ==================== QUẢN LÝ HÓA ĐƠN XUẤT ====================
void themHoaDon(HoaDonXuat*& dsHDX, int& nHDX, int& sucChuaHDX, const MatHang* kho, int nKho) {
    if (nKho == 0) { cout << "[!] Kho hang trong, khong the tao don hang!\n"; return; }
    if (nHDX >= sucChuaHDX) moRongMang(dsHDX, nHDX, sucChuaHDX);

    cout << "--- NHAP THONG TIN DON HANG ---\n";
    dsHDX[nHDX].nhap(kho, nKho);
    nHDX++;
    cout << "Da them don hang thanh cong.\n";
}

void suaThongTinDonHang(HoaDonXuat* dsHDX, int nHDX, const MatHang* kho, int nKho) {
    char ma[21];
    cout << "Nhap ma Don hang can sua: ";
    cin.width(21); cin >> ma; cin.ignore(10000, '\n');

    for (int i = 0; i < nHDX; i++) {
        if (strcmp(dsHDX[i].getMaHDX(), ma) == 0) {
            char choice;
            do {
                cout << "\n--- SUA DON HANG: " << dsHDX[i].getMaHDX() << " ---\n";
                dsHDX[i].xuat();
                cout << "\n1. Them mat hang vao don\n2. Sua so luong mat hang\n3. Xoa mat hang khoi don\n4. Thoat\nLua chon: ";
                cin >> choice; cin.ignore(10000, '\n');

                char maSP[21]; int sl;
                switch (choice) {
                    case '1':
                        cout << "Nhap ma SP can them: "; cin.width(21); cin >> maSP; cin.ignore(10000, '\n');
                        cout << "Nhap so luong: "; sl = nhapSoNguyenDuong("So luong phai lon hon 0, nhap lai: ");
                        dsHDX[i].themMatHang(maSP, sl, kho, nKho);
                        break;
                    case '2':
                        cout << "Nhap ma SP can sua so luong: "; cin.width(21); cin >> maSP; cin.ignore(10000, '\n');
                        cout << "Nhap so luong moi: "; sl = nhapSoNguyenDuong("So luong phai lon hon 0, nhap lai: ");
                        dsHDX[i].suaSoLuong(maSP, sl);
                        break;
                    case '3':
                        cout << "Nhap ma SP can xoa: "; cin.width(21); cin >> maSP; cin.ignore(10000, '\n');
                        dsHDX[i].xoaMatHang(maSP);
                        break;
                }
            } while (choice != '4');
            return;
        }
    }
    cout << "[!] Khong tim thay don hang '" << ma << "'.\n";
}

void xoaHoaDon(HoaDonXuat*& dsHDX, int& nHDX) {
    char ma[21];
    cout << "Nhap ma Don hang can xoa: ";
    cin.width(21); cin >> ma; cin.ignore(10000, '\n');

    for (int i = 0; i < nHDX; i++) {
        if (strcmp(dsHDX[i].getMaHDX(), ma) == 0) {
            for (int j = i; j < nHDX - 1; j++) dsHDX[j] = dsHDX[j + 1];
            nHDX--;
            cout << "Da xoa don hang '" << ma << "'.\n"; return;
        }
    }
    cout << "[!] Khong tim thay don hang '" << ma << "'.\n";
}

void lietKeHoaDon(HoaDonXuat* dsHDX, int nHDX, const MatHang* kho, int nKho) {
    if (nHDX == 0) { cout << "Danh sach don hang dang trong.\n"; return; }
    cout << "--- DANH SACH DON HANG (" << nHDX << " don) ---\n";
    for (int i = 0; i < nHDX; i++) dsHDX[i].xuat(kho, nKho);
}