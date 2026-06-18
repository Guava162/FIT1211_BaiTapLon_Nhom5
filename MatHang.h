#ifndef MATHANG_H
#define MATHANG_H

class MatHang {
private:
    char   maHang[21];
    char   tenHang[51];
    double giaBan;

public:
    MatHang();
    void nhap();                       // Nhập đủ: mã + tên + giá (dùng khi không cần validate trước)
    void nhapConMa(const char* ma);    // Gán mã có sẵn, chỉ nhập tên + giá
    void xuat() const;
    const char* getMaHang()  const;
    const char* getTenHang() const;
    double      getGiaBan()  const;
    void setTenHang(const char* ten);
    void setGiaBan(double gia);
};

#endif
