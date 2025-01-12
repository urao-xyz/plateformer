#include "element.h"

bool Element::loadTexture(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) return false;
    sprite.setTexture(texture);
    return true;
}

void Element::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Element::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Element::setScale(float x, float y) {
    sprite.setScale(x, y);
}

void Element::setColor(int r,int g,int b) {
    sprite.setColor(sf::Color(r,g,b));
}

void Element::setOrigine(float x, float y) {
    sprite.setOrigin(x, y);
}

void Element::translate(float x, float y) {
    sprite.move(x, y);
}

sf::FloatRect Element::getBounds() const {
    return sprite.getGlobalBounds();
}
