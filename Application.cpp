#include "Application.hpp"

Application::Application()
    : m_window{sf::VideoMode{c_window_x, c_window_y}, "ball collision demo"},
      m_balls{Math::random<size_t>(c_balls_min, c_balls_max)},
      m_tree{{0, 0, c_window_x, c_window_y}}
{
    for (auto &it : m_balls)
    {
        it.setPosition(Math::random<float>(0, c_window_x), Math::random<float>(0, c_window_y));
        it.setDirection({Math::random<float>(-5.0f / 3.0f, 5.0f / 3.0f), Math::random<float>(-5.0f / 3.0f, 5.0f / 3.0f)});
        it.setRadius(Math::random<float>(5, 10));
        it.setSpeed(Math::random<float>(30, 60));
    }

    m_window.setFramerateLimit(60);
}

void Application::run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                m_window.close();

        float deltaTime = m_clock.restart().asSeconds();

        m_window.clear();

        loop(deltaTime);

        m_fpsCounter.push(1.0f / deltaTime);
        drawFPS(m_fpsCounter.getAverage());

        m_window.display();
    }
}

void Application::loop(float deltaTime)
{
    auto windowSize = m_window.getSize();
    auto endIt = m_balls.end();

    m_tree.clear();
    for (auto &it : m_balls)
        m_tree.insert(it);

    m_tree.draw(m_window);

    for (auto &lhs : m_balls)
    {
        auto &nearbyObjects = m_tree.getNearbyObjects(lhs.getGlobalBounds());

        // Ищем коллизию среди объектов поблизости
        auto collide = std::find_if(nearbyObjects.begin(), nearbyObjects.end(),
                                    [&lhs](const auto &it)
                                    {
                                        auto &rhs = it.get();
                                        if (&rhs <= &lhs) // нам нужны только следующие за lhs элементы
                                            return false;

                                        return Ball::hasCollide(lhs, rhs);
                                    });

        if (collide != nearbyObjects.end())
            Ball::onCollide(lhs, collide->get());

        // Отскакиваем от стен
        if (lhs.getPosition().x < 0 || lhs.getPosition().x + lhs.getRadius() * 2 > windowSize.x)
            lhs.setDirection({-lhs.getDirection().x, lhs.getDirection().y});

        if (lhs.getPosition().y < 0 || lhs.getPosition().y + lhs.getRadius() * 2 > windowSize.y)
            lhs.setDirection({lhs.getDirection().x, -lhs.getDirection().y});
    }

    for (auto &ball : m_balls)
        ball.update(deltaTime);

    for (const auto ball : m_balls)
        m_window.draw(ball);
}

void Application::drawFPS(float fps)
{
    char c[32];
    std::snprintf(c, sizeof(c), "FPS: %f", fps);
    m_window.setTitle(c);
}