#ifndef task_h
#define task_h

#include <iostream>
#include <string>
#include "draw.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Task {
private:
    string title;       // Chủ đề
    string description; // Mô tả công việc
    string date;        // Ngày
    int start_time;     // Thời gian bắt đầu
    int end_time;       // Thời gian kết thúc
    int priority;       // Mức độ ưu tiên

public:
    Task();
    Task(const string& title, const string& description, const string& date, int start_time, int end_time, int priority);
    ~Task();
    Task* creTask(sf::RenderWindow& window, sf::Font& font);

    string get_title() const;
    string get_description() const;
    string get_date() const;
    int get_start_time() const;
    int get_end_time() const;
    int get_priority() const;


    void set_title(const string& t);
    void set_description(const string& d);
    void set_date(const string& da);
    void set_start_time(int s);
    void set_end_time(int e);
    void set_priority(int p);

    void show() const;
    bool check_time(int);
};




#endif
