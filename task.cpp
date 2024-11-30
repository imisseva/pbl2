#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <stdexcept>
#include "task.h"
#include "calendar.h"

using namespace std;

Task::Task() {}

Task::Task(const string& title, const string& description, const string& date, int start_time, int end_time, int priority) : title(title), description(description), date(date), start_time(start_time), end_time(end_time), priority(priority) {}

Task::~Task() {}

string Task::get_title() const {
    return title;
}

string Task::get_description() const {
    return description;
}

string Task::get_date() const {
    return date;
}

int Task::get_start_time() const {
    return start_time;
}

int Task::get_end_time() const {
    return end_time;
}

int Task::get_priority() const {
    return priority;
}


void Task::set_title(const string& t) {
    title = t;
}

void Task::set_description(const string& d) {
    description = d;
}

void Task::set_date(const string& da) {
    date = da;
}

void Task::set_start_time(int s) {
    start_time = s;
}

void Task::set_end_time(int e) {
    end_time = e;
}

void Task::set_priority(int p) {
    priority = p;
}
void Task::show() const {
    cout << "Title: " << title << "\nDescription: " << description
        << "\nDate: " << date << "\nStart Time: " << start_time
        << "\nEnd Time: " << end_time << "\nPriority: " << priority << endl;
}
bool Task::check_time(int time) {
    return time >= 0 && time <= 24;
}


