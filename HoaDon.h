#ifndef HOADON_H
#define HOADON_H

#include "MatHang.h"

// Biểu diễn một dòng sản phẩm khách mua trong hóa đơn (Snapshot giá tại thời điểm mua)
class ChiTietHoaDon {
private:
    char maHang[maxMa];   
    char tenHang[maxTen]; 
    double donGia;        
    int soLuong;          

public:
    ChiTietHoaDon(); 
    ChiTietHoaDon(const char* ma, const char* ten, double gia, int sl); 
    
    const char* getMaHang() const;
    int getSoLuong() const;
    void setSoLuong(int sl);
    void congThemSoLuong(int slThem); 
    
    void xuatNgan() const;        
    double tinhThanhTien() const; 
    void inChiTietFormat() const; 
};

// Quản lý tổng thể một đơn hàng chứa nhiều ChiTietHoaDon
class HoaDon {
private:
    char maHD[maxMa];                       
    int soLuongMatHang;                     
    ChiTietHoaDon danhSachBan[maxSpDon];    

public:
    HoaDon(); 

    void setMaHD(const char* ma);
    const char* getMaHD() const;
    bool chuaMatHang(const char* ma) const; 
    
    int getSoLuongCacLoaiHang() const;                  
    const ChiTietHoaDon& getChiTiet(int index) const;   
    int laySoLuongCuaMatHang(const char* ma) const;     
    
    void themMatHang(const char* ma, const char* ten, double gia, int sl);
    void suaSoLuong(const char* ma, int slMoi);
    void xoaMatHang(const char* ma);

    void xuatNgan() const;    
    void xuatChiTiet() const; 
};

#endif