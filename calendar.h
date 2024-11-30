#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
// Cấu trúc Node cho danh sách liên kết
struct DayNode {
    int day;
    sf::RectangleShape box;
    sf::Text text;
    DayNode* next;

    DayNode(int d, const sf::RectangleShape& b, const sf::Text& t)
        : day(d), box(b), text(t), next(nullptr) {}
};
bool isLeapYear(int year);
// Hàm vẽ lịch
void drawCalendar(sf::Font& font, int& year, int& month, int& selectedDay);
std::string getCurrentDate(); // thêm
bool isValidDate(const std::string& date);
bool isValidTime(const std::string& timeStr);
std::string get_today_date() ;
std::string get_relative_date(int days_offset) ;
