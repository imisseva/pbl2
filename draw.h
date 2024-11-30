#ifndef DRAW_H
#define DRAW_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
    template <typename T>
    void drawText(T& paint, sf::Font& font, const std::string& s, int size, const sf::Vector2f& position, const sf::Color& color) {
        sf::Text text;
        text.setFont(font);
        text.setString(s);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setPosition(position);
        paint.draw(text);
    }
    void pressEnterToContinue(sf::RenderWindow& window, sf::Font& font, float x, float y);
    void drawButton(sf::RenderWindow& window, const sf::RectangleShape& button, const std::string& text, const sf::Font& font,sf::Color color=sf::Color::Black);
    void showNotiPopup(sf::RenderWindow& parentWindow, const string& message, sf::Font& font);
    void showErrorPopup(sf::RenderWindow& parentWindow, const std::string& message, sf::Font& font);
    void showPopUp(sf::RenderWindow& parentWindow, sf::Font& font, const std::string& message, std::string& text);
    sf::Text save_text(sf::Font &font,const std::string&,int size,const sf::Vector2f &position,const sf::Color &color); 
    sf::Text box_write(sf::RenderWindow& window, sf::Font& font, sf::RectangleShape rec, sf::Vector2f position, unsigned size, float size_rec,string &raw,int dai ,bool Private=0, sf::Color color = sf::Color::Black,sf::Color color_text=sf::Color::Black,sf::Color color_rec_thin=sf::Color::Black);
	sf::RectangleShape drawrec(float dai, float rong, float day, sf::Vector2f position, sf::Color color, sf::Color color1);
	sf::CircleShape drawcir(float R, float day, sf::Vector2f position, sf::Color color, sf::Color color1);
	void writeText(sf::RenderTexture& texture, sf::Font& font, string s, int size, sf::Vector2f position, sf::Color);
    bool drawNextButton(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position);
    bool drawBackButton(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position);
#endif