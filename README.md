# FIT1211_BaiTapLon_Nhom5
BTL Lập trình hướng đối tượng
## TỔNG QUAN HỆ THỐNG QUẢN LÝ ĐƠN HÀNG VÀ KHO HÀNG
Đây là một ứng dụng Console (chạy trên giao diện dòng lệnh) được viết bằng ngôn ngữ C++, ứng dụng các nguyên lý Lập trình Hướng đối tượng (OOP). Hệ thống giải quyết bài toán quản lý bán hàng cơ bản, trong đó có sự liên kết chặt chẽ giữa việc xuất/nhập kho và tạo lập/hủy bỏ hóa đơn.
### 1. Kiến trúc Dữ liệu (Data Models)
Hệ thống được chia thành 3 thực thể (Class) chính:
 * *MatHang (Sản phẩm trong kho):* Đại diện cho danh mục hàng hóa lưu trữ trong kho. Chứa các thông tin gốc như: Mã sản phẩm, Tên sản phẩm, Giá bán và Số lượng tồn kho hiện tại.
 * *ChiTietDonHang (Món hàng trong giỏ):* Đại diện cho một dòng sản phẩm mà khách hàng mua. Khác với MatHang, lớp này hoạt động theo cơ chế *Snapshot* (Chụp ảnh trạng thái): Nó lưu lại tên và mức giá tại đúng thời điểm khách chốt đơn. Điều này đảm bảo khi kho hàng tăng/giảm giá bán trong tương lai, tổng tiền của các hóa đơn cũ không bị sai lệch.
 * *DonHang (Tờ hóa đơn tổng):* Đóng vai trò là một "giỏ hàng", áp dụng quan hệ Composition (Bao gộp) để chứa một mảng danh sách các ChiTietDonHang bên trong nó. Lớp này quản lý mã đơn, điều phối việc thêm/sửa/xóa các món hàng trong tờ đơn và tính toán tổng tiền.
### 2. Các tính năng cốt lõi (Core Features)
*📦 Quản lý Kho hàng:*
 * Nhập thêm sản phẩm mới vào danh mục.
 * Sửa đổi thông tin (tên, giá) và linh hoạt điều chỉnh số lượng tồn kho (cộng thêm hoặc trừ bớt).
 * Kiểm tra ràng buộc: Không cho phép xóa một sản phẩm khỏi hệ thống nếu nó đã từng tồn tại trong lịch sử giao dịch (đã nằm trong một đơn hàng nào đó).
 * Liệt kê toàn bộ trạng thái tồn kho.
*🛒 Quản lý Đơn hàng (Nghiệp vụ Bán hàng):*
 * *Tạo đơn mới:* Tự động kiểm tra số lượng tồn kho trước khi bán. Nếu đủ hàng, hệ thống sẽ chép thông tin sản phẩm sang đơn và lập tức *trừ đi số lượng tồn kho* tương ứng.
 * *Chỉnh sửa đơn hàng (Sub-menu):* Cho phép can thiệp sâu vào một đơn hàng đã tạo để:
   * Thêm món mới vào đơn.
   * Sửa số lượng: Tự động tính toán mức chênh lệch để bù/trừ lại số lượng trên kệ kho.
   * Xóa món hàng: Hủy mua một món và hoàn trả số lượng món đó về kho.
 * *Hủy đơn hàng:* Khi xóa hẳn một tờ đơn, toàn bộ sản phẩm bên trong tờ đơn đó sẽ được tự động trích xuất để *hoàn trả toàn bộ (Restock)* về kho.
 * In danh sách bảng kê chi tiết toàn bộ đơn hàng kèm tổng doanh thu hệ thống.
*💾 Lưu trữ Dữ liệu (File I/O):*
 * Hệ thống sử dụng cơ chế đọc/ghi file nhị phân (.dat) để lưu trữ vĩnh viễn mảng dữ liệu.
 * Dữ liệu tự động tải lên (Load) khi bật chương trình và tự động sao lưu (Save) mỗi khi có bất kỳ sự thay đổi nào (thêm/sửa/xóa), giúp hệ thống không bao giờ bị mất dữ liệu khi tắt máy đột ngột.
### 3. Ưu điểm Kỹ thuật
 * *Bẫy lỗi nhập liệu (Input Validation) an toàn:* Toàn bộ các chức năng nhập số (tiền, số lượng) đều được bảo vệ bởi các vòng lặp kiểm tra trạng thái của cin. Hệ thống tự động dọn dẹp bộ nhớ đệm nếu người dùng cố tình nhập sai kiểu dữ liệu (nhập chữ thay vì số), giúp chương trình không bao giờ bị crash.
 * *Thuật toán tối ưu vừa đủ:* Dùng mảng tĩnh để dễ quản lý bộ nhớ trong phạm vi bài toán nhỏ, áp dụng thuật toán dịch mảng để xóa phần tử và các hàm helper ẩn (static) để dò tìm vị trí (index) nhanh chóng, tái sử dụng code tốt.
