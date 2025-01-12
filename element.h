#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#ifndef ELEMENT_H
#define ELEMENT_H

using namespace std;

class Element {
public:
	sf::Sprite sprite;
	sf::Texture texture;
    sf::Transform sprite2;

	Element() = default;
    virtual ~Element() = default;

	bool loadTexture(const std::string& filePath);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setColor(int r,int g,int b);
    void translate(float x, float y);
    void setOrigine(float x, float y);
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

protected:


};

#endif