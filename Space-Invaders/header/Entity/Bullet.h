#pragma once
#include <SFML/Graphics.hpp>

namespace Bullet
{
    class Bullet
    {
    public:
        Bullet();
        Bullet(sf::Vector2f position, sf::Vector2f velocity); // Constructor with position and velocity
        ~Bullet();

        void setPosition(sf::Vector2f position);
        void setVelocity(sf::Vector2f velocity);
        sf::Vector2f getPosition() const;
        sf::Vector2f getVelocity() const;

        void update();
        void render(sf::RenderWindow& window); // Render method taking SFML window reference

        bool isOutOfBounds(const sf::RenderWindow& window); // To check if the bullet leaves the screen

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::CircleShape m_shape; // For visual representation (circle in this case)
    };
}
