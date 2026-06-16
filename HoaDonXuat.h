#ifndef HOADONXUAT_H
#define HOADONXUAT_H

#include "MatHang.h"

class ChiTietHoaDon {
private:
    char maHang[21];
    int soLuong;

public:
    ChiTietHoaDon();
    ChiTietHoaDon(const char* ma, int sl);
    const char* getMaHang() const;
    int getSoLuong() const;
    void setSoLuong(int sl);
    void xuat() const;
};

class HoaDonXuat {
private:
    char maHDX[21];
    int soLuongMatHang;
    ChiTietHoaDon danhSachBan[100];

public:
    HoaDonXuat();

    // Truyền kho vào để validate mã hàng khi nhập
    void nhap(const MatHang* kho, int nKho);
    void xuat() const;                              // In don gian (ma + so luong)
    void xuat(const MatHang* kho, int nKho) const; // In day du (ten, don gia, thanh tien)

    const char* getMaHDX() const;
    bool chuaMatHang(const char* ma) const;

    // Truyền kho vào để validate khi thêm từ menu sửa
    void themMatHang(const char* ma, int sl, const MatHang* kho, int nKho);
    void suaSoLuong(const char* ma, int slMoi);
    void xoaMatHang(const char* ma);
};

#endif
