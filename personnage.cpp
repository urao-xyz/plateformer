#include "personnage.h"
#include "drapeau.h"
#include "danger.h"
#include <iostream>
#include <chrono>
#include <thread>

Personnage::Personnage()
    : velocity(0.f, 0.f), gravity(0.5f), jumpStrength(-10.0f), moveSpeed(4.0f), onGround(true), hasWon(false), hasLost(false), gameOver(false), physicsEnabled(true) {
    // Charger la texture du sprite sheet
    if (!loadTexture("character.png")) {
        std::cerr << "Erreur de chargement de la texture du personnage" << std::endl;
    }

    // Initialiser le texte
    if (!font.loadFromFile("arial.ttf")) { // Assurez-vous d'avoir une police disponible
        std::cerr << "Erreur de chargement de la police" << std::endl;
    }
    
    victoryText.setFont(font);
    victoryText.setString("Vous avez gagne !");
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setPosition(225, 100); // Positionner le texte sur l'écran

    defeatText.setFont(font);
    defeatText.setString("Vous avez perdu !");
    defeatText.setCharacterSize(50);
    defeatText.setFillColor(sf::Color::Red);
    defeatText.setPosition(225, 100); // Positionner le texte sur l'écran


    int frameWidth = 31;
    int frameHeight = 30;
    int frameX = 3; 
    int frameY = 1;

    sprite.setTextureRect(sf::IntRect(frameX * frameWidth, frameY * frameHeight, frameWidth, frameHeight));
}

void Personnage::moveLeft() {
    sprite.move(-moveSpeed, 0.f);
}

void Personnage::moveRight() {
    sprite.move(moveSpeed, 0.f);
}


void Personnage::jump() {
    if (onGround) {
        velocity.y = jumpStrength;
        onGround = false;
    }
}

void Personnage::update(const std::vector<Plateforme>& plateformes, const Drapeau& drapeau, const Danger& danger) {
    // Appliquer la gravité si la physique est activée et si le personnage est en l'air
    if (physicsEnabled && !onGround) {
        velocity.y += gravity;
    }

    // Appliquer le mouvement vertical
    sprite.move(0.f, velocity.y);

    // Gérer les collisions avec les plateformes
    handleCollisions(plateformes, drapeau, danger);

    // Vérifier si le personnage touche le sol arbitraire
    if (sprite.getPosition().y >= 700.f && !hasLost) { // Sol arbitraire
        sprite.setPosition(sprite.getPosition().x, 700.f);
        velocity.y = 0;
        onGround = true;
        showDefeatMessage();
        hasLost = true; // Marquer que le personnage a perdu
        physicsEnabled = false; // Désactiver la physique
        gameOver = true; // Indiquer que le jeu est terminé
        clock.restart(); // Redémarrer le timer
    }
}



void Personnage::render(sf::RenderWindow& window) {
    window.draw(sprite);
    if (hasWon) {
        window.draw(victoryText);
    } else if (hasLost) {
        window.draw(defeatText);
    }
}

void Personnage::handleCollisions(const std::vector<Plateforme>& plateformes, const Drapeau& drapeau,const Danger& danger) {
    sf::FloatRect personnageBounds = sprite.getGlobalBounds();
    bool wasOnGround = onGround; // Garder une trace de l'état précédent

    onGround = false; // Réinitialiser onGround avant de vérifier les collisions
    // Vérifier la collision avec le drapeau
    if (personnageBounds.intersects(drapeau.getBounds())) {
        hasWon = true;
        showVictoryMessage();
        physicsEnabled = false;
        gameOver = true; // Indiquer que le jeu est terminé
        clock.restart(); // Redémarrer le timer
    }

    if (personnageBounds.intersects(danger.getBounds())) {
        hasLost = true;
        showDefeatMessage();
        physicsEnabled = false;
        gameOver = true; // Indiquer que le jeu est terminé
        clock.restart(); // Redémarrer le timer
    }

    for (const auto& plateforme : plateformes) {
        sf::FloatRect plateformeBounds = plateforme.getBounds();

        // Si le personnage intersecte une plateforme
        if (personnageBounds.intersects(plateformeBounds)) {
            // Vérifie si le personnage descend et touche le haut de la plateforme
            if (velocity.y > 0 && // En chute seulement
                personnageBounds.top + personnageBounds.height <= plateformeBounds.top + 40) { // Juste avant de traverser
                
                // Positionner le personnage sur la plateforme
                sprite.setPosition(sprite.getPosition().x, plateformeBounds.top - personnageBounds.height);
                velocity.y = 0;  // Arrêter la chute
                onGround = true; // Confirmer qu'il est au sol
                return;          // Terminer la détection pour cette frame
            }
            // Vérifie si le personnage monte et touche le bas de la plateforme
            else if (velocity.y < 0 && // En montée seulement
                     personnageBounds.top >= plateformeBounds.top + plateformeBounds.height ) {
                // Positionner le personnage juste en dessous de la plateforme
                sprite.setPosition(sprite.getPosition().x, plateformeBounds.top + plateformeBounds.height);
                onGround = true;
                velocity.y = 0;  // Arrêter le mouvement vertical
                return;          // Terminer la détection pour cette frame
            }
         

        
        }
    }

    // Si le personnage n'est pas sur une plateforme, réinitialiser onGround
    if (!wasOnGround) {
        onGround = false; // Le personnage n'est pas au sol
    }
    
}

void Personnage::showVictoryMessage() {
    hasWon = true; // Mettre à jour l'état de victoire
}

void Personnage::showDefeatMessage() {
    hasLost = true; // Mettre à jour l'état de défaite
}
