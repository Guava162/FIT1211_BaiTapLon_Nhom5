#include "QuanLy.h"

using namespace std;

// ==================== HÀM TIỆN ÍCH ====================

// Các hàm bắt lỗi nhập liệu
double nhapSoThucDuong(const char* thongBaoLoi) {
    double value;
    while (!(cin >> value) || value <= 0) { 
        cin.clear(); cin.ignore(10000, '\n'); cout << thongBaoLoi; 
    }
    cin.ignore(10000, '\n'); return value; 
}

int nhapSoNguyenDuong(const char* thongBaoLoi) {
    int value;
    while (!(cin >> value) || value <= 0) {
        cin.clear(); cin.ignore(10000, '\n'); cout << thongBaoLoi;
    }
    cin.ignore(10000, '\n'); return value;
}

int nhapSoNguyenKhongAm(const char* thongBaoLoi) {
    int value;
    while (!(cin >> value) || value < 0) { 
        cin.clear(); cin.ignore(10000, '\n'); cout << thongBaoLoi;
    }
    cin.ignore(10000, '\n'); return value;
}

// Tìm vị trí của mã hàng trong mảng kho. Trả về index hoặc -1
static int timViTriMatHang(const char* ma, const MatHang kho[], int nKho) {
    for (int i = 0; i < nKho; i++) {
        if (strcmp(kho[i].getMaHang(), ma) == 0) return i;
    }
    return -1;
}

// ==================== FILE I/O ====================

// Ghi toàn bộ cấu trúc dữ liệu từ mảng xuống file nhị phân
void SaveData(const MatHang kho[], int nKho, const DonHang dsHD[], int nHD) {
    ofstream fKho("Kho.dat", ios::binary); 
    if (fKho) {
        fKho.write((const char*)&nKho, sizeof(nKho)); 
        fKho.write((const char*)kho, sizeof(MatHang) * nKho); 
    }
    
    ofstream fHD("DonHang.dat", ios::binary); 
    if (fHD) {
        fHD.write((const char*)&nHD, sizeof(nHD)); 
        fHD.write((const char*)dsHD, sizeof(DonHang) * nHD); 
    }
}

// Đọc dữ liệu từ file nhị phân đưa lên mảng
void LoadData(MatHang kho[], int& nKho, DonHang dsHD[], int& nHD) {
    nKho = 0; nHD = 0; 
    
    ifstream fKho("Kho.dat", ios::binary);
    if (fKho && fKho.read((char*)&nKho, sizeof(nKho)) && nKho >= 0 && nKho <= maxKho) {
        fKho.read((char*)kho, sizeof(MatHang) * nKho); 
    } else nKho = 0; 

    ifstream fHD("DonHang.dat", ios::binary);
    if (fHD && fHD.read((char*)&nHD, sizeof(nHD)) && nHD >= 0 && nHD <= maxHd) {
        fHD.read((char*)dsHD, sizeof(DonHang) * nHD);
    } else nHD = 0;
}

// ==================== QUẢN LÝ MẶT HÀNG (KHO) ====================

void themMatHang(MatHang kho[], int& nKho) {
    if (nKho >= maxKho) { cout << "[!] Kho da day.\n"; return; } 

    char ma[maxMa];
    cout << "--- NHAP THEM MAT HANG ---\n  Nhap ma (toi da 20 ky tu): ";
    cin.width(maxMa); cin >> ma; cin.ignore(10000, '\n');

    if (timViTriMatHang(ma, kho, nKho) != -1) {
        cout << "[!] Ma hang '" << ma << "' da ton tai!\n"; return;
    }

    kho[nKho].nhapTrungMa(ma); 
    nKho++; 
    cout << "Da them mat hang thanh cong.\n";
}

