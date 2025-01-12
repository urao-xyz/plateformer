#include "danger.h"
#include <iostream>

Danger::Danger()
    : moveSpeed(2.0f), direction(1), leftBound(100.f), rightBound(700.f) {
    loadTexture("drapeau.png"); // Assurez-vous d'avoir une texture pour le danger
    setPosition(150.f, 495.f); // Position initiale
}

void Danger::update() {
    // Déplacer le danger
    sprite.move(moveSpeed * direction, 0.f);

    // Vérifier les limites pour inverser la direction
    if (sprite.getPosition().x <= leftBound || sprite.getPosition().x >= rightBound) {
        direction *= -1; // Inverser la direction
    }
}