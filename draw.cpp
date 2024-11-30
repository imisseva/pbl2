#include "draw.h"
void pressEnterToContinue(sf::RenderWindow& window, sf::Font& font, float x, float y) {
	drawText(window, font, "Press Enter To Continue", 20, { x,y }, sf::Color::Black);
	window.display();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return;
			}
			// Kiểm tra nếu phím Enter được nhấn
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				return;
			}
		}

	}
}
sf::RectangleShape drawrec(float dai, float rong, float day, sf::Vector2f position, sf::Color color, sf::Color color1) {
	sf::RectangleShape rec(sf::Vector2f(dai, rong));
	rec.setPosition(position);
	rec.setFillColor(color);
	rec.setOutlineThickness(day);
	rec.setOutlineColor(color1);
	return rec;
}
void writeText(sf::RenderTexture& texture, sf::Font& font, string s, int size, sf::Vector2f position, sf::Color color) {
	sf::Text text;
	text.setFont(font);
	text.setString(s);
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setFillColor(color);
	texture.draw(text);
}
void drawButton(sf::RenderWindow& window, const sf::RectangleShape& button, const std::string& text, const sf::Font& font, sf::Color color) {
	window.draw(button);
	sf::Text buttonText(text, font, 20);
	buttonText.setPosition(button.getPosition().x + 10, button.getPosition().y + 10);
	buttonText.setFillColor(color);
	window.draw(buttonText);
}
sf::CircleShape drawcir(float R, float day, sf::Vector2f position, sf::Color color, sf::Color color1) {
	sf::CircleShape circle(R);
	circle.setPosition(position);
	circle.setFillColor(color);
	circle.setOutlineThickness(day);
	circle.setOutlineColor(color1);
	return circle;
}
sf::Text save_text(sf::Font& font, const std::string& String, int size, const sf::Vector2f& position, const sf::Color& color) {
	sf::Text text; 
	text.setFont(font); 
	text.setCharacterSize(size);
	text.setString(String); 
	text.setFillColor(color); 
	text.setPosition(position);
	return text;
}
sf::Text box_write(sf::RenderWindow& window, sf::Font& font, sf::RectangleShape rec, sf::Vector2f position, unsigned size, float size_rec, string& raw,int dai ,bool Private, sf::Color color, sf::Color color_text, sf::Color color_rec_thin) {
	bool hien_hinh = 1, key_thin_delete = 0;
	vector<float> toa_do_text;
	toa_do_text.push_back(position.x + 1.2f);
	size_t located_s = 0;
	int dem = 0, dem_chu = 0;
	int dem_1 = 0;
	sf::RenderTexture texture;
	sf::Texture texture_0;
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	sf::Clock clock;
	sf::RectangleShape rec_thin = drawrec(0.8f, size_rec, 0, { 0,0 }, color_rec_thin, sf::Color::Black);
	sf::Text text = save_text(font, "", size, position, color_text);
	if (Private) {
		sf::Text pass_0 = save_text(font, "", size, position, color_text);
	}
	texture.create(window.getSize().x, window.getSize().y);
	texture_0.create(window.getSize().x, window.getSize().y);
	texture_0.update(window);
	sf::Sprite sprite_0(texture_0);
	string da_nhap = raw;
	string da_nhap_0;
	string all_da_nhap = raw;
	string all_da_nhap_0;
	for (int i = 0;i < da_nhap.size();++i) {
		da_nhap_0 += '*';
		all_da_nhap_0 += '*';
	}
	for (int i = 0;i < raw.size();++i) {
		string save = da_nhap.substr(0, i + 1);
		if (Private) save = da_nhap_0.substr(0, i + 1);
		sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
		toa_do_text.push_back(position.x + text1.getGlobalBounds().width + 2.2f);
		rec_thin.setPosition(position.x + text1.getGlobalBounds().width + 2.2f, position.y);
	}
	located_s = static_cast<size_t>(raw.size());
	while (rec.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return text;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouse_pos.x = event.mouseButton.x;
					mouse_pos.y = event.mouseButton.y;
				}
				if (rec.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
					int i;
					for (i = 0;i < toa_do_text.size();++i) {
						if (mouse_pos.x < toa_do_text[i]) {
							break;
						}
					}
					if (i > 0) located_s = i - 1;
					else located_s = 0;
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					if (dem == 0 || located_s > 0) {
						if (located_s > 0) located_s--;
						key_thin_delete = 1;
					}
					else if (dem != 0 && located_s == 0) {
						if (dem + dem_1 != 0) {
							--dem_1;
							da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
							da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
							for (size_t i = 1;i < toa_do_text.size();++i) {
								string save;
								if (!Private) save = da_nhap.substr(0, i);
								else  save = da_nhap_0.substr(0, i);
								sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
								toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
							}
							key_thin_delete = 1;
						}
					}
					/*if (abs(dem_1) <= dem&&located_s==0) {
						if (dem_1== 1) dem_1 -= 2;
						else dem_1 -= 1;
					}
					if (dem==0||dem_1==1) {
						if (located_s > 0) located_s--;
						key_thin_delete = 1;
					}
					else if(dem+dem_1>-1) {
						key_thin_delete = 1;
						da_nhap = all_da_nhap.substr(dem+dem_1,dem_chu);
						da_nhap_0 = all_da_nhap_0.substr(dem+dem_1,dem_chu);
						for (size_t i =1;i < toa_do_text.size();++i) {
							string save;
							if (!Private) save = da_nhap.substr(0, i);
							else  save = da_nhap_0.substr(0, i);
							sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
							toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
						}
					}*/
				}
				else if (event.key.code == sf::Keyboard::Right) {
					if (dem == 0 || located_s < da_nhap.size()) {
						if (located_s < da_nhap.size()) located_s++;
						key_thin_delete = 1;
					}
					else if (dem != 0 && located_s == da_nhap.size()) {
						if (dem_1 != 0) {
							++dem_1;
							da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
							da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
							for (size_t i = 1;i < toa_do_text.size();++i) {
								string save;
								if (!Private) save = da_nhap.substr(0, i);
								else  save = da_nhap_0.substr(0, i);
								sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
								toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
							}
							key_thin_delete = 1;
						}
					}
					/*if (dem_1 <=0 && located_s == toa_do_text.size()-1) {
						if (dem_1 + dem == -1) dem_1 += 2;
						else dem_1 += 1;
					}
					if (dem == 0||dem+dem_1==-1) {
						if (located_s < da_nhap.size()) located_s++;
						key_thin_delete = 1;
					}
					else if (dem + dem_1 <= dem) {
						cout << 1;
						key_thin_delete = 1;
						da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
						da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
						for (size_t i = 1;i < toa_do_text.size();++i) {
							string save;
							if (!Private) save = da_nhap.substr(0, i);
							else  save = da_nhap_0.substr(0, i);
							sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
							toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
						}
					}
					*/
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					raw = all_da_nhap;
					if (!Private) return text;
					else {
						text.setString(all_da_nhap);
						return text;
					}
				}
			}
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode != 8 && event.text.unicode != 9 && event.text.unicode < 128 ) {
					char key_press = static_cast<char>(event.text.unicode);
					if (position.x + text.getGlobalBounds().width <= position.x + rec.getGlobalBounds().width - dai && dem == 0) {
						++dem_chu;
						all_da_nhap.insert(located_s, 1, key_press);
						all_da_nhap_0.insert(located_s, 1, '*');
						da_nhap.insert(located_s, 1, key_press);
						da_nhap_0.insert(located_s, 1, '*');
						located_s += 1;
						string copy;
						if (!Private) copy = da_nhap.substr(0, located_s);
						else copy = da_nhap_0.substr(0, located_s);
						text.setString(copy);
						key_thin_delete = 1;
						toa_do_text.insert(toa_do_text.begin() + located_s, position.x + text.getGlobalBounds().width + 2.2f);
						for (size_t i = located_s + 1;i < toa_do_text.size();++i) {
							string save;
							if (!Private) save = da_nhap.substr(0, i);
							else  save = da_nhap_0.substr(0, i);
							sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
							toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
						}
					}
					else {
						if (located_s < da_nhap.size()) {
							all_da_nhap.insert(located_s + dem + dem_1, 1, key_press);
							all_da_nhap_0.insert(located_s + dem + dem_1, 1, '*');
							--dem_1;
							++dem;
							da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
							da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
							++located_s;
						}
						else if (located_s == da_nhap.size() && dem_1 != 0) {
							all_da_nhap.insert(located_s + dem + dem_1, 1, key_press);
							all_da_nhap_0.insert(located_s + dem + dem_1, 1, '*');
							dem += 1;
							da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
							da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
						}
						else if (located_s == da_nhap.size() && dem_1 == 0) {
							all_da_nhap.insert(located_s + dem, 1, key_press);
							all_da_nhap_0.insert(located_s + dem, 1, '*');
							dem += 1;
							da_nhap = all_da_nhap.substr(dem);
							da_nhap_0 = all_da_nhap_0.substr(dem);
						}
						//cout << all_da_nhap << endl; 
						//cout << da_nhap << endl;
						//cout<<"cat:" << da_nhap.size() << endl;
						//cout << all_da_nhap.size()<<endl;
						string copy;
						if (!Private) copy = da_nhap.substr(0, 0);
						else copy = da_nhap_0.substr(0, 0);
						text.setString(copy);
						key_thin_delete = 1;
						//toa_do_text.insert(toa_do_text.begin(), position.x + text.getGlobalBounds().width + 2.2f);
						for (size_t i = 0 + 1;i < toa_do_text.size();++i) {
							string save;
							if (!Private) save = da_nhap.substr(0, i);
							else  save = da_nhap_0.substr(0, i);
							sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
							toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
						}
					}
				}
				if (event.text.unicode == 8) {
					if (!da_nhap.empty() && (located_s != 0 || dem != 0)) {
						if (dem == 0) {
							--dem_chu;
							all_da_nhap.erase(located_s - 1, 1);
							all_da_nhap_0.erase(located_s - 1, 1);
							da_nhap.erase(located_s - 1, 1);
							da_nhap_0.erase(located_s - 1, 1);
							toa_do_text.erase(toa_do_text.begin() + located_s);
							located_s -= 1;
							for (size_t i = located_s;i < toa_do_text.size();++i) {
								string save;
								if (!Private)	save = da_nhap.substr(0, i);
								else save = da_nhap_0.substr(0, i);
								sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
								toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
							}
						}
						else {
							if (located_s > 0 && dem_1 == 0) {
								all_da_nhap.erase(located_s + dem - 1, 1);
								all_da_nhap_0.erase(located_s + dem - 1, 1);
								--dem;
								da_nhap = all_da_nhap.substr(dem, dem_chu);
								da_nhap_0 = all_da_nhap_0.substr(dem, dem_chu);
							}
							else if (located_s == 0 && dem_1 != 0) {
								if (abs(dem_1) < dem) {
									all_da_nhap.erase(located_s + dem + dem_1 - 1, 1);
									all_da_nhap_0.erase(located_s + dem + dem_1 - 1, 1);
									--dem;
									da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
									da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
								}
							}
							else if (located_s > 0) {
								all_da_nhap.erase(located_s + dem + dem_1 - 1, 1);
								all_da_nhap_0.erase(located_s + dem + dem_1 - 1, 1);
								--dem;
								++dem_1;
								da_nhap = all_da_nhap.substr(dem + dem_1, dem_chu);
								da_nhap_0 = all_da_nhap_0.substr(dem + dem_1, dem_chu);
								--located_s;
							}
							//cout << "dem+dem_1="<<dem+dem_1 << endl;
							/*all_da_nhap.erase(located_s + dem+dem_1-1, 1);
							all_da_nhap_0.erase(located_s + dem+dem_1-1, 1);
							--dem;
							if (dem_1 < 0&&abs(dem_1)==dem) ++dem_1;
							da_nhap = all_da_nhap.substr(dem+dem_1,dem_chu);
							cout << da_nhap << endl;
							da_nhap_0 = all_da_nhap_0.substr(dem+dem_1,dem_chu);*/
							string copy;
							if (!Private) copy = da_nhap.substr(0, 0);
							else copy = da_nhap_0.substr(0, 0);
							//toa_do_text.insert(toa_do_text.begin(), position.x + text.getGlobalBounds().width + 2.2f);
							//toa_do_text.insert(toa_do_text.begin(), position.x + text.getGlobalBounds().width + 2.2f);
							for (size_t i = 0;i < toa_do_text.size();++i) {
								string save;
								if (!Private) save = da_nhap.substr(0, i);
								else  save = da_nhap_0.substr(0, i);
								sf::Text text1 = save_text(font, save, text.getCharacterSize(), text.getPosition(), text.getFillColor());
								toa_do_text[i] = position.x + text1.getGlobalBounds().width + 2.2f;
							}
							//if(located_s!=da_nhap.size()) located_s -=1;
						}
					}
					key_thin_delete = 1;
				}
			}
		}
		if (clock.getElapsedTime().asSeconds() >= 0.6) {
			hien_hinh = !hien_hinh;
			clock.restart();
		}
		if (key_thin_delete == 1) {
			hien_hinh = 1;
			key_thin_delete = 0;
			clock.restart();
		}
		if (!Private) text.setString(da_nhap);
		else text.setString(da_nhap_0);
		rec_thin.setPosition(toa_do_text[located_s], position.y);
		texture.clear(sf::Color::Transparent);
		texture.draw(text);
		if (hien_hinh) texture.draw(rec_thin);
		texture.display();
		sf::Sprite sprite(texture.getTexture());
		window.clear();
		window.draw(sprite_0);
		window.draw(sprite);
		window.display();
	}
	raw = all_da_nhap;
	if (!Private) return text;
	else {
		text.setString(all_da_nhap);
		return text;
	}
}
bool drawNextButton(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position) {
	//sf::RectangleShape nextButton = drawrec(100, 40, 5, { 400,400 }, sf::Color::White, sf::Color::Magenta);
	sf::RectangleShape nextButton(sf::Vector2f(100, 40));
	nextButton.setPosition(position);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (nextButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			return true; 
		}
	}
	return false;  
}


