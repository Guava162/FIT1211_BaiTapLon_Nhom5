#ifndef DONHANG_H
#define DONHANG_H

#include "MatHang.h"

// Thông tin đơn hàng
class ChiTietDonHang {
private:
    char maHang[maxMa];   
    char tenHang[maxTen]; 
    double donGia;        
    int soLuong;          

public:
    ChiTietDonHang(); 
    ChiTietDonHang(const char* ma, const char* ten, double gia, int sl); 
    
    const char* getMaHang() const;
    int getSoLuong() const;
    void setSoLuong(int sl);
    void congThemSoLuong(int slThem); 

    void xuatNgan() const;        
    double tinhThanhTien() const; 
    void inChiTietFormat() const; 
};

// Quản lý đơn hàng (thêmm, bớt, thay đổi số lượng sản phẩm)
class DonHang {
private:
    char maHD[maxMa];                       
    int soLuongMatHang;                     
    ChiTietDonHang danhSachBan[maxSpDon];    

public:
    DonHang(); 

    void setMaHD(const char* ma);
    const char* getMaHD() const;
    bool chuaMatHang(const char* ma) const; 
    
    int getSoLuongLoaiHang() const;                  
    const ChiTietDonHang& getChiTiet(int index) const;   
    int laySoLuongMatHang(const char* ma) const;     
    
    void themMatHang(const char* ma, const char* ten, double gia, int sl);
    void suaSoLuong(const char* ma, int slMoi);
    void xoaMatHang(const char* ma);

    void xuatNgan() const;    
    void xuatChiTiet() const; 
};

#endif