void suaThongTinMatHang(MatHang kho[], int nKho) {
    char ma[maxMa];
    cout << "Nhap ma mat hang can sua: ";
    
    // Nhập mã mặt hàng cần tìm để sửa
    cin.width(maxMa); cin >> ma; cin.ignore(10000, '\n');

    // Bước 1: Gọi hàm tìm kiếm để xem mặt hàng này nằm ở vị trí thứ mấy (idx) trong mảng
    int idx = timViTriMatHang(ma, kho, nKho); 
    
    // Bước 2: Nếu mặt hàng đã tồn tại (idx != -1)
    if (idx != -1) {
        char tenMoi[maxTen];
        cout << "Nhap ten moi: "; 
        cin.getline(tenMoi, maxTen); 
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); } 
        
        cout << "Nhap gia moi: ";
        double giaMoi = nhapSoThucDuong("Gia khong hop le: ");
        
        cout << "Nhap so luong ton moi (Nhap 0 de giu nguyen kho hien tai): ";
        int khoMoi = nhapSoNguyenKhongAm("SL ton khong hop le: ");

        // Bước 3: Ghi đè dữ liệu mới vào đúng vị trí idx của mặt hàng đó
        kho[idx].setTenHang(tenMoi); 
        kho[idx].setGiaBan(giaMoi);
        
        // Bước 4: Xử lý logic cập nhật số lượng tồn kho
        // Nếu người dùng nhập số > 0 thì mới cập nhật. Nếu nhập 0 thì bỏ qua lệnh này.
        if (khoMoi > 0) {
            // Tính số lượng chênh lệch giữa thực tế người dùng muốn và số hiện đang có.
            int hieu = khoMoi - kho[idx].getSoLuongTon();
            
            // Hàm capNhatSoLuongTon vốn dùng toán tử (+=)
            // Truyền hieu vào đây giúp kho tự động bù trừ đúng số lượng cần thiết
            kho[idx].capNhatSoLuongTon(hieu); 
        }
        
        cout << "Da sua thong tin thanh cong!\n";
        
    } else {
        // Bước 5: Nếu idx == -1, báo lỗi không tìm thấy
        cout << "[!] Khong tim thay mat hang.\n";
    }
}

// Không cho phép xóa nếu mặt hàng đang tồn tại lịch sử trong đơn hàng
void xoaMatHang(MatHang kho[], int& nKho, DonHang dsHD[], int nHD) {
    char ma[maxMa];
    cout << "Nhap ma mat hang can xoa: ";
    cin.width(maxMa); cin >> ma; cin.ignore(10000, '\n');

    for (int i = 0; i < nHD; i++) {
        if (dsHD[i].chuaMatHang(ma)) {
            cout << "[!] Mat hang dang nam trong don '" << dsHD[i].getMaHD() << "'. KHONG THE XOA!\n"; return;
        }
    }
    
    // Vòng lặp xếp lại vị trí hàng trong kho
    int idx = timViTriMatHang(ma, kho, nKho);
    if (idx != -1) {
        for (int j = idx; j < nKho - 1; j++) kho[j] = kho[j + 1];
        nKho--;
        cout << "Da xoa mat hang.\n";
    } else {
        cout << "[!] Khong tim thay.\n";
    }
}

// In thông tin kho hàng
void lietKeMatHang(const MatHang kho[], int nKho) {
    if (nKho == 0) { cout << "Kho hang trong.\n"; return; }
    cout << "--- DANH SACH MAT HANG ---\n";
    cout << left << setw(15) << "Ma Hang" << setw(30) << "Ten Hang" << setw(10) << "Ton Kho" << "Gia Ban\n" << string(75, '-') << "\n";
    for (int i = 0; i < nKho; i++) kho[i].xuat();
}

// ==================== QUẢN LÝ ĐƠN HÀNG ====================