bool drawBackButton(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position) {
	sf::RectangleShape backButton(sf::Vector2f(100, 40));  
	backButton.setPosition(position);                      
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			return true; 
		}
	}
	return false;  
}

void showErrorPopup(sf::RenderWindow& parentWindow, const std::string& message, sf::Font& font) {
	sf::RenderWindow errorWindow(sf::VideoMode(350, 150), "Error", sf::Style::Close);

	sf::RectangleShape background(sf::Vector2f(350.f, 150.f));
	background.setFillColor(sf::Color(240, 240, 240));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);

	sf::Text errorMessage;
	errorMessage.setFont(font);
	errorMessage.setString(message);
	errorMessage.setCharacterSize(18);
	errorMessage.setFillColor(sf::Color::Black);
	errorMessage.setPosition(20.f, 40.f);

	sf::RectangleShape okButton(sf::Vector2f(80.f, 30.f));
	okButton.setFillColor(sf::Color(200, 200, 200));
	okButton.setOutlineColor(sf::Color::Black);
	okButton.setOutlineThickness(2.f);
	okButton.setPosition(110.f, 90.f);

	sf::Text okText;
	okText.setFont(font);
	okText.setString("OK");
	okText.setCharacterSize(16);
	okText.setFillColor(sf::Color::Black);
	okText.setPosition(okButton.getPosition().x + 25.f, okButton.getPosition().y + 5.f);

	while (errorWindow.isOpen()) {
		sf::Event event;
		while (errorWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				errorWindow.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(errorWindow);
				if (okButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					errorWindow.close();
				}
			}
		}

		errorWindow.clear(sf::Color::White);
		errorWindow.draw(background);
		errorWindow.draw(errorMessage);
		errorWindow.draw(okButton);
		errorWindow.draw(okText);
		errorWindow.display();
	}
}


