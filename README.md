# Game DOTS AND BOXES
Nguyễn Khánh Huyền: 22026502  
K67-CN16-UET
## GIỚI THIỆU CHUNG:
Dots and Boxes được hoàn thành dựa trên dots & boxes (app Plato) được bổ sung thêm boardSize thay vì chỉ có một kích cỡ duy nhất.    
Game được viết bằng ngôn ngữ C++ và sử dụng thư viện SDL2.

### Luật chơi
  1. Đây là một trò chơi cổ điển dành cho 2 người. Trò chơi bắt đầu với bảng chấm trống. Bảng có kích cỡ phụ thuộc vào sự lựa chọn của người chơi.
  2. Người chơi 1( hay người chơi X) luôn là người đi trước người còn lại là người chơi 2( người chơi O).
  3. Người chơi thay phiên nhau kết nối 2 dấu chấm liền kề theo chiều ngang hoặc chiều dọc. Người chơi hoàn thành mặt thứ tư của ô 1x1 sẽ kiếm được một điểm và phải thực hiện một lượt khác.
  4.Trò chơi kết thúc khi tất cả các dòng được rút ra và các hộp được yêu cầu. Người chơi với số điểm cao nhất sẽ chiến thắng.
  
### Mô tả chức năng
![alt text](https://github.com/22026502NguyenKhanhHuyen/Game/blob/main/demo/Screenshot%20(1).png)
![alt text](https://github.com/22026502NguyenKhanhHuyen/Game/blob/main/demo/Screenshot%20(2).png)
![alt text](https://github.com/22026502NguyenKhanhHuyen/Game/blob/main/demo/Screenshot%20(3).png)


### Hướng dẫn cài đặt
  * Cài đặt [Code Blocks](http://www.codeblocks.org/downloads/binaries/).
  * Tải các thư viện hỗ trợ SDL: [SDL2](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php), [SDL2_mixer](https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php), [SDL2_image](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php), [SDL2_ttf](https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php).
  * Tải project về máy dưới dạng Zip.
  * Mở project bằng CodeBlocks, vào Settings -> Complier -> Search directories -> Complier -> Add -> lấy đường dẫn file headers trong folder project -> OK -> OK.
  * Chạy chương trình: Click vào icon Build and run để chạy game.
### Tổng Kết
#### Điều tâm đắc
  * Em đã tự làm được một project của riêng mình.
  * Cải thiện nhiều kĩ năng lập trình đã được học ở kì I cũng như học tập biết thêm nhiều kiến thức hơn.
  * Khả năng tự học của em cũng tốt hơn.
  * Biết thêm cách design ảnh cũng như photoshop.
  * Biết cách sử dụng SDL2 với những thao tác cơ bản như(load ảnh, sự kiện chuột, render chữ lên màn hình bằng ttf,..).
#### Điều hạn chế
  * Còn nhiều thiếu sót trong trình bày cũng như quản lí đối tượng, bộ nhớ,...
#### Hướng phát triển
  * Phát triển thêm AI (có chế độ 1 người chơi vs AI),
  * Cải thiện thêm chất lượng âm thanh cũng như hình ảnh để game trở nên tốt hơn.
 
### Credit
**Special thanks to:**    
Thầy Trần Quốc Long  
Thầy Nguyễn Lê Đức Trọng  
Thầy Tạ Việt Cường  
Thầy Đỗ Minh Khá    
Vì đã giúp em hoàn thành bài tập này.

### Resources:
 [Lazy Foo' Productions](https://lazyfoo.net/tutorials/SDL/)  
 [cách dùng SDL2](https://www.youtube.com/@tranthiminhchau9465)  
 [image](https://www.canva.com/)  
 [sound](http://jadict.net/vi)
