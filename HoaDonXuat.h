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

    void nhap(const MatHang* kho, int nKho);
    void xuat() const;
    void xuat(const MatHang* kho, int nKho) const;

    const char* getMaHDX() const;
    bool chuaMatHang(const char* ma) const;

    void themMatHang(const char* ma, int sl, const MatHang* kho, int nKho);
    void suaSoLuong(const char* ma, int slMoi);
    void xoaMatHang(const char* ma);
};

#endif
