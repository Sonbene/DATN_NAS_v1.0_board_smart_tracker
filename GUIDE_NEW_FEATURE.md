# Hướng dẫn tích hợp thiết bị (Device Integration Guide)

Tài liệu này mô tả cách thiết bị (Tracker) giao tiếp với Server qua MQTT để thực hiện cập nhật cấu hình.

## 1. Cập nhật cấu hình (Configuration Update)

Để tiết kiệm băng thông và tối ưu cho thiết bị nhúng, Server sẽ gửi cấu hình ở dạng JSON rút gọn các từ khóa (Compressed JSON).

### Luồng xử lý:
1. Server gửi cấu hình xuống topic: `Son/{imei}/config`
2. Nội dung tin nhắn (Payload): JSON rút gọn.
3. Thiết bị giải mã, lưu cấu hình mới và áp dụng.
4. Thiết bị gửi phản hồi (Confirmation) lên topic: `Son/{imei}/config/res`
   - Nội dung phản hồi: `{"status": "done"}` (Định dạng JSON).

### Bảng tra cứu từ khóa (Key Mapping):

| Từ khóa gốc (RTDB) | Từ khóa rút gọn (MQTT) | Mô tả |
| :--- | :--- | :--- |
| `interval` | `iv` | Khoảng cách gửi dữ liệu khi di chuyển (giây) |
| `sleep_delay` | `sd` | Thời gian chờ trước khi ngủ (giây) |
| `sms_phone1` | `p1` | Số điện thoại nhận SMS 1 |
| `sms_phone2` | `p2` | Số điện thoại nhận SMS 2 |
| `sms_phone3` | `p3` | Số điện thoại nhận SMS 3 |
| `static_interval` | `siv` | Khoảng cách gửi dữ liệu khi đứng yên (giây) |

**Lưu ý**:
- `updated_at` sẽ không được gửi xuống thiết bị.
- Các trường `sms_phone` nếu để trống trên Firebase sẽ không có trong chuỗi JSON gửi xuống.
- Ví dụ chuỗi JSON (1 số ĐT): `{"iv":30,"sd":60,"p1":"0359868203","siv":3600}`
- Ví dụ chuỗi JSON (2 số ĐT): `{"iv":30,"sd":60,"p1":"0359868203","p2":"0912345678","siv":3600}`
- Ví dụ chuỗi JSON (3 số ĐT): `{"iv":30,"sd":60,"p1":"0359868203","p2":"0912345678","p3":"0988888888","siv":3600}`

---

## 2. Cơ chế Thử lại và Thức dậy (Retry & Wake-up)

Thiết bị cần lưu ý về logic gửi lệnh của Server:
- Nếu thiết bị đang ngủ (không nhận được lệnh), Server sẽ chờ cho đến khi nhận được bất kỳ dữ liệu nào (`data`, `status`, `alarm`) từ thiết bị gửi lên.
- Ngay khi nhận được dữ liệu (chứng tỏ thiết bị đã thức), Server sẽ gửi lại lệnh đang chờ.
- Đối với lệnh cấu hình, Server sẽ chờ ít nhất 30 giây giữa các lần thử lại để tránh làm nghẽn thiết bị.

---

## 3. Lưu trữ và Quản lý cấu hình trên thiết bị

Thiết bị phải đảm bảo các yêu cầu sau về việc quản lý cấu hình:

### 3.1. Lưu trữ bền vững (Persistence)
- **Lưu vào Flash**: Toàn bộ các tham số nhận được từ Server (`iv`, `sd`, `p1`, `p2`, `p3`, `siv`) phải được lưu vào bộ nhớ Flash (hoặc EEPROM giả lập).
- **Vị trí**: Chọn một Sector/Page Flash phù hợp ( xem block/sector nào trống (ghi riêng vào 1 sector nhé)) để tránh ghi đè lên mã chương trình.
- **Khởi động**: Mỗi khi thiết bị khởi động lại (Startup), phải đọc cấu hình từ Flash để nạp vào các biến chương trình tương ứng.

### 3.2. Quản lý biến (Variable Management)
- **Chuyển đổi từ Define**: Các tham số như `interval`, `sleep_delay`... không được để ở dạng `#define` cố định. Chúng phải được chuyển đổi thành các **biến toàn cục (Global Variables)** để có thể thay đổi giá trị ngay trong lúc chương trình đang chạy.

### 3.3. Quy trình cập nhật (Update Workflow)
Để đảm bảo tính toàn vẹn dữ liệu, thiết bị phải tuân thủ quy trình sau khi nhận được tin nhắn trên topic `config`:
1. **Giải mã (Parse)** chuỗi JSON nhận được.
2. **Ghi vào Flash**: Thực hiện xóa Sector và ghi lại bộ tham số mới vào Flash.
3. **Kiểm tra**: Đảm bảo việc ghi Flash thành công (Verify).
4. **Phản hồi**: CHỈ SAU KHI ghi Flash thành công, thiết bị mới được gửi tin nhắn xác nhận `{"status": "done"}` lên topic `Son/{imei}/config/res`.

*Lưu ý: Nếu gửi phản hồi trước khi ghi Flash mà gặp lỗi ghi, Server sẽ hiểu lầm là thiết bị đã cập nhật thành công.*

---

### 3.4. Gửi sms
Nếu có tai nạn sẽ gửi vị trí qua sms đến các số điện thoại trong flash, nếu không có số điện thoại trong flash thì không gửi sms. THÊM CÁI DEFINE ĐỂ BẬT TẮT CÁI TÍNH NĂNG NÀY NHÉ

## 4. Topic phản hồi chung
- Mọi phản hồi thành công từ thiết bị nên tuân thủ định dạng: `{"status": "done"}`.
- Nếu thất bại, thiết bị có thể gửi: `{"status": "error", "msg": "Lý do lỗi"}`.
