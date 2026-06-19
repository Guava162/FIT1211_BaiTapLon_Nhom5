#ifndef QUANLY_H
#define QUANLY_H

#include <iostream>
#include <string>   
#include <fstream>    
#include <cstring>    
#include <iomanip>    

#include "MatHang.h"
#include "DonHang.h"

#define maxKho 100   
#define maxHd 100    

// Các hàm tiện ích kiểm tra lỗi nhập liệu
double nhapSoThucDuong(const char* thongBaoLoi);    
int nhapSoNguyenDuong(const char* thongBaoLoi);     
int nhapSoNguyenKhongAm(const char* thongBaoLoi);   

// Hệ thống File I/O
void SaveData(const MatHang kho[], int nKho, const DonHang dsHD[], int nHD);
void LoadData(MatHang kho[], int& nKho, DonHang dsHD[], int& nHD);

// Các hàm quản lý Kho
void themMatHang(MatHang kho[], int& nKho);
void suaThongTinMatHang(MatHang kho[], int nKho);
void xoaMatHang(MatHang kho[], int& nKho, DonHang dsHD[], int nHD);
void lietKeMatHang(const MatHang kho[], int nKho);

// Các hàm quản lý Đơn hàng
void themDonHang(DonHang dsHD[], int& nHD, MatHang kho[], int nKho); 
void suaThongTinDonHang(DonHang dsHD[], int nHD, MatHang kho[], int nKho);
void xoaDonHang(DonHang dsHD[], int& nHD, MatHang kho[], int nKho);
void lietKeDonHang(const DonHang dsHD[], int nHD); 

#endif