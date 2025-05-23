#include "button.hpp"

const sf::Color BUTTON_COLOR = sf::Color(200, 200, 200);
const sf::Color OUTLINE_COLOR = sf::Color(170, 170, 170);
const sf::Color TEXT_COLOR = sf::Color::Black;

Button::Button(const std::string &textString,
               const sf::Vector2f &position,
               const sf::Vector2f &size,
               const sf::Font &font,
               const unsigned int fontSize,
               std::function<void()> onClickCallback)
    : m_shape(size),
      m_text(font, textString, fontSize),
      m_onClickCallback(onClickCallback)
{
    m_shape.setPosition(position);
    m_shape.setFillColor(BUTTON_COLOR);
    m_shape.setOutlineThickness(2);
    m_shape.setOutlineColor(OUTLINE_COLOR);

    m_text.setFillColor(TEXT_COLOR);

    // Center text within the button
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x + textBounds.size.x / 2.0f,
                      textBounds.position.y + textBounds.size.y / 2.0f});

    m_text.setPosition({position.x + size.x / 2.0f,
                        position.y + size.y / 2.0f});

    // updateAppearance();
}

void Button::setPosition(const sf::Vector2f &position)
{
    m_shape.setPosition(position);

    sf::Vector2f size = m_shape.getSize();
    m_text.setPosition({position.x + size.x / 2.0f,
                        position.y + size.y / 2.0f});
}

sf::Vector2f Button::getSize() const
{
    return m_shape.getSize();
}

void Button::handleEvent(const sf::Event::MouseButtonPressed &mouseButtonPressed, const sf::RenderWindow &window)
{
    // Convert mouse position from window coordinates to view coordinates
    sf::Vector2f mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    m_isHovered = m_shape.getGlobalBounds().contains(mousePosView);

    if (m_isHovered && mouseButtonPressed.button == sf::Mouse::Button::Left)
    {
        if (m_onClickCallback)
        {
            m_onClickCallback();
        }
    }
}

void Button::draw(sf::RenderTarget &target) const
{
    target.draw(m_shape);
    target.draw(m_text);
}

// void Button::setPosition(const sf::Vector2f &position)
// {
//     m_shape.setPosition(position);
//     // Recenter text
//     sf::Vector2f size = m_shape.getSize();
//     sf::FloatRect textBounds = m_text.getLocalBounds();
//     m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
//                      textBounds.top + textBounds.height / 2.0f);
//     m_text.setPosition(position.x + size.x / 2.0f,
//                        position.y + size.y / 2.0f);
// }

// void Button::setText(const std::string &textString)
// {
//     m_text.setString(textString);
//     // Recenter text
//     sf::Vector2f position = m_shape.getPosition();
//     sf::Vector2f size = m_shape.getSize();
//     sf::FloatRect textBounds = m_text.getLocalBounds();
//     m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
//                      textBounds.top + textBounds.height / 2.0f);
//     m_text.setPosition(position.x + size.x / 2.0f,
//                        position.y + size.y / 2.0f);
// }