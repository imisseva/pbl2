//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include "user.h"
//#include "schedule.h"
//#include "task.h"
//#include "admin.h"
//#include "draw.h"
//
//
//using namespace std;
//void pressEnterToContinue(sf::RenderWindow& window, sf::Font& font, float x, float y) {
//    drawText(window, font, "Press Enter To Continue", 20, { x,y }, sf::Color::White);
//    window.display();
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//                return;
//            }
//            // Kiểm tra nếu phím Enter được nhấn
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
//                return;
//            }
//        }
//
//    }
//}
//void AdminMenu(Admin& admin, sf::RenderWindow& window, sf::Font& font);
//void UserMenu(User* currentUser, Admin& admin, sf::RenderWindow& window, sf::Font& font);
//void accUser(Admin& admin, sf::RenderWindow& window, sf::Font& font);
//void MainMenu(Admin& admin, sf::RenderWindow& window) {
//    sf::Font font;
//    if (!font.loadFromFile("OpenSans.ttf")) {
//        std::cerr << "Error loading font\n";
//        return;
//    }
//    sf::Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("background.jpg")) {
//        std::cerr << "Error loading background image\n";
//        return;
//    }
//    sf::Sprite backgroundSprite;
//    backgroundSprite.setTexture(backgroundTexture);
//    //chỉnh size
//    backgroundSprite.setScale(
//        window.getSize().x / backgroundTexture.getSize().x,
//        window.getSize().y / backgroundTexture.getSize().y
//    );
//    sf::RectangleShape adminButton = drawrec(200, 50, 5, { 100,100 }, sf::Color::Blue, sf::Color::Green);
//    sf::RectangleShape userButton = drawrec(200, 50, 5, { 100,200 }, sf::Color::Blue, sf::Color::Green);
//    while (window.isOpen()) {
//        window.clear(sf::Color::Black);
//        window.draw(backgroundSprite);
//        // Vẽ các nút Admin và User
//        drawButton(window, adminButton, "Admin", font);
//        drawButton(window, userButton, "User", font);
//        window.display();
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            if (event.type == sf::Event::MouseButtonPressed) {
//                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                sf::Text password;
//                sf::Text password1;
//                if (adminButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    int thoat = 1;
//                    string password_ = "";
//                    string password_0 = "";
//                    while (thoat) {
//                        sf::RectangleShape passwordBox = drawrec(400, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Yellow);
//                        sf::RectangleShape nextButton = drawrec(100, 40, 5, { 400,400 }, sf::Color::White, sf::Color::Magenta);
//                        sf::RectangleShape backButton = drawrec(100, 40, 5, { 40,40 }, sf::Color::White, sf::Color::Red);
//                        sf::Event event1;
//                        while (window.pollEvent(event1)) {
//
//                            if (event1.type == sf::Event::MouseButtonPressed) {
//                                if (event1.type == sf::Event::Closed) {
//                                    thoat = 0;
//
//                                }
//                                sf::Vector2i mousePos1 = sf::Mouse::getPosition(window);
//                                if (passwordBox.getGlobalBounds().contains(mousePos1.x, mousePos1.y)) {
//                                    drawButton(window, passwordBox, "Password:", font);
//                                    password = box_write(window, font, passwordBox, { 230,110 }, 20, 23, password_, 1, sf::Color::Blue, sf::Color::Black);
//                                    password_0 = "";
//
//                                    for (int i = 0;i < password_.size();++i) {
//                                        password_0 += '*';
//                                    }
//                                    password1 = password;
//                                    password1.setString(password_0);
//                                }
//                            }
//                            if (drawNextButton(window, font, { 400, 400 })) {
//                                if (password_ == "2005") {
//                                    AdminMenu(admin, window, font);
//                                }
//                                else {
//                                    drawText(window, font, "Incorrect, try again!", 20, { 250,200 }, sf::Color::White);
//                                    pressEnterToContinue(window, font, 250, 250);
//                                }
//                            }
//                            else if (drawBackButton(window, font, { 40, 40 })) {
//                                thoat = 0;
//                            }
//
//                        }
//                        window.clear(sf::Color::Black);
//                        drawButton(window, passwordBox, "Password:", font);
//                        drawButton(window, nextButton, "Next", font);
//                        drawButton(window, backButton, "back", font);
//                        window.draw(password1);
//                        window.display();
//                    }
//                }
//
//                else if (userButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                    accUser(admin, window, font);
//                }
//            }
//        }
//    }
//}
//void accUser(Admin& admin, sf::RenderWindow& window, sf::Font& font) {
//    string user = "";
//    sf::RectangleShape loginButton = drawrec(100, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Yellow);
//    sf::RectangleShape registerButton = drawrec(100, 50, 5, { 100,200 }, sf::Color::White, sf::Color::Yellow);
//    while (window.isOpen()) {
//        sf::Event userEvent;
//        while (window.pollEvent(userEvent)) {
//            if (userEvent.type == sf::Event::Closed) {
//                window.close();
//                return;
//            }
//            if (userEvent.type == sf::Event::KeyPressed && userEvent.key.code == sf::Keyboard::Escape) {
//                break;
//            }
//            if (userEvent.type == sf::Event::MouseButtonPressed) {
//                sf::Vector2i mousePosUser = sf::Mouse::getPosition(window);
//
//                if (loginButton.getGlobalBounds().contains(mousePosUser.x, mousePosUser.y)) {
//                    //window.clear(sf::Color::Black);
//
//                    sf::RectangleShape usernameBox = drawrec(400, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Yellow);
//                    drawButton(window, usernameBox, "Username:", font);
//                    sf::Text username = box_write(window, font, usernameBox, { 230,110 }, 20, 23, user, 0, sf::Color::Blue, sf::Color::Black);
//
//                    User* currentUser = admin.findUser(username.getString());
//                    if (currentUser) {
//                        UserMenu(currentUser, admin, window, font);
//                        return;
//                    }
//                    else {
//                        drawText(window, font, "User does not exist!", 24, { 300,200 }, sf::Color::White);
//                        pressEnterToContinue(window, font, 300, 250);
//                    }
//                }
//
//                else if (registerButton.getGlobalBounds().contains(mousePosUser.x, mousePosUser.y)) {
//                    window.clear(sf::Color::Black);
//                    while (true) {
//                        sf::RectangleShape usernameBox = drawrec(400, 50, 5, { 100,200 }, sf::Color::White, sf::Color::Yellow);
//                        drawButton(window, usernameBox, "Username:", font);
//                        sf::Text username = box_write(window, font, usernameBox, { 230,210 }, 20, 23, user, 0, sf::Color::Blue, sf::Color::Black);
//                        User* currentUser = admin.findUser(username.getString());
//                        if (!currentUser) {
//                            admin.addUser(username.getString());
//                            currentUser = admin.findUser(username.getString());
//                            UserMenu(currentUser, admin, window, font);
//                            return;
//                        }
//                        else {
//                            drawText(window, font, "User exists, enter another username.", 24, { 300,200 }, sf::Color::White);
//                            window.display();
//                            pressEnterToContinue(window, font, 250, 250);
//                        }
//                    }
//                }
//            }
//        }
//
//        window.clear(sf::Color::Black);
//        drawButton(window, loginButton, "Login", font);
//        drawButton(window, registerButton, "Register", font);
//        window.display();
//    }
//}
//void AdminMenu(Admin& admin, sf::RenderWindow& window, sf::Font& font) {
//
//
//    // Tạo các nút cho các chức năng Admin
//    sf::RectangleShape addUserButton = drawrec(200, 50, 5, { 100,100 }, sf::Color::Blue, sf::Color::Green);
//    sf::RectangleShape removeUserButton = drawrec(200, 50, 5, { 100,200 }, sf::Color::Blue, sf::Color::Green);
//    sf::RectangleShape displayUsersButton = drawrec(200, 50, 5, { 100,300 }, sf::Color::Blue, sf::Color::Green);\
//
//
//
//        while (window.isOpen()) {
//            sf::Event event;
//            string user = "";
//            while (window.pollEvent(event)) {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//
//                if (event.type == sf::Event::MouseButtonPressed) {
//                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                    if (addUserButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        sf::RectangleShape usernamebox = drawrec(500, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Yellow);
//                        drawButton(window, usernamebox, "Enter Username to add:", font);
//                        sf::Text username = box_write(window, font, usernamebox, { 350,110 }, 20, 23, user, 0, sf::Color::Blue, sf::Color::Black);
//                        admin.addUser(username.getString());
//                        drawText(window, font, "Added user succesfully", 20, { 600,100 }, sf::Color::White);
//                        pressEnterToContinue(window, font, 600, 150);
//                    }
//                    else if (removeUserButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        sf::RectangleShape removeuserbox = drawrec(500, 50, 5, { 100,200 }, sf::Color::White, sf::Color::Yellow);
//                        drawButton(window, removeuserbox, "Enter Username to delete:", font);
//                        sf::Text deleteuser = box_write(window, font, removeuserbox, { 370,210 }, 20, 23, user, 0, sf::Color::Blue, sf::Color::Black);
//                        admin.removeUser(deleteuser.getString());
//                        drawText(window, font, "Removed user succesfully", 20, { 600,200 }, sf::Color::White);
//                        pressEnterToContinue(window, font, 600, 250);
//                    }
//                    else if (displayUsersButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        window.clear(sf::Color::Black);
//                        admin.displayUsers(window, font);
//                        pressEnterToContinue(window, font, 600, 800);
//
//                    }
//                }
//            }
//            window.clear(sf::Color::Black);
//            drawButton(window, addUserButton, "Add User", font);
//            drawButton(window, removeUserButton, "Remove User", font);
//            drawButton(window, displayUsersButton, "Display Users", font);
//            window.display();
//        }
//}
//void UserMenu(User* currentUser, Admin& admin, sf::RenderWindow& window, sf::Font& font) {
//
//    // Tạo các nút cho các chức năng của User
//    sf::RectangleShape addTaskButton = drawrec(200, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Magenta);
//    sf::RectangleShape removeTaskButton = drawrec(200, 50, 5, { 100,200 }, sf::Color::White, sf::Color(255, 165, 0));
//    sf::RectangleShape showScheduleButton = drawrec(200, 50, 5, { 100,300 }, sf::Color::White, sf::Color::Green);
//    sf::RectangleShape showDateScheduleButton = drawrec(200, 50, 5, { 100,400 }, sf::Color::White, sf::Color::Cyan);
//    sf::RectangleShape addFileButton = drawrec(200, 50, 5, { 100,500 }, sf::Color::White, sf::Color::Transparent);
//    sf::RectangleShape saveFileButton = drawrec(200, 50, 5, { 100,600 }, sf::Color::White, sf::Color::Blue);
//    bool showingSchedule = false;
//    bool showingDateSchedule = false;
//    bool isRemovingTask = false;
//    string taskTitle = " ";
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (showingSchedule) {
//                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//                    showingSchedule = false;
//                }
//            }
//            else {
//                if (event.type == sf::Event::MouseButtonPressed) {
//                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                    if (addTaskButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        window.clear(sf::Color::Black);
//                        Task* task = new Task();
//                        task = task->creTask(window, font);
//                        currentUser->add_task(task);
//                        drawText(window, font, "add Task succesfully", 20, { 700,700 }, sf::Color::White);
//                        window.display();
//                    }
//                    else if (showScheduleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        showingSchedule = true;
//                    }
//                    else if (showDateScheduleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        showingDateSchedule = true;
//                    }
//                    else if (removeTaskButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        sf::RectangleShape taskTitleBox = drawrec(400, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Yellow);
//                        drawButton(window, taskTitleBox, "Enter task title: ", font);
//                        string taskTitle = " ";
//                        bool inputTask = false;
//                        sf::Text titleText = box_write(window, font, taskTitleBox, { 110,110 }, 20, 23, taskTitle, 0, sf::Color::Blue, sf::Color::Red);
//                        while (window.isOpen() && !inputTask) {
//                            sf::Event event;
//                            while (window.pollEvent(event)) {
//                                if (event.type == sf::Event::Closed) {
//                                    window.close();
//                                }
//                                if (event.type == sf::Event::TextEntered) {
//                                    if (event.text.unicode == '\b') { // Xóa ký tự cuối
//                                        if (!taskTitle.empty()) {
//                                            taskTitle.pop_back();
//                                        }
//                                    }
//                                    else if (event.text.unicode == '\r') { // Nhấn Enter để xác nhận
//                                        inputTask = true;
//                                    }
//                                    else if (event.text.unicode < 128) { // Nhập ký tự ASCII
//                                        taskTitle += static_cast<char>(event.text.unicode);
//                                    }
//                                }
//                            }
//                        }
//                    }
//                    else if (saveFileButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                        sf::RectangleShape fileBox = drawrec(400, 50, 5, { 100,100 }, sf::Color::White, sf::Color::Yellow);
//                        string filename = "";
//                        drawButton(window, fileBox, "Filename:", font);
//                        sf::Text filenameText = box_write(window, font, fileBox, { 230,110 }, 20, 23, filename, 0, sf::Color::Blue, sf::Color::Black);
//                        currentUser->loadtofile(window, font, filenameText.getString());
//                        drawText(window, font, "Tasks saved to file successfully", 20, { 600,700 }, sf::Color::White);
//                        pressEnterToContinue(window, font, 600, 750);
//                    }
//                }
//            }
//        }
//        window.clear(sf::Color::Black);
//
//
//
//        if (showingSchedule) {
//            // Hiển thị lịch biểu
//            currentUser->sort_task();
//            currentUser->show_schedule(window, font);
//        }
//        else if (showingDateSchedule) {
//            currentUser->sort_task();
//            currentUser->show_date_schedule(window, font);
//        }
//        else if (isRemovingTask) {
//            currentUser->remove_task(window, font, taskTitle);
//        }
//        else {
//            // Hiển thị các nút
//            drawButton(window, addTaskButton, "Add Task", font);
//            drawButton(window, removeTaskButton, "Remove Task", font);
//            drawButton(window, showScheduleButton, "Show Schedule", font);
//            drawButton(window, showDateScheduleButton, "Show Date Schedule", font);
//            drawButton(window, addFileButton, "Add file", font);
//            drawButton(window, saveFileButton, "Save FIle", font);
//            window.display();
//        }
//    }
//}
//
//
//int main() {
//    Admin admin;
//    admin.addUsersFromFile("users.txt");
//    system("cls");
//    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Main Menu");
//    MainMenu(admin, window);
//    return 0;
//}