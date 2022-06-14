#pragma once

#include <array>
#include <numeric>
#include <concepts>
#include <random>

#include <SFML/System/Vector2.hpp>

namespace Math
{
    template <std::integral T>
    T random(T min, T max)
    {
        static std::default_random_engine engine;
        std::uniform_int_distribution<T> distribution{min, max};

        return distribution(engine);
    }

    template <std::floating_point T>
    T random(T min, T max)
    {
        static std::default_random_engine engine;
        std::uniform_real_distribution<T> distribution{min, max};

        return distribution(engine);
    }

    inline float length(const sf::Vector2f &vec)
    {
        return std::sqrt(std::pow(vec.x, 2.0f) + std::pow(vec.y, 2.0f));
    }

    inline sf::Vector2f normalize(const sf::Vector2f &vec)
    {
        auto len = length(vec);

        return {vec.x / len, vec.y / len};
    }

    inline float distance(const sf::Vector2f &lhs, const sf::Vector2f &rhs)
    {
        return length(lhs - rhs);
    }

    template <typename T, size_t N>
    class MiddleAverageFilter
    {
    public:
        void push(const T &value)
        {
            data[id] = value;
            id = (id + 1) % N;
        }

        T getAverage() const
        {
            return std::reduce(data.begin(), data.end()) / N;
        }

    private:
        std::array<T, N> data;
        size_t id = 0u;
    };
}