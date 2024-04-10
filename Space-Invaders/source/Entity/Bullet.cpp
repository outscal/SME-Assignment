#include "../../header/Entity/Bullet.h"

namespace Bullet
{
    Bullet::Bullet()
    {
        // Default constructor, initialize shape properties
        m_shape.setRadius(2.f);
        m_shape.setFillColor(sf::Color::White);
    }

    Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
        : Bullet() // Delegate to default constructor to initialize shape properties
    {
        // Constructor with position and velocity
        m_position = position;
        m_velocity = velocity;
    }

    Bullet::~Bullet()
    {
        // Destructor
    }

    void Bullet::setPosition(sf::Vector2f position)
    {
        m_position = position;
    }

    void Bullet::setVelocity(sf::Vector2f velocity)
    {
        m_velocity = velocity;
    }

    sf::Vector2f Bullet::getPosition() const
    {
        return m_position;
    }

    sf::Vector2f Bullet::getVelocity() const
    {
        return m_velocity;
    }

    void Bullet::update()
    {
        // Update position based on velocity
        m_position += m_velocity;
    }

    void Bullet::render(sf::RenderWindow& window)
    {
        // Set position of shape to bullet position and draw it
        m_shape.setPosition(m_position);
        window.draw(m_shape);
    }

    bool Bullet::isOutOfBounds(const sf::RenderWindow& window)
    {
        // Check if bullet is out of bounds (leaves the screen)
        sf::FloatRect windowBounds(0.f, 0.f, window.getSize().x, window.getSize().y);
        return !windowBounds.contains(m_position);
    }
}
