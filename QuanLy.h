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

double nhapSoThucDuong(const char* thongBaoLoi);
int nhapSoNguyenDuong(const char* thongBaoLoi);
int nhapSoNguyenKhongAm(const char* thongBaoLoi); 

void SaveData(const MatHang kho[], int nKho, const HoaDon dsHD[], int nHD);
void LoadData(MatHang kho[], int& nKho, HoaDon dsHD[], int& nHD);

void themMatHang(MatHang kho[], int& nKho);
void suaThongTinMatHang(MatHang kho[], int nKho);
void xoaMatHang(MatHang kho[], int& nKho, HoaDon dsHD[], int nHD);
void lietKeMatHang(const MatHang kho[], int nKho);

void themHoaDon(HoaDon dsHD[], int& nHD, MatHang kho[], int nKho); 
void suaThongTinDonHang(HoaDon dsHD[], int nHD, MatHang kho[], int nKho);
void xoaHoaDon(HoaDon dsHD[], int& nHD, MatHang kho[], int nKho);
void lietKeHoaDon(const HoaDon dsHD[], int nHD); // Đã bổ sung lại dòng này

#endif