#include <SFML/Graphics.hpp>
#include "personnage.h"
#include "plateforme.h"
#include "drapeau.h"
#include <vector>
#include "danger.h"
#include <chrono>
#include <thread>

int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Plateforme");
    
    window.setFramerateLimit(60);
    Personnage personnage;
    personnage.loadTexture("character.png");
    personnage.setPosition(100.f, 500.f);

    std::vector<Plateforme> plateformes;
    Plateforme sol1, plateforme1, sol2, plateforme2, plateforme3;
///////////////////////////////////////////////////////
    sol1.loadTexture("plateform.png");
    sol1.setOrigine(0.f,-32.f);
    sol1.setPosition(-200.f, 500.f);
///////////////////////////////////////////////////////
    plateforme1.loadTexture("plateform.png");
    plateforme1.setScale(0.2,0.1);
    plateforme1.setPosition(300.f, 450.f);
///////////////////////////////////////////////////////
    sol2.loadTexture("plateform.png");
    sol2.setOrigine(0.f,-32.f);
    sol2.setScale(0.3,1);
    sol2.setPosition(500.f, 500.f);
///////////////////////////////////////////////////////
    plateforme2.loadTexture("plateform.png");
    plateforme2.setScale(0.2,0.1);
    plateforme2.setPosition(650.f, 400.f);
///////////////////////////////////////////////////////
    plateforme3.loadTexture("plateform.png");
    plateforme3.setScale(0.2,0.1);
    plateforme3.setPosition(450.f, 300.f);
///////////////////////////////////////////////////////
    plateformes.push_back(sol1);
    plateformes.push_back(plateforme1);
    plateformes.push_back(plateforme2);
    plateformes.push_back(plateforme3);
    plateformes.push_back(sol2);
//////////////////////////////////////////
//////////////   DRAPEAU   ///////////////
//////////////////////////////////////////
    Drapeau drapeau;
    drapeau.setPosition(600.f, 200.f);
    drapeau.setScale(0.3,0.3);
//////////////////////////////////////////
///////////////   DANGER   ///////////////
//////////////////////////////////////////
    Danger danger;
    danger.setPosition(150.f, 495.f);
    danger.setColor(255,0,0);
    danger.setScale(0.3,0.3);



    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (personnage.gameOver) {
        if (personnage.clock.getElapsedTime().asSeconds() >= 1.0f) {
            window.close(); // Quitter le jeu après 1 seconde
        }
        }
        // Contrôles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            personnage.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            personnage.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            personnage.jump();
        }


        // // Collisions
        // if (personnage.getBounds().intersects(plateforme1.getBounds()) ||
        //     personnage.getBounds().intersects(plateforme2.getBounds())) {
        //     personnage.setPosition(personnage.getBounds().left, personnage.getBounds().top - 1);
        // }

        personnage.update(plateformes,drapeau, danger);
        danger.update();
        // Rendu
        window.clear();
        personnage.render(window);

        for (auto& plateforme : plateformes) {
            plateforme.render(window);
        }
        

        drapeau.render(window);
        danger.render(window);
        window.display();

    }

    return 0;
}
