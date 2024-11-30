#ifndef user_h
#define user_h

#include <iostream>
#include <string>
#include "task.h"
#include "schedule.h"
#include "draw.h"
#include <SFML/Graphics.hpp>
using namespace std;

class User {
private:

    string username;
    string password;
    schedule schedule;
    User* next;
    Task* selectedTask;
public:
    User(const string& username, const string& password);
    User* get_next() const;
    void set_next(User* nextUser);
    void set_password(const string& pass);
    string get_username() const;
    string get_password() const;
    Task* get_selected_task() const;
    void set_selected_task(Task* task);
    void add_task(Task* task);
    void delete_task(const string& title);
    void show_schedule(sf::RenderWindow& window, sf::Font& font) const;
    void show_date_schedule(sf::RenderWindow& window, sf::Font& font, const std::string& input_date) const;
    void handle_click(sf::RenderWindow& window, sf::Font font, sf::Vector2i mousePosition, const std::string& input_date, const int num); //sửa    
    void sort_task();
    void addUser(User*& head);
    void saveAllUsersToFile(const string& filename, User* head);
    void updatePassword(const string& username, const string& newPassword, User*& head);
    void addUsersFromFile(const std::string& filename, User*& head);
    void loadUserToFile(sf::RenderWindow &window,sf::Font &font, const string& filename) const;
    void addTasksFromFile(const string& filename);
    void loadtasktofile(sf::RenderWindow& window, sf::Font& font, const string& filename);

    static void registerUsers(User*& head, const string& username, const string& password);
};





#endif