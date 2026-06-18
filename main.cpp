#include "QuanLy.h"

using namespace std;

int main() {
    MatHang kho[maxKho]; 
    int nKho = 0; 
    
    HoaDon dsHD[maxHd];  
    int nHD = 0;  
    
    int choice; 

    LoadData(kho, nKho, dsHD, nHD);

    do {
        cout << "\n=========== QUAN LY DON HANG ===========\n";
        cout << "1. Nhap them 1 san pham\n2. Sua thong tin san pham (theo ma)\n3. Xoa san pham\n";
        cout << "4. Nhap thong tin don hang\n5. Sua thong tin don hang (theo ma)\n6. Xoa don hang (theo ma)\n";
        cout << "7. Liet ke toan bo san pham trong he thong\n8. Liet ke toan bo don hang co trong he thong\n9. Thoat he thong\n";
        cout << "========================================\nNhap lua chon: "; 
        
        if (!(cin >> choice)) break;
        cin.ignore(10000, '\n'); 

        switch (choice) {
            case 1: themMatHang(kho, nKho); break;
            case 2: suaThongTinMatHang(kho, nKho); break;
            case 3: xoaMatHang(kho, nKho, dsHD, nHD); break;
            case 4: themHoaDon(dsHD, nHD, kho, nKho); break;
            case 5: suaThongTinDonHang(dsHD, nHD, kho, nKho); break;
            case 6: xoaHoaDon(dsHD, nHD, kho, nKho); break; // Cập nhật gọi hàm hoàn kho
            case 7: lietKeMatHang(kho, nKho); break;
            case 8: lietKeHoaDon(dsHD, nHD); break;
            case 9: cout << "Da thoat chuong trinh!\n"; break;
            default: cout << "Lua chon khong hop le!\n"; break;
        }

        if (choice >= 1 && choice <= 6) {
            SaveData(kho, nKho, dsHD, nHD);
        }

    } while (choice != 9); 

    return 0;
}