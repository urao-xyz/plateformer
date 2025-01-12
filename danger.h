#ifndef DANGER_H
#define DANGER_H

#include <SFML/Graphics.hpp>

class Danger {
public:
    Danger(); // Constructeur

    void update(); // Méthode pour mettre à jour la position du danger
    void render(sf::RenderWindow& window) { window.draw(sprite); } // Méthode pour dessiner le danger
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); } // Méthode pour obtenir les limites du danger

    void setPosition(float x, float y) { sprite.setPosition(x, y); } // Méthode pour définir la position
    void setColor(int r, int g, int b) { sprite.setColor(sf::Color(r, g, b)); } // Méthode pour définir la couleur
    void setScale(float x, float y) { sprite.setScale(x, y); } // Méthode pour définir l'échelle

private:
    sf::Sprite sprite; // Sprite du danger
    float moveSpeed; // Vitesse de déplacement
    int direction; // Direction de déplacement (1 ou -1)
    float leftBound; // Limite gauche
    float rightBound; // Limite droite

    // Méthode pour charger la texture
    bool loadTexture(const std::string& filename) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            return false;
        }
        sprite.setTexture(texture);
        return true;
    }
};

#endif // DANGER_H