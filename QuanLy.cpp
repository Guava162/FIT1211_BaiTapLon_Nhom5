#include "QuanLy.h"

using namespace std;

// ==================== FILE I/O ====================

void SaveData(MatHang* kho, int nKho, HoaDonXuat* dsHDX, int nHDX) {
    ofstream fKho("Kho.dat", ios::binary);
    if (!fKho) {
        cerr << "[!] Loi: Khong the mo file Kho.dat de ghi!\n";
        return;
    }
    fKho.write(reinterpret_cast<char*>(&nKho), sizeof(nKho));
    for (int i = 0; i < nKho; i++)
        fKho.write(reinterpret_cast<char*>(&kho[i]), sizeof(MatHang));
    fKho.close();

    ofstream fHDX("HoaDonXuat.dat", ios::binary);
    if (!fHDX) {
        cerr << "[!] Loi: Khong the mo file HoaDonXuat.dat de ghi!\n";
        return;
    }
    fHDX.write(reinterpret_cast<char*>(&nHDX), sizeof(nHDX));
    for (int i = 0; i < nHDX; i++)
        fHDX.write(reinterpret_cast<char*>(&dsHDX[i]), sizeof(HoaDonXuat));
    fHDX.close();

    cout << "Da luu du lieu thanh cong.\n";
}

void LoadData(MatHang*& kho, int& nKho, int& sucChuaKho,
              HoaDonXuat*& dsHDX, int& nHDX, int& sucChuaHDX) {
    // Khởi tạo mặc định để tránh con trỏ rác
    kho    = nullptr; nKho    = 0; sucChuaKho  = 0;
    dsHDX  = nullptr; nHDX    = 0; sucChuaHDX  = 0;

    ifstream fKho("Kho.dat", ios::binary);
    if (fKho) {
        fKho.read(reinterpret_cast<char*>(&nKho), sizeof(nKho));
        if (nKho < 0) nKho = 0; // Bảo vệ dữ liệu file hỏng
        sucChuaKho = (nKho == 0) ? 10 : nKho;
        kho = new MatHang[sucChuaKho];
        for (int i = 0; i < nKho; i++)
            fKho.read(reinterpret_cast<char*>(&kho[i]), sizeof(MatHang));
        fKho.close();
        cout << "Da tai " << nKho << " mat hang tu Kho.dat\n";
    } else {
        sucChuaKho = 10;
        kho = new MatHang[sucChuaKho];
        cout << "Khong tim thay Kho.dat, bat dau voi kho trong.\n";
    }

    ifstream fHDX("HoaDonXuat.dat", ios::binary);
    if (fHDX) {
        fHDX.read(reinterpret_cast<char*>(&nHDX), sizeof(nHDX));
        if (nHDX < 0) nHDX = 0;
        sucChuaHDX = (nHDX == 0) ? 10 : nHDX;
        dsHDX = new HoaDonXuat[sucChuaHDX];
        for (int i = 0; i < nHDX; i++)
            fHDX.read(reinterpret_cast<char*>(&dsHDX[i]), sizeof(HoaDonXuat));
        fHDX.close();
        cout << "Da tai " << nHDX << " don hang tu HoaDonXuat.dat\n";
    } else {
        sucChuaHDX = 10;
        dsHDX = new HoaDonXuat[sucChuaHDX];
        cout << "Khong tim thay HoaDonXuat.dat, bat dau voi danh sach don hang trong.\n";
    }
}

// ==================== QUẢN LÝ MẶT HÀNG ====================

void themMatHang(MatHang*& kho, int& nKho, int& sucChuaKho) {
    // Mở rộng mảng nếu cần (dynamic array)
    if (nKho >= sucChuaKho) {
        int newCap = sucChuaKho * 2;
        MatHang* temp = new MatHang[newCap];
        for (int i = 0; i < nKho; i++) temp[i] = kho[i];
        delete[] kho;
        kho = temp;
        sucChuaKho = newCap;
    }
    cout << "--- NHAP THEM MAT HANG ---\n";
    kho[nKho].nhap();
    nKho++;
    cout << "Da them mat hang thanh cong.\n";
}

void suaThongTinMatHang(MatHang* kho, int nKho) {
    char ma[21];
    cout << "Nhap ma mat hang can sua: ";
    cin.width(21); cin >> ma;
    cin.ignore(10000, '\n');

    for (int i = 0; i < nKho; i++) {
        if (strcmp(kho[i].getMaHang(), ma) == 0) {
            cout << "--- Thong tin hien tai ---\n";
            cout << "  + Ten cu  : " << kho[i].getTenHang() << "\n";
            cout << "  + Gia cu  : " << fixed << setprecision(0) << kho[i].getGiaBan() << defaultfloat << "VND\n";
            cout << "--------------------------\n";

            char tenMoi[51];
            double giaMoi;

            cout << "Nhap ten moi: ";
            cin.getline(tenMoi, 51);

            cout << "Nhap gia moi: ";
            while (!(cin >> giaMoi) || giaMoi < 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Gia khong hop le, nhap lai: ";
            }
            cin.ignore(10000, '\n');

            kho[i].setTenHang(tenMoi);
            kho[i].setGiaBan(giaMoi);
            cout << "Da sua thong tin thanh cong!\n";
            return;
        }
    }
    cout << "[!] Khong tim thay mat hang '" << ma << "'.\n";
}

