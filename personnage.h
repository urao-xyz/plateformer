#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "element.h"
#include <vector>
#include "plateforme.h"
#include "drapeau.h"
#include "danger.h"

class Personnage : public Element {
private:
    sf::Vector2f velocity;
    float gravity;
    float jumpStrength;
    float moveSpeed;
    bool onGround;
    

public:
    Personnage();
    void moveLeft();
    void moveRight();
    void jump();
    void update(const std::vector<Plateforme>& plateformes, const Drapeau& drapeau, const Danger& danger);
    void handleCollisions(const std::vector<Plateforme>& plateformes, const Drapeau& drapeau, const Danger& dangers);
    
    void render(sf::RenderWindow& window);
    bool isOnGround() const { return onGround; }
    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
    
    void showVictoryMessage();
    void showDefeatMessage();
    bool hasWon = false; // Indicateur de victoire
    bool hasLost = false; // Indicateur de défaite
    bool gameOver; // Indique si le jeu est terminé
    sf::Clock clock; // Pour mesurer le temps
    bool physicsEnabled;

    // Variables pour le texte
    sf::Font font;
    sf::Text victoryText;
    sf::Text defeatText;
};

#endif