Task* Task::creTask(sf::RenderWindow& window, sf::Font& font) {
    string title, description, date, start_times, end_times, prioritys;
    int start_time, end_time, priority;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Error loading background image\n";
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::RectangleShape titlebox = drawrec(800, 50, 5, { 100,100 }, sf::Color::Black, sf::Color::White);
    sf::RectangleShape desbox = drawrec(800, 50, 5, { 100,200 }, sf::Color::Black, sf::Color::White);
    sf::RectangleShape datebox = drawrec(800, 50, 5, { 100,300 }, sf::Color::Black, sf::Color::White);
    sf::RectangleShape starttimebox = drawrec(800, 50, 5, { 100,400 }, sf::Color::Black, sf::Color::White);
    sf::RectangleShape endtimebox = drawrec(800, 50, 5, { 100,500 }, sf::Color::Black, sf::Color::White);
    sf::RectangleShape priobox = drawrec(800, 50, 5, { 100,600 }, sf::Color::Black, sf::Color::White);
    sf::RectangleShape nextButton = drawrec(100, 40, 5, { 1300,870 }, sf::Color::White, sf::Color::Magenta);
    sf::RectangleShape backButton = drawrec(100, 40, 5, { 40,40 }, sf::Color::White, sf::Color::Red);
    sf::Text Title, Description, Date, Starttime, Endtime, Priority;
    bool thoat = 1;
    int year = 2024, month = 11, selectedDay = 0;
    bool error = 1, error1 = 1, error2 = 1, error3 = 1;
    while (thoat) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.type == sf::Event::Closed) {
                    thoat = 0;
                }
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (titlebox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.draw(titlebox);
                    drawText(window, font, "Enter Title:", 20, { 110,110 }, sf::Color::White);
                    Title = box_write(window, font, titlebox, { 350,110 }, 20, 23, title, 40, 0, sf::Color::Black, sf::Color::White, sf::Color::White);

                }
                else if (desbox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.draw(desbox);
                    drawText(window, font, "Enter Description:", 20, { 110,210 }, sf::Color::White);
                    Description = box_write(window, font, desbox, { 350,210 }, 20, 23, description, 40, 0, sf::Color::Black, sf::Color::White, sf::Color::White);
                }
                else if (datebox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    drawCalendar(font, year, month, selectedDay);
                    // Cập nhật giá trị date sau khi chọn ngày
                    if (selectedDay != 0) {
                        std::ostringstream oss;
                        oss << (selectedDay < 10 ? "0" : "") << selectedDay << "/"
                            << (month < 10 ? "0" : "") << month << "/" << year;
                        date = oss.str();
                        cout << date;
                        drawText(window, font, date, 20, { 310,310 }, sf::Color::White);
                    }
                }
                else if (starttimebox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.draw(starttimebox);
                    drawText(window, font, "Enter Start Time(hh:mm):", 20, { 110, 410 }, sf::Color::White);
                    Starttime = box_write(window, font, starttimebox, { 350, 410 }, 20, 23, start_times, 40, 0, sf::Color::Black, sf::Color::White, sf::Color::White);
                    error1 = 1;

                    try {
                        if (isValidTime(start_times)) {
                            int hours = std::stoi(start_times.substr(0, 2));
                            int minutes = std::stoi(start_times.substr(3, 2));
                            start_time = hours * 60 + minutes;
                        }
                        else {
                            error1 = 0;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        error1 = 0;
                    }

                    if (!isValidTime(start_times)) {
                        error1 = 0;
                    }
                }
                else if (endtimebox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.draw(endtimebox);
                    drawText(window, font, "Enter End Time(hh:mm):", 20, { 110, 510 }, sf::Color::White);
                    Endtime = box_write(window, font, endtimebox, { 350, 510 }, 20, 23, end_times, 40, 0, sf::Color::Black, sf::Color::White, sf::Color::White);
                    error2 = 1;

                    try {
                        if (isValidTime(end_times)) {
                            int hours = std::stoi(end_times.substr(0, 2));
                            int minutes = std::stoi(end_times.substr(3, 2));
                            end_time = hours * 60 + minutes;
                        }
                        else {
                            error2 = 0;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        error2 = 0;
                    }

                    if (!isValidTime(end_times)) {
                        error2 = 0;
                    }
                }

                else if (priobox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.draw(priobox);
                    drawText(window, font, "Enter Priorty:", 20, { 110,610 }, sf::Color::White);
                    Priority = box_write(window, font, priobox, { 350,610 }, 20, 23, prioritys, 40, 0, sf::Color::Black, sf::Color::White, sf::Color::White);
                    error3 = 1;
                    try
                    {
                        priority = stoi(prioritys);
                    }
                    catch (const invalid_argument& e)
                    {
                        error3 = 0;
                    }
                }
            }
            if (drawNextButton(window, font, { 1300,870 }) == 1 && error == 1 && error1 == 1 && error2 == 1 && error3 == 1) {
                priority = stoi(prioritys);
                return new Task(title, description, date, start_time, end_time, priority);
            }
            if (drawBackButton(window, font, { 40,40 }))
                return nullptr;
        }
        window.draw(backgroundSprite);
        drawText(window, font, "Enter Title:", 20, { 110,110 }, sf::Color::Black);
        drawText(window, font, "Enter Description:", 20, { 110,210 }, sf::Color::Black);
        drawText(window, font, "Enter Date(dd/mm/year):", 20, { 110,310 }, sf::Color::Black);
        drawText(window, font, "Enter Start Time:", 20, { 110,410 }, sf::Color::Black);
        drawText(window, font, "Enter End Time:", 20, { 110,510 }, sf::Color::Black);
        drawText(window, font, "Enter Priorty:", 20, { 110,610 }, sf::Color::Black);
        drawText(window, font, date, 21, { 380,310 }, sf::Color::White);
        if (error == 0) drawText(window, font, "Error!Wrong input format:", 20, { 1000,310 }, sf::Color::Black);
        if (error1 == 0) drawText(window, font, "Error!Wrong input format:", 20, { 1000,410 }, sf::Color::Black);
        if (error2 == 0) drawText(window, font, "Error!Wrong input format:", 20, { 1000,510 }, sf::Color::Black);
        if (error3 == 0) drawText(window, font, "Error!Wrong input format:", 20, { 1000,610 }, sf::Color::Black);


        window.draw(Title);
        window.draw(Description);
        window.draw(Date);
        window.draw(Starttime);
        window.draw(Endtime);
        window.draw(Priority);
        drawButton(window, nextButton, "Next", font);
        drawButton(window, backButton, "back", font);
        window.display();
    }
}