void showNotiPopup(sf::RenderWindow& parentWindow, const std::string& message, sf::Font& font) {
	sf::RenderWindow errorWindow(sf::VideoMode(300, 150), "Notification", sf::Style::Close);

	sf::RectangleShape background(sf::Vector2f(300.f, 300.f));
	background.setFillColor(sf::Color(240, 240, 240));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);

	sf::Text notiMessage;
	notiMessage.setFont(font);
	notiMessage.setString(message);
	notiMessage.setCharacterSize(18);
	notiMessage.setFillColor(sf::Color::Black);
	notiMessage.setPosition(20.f, 40.f);

	sf::RectangleShape okButton(sf::Vector2f(80.f, 30.f));
	okButton.setFillColor(sf::Color(200, 200, 200));
	okButton.setOutlineColor(sf::Color::Black);
	okButton.setOutlineThickness(2.f);
	okButton.setPosition(110.f, 90.f);

	sf::Text okText;
	okText.setFont(font);
	okText.setString("OK");
	okText.setCharacterSize(16);
	okText.setFillColor(sf::Color::Black);
	okText.setPosition(okButton.getPosition().x + 25.f, okButton.getPosition().y + 5.f);

	while (errorWindow.isOpen()) {
		sf::Event event;
		while (errorWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				errorWindow.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(errorWindow);
				if (okButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					errorWindow.close();
				}
			}
		}

		errorWindow.clear(sf::Color::White);
		errorWindow.draw(background);
		errorWindow.draw(notiMessage);
		errorWindow.draw(okButton);
		errorWindow.draw(okText);
		errorWindow.display();
	}
}

