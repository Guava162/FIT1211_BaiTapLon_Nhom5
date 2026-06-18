#ifndef MATHANG_H
#define MATHANG_H

#define maxMa 21      
#define maxTen 51     
#define maxSpDon 100  

class MatHang {
private:
    char   maHang[maxMa];
    char   tenHang[maxTen];
    double giaBan;
    int    soLuongTon; // Bổ sung thuộc tính quản lý số lượng tồn kho

public:
    MatHang(); 
    
    void nhap(); 
    void nhapConMa(const char* ma); 
    void xuat() const; 
    
    const char* getMaHang()  const;
    const char* getTenHang() const;
    double      getGiaBan()  const;
    int         getSoLuongTon() const; // Getter cho tồn kho
    
    void setTenHang(const char* ten);
    void setGiaBan(double gia);
    void capNhatSoLuongTon(int sl);    // Hàm cộng/trừ tồn kho
};

#endif