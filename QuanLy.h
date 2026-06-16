#ifndef QUANLY_H
#define QUANLY_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "MatHang.h"
#include "HoaDonXuat.h"

// Lưu / Tải dữ liệu nhị phân
void SaveData(MatHang* kho, int nKho, HoaDonXuat* dsHDX, int nHDX);
void LoadData(MatHang*& kho, int& nKho, int& sucChuaKho,
              HoaDonXuat*& dsHDX, int& nHDX, int& sucChuaHDX);

// Quản lý mặt hàng
void themMatHang(MatHang*& kho, int& nKho, int& sucChuaKho);
void suaThongTinMatHang(MatHang* kho, int nKho);
void xoaMatHang(MatHang*& kho, int& nKho, HoaDonXuat* dsHDX, int nHDX);
void lietKeMatHang(MatHang* kho, int nKho);

// Quản lý hóa đơn xuất — truyền kho để validate mã hàng
void themHoaDon(HoaDonXuat*& dsHDX, int& nHDX, int& sucChuaHDX,
                const MatHang* kho, int nKho);
void suaThongTinHoaDon(HoaDonXuat* dsHDX, int nHDX,
                       const MatHang* kho, int nKho);
void xoaHoaDon(HoaDonXuat*& dsHDX, int& nHDX);
void lietKeHoaDon(HoaDonXuat* dsHDX, int nHDX, const MatHang* kho, int nKho);

#endif
