#include "user.h"
#include "task.h"
#include "schedule.h"
#include <iostream>
#include <string>
#include<fstream>
#include "draw.h"
#include <SFML/Graphics.hpp>
using namespace std;


User::User(const string& username, const string& password) : username(username), password(password), selectedTask(nullptr), next(nullptr) {}
User* User::get_next() const { return next; }
void User::set_next(User* nextUser) { next = nextUser; }

string User::get_username() const {
    return username;
}
string User::get_password() const {
    return password;
}
void User::set_password(const string& pass){
    password = pass; }

Task* User::get_selected_task() const {
    return selectedTask;
}
void User::set_selected_task(Task* task)
{
    selectedTask = task;
}
void User::add_task(Task* task) {
    schedule.add_task(task);
}

void User::delete_task(const string& title) {
    schedule.del_task(title);
}

void User::show_schedule(sf::RenderWindow& window, sf::Font& font) const {
    schedule.display_tasks(window, font);
}
void User::handle_click(sf::RenderWindow& window, sf::Font font, sf::Vector2i mousePosition, const std::string& input_date, const int num) {
    schedule.handle_click(window, font, mousePosition, input_date, num);
    selectedTask = schedule.get_selected_task();
}

void User::show_date_schedule(sf::RenderWindow& window, sf::Font& font, const std::string& input_date) const {
    schedule.display_date_tasks(window, font, input_date);
}


void User::sort_task() {
    schedule.sort_task();
}
void User::addUser(User*& head) {
    this->next = head;
    head = this;
}
void User::updatePassword(const string& username, const string& newPassword, User*& head) {
    User* current = head;
    bool userFound = false;
    while (current != nullptr) {
        if (current->get_username() == username) {
            current->set_password(newPassword); 
            userFound = true;
            break;
        }
        current = current->get_next();
    }

    if (!userFound) {
        std::cerr << "Error: User not found!" << std::endl;
        return;
    }

    saveAllUsersToFile("users.txt", head);
}

void User::saveAllUsersToFile(const string& filename, User* head) {
    std::ofstream file(filename, std::ios::trunc); 
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << " for writing!" << std::endl;
        return;
    }

    User* current = head;
    while (current != nullptr) {
        file << current->get_username() << "," << current->get_password() << std::endl;
        current = current->get_next();
    }

    file.close();
}

void User::addTasksFromFile(const string& filename) {
    schedule.addTasksFromFile(filename);
}
void User::addUsersFromFile(const string& filename, User*& head) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            size_t commaPos = line.find(',');
            if (commaPos == std::string::npos) {
                std::cerr << "Error: Invalid line format (missing comma): " << line << std::endl;
                continue;
            }

            std::string username = line.substr(0, commaPos);
            std::string password = line.substr(commaPos + 1);

            User* user = new User(username, password);
            user->set_password(password);

            string taskFile = username + "_tasks.txt";
            user->addTasksFromFile(taskFile);
            user->addUser(head);
        }
    }
    file.close();
}

void User::loadUserToFile(sf::RenderWindow& window, sf::Font& font, const string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << " for writing!" << std::endl;
        return;
    }
    file.seekp(0, std::ios::end);  
    if (file.tellp() > 0) { 
        file << std::endl; 
    }
    file << username << "," << password;
    file.close();
}
void User::loadtasktofile(sf::RenderWindow& window, sf::Font& font, const string& filename) {
    schedule.saveTasksToFile(window, font,filename);
}
void User::registerUsers(User*& head, const string& username, const string& password) {
    User* newUser = new User(username, password);
    newUser->addUser(head);
}