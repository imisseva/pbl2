#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

class ClockDisplay {
public:
    // Constructor
    ClockDisplay(sf::Font& font, sf::Vector2f position);

    // Update the time and date
    void update();

    // Draw the clock and date on the window
    void draw(sf::RenderWindow& window);

private:
    // Get the current time (hh:mm format)
    std::string getCurrentTime();

    // Get the current date and weekday (dd/mm/yyyy, weekday format)
    std::string getCurrentDateAndWeekday();

    // SFML Text objects for displaying time, date, and weekday
    sf::Text timeText;
    sf::Text dateText;
};

#endif
