#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdexcept> 
#include "schedule.h"
using namespace std;
schedule :: ~schedule() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp->task;
        delete tmp;
    }
}
Task* schedule::get_selected_task() const {
    return selectedTask;
}

void schedule::set_selected_task(Task* task) {
    selectedTask = task;
}

bool schedule::is_duplicate(const Task* new_task) const {
    Node* current = head;
    while (current) {
        Task* existing_task = current->task;
        if (existing_task->get_date() == new_task->get_date() &&
            existing_task->get_start_time() == new_task->get_start_time() &&
            existing_task->get_end_time() == new_task->get_end_time() &&
            existing_task->get_priority() == new_task->get_priority()) {
            return true;
        }
        current = current->next;
    }
    return false;
}
bool schedule::is_empty() const {
    return head == nullptr;
}
void schedule::add_task(Task* task) {
    Node* newNode = new Node(task);
    newNode->next = head;
    head = newNode;
}
//void schedule::add_task1(Task* task) {
//    if (is_duplicate(task)) {
//        cout << "Cong viec da ton tai voi ngay, gio, do uu tien giong nhau.\n";
//        delete task;
//        return;
//    }
//
//    Node* current = head;
//    while (current) {
//        Task* existing_task = current->task;
//
//        if (existing_task->get_date() == task->get_date() &&
//            task->get_start_time() < existing_task->get_end_time() &&
//            task->get_end_time() > existing_task->get_start_time()) {
//            cout << "Da co mot cong viec trong khoang thoi gian nay.\n";
//            cout << "1. Thay the cong viec cu\n";
//            cout << "2. Huy bo viec them cong viec\n";
//            cout << "Chon lua cua ban (1/2): ";
//
//            int choice;
//            cin >> choice;
//            cin.ignore(); // Clear the input buffer
//
//            if (choice == 1) {
//                delete existing_task;
//                current->task = task;
//                cout << "Cong viec da duoc thay the!\n";
//            }
//            else {
//                delete task;
//                cout << "Huy bo viec them cong viec!\n";
//            }
//            return;
//        }
//        current = current->next;
//    }
//
//    check_local_time(task);
//
//    Node* newNode = new Node(task);
//    newNode->next = head;
//    head = newNode;
//
//    cout << "Cong viec da duoc them thanh cong!\n";
//}
//

void schedule::del_task(const string& title) {
    if (head == nullptr) {
        cout << "empty job list!" << endl;
        return;
    }

    if (head->task->get_title() == title) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Deleted job titled: " << title << endl;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->task->get_title() == title) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Deleted job titled: " << title << endl;
            return;
        }
        current = current->next;
    }

    cout << "No job found with title: " << title << endl;
}
void schedule::remove_task(Node* taskNode) {
    if (!taskNode) return;

    if (taskNode == head) {
        head = head->next;
    }
    else {
        Node* prev = head;
        while (prev && prev->next != taskNode) {
            prev = prev->next;
        }

        if (prev) {
            prev->next = taskNode->next;
        }
    }

    delete taskNode;
    std::cout << "Task removed successfully!" << std::endl;
}



void schedule::edit_task(sf::Font &font,Node* taskNode) {
    sf::RenderWindow editwindow(sf::VideoMode(1500, 1000), "Edit Task");
    if (!taskNode) return;

    Task* newtask = nullptr;
    newtask = newtask->creTask(editwindow, font);

    if (newtask) {
        taskNode->task = newtask; 
    }

    editwindow.close(); 
}
int convertTimeToMinutes(const std::string& time_str) {
    int hours, minutes;
    char colon;
    std::istringstream(time_str) >> hours >> colon >> minutes;
    // Tính số phút kể từ 00:00
    return hours * 60 + minutes;
}
// Hàm chuyển đổi số phút thành giờ phút (hh:mm)
string convertMinutesToTime(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;

    // Đảm bảo rằng giờ và phút có định dạng 2 chữ số
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << mins;

    return oss.str();
}




