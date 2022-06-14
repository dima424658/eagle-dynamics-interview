#include "Ball.hpp"

#include "Math.hpp"

void Ball::setSpeed(float speed)
{
    m_speed = speed;
}

float Ball::getSpeed() const
{
    return m_speed;
}

void Ball::setDirection(const sf::Vector2f &direction)
{
    m_direction = direction;
}

const sf::Vector2f &Ball::getDirection() const
{
    return m_direction;
}

void Ball::update(float deltaTime)
{
    auto delta = getDirection() * (getSpeed() * deltaTime);
    setPosition(getPosition() + delta);
}

float Ball::distance(const Ball &lhs, const Ball &rhs)
{
    auto offset = lhs.getRadius() - rhs.getRadius();
    auto delta = lhs.getPosition() - rhs.getPosition() + sf::Vector2f{offset, offset};

    return Math::length(delta);
}

bool Ball::hasCollide(const Ball &lhs, const Ball &rhs)
{
    auto distance = Ball::distance(lhs, rhs);
    auto radiusSum = lhs.getRadius() + rhs.getRadius();

    return distance < radiusSum;
}

void Ball::onCollide(Ball &lhs, Ball &rhs)
{
    auto m1 = std::pow(lhs.getRadius(), 2.0f);
    auto v1 = lhs.getDirection();
    auto m2 = std::pow(rhs.getRadius(), 2.0f);
    auto v2 = rhs.getDirection();

    // m1v1 + m2v2 = m1u1 + m2u2
    // m1v1^2 + m2v2^2 = m1u1^2 + m2u2^2
    auto u1 = (m1 * v1 - m2 * v1 + 2 * m2 * v2) / (m1 + m2);
    auto u2 = (m1 * v1 + m2 * v2 - m1 * u1) / m2;

    lhs.setDirection(u1);
    rhs.setDirection(u2);
}