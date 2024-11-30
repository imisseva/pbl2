#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "user.h"
#include "schedule.h"
#include "task.h"
#include "admin.h"
#include "draw.h"
#include "clock.h"


using namespace std;

void AdminMenu(Admin& admin, sf::RenderWindow& window, sf::Font& font);
void UserMenu(User* currentUser, Admin& admin, sf::RenderWindow& window, sf::Font& font);
void accUser(Admin& admin, sf::RenderWindow& window, sf::Font& font);
void MainMenu(Admin& admin, sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("AGENCYB.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

   

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

    ClockDisplay clockDisplay(font, sf::Vector2f(200.f, 350.f));
    

    sf::Vector2f boxAdmin(100.f, 100.f);
    sf::Vector2f boxSize(500.f, 250.f);
    sf::Vector2f boxPosition((window.getSize().x - boxSize.x) / 2.f + 400.f, (window.getSize().y - boxSize.y) / 2.f);
    sf::RectangleShape mainBox = drawrec(boxSize.x, boxSize.y, 3, boxPosition, sf::Color(200, 200, 200), sf::Color::Black);

    sf::Text title;

    sf::Vector2f adminButtonPosition(boxPosition.x + 30.f, boxPosition.y + 30.f);
    sf::Vector2f userButtonPosition(boxPosition.x + 30.f, boxPosition.y + 150.f);
    sf::Vector2f titlePosition((window.getSize().x - boxSize.x) / 2.f + 400.f, (window.getSize().y - boxSize.y + 10.f) / 2.f);

    sf::CircleShape adminButton = drawcir(40.f, 3.f, adminButtonPosition, sf::Color::White, sf::Color::Black);
    sf::CircleShape userButton = drawcir(40.f, 3.f, userButtonPosition, sf::Color::White, sf::Color::Black);
    sf::RectangleShape titleBox = drawrec(boxSize.x, boxSize.y - 300.f, 3, titlePosition, sf::Color(200, 200, 200), sf::Color::Black);

    sf::Texture adminTexture;
    sf::Texture userTexture;

    if (!adminTexture.loadFromFile("admin.jpg")) {
        std::cerr << "Error loading admin image\n";
    }
    if (!userTexture.loadFromFile("user.jpg")) {
        std::cerr << "Error loading user image\n";
    }

    adminButton.setTexture(&adminTexture);
    userButton.setTexture(&userTexture);

   
   
    while (window.isOpen()) {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.draw(mainBox);
        window.draw(title);

        clockDisplay.update();

        
        clockDisplay.draw(window);


        if (adminButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
            adminButton.setFillColor(sf::Color(166, 173, 170));
        }
        else {
            adminButton.setFillColor(sf::Color::White);
        }


        if (userButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
            userButton.setFillColor(sf::Color(166, 173, 170));
        }
        else {
            userButton.setFillColor(sf::Color::White);
        }


        window.draw(adminButton);
        window.draw(userButton);
        window.draw(titleBox);
        drawText(window, font, "Login option", 24, { titleBox.getPosition().x - 50.f + (titleBox.getSize().x + title.getGlobalBounds().width) / 2.f , titleBox.getPosition().y - 15.f + (titleBox.getSize().y - title.getGlobalBounds().height) / 2.f }, sf::Color::Black);
        drawText(window, font, "Login as Admin", 20,
            { adminButton.getPosition().x + adminButton.getRadius() * 2 + 20.f,
                adminButton.getPosition().y + adminButton.getRadius() - 10.f },
            sf::Color::Black);


        drawText(window, font, "Login as User", 20,
            { userButton.getPosition().x + userButton.getRadius() * 2 + 20.f,
                userButton.getPosition().y + userButton.getRadius() - 10.f },
            sf::Color::Black);



        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (adminButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {

                    int thoat = 1;
                    string name_ = " ";
                    string password_ = "";
                    string usernameError = "";
                    string passwordError = "";

                    while (thoat) {

                        sf::Vector2f mainBoxSize(500.f, 250.f);
                        sf::Vector2f mainBoxPosition((window.getSize().x - mainBoxSize.x) / 2.f, (window.getSize().y - mainBoxSize.y) / 2.f);
                        sf::RectangleShape mainBox = drawrec(mainBoxSize.x, mainBoxSize.y, 3, mainBoxPosition, sf::Color(200, 200, 200), sf::Color::Black);
            
                        sf::Vector2f nameBoxPosition(mainBoxPosition.x + 10, mainBoxPosition.y + 30);
                        sf::Vector2f passwordBoxPosition(mainBoxPosition.x + 10, mainBoxPosition.y + 100);

                        sf::RectangleShape passwordBox = drawrec(mainBoxSize.x - 20, 50, 3, passwordBoxPosition, sf::Color::White, sf::Color::Black);
                        sf::RectangleShape nameBox = drawrec(mainBoxSize.x - 20, 50, 3, nameBoxPosition, sf::Color::White, sf::Color::Black);

                        sf::Vector2f nextButtonPosition(mainBoxPosition.x + mainBoxSize.x - 120, mainBoxPosition.y + mainBoxSize.y - 60);
                        sf::RectangleShape nextButton = drawrec(100, 40, 3, nextButtonPosition, sf::Color::White, sf::Color::Black);

                        sf::Vector2f backButtonPosition(mainBoxPosition.x + 20, mainBoxPosition.y + mainBoxSize.y - 60);
                        sf::RectangleShape backButton = drawrec(100, 40, 3, backButtonPosition, sf::Color::White, sf::Color::Black);

                        sf::Event event1;
                        while (window.pollEvent(event1)) {
                            if (event1.type == sf::Event::Closed) {
                                window.close();
                            }
                            if (event1.type == sf::Event::MouseButtonPressed) {
                                sf::Vector2i mousePos1 = sf::Mouse::getPosition(window);
                                if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos1))) {
                                    thoat = 0;
                                    break;
                                }
                                if (nextButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos1))) {
                                    if ((name_ == "phong" || name_ == "toan") && password_ == "2005") {
                                        AdminMenu(admin, window, font);
                                        thoat = 0;
                                        pressEnterToContinue(window, font, 600, 150);
                                        break;
                                    }
                                    else {
                                        if (name_ != "phong" && name_ != "toan" && password_ != "2005") {
                                            showErrorPopup(window, "Invalid Username and Password. Please try again.", font);
                                        }
                                        else if (name_ != "phong" && name_ != "toan") {
                                            showErrorPopup(window, "Invalid Username. Please try again.", font);
                                        }
                                        else if (password_ != "2005") {
                                            showErrorPopup(window, "Invalid Password. Please try again.", font);
                                        }
                                        else {
                                            AdminMenu(admin, window, font);
                                        
                                            thoat = 0;
                                        }

                                    }
                                }
                                if (nameBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos1))) {
                                    name_.clear();
                                }
                                if (passwordBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos1))) {
                                    password_.clear();
                                }
                            }


                            if (event1.type == sf::Event::TextEntered) {

                                if (event.text.unicode == '\r') continue;
                                sf::Vector2i mousePos1 = sf::Mouse::getPosition(window);
                                if (nameBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos1))) {
                                    if (event1.text.unicode == '\b') { // Backspace
                                        if (!name_.empty()) name_.pop_back();
                                    }
                                    else if (event1.text.unicode < 128) { // Valid character
                                        name_ += static_cast<char>(event1.text.unicode);
                                    }
                                }
                                if (passwordBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos1))) {
                                    if (event1.text.unicode == '\b') { // Backspace
                                        if (!password_.empty()) password_.pop_back();
                                    }
                                    else if (event1.text.unicode < 128) { // Valid character
                                        password_ += static_cast<char>(event1.text.unicode);
                                    }
                                }
                            }



                            std::string maskedPassword(password_.size(), '*');

                            sf::Text passwordLabel;
                            passwordLabel.setFont(font);
                            passwordLabel.setString("Password:");
                            passwordLabel.setCharacterSize(20);
                            passwordLabel.setFillColor(sf::Color::Black);
                            passwordLabel.setPosition(passwordBoxPosition.x + 10, passwordBoxPosition.y + 10);


                            sf::Text passwordText;
                            passwordText.setFont(font);
                            passwordText.setString(maskedPassword);
                            passwordText.setCharacterSize(20);
                            passwordText.setFillColor(sf::Color::Black);
                            passwordText.setPosition(passwordBoxPosition.x + 120, passwordBoxPosition.y + 10);

                            sf::Text usernameText;
                            usernameText.setFont(font);
                            usernameText.setString(name_);
                            usernameText.setCharacterSize(20);
                            usernameText.setFillColor(sf::Color::Black);
                            usernameText.setPosition(nameBoxPosition.x + 120, nameBoxPosition.y + 10);

                            sf::Text usernameLable;
                            usernameLable.setFont(font);
                            usernameLable.setString("Username: ");
                            usernameLable.setCharacterSize(20);
                            usernameLable.setFillColor(sf::Color::Black);
                            usernameLable.setPosition(nameBoxPosition.x + 10, nameBoxPosition.y + 10);


                            window.clear(sf::Color::Black);
                            window.draw(backgroundSprite);
                            window.draw(mainBox);
                            window.draw(nameBox);
                            window.draw(passwordBox);
                            window.draw(usernameLable);
                            window.draw(usernameText);
                            window.draw(passwordLabel);
                            window.draw(passwordText);
                 
                            drawButton(window, nextButton, "Next", font);
                            drawButton(window, backButton, "Back", font);

                            window.display();
                        }
                    }
                }
                else if (userButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    accUser(admin, window, font);
                    
                }
            }
        }
    }
}