//void showPopUp(sf::RenderWindow& parentWindow, sf::Font& font, const std::string& message, std::string& text, std::string& noti) {
//    // Create a popup window
//	
//    sf::RenderWindow popUpWindow(sf::VideoMode(400, 200), noti, sf::Style::Titlebar | sf::Style::Close);
//
//    // Setup message text
//    sf::Text messageText;
//    messageText.setFont(font);
//    messageText.setString(message);
//    messageText.setCharacterSize(20);
//    messageText.setFillColor(sf::Color::Black);
//    messageText.setPosition(20.f, 20.f);
//
//    // Setup input box
//    sf::RectangleShape inputBox = drawrec(340.f, 40.f, 2.f, {30.f, 80.f}, sf::Color(200, 200, 200), sf::Color::Black);
//	sf::Text inputText = box_write(popUpWindow, font, inputBox, { 40.f, 90.f }, 20, 23, text, 15, false, sf::Color(200, 200, 200), sf::Color::Black);
//
//    inputText.setFont(font);
//    inputText.setCharacterSize(20);
//    inputText.setFillColor(sf::Color::Black);
//    inputText.setPosition(40.f, 90.f);
//
//    bool isRunning = true;
//
//	while (popUpWindow.isOpen() && isRunning) {
//		sf::Event event;
//		while (popUpWindow.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				popUpWindow.close();
//			}
//			if (event.type == sf::Event::TextEntered) {
//				if (event.text.unicode == '\b') { // Handle backspace
//					if (!text.empty()) {
//						text.pop_back();
//					}
//				}
//				else if (event.text.unicode == '\r') { // Handle enter
//					isRunning = false;
//				}
//				else if (event.text.unicode < 128) { // Handle ASCII characters
//					text += static_cast<char>(event.text.unicode);
//				}
//			}
//		}
//
//		// Update input text
//		inputText.setString(text);
//
//		
//		popUpWindow.clear(sf::Color(200, 200, 200));
//		popUpWindow.draw(messageText);
//		drawButton(popUpWindow, inputBox, " ", font, sf::Color::Black);
//		popUpWindow.draw(inputText);
//		popUpWindow.display();
//	}
//
//    popUpWindow.close();
//}