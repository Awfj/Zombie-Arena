// Zombie Arena.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
    enum class State { PAUSED, LEVELING_UP, 
        GAME_OVER, PLAYING };
    State state = State::GAME_OVER;

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(
        VideoMode(resolution.x, resolution.y),
        "Zombie Arena", Style::Fullscreen);

    View mainView(sf::FloatRect(0, 0, 
        resolution.x, resolution.y));

    Clock clock;
    Time gameTimeTotal;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Player player;
    IntRect arena;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return &&
                    state == State::PLAYING) {
                    state = State::PAUSED;
                }
                else if (event.key.code == Keyboard::Return &&
                    state == State::PAUSED) {
                    state = State::PLAYING;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::Return &&
                    state == State::GAME_OVER) {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING) {

                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (state == State::PLAYING) {
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                player.moveUp();
            }
            else {
                player.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S)) {
                player.moveDown();
            }
            else {
                player.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::A)) {
                player.moveLeft();
            }
            else {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D)) {
                player.moveRight();
            }
            else {
                player.stopRight();
            }
        }

        if (state == State::LEVELING_UP) {
            if (event.key.code == Keyboard::Num1) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6) {
                state = State::PLAYING;
            }

            if (state == State::PLAYING) {
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                int tileSize = 50;
                player.spawn(arena, resolution, tileSize);
                clock.restart();
            }
        }

        if (state == State::PLAYING) {
            Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();

            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(
                Mouse::getPosition(), mainView);

            player.update(dtAsSeconds, Mouse::getPosition());
            Vector2f playerPosition(player.getCenter());

            mainView.setCenter(player.getCenter());
        }

        if (state == State::PLAYING) {
            window.clear();
            window.setView(mainView);
            window.draw(player.getSprite());
        }

        if (state == State::LEVELING_UP) {

        }
        if (state == State::PAUSED) {

        }
        if (state == State::GAME_OVER) {

        }

        window.display();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
