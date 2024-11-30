#include "user.h"
#include <iostream>
#include <string>
#include <fstream>
#include "admin.h"
using namespace std;
Admin::Admin() : head(nullptr) {}  // Constructor khởi tạo head là nullptr

// Thêm người dùng mới
void Admin::addUser(const std::string& username,const std::string& password) {
    User* newUser = new User(username, password);
    newUser->addUser(head);
}

// Xóa người dùng khỏi danh sách
void Admin::removeUser(const std::string& username) {
    User* current = head;
    User* previous = nullptr;

    while (current != nullptr && current->get_username() != username) {
        previous = current;
        current = current->get_next();
    }

    if (current == nullptr) {
        std::cout << "User " << username << " not found!" << std::endl;
        return;
    }

    if (previous == nullptr) {
        head = current->get_next();
    }
    else {
        previous->set_next(current->get_next());
    }

    delete current;
}

// Tìm người dùng theo tên
User* Admin::findUser(const std::string& username) const {
    User* current = head;
    while (current != nullptr) {
        if (current->get_username() == username) {
            return current;
        }
        current = current->get_next();
    }
    std::cout << "User " << username << " not found!" << std::endl;
    return nullptr;
}

// Hiển thị tất cả người dùng
void Admin::displayUsers(sf::RenderWindow & window, sf::Font &font) const {
    User* current = head;
    if (!current) {
        std::cout << "No users to display." << std::endl;
        return;
    }
    sf::Vector2f pos(200, 200);
    while (current != nullptr) {
        drawText(window, font, "Username:", 24, pos, sf::Color::White);
        pos.x += 150;
        drawText(window, font,current->get_username(), 24, pos, sf::Color::White);
        pos.y += 50;
        pos.x -= 150;
        current = current->get_next();
    }
}
void Admin::saveAllUsersToFile(const string& filename) {
    head->saveAllUsersToFile(filename, head);
}
void Admin::updatePassword(const string& username, const string& newPassword) {
    head->updatePassword(username, newPassword, head);
}

// Thêm người dùng từ file
void Admin::addUsersFromFile(const std::string& filename) {
    head->addUsersFromFile(filename, head);
}
void Admin::loadUserToFile(sf::RenderWindow& window, sf::Font& font, const string& filename) const {
    head->loadUserToFile(window, font, filename);
}
// Thêm công việc cho một người dùng cụ thể
void Admin::addTaskToUser(const std::string& username, Task* task) {
    User* user = findUser(username);
    if (user) {
        user->add_task(task);
    }
}

