#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::CircleShape
{
public:
    void update(float deltaTime);

    void setSpeed(float speed);
    float getSpeed() const;

    void setDirection(const sf::Vector2f &direction);
    const sf::Vector2f &getDirection() const;

    static float distance(const Ball &lhs, const Ball &rhs);
    static void onCollide(Ball &lhs, Ball &rhs);
    static bool hasCollide(const Ball &lhs, const Ball &rhs);

private:
    sf::Vector2f m_direction;
    float m_speed = 0;
};