// Tạo đơn hàng mới, thực hiện thêm sản phẩm vào giỏ và trừ kho
void themDonHang(DonHang dsHD[], int& nHD, MatHang kho[], int nKho) {
    if (nKho == 0) { cout << "[!] Kho hang trong! Vui long tao san pham truoc.\n"; return; }
    if (nHD >= maxHd) { cout << "[!] He thong da luu toi da " << maxHd << " don hang.\n"; return; }
    
    char maHD[maxMa];
    cout << "--- NHAP THONG TIN DON HANG ---\nNhap ma don hang: ";
    cin.width(maxMa); cin >> maHD; cin.ignore(10000, '\n');

    for (int i = 0; i < nHD; i++) {
        if (strcmp(dsHD[i].getMaHD(), maHD) == 0) {
            cout << "[!] Ma don hang da ton tai!\n"; return;
        }
    }

    dsHD[nHD].setMaHD(maHD); 

    cout << "Nhap so luong loai mat hang muon mua: ";
    int slMatHang = nhapSoNguyenDuong("Gia tri khong hop le. Nhap lai: ");
    
    for (int i = 0; i < slMatHang; i++) {
        char ma[maxMa];
        cout << "  Ma mat hang " << i + 1 << ": ";
        cin.width(maxMa); cin >> ma; cin.ignore(10000, '\n');

        int idx = timViTriMatHang(ma, kho, nKho);
        if (idx == -1) { cout << "  [!] Ma hang khong co trong kho.\n"; continue; }

        cout << "  So luong mua: ";
        int slMua = nhapSoNguyenDuong("  So luong phai lon hon 0. Nhap lai: ");
        
        // Kiểm tra tồn kho trước khi bán
        if (slMua > kho[idx].getSoLuongTon()) {
            cout << "  [!] Khong du hang. Kho chi con: " << kho[idx].getSoLuongTon() << " san pham.\n";
            continue; 
        }

        // Bán hàng: Trừ kho và chép dữ liệu sang đơn hàng
        kho[idx].capNhatSoLuongTon(-slMua); 
        dsHD[nHD].themMatHang(ma, kho[idx].getTenHang(), kho[idx].getGiaBan(), slMua);
    }
    
    nHD++; 
    cout << "Da khoi tao don hang thanh cong.\n";
}

// Menu con tùy chỉnh chi tiết từng đơn hàng
void suaThongTinDonHang(DonHang dsHD[], int nHD, MatHang kho[], int nKho) {
    char ma[maxMa];
    cout << "Nhap ma Don hang can sua: ";
    cin.width(maxMa); cin >> ma; cin.ignore(10000, '\n');

    // 1. Vòng lặp tìm kiếm xem mã đơn hàng người dùng nhập có tồn tại trong hệ thống không
    for (int i = 0; i < nHD; i++) {
        if (strcmp(dsHD[i].getMaHD(), ma) == 0) { // Nếu tìm thấy đơn hàng trùng mã
            char choice;
            
            // 2. Mở vòng lặp do-while để giữ người dùng lại trong giao diện "Sửa đơn hàng"
            // cho đến khi họ chọn '4' để thoát.
            do {
                cout << "\n--- SUA DON: " << dsHD[i].getMaHD() << " ---\n";
                
                // In tóm tắt các món đang có trong đơn này để người dùng dễ nhìn trước khi sửa
                dsHD[i].xuatNgan(); 
                
                cout << "\n1. Them mat hang\n2. Sua so luong\n3. Xoa mat hang\n4. Thoat\nLua chon: ";
                cin >> choice; cin.ignore(10000, '\n');

                char maSP[maxMa]; int sl;
                switch (choice) {
                    
                    // CHỨC NĂNG 1: MUA THÊM MỘT MÓN HÀNG MỚI VÀO ĐƠN NÀY
                    case '1': { 
                        cout << "Nhap ma SP can them: "; cin.width(maxMa); cin >> maSP; cin.ignore(10000, '\n');
                        
                        // Kiểm tra xem món họ muốn mua có bán trong kho hay không
                        int idx = timViTriMatHang(maSP, kho, nKho);
                        if (idx == -1) { cout << "[!] Ma SP khong ton tai trong kho he thong.\n"; break; }
                        
                        cout << "Nhap so luong: "; sl = nhapSoNguyenDuong("So luong > 0: ");
                        
                        // Kiểm tra tồn kho có đủ để bán không
                        if (sl > kho[idx].getSoLuongTon()) {
                            cout << "[!] Kho chi con " << kho[idx].getSoLuongTon() << " san pham.\n";
                        } else {
                            // Bán được: Trừ số lượng tồn kho (truyền số âm)
                            kho[idx].capNhatSoLuongTon(-sl); 
                            // Chép thông tin món hàng từ kho đẩy vào trong đơn hàng
                            dsHD[i].themMatHang(maSP, kho[idx].getTenHang(), kho[idx].getGiaBan(), sl);
                            // Lưu xuống file ngay lập tức để tránh mất dữ liệu
                            SaveData(kho, nKho, dsHD, nHD);  
                        }
                        break;
                    }
                    
                    // CHỨC NĂNG 2: THAY ĐỔI SỐ LƯỢNG CỦA MỘT MÓN ĐÃ MUA
                    case '2': { 
                        cout << "Nhap ma SP: "; cin.width(maxMa); cin >> maSP; cin.ignore(10000, '\n');
                        
                        // Lấy số lượng cũ mà khách đã mua trong tờ đơn này
                        int slCu = dsHD[i].laySoLuongMatHang(maSP); 
                        if (slCu == 0) { cout << "[!] SP khong ton tai trong don.\n"; break; }
                        
                        cout << "Nhap so luong moi: "; sl = nhapSoNguyenDuong("So luong > 0: ");
                        
                        // Tính chênh lệch = Số mới - Số cũ. 
                        int chenhLech = sl - slCu; 
                        
                        int idx = timViTriMatHang(maSP, kho, nKho);
                        
                        // Nếu khách MUA THÊM (chenhLech > 0) thì phải kiểm tra xem kho có đủ hàng bù vào không
                        if (chenhLech > 0 && idx != -1 && chenhLech > kho[idx].getSoLuongTon()) {
                            cout << "[!] Kho khong du de tang them (Chi con " << kho[idx].getSoLuongTon() << ").\n";
                        } else {
                            // Cập nhật lại kho (nếu mua thêm thì trừ kho, nếu trả lại thì cộng kho)
                            if (idx != -1) kho[idx].capNhatSoLuongTon(-chenhLech); 
                            
                            // Ghi đè con số mới vào tờ hóa đơn
                            dsHD[i].suaSoLuong(maSP, sl);
                            SaveData(kho, nKho, dsHD, nHD);
                        }
                        break;
                    }
                    
                    // CHỨC NĂNG 3: XÓA BỎ HOÀN TOÀN MỘT MÓN KHỎI TỜ ĐƠN
                    case '3': { 
                        cout << "Nhap ma SP can xoa khoi don: "; cin.width(maxMa); cin >> maSP; cin.ignore(10000, '\n');
                        
                        // Lấy số lượng hàng bị huỷ đơn
                        int slCu = dsHD[i].laySoLuongMatHang(maSP);
                        if (slCu > 0) { 
                            int idx = timViTriMatHang(maSP, kho, nKho);
                            // Hoàn trả toàn bộ số hàng đó ngược lại kho
                            if (idx != -1) kho[idx].capNhatSoLuongTon(slCu); 
                            
                            // Tiến hành xóa sản phẩm đó khỏi hóa đơn
                            dsHD[i].xoaMatHang(maSP); 
                            SaveData(kho, nKho, dsHD, nHD);
                        } else {
                            cout << "[!] SP khong ton tai trong don.\n";
                        }
                        break;
                    }
                }
            } while (choice != '4'); // Thoát khỏi Sub-menu
            
            return;
        }
    }
    
    cout << "[!] Khong tim thay don hang.\n";
}