void schedule::display_tasks(sf::RenderWindow& window, sf::Font& font) const {
    if (is_empty()) {
        drawText(window, font, "EMPTY JOBS LIST", 26, { 100, 100 }, sf::Color::White);
        window.display();
    }
    else {
        Node* cur = head;
        while (cur) {
            cur->bounds = sf::FloatRect(); 
            cur = cur->next;
        }
        cur = head;

        drawText(window, font, "Date", 26, { 100,100 }, sf::Color::White);
        drawText(window, font, "Title", 26, { 300,100 }, sf::Color::White);
        drawText(window, font, "Description", 26, { 500,100 }, sf::Color::White);
        drawText(window, font, "Start Time", 26, { 750,100 }, sf::Color::White);
        drawText(window, font, "End Time", 26, { 950,100 }, sf::Color::White);
        drawText(window, font, "Priority", 26, { 1150,100 }, sf::Color::White);

        sf::Vector2f position(100, 140);
        int textSize = 21;
        sf::Color textColor = sf::Color::White;
        float taskHeight = 35;

        while (cur) {
            // Nếu task là task được chọn, tô màu vàng (hoặc màu khác bạn chọn)
            sf::Color taskColor = (cur->task == selectedTask) ? sf::Color::Yellow : sf::Color::White; // Màu vàng cho task được chọn

            // Vẽ thông tin của task
            drawText(window, font, cur->task->get_date(), textSize, position, taskColor);
            position.x += 200;

            drawText(window, font, cur->task->get_title(), textSize, position, taskColor);
            position.x += 200;

            drawText(window, font, cur->task->get_description(), textSize, position, taskColor);
            position.x += 250;

            drawText(window, font, convertMinutesToTime(cur->task->get_start_time()), textSize, position, taskColor);
            position.x += 200;

            drawText(window, font, convertMinutesToTime(cur->task->get_end_time()), textSize, position, taskColor);
            position.x += 200;

            drawText(window, font, to_string(cur->task->get_priority()), textSize, position, taskColor);
            cur->bounds = sf::FloatRect(100, position.y, 1200, taskHeight);

            position.x = 100;
            position.y += taskHeight;

            cur = cur->next;
        }

        window.display();
    }
}
void schedule::handle_click(sf::RenderWindow& window, sf::Font font, sf::Vector2i mousePos, const std::string& input_date,const int num) {
    Node* cur = head;
    bool key = 1;
    while (cur) {
        if (cur->bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            // Tô sáng task được chọn (tuỳ chọn)
            window.clear(sf::Color::Black);
            set_selected_task(cur->task);
            sf::RectangleShape Delbox = drawrec(100, 50, 5, { 800, 800 }, sf::Color::White, sf::Color::Red);
            sf::RectangleShape Editbox = drawrec(100, 50, 5, { 1000, 800 }, sf::Color::White, sf::Color::Green);
            drawButton(window, Delbox, "Delete", font, sf::Color::Black);
            drawButton(window, Editbox, "Edit", font, sf::Color::Black);
            if (num==1) display_tasks(window, font);
            if (num == 2) display_date_tasks(window, font,input_date);
            sf::Event event;
            while (true) {
                if (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }

                    // Nếu click chuột
                    if (event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2i mousePos1 = sf::Mouse::getPosition(window);

                        if (Delbox.getGlobalBounds().contains(static_cast<float>(mousePos1.x), static_cast<float>(mousePos1.y))) {
                            remove_task(cur);
                            if (num == 1) display_tasks(window, font);
                            if (num == 2) display_date_tasks(window, font, input_date);
                            return;
                        }


                        if (Editbox.getGlobalBounds().contains(static_cast<float>(mousePos1.x), static_cast<float>(mousePos1.y))) {
                            edit_task(font, cur);
                            if (num == 1) display_tasks(window, font);
                            if (num == 2) display_date_tasks(window, font, input_date);
                            return; 
                        }

                        // Kiểm tra nếu người dùng click vào một task khác
                        Node* newCur = head;
                        while (newCur) {
                            if (newCur->bounds.contains(static_cast<float>(mousePos1.x), static_cast<float>(mousePos1.y))) {
                                set_selected_task(newCur->task);
                                if (num == 1) display_tasks(window, font);
                                if (num == 2) display_date_tasks(window, font, input_date);
                                break; // Thoát vòng lặp nội bộ để xử lý task mới
                            }
                            newCur = newCur->next;
                        }
                        mousePos = mousePos1;
                        cur = head;
                        key= 0;
                        break;
                        //    // Nếu không phải nút hoặc task, thoát vòng chờ
                    }
                    //return;
                }
                drawButton(window, Delbox, "Delete", font, sf::Color::Black);
                drawButton(window, Editbox, "Edit", font, sf::Color::Black);
            }

        // Kết thúc xử lý cho task hiện tại
    }
        set_selected_task(nullptr);
        if (key ==1) cur = cur->next;
        else key = 1;
    }
}

