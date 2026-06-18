#ifndef QUANLY_H
#define QUANLY_H

#include <iostream>   
#include <fstream>    
#include <cstring>    
#include <iomanip>    

#include "MatHang.h"
#include "HoaDon.h"

#define maxKho 100   
#define maxHd 100    

// Các hàm tiện ích kiểm tra lỗi nhập liệu
double nhapSoThucDuong(const char* thongBaoLoi);    
int nhapSoNguyenDuong(const char* thongBaoLoi);     
int nhapSoNguyenKhongAm(const char* thongBaoLoi);   

// Hệ thống File I/O
void SaveData(const MatHang kho[], int nKho, const HoaDon dsHD[], int nHD);
void LoadData(MatHang kho[], int& nKho, HoaDon dsHD[], int& nHD);

// Các hàm quản lý Kho
void themMatHang(MatHang kho[], int& nKho);
void suaThongTinMatHang(MatHang kho[], int nKho);
void xoaMatHang(MatHang kho[], int& nKho, HoaDon dsHD[], int nHD);
void lietKeMatHang(const MatHang kho[], int nKho);

// Các hàm quản lý Đơn hàng
void themHoaDon(HoaDon dsHD[], int& nHD, MatHang kho[], int nKho); 
void suaThongTinDonHang(HoaDon dsHD[], int nHD, MatHang kho[], int nKho);
void xoaHoaDon(HoaDon dsHD[], int& nHD, MatHang kho[], int nKho);
void lietKeHoaDon(const HoaDon dsHD[], int nHD); 

#endif