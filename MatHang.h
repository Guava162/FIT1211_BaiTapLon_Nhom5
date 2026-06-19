#ifndef MATHANG_H
#define MATHANG_H

#define maxMa 21      
#define maxTen 51     
#define maxSpDon 100  

// Quản lý thông tin mặt hàng trong kho
class MatHang {
private:
    char   maHang[maxMa];
    char   tenHang[maxTen];
    double giaBan;
    int    soLuongTon; 

public:
    MatHang(); 
    
    void nhap();                    
    void nhapTrungMa(const char* ma); 
    void xuat() const;              
    
    const char* getMaHang() const;
    const char* getTenHang() const;
    double getGiaBan() const;
    int getSoLuongTon() const; 
    
    void setTenHang(const char* ten);
    void setGiaBan(double gia);
    void capNhatSoLuongTon(int sl);
};

#endif