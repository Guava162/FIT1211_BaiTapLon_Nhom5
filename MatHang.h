#ifndef MATHANG_H
#define MATHANG_H

class MatHang {
private:
    char maHang[21];
    char tenHang[51];
    double giaBan;

public:
    MatHang();
    void nhap();
    void xuat() const;
    const char* getMaHang() const;
    const char* getTenHang() const;
    double getGiaBan() const;
    void setTenHang(const char* ten);
    void setGiaBan(double gia);
};

#endif
