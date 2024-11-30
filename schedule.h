#ifndef schedule_h
#define schedule_h

#include <iostream>
#include <string>
#include "task.h"
#include "draw.h"
#include"calendar.h"
class schedule {
private:
    struct Node {
        Task* task;
        Node* next;
        sf::FloatRect bounds;
        Node(Task* t) : task(t), next(nullptr){}
    };
    Node* head;
    Task* selectedTask;
    bool compare_tasks(Task* task1, Task* task2);

public:
    schedule() : head(nullptr), selectedTask(nullptr) {}
    ~schedule();
    Task* get_selected_task() const;
    void set_selected_task(Task* task);
    bool is_duplicate(const Task* new_task) const;
    void add_task(Task* task);
    //void add_task1(Task* task);
    void del_task(const string& title);
    void remove_task(Node* taskNode);
    void edit_task(sf::Font &font,Node* taskNode);
    void sort_task();
    void handle_click(sf::RenderWindow& window, sf::Font font, sf::Vector2i mousePosition, const std::string& input_date, const int num); // thêm biến
    void display_tasks(sf::RenderWindow& window,sf::Font &font) const; // sửa lại
    void display_date_tasks(sf::RenderWindow& window, sf::Font& font, const std::string& input_date) const; // hàm mới
    bool is_empty() const;
    void addTasksFromFile(const std::string& filename);
    void saveTasksToFile(sf::RenderWindow& window, sf::Font& font, const std::string& filename) const;
    friend class user;
};
int convertTimeToMinutes(const std::string& time_str);
string convertMinutesToTime(int minutes);




#endif