void xoaMatHang(MatHang*& kho, int& nKho, HoaDonXuat* dsHDX, int nHDX) {
    char ma[21];
    cout << "Nhap ma mat hang can xoa: ";
    cin.width(21); cin >> ma;
    cin.ignore(10000, '\n');

    // Kiểm tra mã hàng có đang nằm trong bất kỳ đơn hàng nào không
    for (int i = 0; i < nHDX; i++) {
        if (dsHDX[i].chuaMatHang(ma)) {
            cout << "[!] Mat hang '" << ma
                 << "' dang ton tai trong don hang '"
                 << dsHDX[i].getMaHDX()
                 << "'. KHONG THE XOA!\n";
            return;
        }
    }

    for (int i = 0; i < nKho; i++) {
        if (strcmp(kho[i].getMaHang(), ma) == 0) {
            for (int j = i; j < nKho - 1; j++) kho[j] = kho[j + 1];
            nKho--;
            cout << "Da xoa mat hang '" << ma << "'.\n";
            return;
        }
    }
    cout << "[!] Khong tim thay mat hang '" << ma << "'.\n";
}

void lietKeMatHang(MatHang* kho, int nKho) {
    if (nKho == 0) {
        cout << "Kho hang dang trong.\n";
        return;
    }
    cout << "--- DANH SACH MAT HANG ---\n";
    cout << left << setw(20) << "Ma Hang"
                 << setw(35) << "Ten Hang"
                 << "Gia Ban\n";
    cout << string(65, '-') << "\n";
    for (int i = 0; i < nKho; i++) kho[i].xuat();
}

// ==================== QUẢN LÝ HÓA ĐƠN XUẤT ====================

void themHoaDon(HoaDonXuat*& dsHDX, int& nHDX, int& sucChuaHDX,
                const MatHang* kho, int nKho) {
    if (nKho == 0) {
        cout << "[!] Kho hang trong, khong the tao don hang!\n";
        return;
    }

    // Mở rộng mảng nếu cần
    if (nHDX >= sucChuaHDX) {
        int newCap = sucChuaHDX * 2;
        HoaDonXuat* temp = new HoaDonXuat[newCap];
        for (int i = 0; i < nHDX; i++) temp[i] = dsHDX[i];
        delete[] dsHDX;
        dsHDX = temp;
        sucChuaHDX = newCap;
    }

    cout << "--- NHAP THONG TIN DON HANG ---\n";
    dsHDX[nHDX].nhap(kho, nKho); // Truyền kho để validate
    nHDX++;
    cout << "Da them don hang thanh cong.\n";
}

void suaThongTinHoaDon(HoaDonXuat* dsHDX, int nHDX,
                       const MatHang* kho, int nKho) {
    char ma[21];
    cout << "Nhap ma Don hang can sua: ";
    cin.width(21); cin >> ma;
    cin.ignore(10000, '\n');

    for (int i = 0; i < nHDX; i++) {
        if (strcmp(dsHDX[i].getMaHDX(), ma) == 0) {
            char choice;
            do {
                cout << "\n--- SUA DON HANG: " << dsHDX[i].getMaHDX() << " ---\n";
                dsHDX[i].xuat(); // Hiển thị nội dung hiện tại
                cout << "\n1. Them mat hang vao don\n";
                cout << "2. Sua so luong mat hang\n";
                cout << "3. Xoa mat hang khoi don\n";
                cout << "4. Thoat\n";
                cout << "Lua chon: ";
                cin >> choice;
                cin.ignore(10000, '\n');

                char maSP[21];
                int sl;

                switch (choice) {
                    case '1':
                        cout << "Nhap ma SP can them: ";
                        cin.width(21); cin >> maSP;
                        cin.ignore(10000, '\n');
                        cout << "Nhap so luong: ";
                        while (!(cin >> sl) || sl <= 0) {
                            cin.clear(); cin.ignore(10000, '\n');
                            cout << "So luong phai lon hon 0, nhap lai: ";
                        }
                        cin.ignore(10000, '\n');
                        // Truyền kho để validate
                        dsHDX[i].themMatHang(maSP, sl, kho, nKho);
                        break;

                    case '2':
                        cout << "Nhap ma SP can sua so luong: ";
                        cin.width(21); cin >> maSP;
                        cin.ignore(10000, '\n');
                        cout << "Nhap so luong moi: ";
                        while (!(cin >> sl) || sl <= 0) {
                            cin.clear(); cin.ignore(10000, '\n');
                            cout << "So luong phai lon hon 0, nhap lai: ";
                        }
                        cin.ignore(10000, '\n');
                        dsHDX[i].suaSoLuong(maSP, sl);
                        break;

                    case '3':
                        cout << "Nhap ma SP can xoa: ";
                        cin.width(21); cin >> maSP;
                        cin.ignore(10000, '\n');
                        dsHDX[i].xoaMatHang(maSP);
                        break;

                    case '4':
                        cout << "Thoat che do sua don hang.\n";
                        break;

                    default:
                        cout << "Lua chon khong hop le!\n";
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
    cin.width(21); cin >> ma;
    cin.ignore(10000, '\n');

    for (int i = 0; i < nHDX; i++) {
        if (strcmp(dsHDX[i].getMaHDX(), ma) == 0) {
            for (int j = i; j < nHDX - 1; j++) dsHDX[j] = dsHDX[j + 1];
            nHDX--;
            cout << "Da xoa don hang '" << ma << "'.\n";
            return;
        }
    }
    cout << "[!] Khong tim thay don hang '" << ma << "'.\n";
}

void lietKeHoaDon(HoaDonXuat* dsHDX, int nHDX, const MatHang* kho, int nKho) {
    if (nHDX == 0) {
        cout << "Danh sach don hang dang trong.\n";
        return;
    }
    cout << "--- DANH SACH DON HANG (" << nHDX << " don) ---\n";
    for (int i = 0; i < nHDX; i++)
        dsHDX[i].xuat(kho, nKho); // Dùng bản in đầy đủ có tra kho
}
