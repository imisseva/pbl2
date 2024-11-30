#include "Clock.h"
#include <ctime>
#include <iostream>

// Constructor
ClockDisplay::ClockDisplay(sf::Font& font, sf::Vector2f position) {
    // Set up the time display
    timeText.setFont(font);
    timeText.setCharacterSize(50);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(position);

    // Set up the date and weekday display
    dateText.setFont(font);
    dateText.setCharacterSize(60);
    dateText.setFillColor(sf::Color::Black);
    dateText.setPosition(position.x, position.y + 100); // Date and weekday will be shown here
}

// Update the time, date, and weekday
void ClockDisplay::update() {
    timeText.setString(getCurrentTime());
    dateText.setString(getCurrentDateAndWeekday()); // Combine date and weekday
}

// Draw the clock, date, and weekday
void ClockDisplay::draw(sf::RenderWindow& window) {
    window.draw(timeText);
    window.draw(dateText);
}

// Get the current time in hh:mm format
std::string ClockDisplay::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);  // Use localtime_s

    char buffer[6];
    std::strftime(buffer, sizeof(buffer), "%H:%M", &localTime);
    return std::string(buffer);
}

// Get the current date in dd/mm/yyyy format
std::string ClockDisplay::getCurrentDateAndWeekday() {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);  // Use localtime_s

    char buffer[50];  // Increased size to accommodate both date and weekday

    // Format the date and weekday together: dd/mm/yyyy, weekday
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y, %A", &localTime);
    return std::string(buffer);
}
