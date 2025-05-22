#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(const std::string &text,
           const sf::Vector2f &position,
           const sf::Vector2f &size,
           const sf::Font &font,
           const unsigned int fontSize,
           std::function<void()> onClickCallback);

    void handleEvent(const sf::Event::MouseButtonPressed &mouseButtonPressed, const sf::RenderWindow &window);
    void draw(sf::RenderTarget &target) const;

    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getSize() const;

private:
    bool m_isHovered = false;
    std::function<void()> m_onClickCallback;

    sf::RectangleShape m_shape;
    sf::Text m_text;

    // void updateAppearance();
};

#endif