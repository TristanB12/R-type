/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** TextField
*/

#include "TextField.hpp"

namespace gui {
TextField::TextField(unsigned int maxLength, const sf::Font &font) :
    m_maxLength(maxLength),
    m_text("", font)
{
    unsigned int charSize = m_text.getCharacterSize();
    sf::Vector2u boxSize(charSize * m_maxLength, charSize + 5);
    m_box = sf::RectangleShape(sf::Vector2f(boxSize));
    m_box.setOutlineThickness(2.0f);
    m_box.setOutlineColor(sf::Color(127, 127, 127));
    m_box.setFillColor(sf::Color(0, 0, 0, 190));
    centerOrigin(m_text);
}

void TextField::handleEvent(const sf::Event &event)
{
    if (event.type != sf::Event::TextEntered) {
        return;
    }
    char character = static_cast<char>(event.text.unicode);
    if (std::isalpha(character) && m_string.length() + 1 <= m_maxLength)  {
        m_string += character;
        m_text.setString(m_string);
    } else if (character == '\b' && m_string.length() > 0) {
        m_string.pop_back();
        m_text.setString(m_string);
    }
}

} // namespace gui