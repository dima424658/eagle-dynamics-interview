#pragma once

#include <memory>
#include <functional>
#include <concepts>
#include <stdexcept>
#include <algorithm>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

template <typename T, size_t MaxWidth>
class TreeNode
{
public:
    TreeNode(const sf::FloatRect &bounds, size_t level = 0, bool isHorizontal = false);

    void subdivide();
    void insert(T &object);
    void clear();

    void draw(sf::RenderTarget &target) const;

    const sf::FloatRect &getBounds() const;
    const std::vector<std::reference_wrapper<T>> &getNearbyObjects(const sf::FloatRect &bounds) const;

private:
    std::vector<std::reference_wrapper<T>> m_children;

    std::unique_ptr<TreeNode> m_firstNode, m_secondNode;
    const bool m_isHorizontal; // true - горизонтальная ветка, false - вертикальная
    const size_t m_level;      // глубина ноды

    sf::FloatRect m_bounds;
    sf::RectangleShape m_renderingBounds;
};

// Возможно переполнение стека при маленьком значении MaxWidth
template <std::derived_from<sf::Shape> T, size_t MaxWidth>
using Tree = TreeNode<T, MaxWidth>;

#include "Tree.tpp"