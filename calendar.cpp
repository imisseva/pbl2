#include "calendar.h"
std::string getCurrentDate() {
    // Lấy thời gian hiện tại
    std::time_t t = std::time(nullptr);
    std::tm now;

    // Sử dụng localtime_s để thay thế localtime
    localtime_s(&now, &t);

    // Định dạng ngày "dd/mm/yyyy"
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << now.tm_mday << "/"
        << std::setfill('0') << std::setw(2) << (now.tm_mon + 1) << "/"
        << (now.tm_year + 1900);

    return oss.str();
}
bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return false;
    }

    int day, month, year;
    char delimiter1, delimiter2;

    std::istringstream dateStream(date);
    dateStream >> day >> delimiter1 >> month >> delimiter2 >> year;

    if (delimiter1 != '/' || delimiter2 != '/' || dateStream.fail()) {
        return false;
    }

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        daysInMonth[2] = 29;
    }

    if (day > daysInMonth[month]) {
        return false;
    }

    return true;
}
bool isValidTime(const std::string& timeStr) {
    if (timeStr.size() != 5 || timeStr[2] != ':') {
        return false;
    }

    std::string hoursStr = timeStr.substr(0, 2);
    std::string minutesStr = timeStr.substr(3, 2);

    int hours = std::stoi(hoursStr);
    if (hours < 0 || hours > 23) {
        return false;
    }

    int minutes = std::stoi(minutesStr);
    if (minutes < 0 || minutes > 59) {
        return false;
    }

    return true;
}
std::string get_today_date() {
    time_t now = time(0);
    tm now_tm;

    if (localtime_s(&now_tm, &now) != 0) {
        throw std::runtime_error("Failed to get local time.");
    }

    char date_str[11];
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", &now_tm);
    return std::string(date_str);
}
std::string get_relative_date(int days_offset)  {
    time_t now = time(0);
    now += static_cast<time_t>(days_offset) * 24 * 60 * 60;

    tm target_tm;

    if (localtime_s(&target_tm, &now) != 0) {
        throw std::runtime_error("Failed to calculate the relative date.");
    }

    char date_str[11];
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", &target_tm);
    return std::string(date_str);
}


bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int year, int month) {
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) return 29;
    return daysInMonth[month - 1];
}

int getFirstDayOfMonth(int year, int month) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int K = year % 100;  
    int J = year / 100;  
    int dayOfWeek = (1 + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    return (dayOfWeek + 6) % 7;  
}

void drawCalendar(sf::Font& font, int& year, int& month, int& selectedDay) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Calendar");

    while (window.isOpen()) {
        int daysInMonth = getDaysInMonth(year, month);
        int startDay = getFirstDayOfMonth(year, month);

        // Header
        sf::Text header;
        header.setFont(font);
        header.setString("Calendar: " + std::to_string(month) + "/" + std::to_string(year));
        header.setCharacterSize(30);
        header.setFillColor(sf::Color::White);
        header.setPosition(250, 20);

        // Dòng ngày trong tuần
        std::string weekdays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        int offsetX = 50, offsetY = 100;
        std::vector<sf::Text> weekdayTexts;
        for (int i = 0; i < 7; ++i) {
            sf::Text dayHeader;
            dayHeader.setFont(font);
            dayHeader.setString(weekdays[i]);
            dayHeader.setCharacterSize(20);
            dayHeader.setFillColor(sf::Color::White);
            dayHeader.setPosition(offsetX + i * 100, offsetY);
            weekdayTexts.push_back(dayHeader);
        }

        // Tạo danh sách liên kết các ô ngày
        DayNode* head = nullptr;
        DayNode* tail = nullptr;

        int day = 1;
        for (int week = 0; week < 6; ++week) {
            for (int weekday = 0; weekday < 7; ++weekday) {
                if ((week == 0 && weekday < startDay) || day > daysInMonth) continue;

                sf::RectangleShape box(sf::Vector2f(80, 80));
                box.setFillColor(day == selectedDay ? sf::Color::Green : sf::Color::Blue);
                box.setOutlineThickness(2);
                box.setOutlineColor(sf::Color::White);
                box.setPosition(offsetX + weekday * 100, offsetY + 50 + week * 100);

                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(day));
                text.setCharacterSize(25);
                text.setFillColor(sf::Color::White);
                text.setPosition(box.getPosition().x + 25, box.getPosition().y + 20);

                DayNode* newNode = new DayNode(day, box, text);
                if (!head) {
                    head = tail = newNode;
                }
                else {
                    tail->next = newNode;
                    tail = newNode;
                }

                ++day;
            }
        }

        // Nút chuyển tháng
        sf::RectangleShape prevButton(sf::Vector2f(100, 50));
        prevButton.setFillColor(sf::Color::Red);
        prevButton.setPosition(50, 20);
        sf::Text prevText;
        prevText.setFont(font);
        prevText.setString("Prev");
        prevText.setCharacterSize(20);
        prevText.setFillColor(sf::Color::White);
        prevText.setPosition(75, 25);

        sf::RectangleShape nextButton(sf::Vector2f(100, 50));
        nextButton.setFillColor(sf::Color::Green);
        nextButton.setPosition(600, 20);
        sf::Text nextText;
        nextText.setFont(font);
        nextText.setString("Next");
        nextText.setCharacterSize(20);
        nextText.setFillColor(sf::Color::White);
        nextText.setPosition(625, 25);

        // Nút chọn ngày (Choose)
        sf::RectangleShape chooseButton(sf::Vector2f(150, 50));
        chooseButton.setFillColor(sf::Color::Yellow);
        chooseButton.setPosition(325, 700);
        sf::Text chooseText;
        chooseText.setFont(font);
        chooseText.setString("Choose");
        chooseText.setCharacterSize(20);
        chooseText.setFillColor(sf::Color::Black);
        chooseText.setPosition(355, 710);

        // Vẽ các thành phần
        window.clear(sf::Color::Black);
        window.draw(header);
        for (const auto& weekday : weekdayTexts) {
            window.draw(weekday);
        }

        DayNode* current = head;
        while (current) {
            window.draw(current->box);
            window.draw(current->text);
            current = current->next;
        }
        window.draw(prevButton);
        window.draw(prevText);
        window.draw(nextButton);
        window.draw(nextText);
        window.draw(chooseButton);
        window.draw(chooseText);

        window.display();

        // Xử lý sự kiện
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Xử lý click vào nút Previous
                if (prevButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    --month;
                    if (month < 1) {
                        month = 12;
                        --year;
                    }
                    selectedDay = 0; // Xóa lựa chọn ngày cũ
                }

                // Xử lý click vào nút Next
                if (nextButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    ++month;
                    if (month > 12) {
                        month = 1;
                        ++year;
                    }
                    selectedDay = 0; // Xóa lựa chọn ngày cũ
                }

                // Xử lý chọn ngày
                current = head;
                while (current) {
                    if (current->box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedDay = current->day;
                        break;
                    }
                    current = current->next;
                }

                // Xử lý click vào nút Choose
                if (chooseButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                    
                }
            }
        }

        // Giải phóng bộ nhớ
        current = head;
        while (current) {
            DayNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}