// Hủy đơn hàng và tự động hoàn trả số lượng lại cho kho hàng
void xoaDonHang(DonHang dsHD[], int& nHD, MatHang kho[], int nKho) {
    char ma[maxMa];
    cout << "Nhap ma Don hang can xoa: ";
    cin.width(maxMa); cin >> ma; cin.ignore(10000, '\n');

    for (int i = 0; i < nHD; i++) {
        if (strcmp(dsHD[i].getMaHD(), ma) == 0) {
            // Duyệt danh sách các sản phẩm đang có trong đơn hàng bị hủy để hoàn kho
            for (int k = 0; k < dsHD[i].getSoLuongLoaiHang(); k++) {
                const char* maMua = dsHD[i].getChiTiet(k).getMaHang();
                int slMua = dsHD[i].getChiTiet(k).getSoLuong();
                
                int idx = timViTriMatHang(maMua, kho, nKho);
                if (idx != -1) kho[idx].capNhatSoLuongTon(slMua); 
            }

            // Vòng lặp xếp lại vị trí đơn hàng trong mảng
            for (int j = i; j < nHD - 1; j++) {
                dsHD[j] = dsHD[j + 1];
            }
            nHD--;
            cout << "Da xoa don hang va hoan tra ton kho thanh cong.\n"; return;
        }
    }
    cout << "[!] Khong tim thay don hang.\n";
}

// In danh sách các đơn hàng
void lietKeDonHang(const DonHang dsHD[], int nHD) {
    if (nHD == 0) { cout << "Danh sach don hang trong.\n"; return; }
    cout << "--- DANH SACH DON HANG (" << nHD << " don) ---\n";
    for (int i = 0; i < nHD; i++) dsHD[i].xuatChiTiet();
}