void schedule::display_date_tasks(sf::RenderWindow& window, sf::Font& font, const std::string& input_date) const {
        if (!isValidDate(input_date)) {
            drawText(window, font, "Invalid date format. Please use dd/mm/yyyy.", 23, { 200,200 }, sf::Color::Black);
            window.display();
            return;
        }

        bool found = false;
        Node* cur = head;
        while (cur) {
            cur->bounds = sf::FloatRect(); 
            cur = cur->next;
        }
        cur = head;
        while (cur) {
            Task* task = cur->task;
            if (task->get_date() == input_date) {
                found = true;
            }
            cur = cur->next;
        }
        cur = head;
        if (found) {
            drawText(window, font, "Tasks for: ", 25, { 400,50 }, sf::Color::White);
            drawText(window, font, input_date, 25, { 550,50 }, sf::Color::White);
            drawText(window, font, "Title", 26, { 100,100 }, sf::Color::White);
            drawText(window, font, "Description", 26, { 300,100 }, sf::Color::White);
            drawText(window, font, "Start Time", 26, { 550,100 }, sf::Color::White);
            drawText(window, font, "End Time", 26, { 750,100 }, sf::Color::White);
            drawText(window, font, "Priority", 26, { 950,100 }, sf::Color::White);
            sf::Vector2f position(100, 140);
            int textSize = 21;
            sf::Color textColor = sf::Color::White;
            float taskHeight = 35;

            while (cur) {
                Task* task = cur->task;
                if (task->get_date() == input_date) {
                    sf::Color taskColor = (cur->task == selectedTask) ? sf::Color::Yellow : sf::Color::White;

                    drawText(window, font, cur->task->get_title(), textSize, position, taskColor);
                    position.x += 200;

                    drawText(window, font, cur->task->get_description(), textSize, position, taskColor);
                    position.x += 250;

                    drawText(window, font, convertMinutesToTime(cur->task->get_start_time()), textSize, position, taskColor);
                    position.x += 200;

                    drawText(window, font, convertMinutesToTime(cur->task->get_end_time()), textSize, position, taskColor);
                    position.x += 200;

                    drawText(window, font, to_string(cur->task->get_priority()), textSize, position, taskColor);

                    cur->bounds = sf::FloatRect(100, position.y, 1200, taskHeight);
                    position.x = 100;
                    position.y += taskHeight;
                }
                cur = cur->next;
            }

            window.display();
        }
        else if (!found) {
            drawText(window, font, "No tasks found for: ", 26, { 200,200 }, sf::Color::White);
            drawText(window, font, input_date, 26, { 550,200 }, sf::Color::White);
            window.display();
        }
    }
bool schedule::compare_tasks(Task* task1, Task* task2) {
    int day1, month1, year1;
    int day2, month2, year2;
    char colon;
    std::istringstream(task1->get_date()) >> day1 >>colon>> month1>>colon >> year1;
    std::istringstream(task2->get_date()) >> day2 >>colon>> month2 >>colon>> year2;

    if (year1 < year2) {
        return true;
    }
    else if (year1 > year2) {
        return false;
    }

    if (month1 < month2) {
        return true;
    }
    else if (month1 > month2) {
        return false;
    }

    if (day1 < day2) {
        return true;
    }
    else if (day1 > day2) {
        return false;
    }

    if (task1->get_start_time() < task2->get_start_time()) {
        return true;
    }
    else if (task1->get_start_time() > task2->get_start_time()) {
        return false;
    }

    return task1->get_priority() < task2->get_priority();
}



void schedule::sort_task() {
    if (!head) return;  

    Node* current = head;
    while (current != nullptr) {
        Node* minNode = current;
        Node* nextNode = current->next;

        while (nextNode != nullptr) {
            if (!compare_tasks(minNode->task, nextNode->task)) {
                minNode = nextNode;  
            }
            nextNode = nextNode->next;
        }

        if (minNode != current) {
            Task* tempTask = current->task;
            current->task = minNode->task;
            minNode->task = tempTask;
        }

        current = current->next;
    }
}
void schedule::addTasksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, description, date, start_time_str, end_time_str;
        int start_time, end_time, priority;

        if (iss >> std::quoted(title) >> std::quoted(description) >> date >> std::quoted(start_time_str) >> std::quoted(end_time_str) >> priority) {
            start_time = convertTimeToMinutes(start_time_str);
            end_time = convertTimeToMinutes(end_time_str);
            Task* task = new Task(title, description, date, start_time, end_time, priority);
            add_task(task);  
        }
    }
    file.close();
    std::cout << "Tasks from file added successfully!" << std::endl;
}
void schedule::saveTasksToFile(sf::RenderWindow& window, sf::Font& font, const std::string& filename) const {
    std::string taskFile = filename + "_tasks.txt";
    std::ofstream file(taskFile, std::ios::out); 

    if (!file.is_open()) {
        std::cerr << "Failed to create or open file: " << taskFile << std::endl;
        return;
    }
    string star_timeStr, end_timeStr;
    // Duyệt qua danh sách liên kết các Node
    Node* current = head;
    while (current != nullptr) {
        Task* task = current->task;
        star_timeStr=convertMinutesToTime(task->get_start_time());
        end_timeStr = convertMinutesToTime(task->get_end_time());
        // Ghi thông tin của Task vào file
        file << std::quoted(task->get_title()) << " "
            << std::quoted(task->get_description()) << " "
            << task->get_date() << " "
            << std::quoted(star_timeStr) << " "
            << std::quoted(end_timeStr) << " "
            << task->get_priority() << std::endl;

        // Chuyển sang Node tiếp theo
        current = current->next;
    }

    file.close();
    string notice = "Tasks " + filename +"save to file successfully!";
    drawText(window, font, notice, 23, { 500,800 }, sf::Color::White);
    window.display();
}