void accUser(Admin& admin, sf::RenderWindow& window, sf::Font& font) {
    string user = "", newuser = "", pass = "", newpass = "";
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

    sf::Vector2f boxSize(500.f, 250.f);
    sf::Vector2f boxPosition((window.getSize().x - boxSize.x) / 2.f, (window.getSize().y - boxSize.y) / 2.f);
    sf::RectangleShape mainBox = drawrec(boxSize.x, boxSize.y, 3, boxPosition, sf::Color(200, 200, 200), sf::Color::Black);

   
    sf::Text title;
    title.setFont(font);
    title.setString("Choose an option");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Black);
    title.setPosition(
        boxPosition.x + (boxSize.x - title.getGlobalBounds().width) / 2.f,
        boxPosition.y + 10.f
    );

    sf::Vector2f loginPos(boxPosition.x + 30.f , boxPosition.y + 50.f);
    sf::Vector2f registerPos(boxPosition.x + 30.f, boxPosition.y + 150.f);
    sf::RectangleShape loginButton = drawrec(200, 50, 3,loginPos , sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape registerButton = drawrec(200, 50, 3,registerPos , sf::Color(200, 200, 200), sf::Color::Black);



    while (window.isOpen()) {
        sf::Event userEvent;
        while (window.pollEvent(userEvent)) {
            window.draw(backgroundSprite);
            if (userEvent.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (userEvent.type == sf::Event::KeyPressed && userEvent.key.code == sf::Keyboard::Escape) {
                break;
            }
            if (userEvent.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosUser = sf::Mouse::getPosition(window);
                sf::Text username;
                sf::Text password;
                sf::Text password1;
                sf::Text newusername;
                sf::Text newpassword;
                sf::Text newpassword1;
                if (loginButton.getGlobalBounds().contains(mousePosUser.x, mousePosUser.y)) {  
                    window.draw(backgroundSprite);
                    window.draw(mainBox);

                    string password_0 = "";
                    bool thoat = 1;
                    while (thoat) {
                        sf::Event event1;
                        sf::Vector2f usernameBoxPos(boxPosition.x + 30.f, boxPosition.y + 50.f);
                        sf::Vector2f passwordBoxPos(boxPosition.x + 30.f, boxPosition.y + 150.f);
                        sf::Vector2f backButtonPos(boxPosition.x + 100.f, boxPosition.y + 300.f);
                        sf::Vector2f nextButtonPos(boxPosition.x + 300.f, boxPosition.y + 300.f);


                        sf::RectangleShape nextButton = drawrec(100, 40, 3,nextButtonPos , sf::Color(200,200,200), sf::Color::Black);
                        sf::RectangleShape backButton = drawrec(100, 40, 3, backButtonPos, sf::Color(200,200,200), sf::Color::Black);
                        sf::RectangleShape usernameBox = drawrec(400, 50, 3, usernameBoxPos, sf::Color(200,200,200), sf::Color::Black);
                        sf::RectangleShape passwordBox = drawrec(400, 50, 3, passwordBoxPos, sf::Color(200,200,200), sf::Color::Black);
                        while (window.pollEvent(event1)) {
                            if (event1.type == sf::Event::MouseButtonPressed) {
                                if (event1.type == sf::Event::Closed) {
                                    thoat = 0;

                                }
                                sf::Vector2i mousePos1 = sf::Mouse::getPosition(window);
                                if (usernameBox.getGlobalBounds().contains(mousePos1.x, mousePos1.y)) {
                                    drawButton(window, usernameBox, "Username:", font);
                                    username = box_write(window, font, usernameBox,{usernameBoxPos.x + 100.f, usernameBoxPos.y + 10.f}, 20, 23, user, 20, 0, sf::Color::Blue, sf::Color::Black);
                                }
                                if (passwordBox.getGlobalBounds().contains(mousePos1.x, mousePos1.y)) {
                                    drawButton(window, passwordBox, "Password:", font);
                                    password = box_write(window, font, passwordBox, {passwordBoxPos.x + 100.f, passwordBoxPos.y + 10.f }, 20, 23, pass, 20, 1, sf::Color::Blue, sf::Color::Black);
                                    password_0 = "";

                                    for (int i = 0;i < pass.size();++i) {
                                        password_0 += '*';
                                    }
                                    password1 = password;
                                    password1.setString(password_0);
                                }
                            }
                            if (drawNextButton(window, font, nextButtonPos)) {
                                User* currentUser = admin.findUser(username.getString());
                                if (currentUser) {
                                    if (currentUser->get_password() == pass) {
                                        UserMenu(currentUser, admin, window, font);
                                        return;
                                    }
                                    else {
                                        showErrorPopup(window, "Incorrect, try again!", font);
                                        
                                    }
                                }
                                else {
                                    showErrorPopup(window, "User doesn't exist", font);
                                 
                                }
                            }
                            else if (drawBackButton(window, font, backButtonPos )) {
                                thoat = 0;
                            }
                        }
                        window.clear(sf::Color::Black);
                        window.draw(backgroundSprite);
                        window.draw(mainBox);
                        drawButton(window, usernameBox, "Username:", font);
                        drawButton(window, passwordBox, "Password:", font);
                        drawButton(window, nextButton, "Next", font);
                        drawButton(window, backButton, "Back", font);
                        window.draw(password1);
                        window.draw(username);
                        
                        window.display();
                    }
                }
                else if (registerButton.getGlobalBounds().contains(mousePosUser.x, mousePosUser.y)) {
                    string password_0 = "";
                    bool thoat = 1;
                    bool error = -1;
                    while (thoat) {
                        sf::Event event1;
                        
                        sf::Vector2f usernameBoxPos(boxPosition.x + 30.f, boxPosition.y + 50.f);
                        sf::Vector2f passwordBoxPos(boxPosition.x + 30.f, boxPosition.y + 150.f);
                        sf::Vector2f nextButtonPos(boxPosition.x + 300.f, boxPosition.y + 300.f);
                        sf::Vector2f backButtonPos(boxPosition.x + 100.f, boxPosition.y + 300.f);

                       
                        sf::RectangleShape nextButton = drawrec(100, 40, 3, nextButtonPos, sf::Color::White, sf::Color::Magenta);
                        sf::RectangleShape backButton = drawrec(100, 40, 3, backButtonPos, sf::Color::White, sf::Color::Red);
                        sf::RectangleShape usernameBox = drawrec(400, 50, 3, usernameBoxPos, sf::Color::White, sf::Color::Yellow);
                        sf::RectangleShape passwordBox = drawrec(400, 50, 3, passwordBoxPos, sf::Color::White, sf::Color::Yellow);
                        while (window.pollEvent(event1)) {
                            if (event1.type == sf::Event::MouseButtonPressed) {
                                if (event1.type == sf::Event::Closed) {
                                    window.close();
                                    thoat = 0;
                                    return;

                                }
                                sf::Vector2i mousePos1 = sf::Mouse::getPosition(window);
                                if (usernameBox.getGlobalBounds().contains(mousePos1.x, mousePos1.y)) {
                                    drawButton(window, usernameBox, "Username:", font);
                                    newusername = box_write(window, font, usernameBox, {usernameBoxPos.x + 100.f, usernameBoxPos.y + 10.f}, 20, 23, newuser, 20, 0, sf::Color::Blue, sf::Color::Black);
                                    User* currentUser = admin.findUser(newuser);
                                    error = 1;
                                    if (currentUser) {
                                        error = 0;
                                    }
                                }
                                if (passwordBox.getGlobalBounds().contains(mousePos1.x, mousePos1.y)) {
                                    drawButton(window, passwordBox, "Password:", font);
                                    newpassword = box_write(window, font, passwordBox, {passwordBoxPos.x + 100.f, passwordBoxPos.y + 10.f }, 20, 23, newpass, 20, 1, sf::Color::Blue, sf::Color::Black);
                                    password_0 = "";

                                    for (int i = 0;i < newpass.size();++i) {
                                        password_0 += '*';
                                    }
                                    newpassword1 = newpassword;
                                    newpassword1.setString(password_0);
                                }
                            }
                            if (drawNextButton(window, font, { boxPosition.x + 300.f, boxPosition.y + 300.f }) == 1 && error == 1) {
                                User* currentUser = admin.findUser(newuser);
                                if (currentUser) {
                                    showErrorPopup(window, "User exists, enter another username.", font );
                                }
                                else if (error == 1) {
                                    
                                    admin.addUser(newuser, newpass);
                                    showNotiPopup(window, "Register successfully", font);
                                    window.display();
                                    sf::Clock clock;
                                    while (clock.getElapsedTime().asSeconds() < 2) {
                                    }
                                    currentUser = admin.findUser(newuser);

                                   
                                    UserMenu(currentUser, admin, window, font);
                                    return;
                                }
                            }
                            else if (drawBackButton(window, font, { boxPosition.x + 100.f, boxPosition.y + 300.f })) {
                                thoat = 0;
                            }
                        }
                        window.clear(sf::Color::Black);
                        window.draw(backgroundSprite);
                        window.draw(mainBox);
                        drawButton(window, usernameBox, "Username:", font);
                        drawButton(window, passwordBox, "Password:", font);
                        drawButton(window, nextButton, "Next", font);
                        drawButton(window, backButton, "Back", font);
                        window.draw(newpassword1);
                        window.draw(newusername);
                        window.display();
                    }
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.draw(mainBox);
        window.draw(title);
        drawButton(window, loginButton, "Login", font);
        drawButton(window, registerButton, "Register", font);
        window.display();
    }
}


void AdminMenu(Admin& admin, sf::RenderWindow& window, sf::Font& font) {
  

    sf::Vector2f boxSize(500.f, 350.f);
    sf::Vector2f boxPosition((window.getSize().x - boxSize.x) / 2.f, (window.getSize().y - boxSize.y) / 2.f);
    sf::RectangleShape mainBox = drawrec(boxSize.x, boxSize.y, 3, boxPosition, sf::Color(200, 200, 200), sf::Color::Black);

    sf::Vector2f addUserPosition(boxPosition.x + 30.f, boxPosition.y + 30.f);
    sf::Vector2f removeUserPosition(boxPosition.x + 30.f, boxPosition.y + 150.f);
    sf::Vector2f displayUsersPosition(boxPosition.x + 30.f, boxPosition.y + 280.f);

    sf::RectangleShape addUserButton = drawrec(200, 50, 3, addUserPosition, sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape removeUserButton = drawrec(200, 50, 3, removeUserPosition, sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape displayUsersButton = drawrec(200, 50, 3, displayUsersPosition, sf::Color(200, 200, 200), sf::Color::Black);

    sf::Vector2f backButtonSize(100.f, 40.f);
    sf::Vector2f backButtonPosition(20.f, 20.f);
    sf::RectangleShape backButton = drawrec(backButtonSize.x, backButtonSize.y, 3, backButtonPosition, sf::Color::White, sf::Color::Black);
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


    while (window.isOpen()) {
            sf::Event event;
            

            string user = "";
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (addUserButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.clear(sf::Color::Black);
                        window.draw(backgroundSprite);
                        window.draw(mainBox);
                        sf::Vector2f usernameboxPos(boxPosition.x + 10.f, boxPosition.y + 30.f);
                        sf::RectangleShape usernamebox = drawrec(350, 50, 3, usernameboxPos, sf::Color(200, 200, 200), sf::Color::White);
                        drawButton(window, usernamebox, "Enter Username to add:", font);
                        sf::Text username = box_write(window, font, usernamebox, { usernameboxPos.x + 200.f, usernameboxPos.y + 10.f }, 20, 23, user, 150, 0, sf::Color::Blue, sf::Color::Black);
                        admin.addUser(username.getString(), "1234");
                        admin.loadUserToFile(window, font, "users.txt");
                        showNotiPopup(window, "Added username Successfully!", font);
                    }
                    else if (removeUserButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.clear(sf::Color::Black);
                        window.draw(mainBox);
                        sf::Vector2f removeuserPos(boxPosition.x + 10.f, boxPosition.y + 30.f);
                        sf::RectangleShape removeuserbox = drawrec(500, 50, 5, removeuserPos, sf::Color(200, 200, 200), sf::Color::White);
                        drawButton(window, removeuserbox, "Enter Username to delete:", font);
                        sf::Text deleteuser = box_write(window, font, removeuserbox, { removeuserPos.x + 200.f, removeuserPos.y + 10.f }, 20, 23, user, 150, 0, sf::Color::Blue, sf::Color::Black);
                        admin.removeUser(deleteuser.getString());
                        showNotiPopup(window, "User removed successfully", font);
                    } //tí fix lại sao cho có thể viết được tên người cần xóa
                    else if (displayUsersButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.clear(sf::Color::Black);
                        window.draw(backgroundSprite);
                        admin.displayUsers(window, font);
                        pressEnterToContinue(window, font, 600, 800);
                        drawBackButton(window, font, { 500.f, 500.f });

                    }

                    else if (drawBackButton(window, font, backButtonPosition)) {
                        MainMenu(admin, window);
                    }
                }
            
            }
        

       
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.draw(mainBox);
        drawButton(window, addUserButton, "Add User", font);
        drawButton(window, removeUserButton, "Remove User", font);
        drawButton(window, displayUsersButton, "Display Users", font);
        drawButton(window, backButton, "Back", font);
        window.display();
    }
}

void UserMenu(User* currentUser, Admin& admin, sf::RenderWindow& window, sf::Font& font) {
    string currentDate = getCurrentDate(), date; // tạo biến
    int year = 2024, month = 11, selectedDay = 0; //tạo biến 

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
    sf::Vector2f boxSize(500.f, 500.f);
    sf::Vector2f boxPosition((window.getSize().x - boxSize.x) / 2.f , (window.getSize().y - boxSize.y) / 2.f);
    sf::RectangleShape mainBox = drawrec(boxSize.x, boxSize.y, 3, boxPosition, sf::Color(200, 200, 200), sf::Color::Black);


    sf::Vector2f addTaskPos(200.f, 100.f);
    sf::Vector2f showSchedulePos(400.f, 100.f);
    sf::Vector2f showDateSchedulePos(600.f, 100.f);
    sf::Vector2f changePasswordPos(800.f,100.f);
    sf::Vector2f saveFilePos(1000.f, 100.f);

   
    sf::RectangleShape addTaskButton = drawrec(200, 50, 3, addTaskPos, sf::Color(200,200,200), sf::Color::Black);
    sf::RectangleShape showScheduleButton = drawrec(200, 50, 3, showSchedulePos, sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape showDateScheduleButton = drawrec(200, 50, 3, showDateSchedulePos, sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape changePasswordButton = drawrec(200, 50, 3, changePasswordPos, sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape saveFileButton = drawrec(200, 50, 3, saveFilePos, sf::Color(200, 200, 200), sf::Color::Black);
    sf::RectangleShape CalendarButton = drawrec(200, 50, 3, { 900,900 }, sf::Color(200, 200, 200), sf::Color::White); 

    
    bool showingSchedule = false;
    bool showingDateSchedule = false;
    bool isRemovingTask = false;
    string taskTitle = " ";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (showingSchedule) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    currentUser->handle_click(window, font, mousePos, currentDate, 1);

                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    showingSchedule = false;
                    // Thoát chế độ xem schedule
                }
            }
            else if (showingDateSchedule) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    // thêm đoạn này
                    if (CalendarButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        drawCalendar(font, year, month, selectedDay);
                        if (selectedDay != 0) {
                            std::ostringstream oss;
                            oss << (selectedDay < 10 ? "0" : "") << selectedDay << "/"
                                << (month < 10 ? "0" : "") << month << "/" << year;
                            currentDate = oss.str();
                        }
                    }
                    currentUser->handle_click(window, font, mousePos, currentDate, 2);
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    showingDateSchedule = false;
                    // Thoát chế độ xem schedule
                }
            }
            else {
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (addTaskButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.draw(backgroundSprite);
                        Task* task = nullptr;
                        task = task->creTask(window, font);
                        if (task != nullptr) {
                            currentUser->add_task(task);
                            showNotiPopup(window, "Task added successfully", font);
                        }
                        else {
                            showErrorPopup(window, "Task added failed", font);
                        }

                    }
                    else if (showScheduleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentUser->sort_task();
                        showingSchedule = true;
                    }
                    else if (showDateScheduleButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentUser->sort_task();
                        showingDateSchedule = true;
                    }
                    else if (saveFileButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentUser->loadtasktofile(window, font, currentUser->get_username());
                        sf::Clock clock;
                        while (clock.getElapsedTime().asSeconds() < 2) {
                        }
                    }
                  /*  else if (changePasswordButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::string newpassword;
                        showPopUp(window, font, "Enter new password:", newpassword);

                        if (!newpassword.empty()) {
                            admin.updatePassword(currentUser->get_username(), newpassword);
                            showNotiPopup(window, "Password changed successfully!", font);
                        }
                        else {
                            showNotiPopup(window, "Password change canceled.", font);
                        }
                    }*/
                }
            }
        }
        
  
         if (showingSchedule) {
            window.clear(sf::Color::Black);
            currentUser->show_schedule(window, font);

        }
        else if (showingDateSchedule) {
            window.clear(sf::Color::Black);
            drawButton(window, CalendarButton, "Change Day", font);
            currentUser->show_date_schedule(window, font, currentDate);
        }


        else {
            window.clear(sf::Color::Black);
            window.draw(backgroundSprite);
            window.draw(mainBox);
            drawButton(window, addTaskButton, "Add Task", font);
            drawButton(window, showScheduleButton, "Show Schedule", font);
            drawButton(window, changePasswordButton, "Change Password", font);
            drawButton(window, showDateScheduleButton, "Show Date Schedule", font);
            drawButton(window, saveFileButton, "Save tasks", font);
            window.display();
        }
    }
}


int main() {
    Admin admin;
    admin.addUsersFromFile("users.txt");
    system("cls");
    sf::RenderWindow window(sf::VideoMode(1500, 900), "Main Menu", sf::Style::Close);
    MainMenu(admin, window);
    return 0;
}

