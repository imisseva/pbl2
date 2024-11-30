#include "user.h"
#include <iostream>
#include <string>
#include <fstream>

class Admin {
private:
    User* head;  // Con trỏ đầu danh sách người dùng

public:
    Admin();
    // Thêm người dùng mới
    void addUser(const std::string& username,const std::string& password);
    // Xóa người dùng khỏi danh sách
    void removeUser(const std::string& username);
    // Tìm người dùng theo tên
    User* findUser(const std::string& username) const;
    void saveAllUsersToFile(const string& filename);
    void updatePassword(const string& username, const string& newPassword);
    // Hiển thị tất cả người dùng
    void displayUsers(sf::RenderWindow& window, sf::Font& font) const;

    // Thêm người dùng từ file
    void addUsersFromFile(const std::string& filename);
    void loadUserToFile(sf::RenderWindow& window, sf::Font& font, const string& filename) const;
    // Thêm công việc cho một người dùng cụ thể
    void addTaskToUser(const std::string& username, Task* task);
};
