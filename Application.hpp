#pragma once

#include <SFML/Graphics.hpp>

#include "Math.hpp"
#include "Ball.hpp"
#include "Tree.hpp"

class Application
{
public:
    Application();
    void run();

private:
    void loop(float deltaTime);
    void drawFPS(float fps);

private:
    sf::RenderWindow m_window;

    Math::MiddleAverageFilter<float, 100> m_fpsCounter;
    sf::Clock m_clock;

    std::vector<Ball> m_balls;

    // When choosing a container, remember vector is best
    // Leave a comment to explain if you choose from the rest
    //                                        - Tony Van Eerd
    // Используем дерево для сложности NlogN
    Tree<Ball, 10> m_tree;

private:
    static constexpr auto c_window_x{1024ul};
    static constexpr auto c_window_y{768ul};

    static constexpr auto c_balls_min{100ul};
    static constexpr auto c_balls_max{300ul};
};