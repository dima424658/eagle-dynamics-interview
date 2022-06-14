#pragma once

template <typename T, size_t MaxWidth>
TreeNode<T, MaxWidth>::TreeNode(const sf::FloatRect &bounds, size_t level, bool isHorizontal)
    : m_level{level}, m_bounds{bounds}, m_isHorizontal{isHorizontal}
{
    m_renderingBounds.setPosition(m_bounds.left, m_bounds.top);
    m_renderingBounds.setSize({m_bounds.width, m_bounds.height});

    m_renderingBounds.setOutlineThickness(1.0f);
    m_renderingBounds.setOutlineColor(sf::Color::Cyan);
    m_renderingBounds.setFillColor(sf::Color::Transparent);
}

template <typename T, size_t MaxWidth>
void TreeNode<T, MaxWidth>::subdivide()
{
    if (m_firstNode.get() != nullptr || m_secondNode.get() != nullptr)
        return;

    sf::FloatRect firstRect, secondRect;

    if (m_isHorizontal)
    {
        // Расположение вертикальных нод
        auto halfOfWidth = m_bounds.width / 2.0f;

        firstRect = sf::FloatRect{m_bounds.left, m_bounds.top, halfOfWidth, m_bounds.height};                // лево
        secondRect = sf::FloatRect{m_bounds.left + halfOfWidth, m_bounds.top, halfOfWidth, m_bounds.height}; // право
    }
    else
    {
        // Расположение горизонтальных нод
        auto halfOfHeight = m_bounds.height / 2.0f;
        firstRect = sf::FloatRect{m_bounds.left, m_bounds.top, m_bounds.width, halfOfHeight};                 // верх
        secondRect = sf::FloatRect{m_bounds.left, m_bounds.top + halfOfHeight, m_bounds.width, halfOfHeight}; // низ
    }

    m_firstNode = std::make_unique<TreeNode>(firstRect, m_level + 1, !m_isHorizontal);
    m_secondNode = std::make_unique<TreeNode>(secondRect, m_level + 1, !m_isHorizontal);
}

template <typename T, size_t MaxWidth>
void TreeNode<T, MaxWidth>::insert(T &object)
{
    auto firstNode = m_firstNode.get();
    auto secondNode = m_secondNode.get();

    // Добавляем объект в дочерние ноды, если они уже существуют
    if (firstNode != nullptr && secondNode != nullptr)
    {
        sf::FloatRect objectBounds = object.getGlobalBounds();

        if (firstNode->getBounds().intersects(objectBounds))
            firstNode->insert(object);

        if (secondNode->getBounds().intersects(objectBounds))
            secondNode->insert(object);

        return;
    }

    m_children.push_back(object);

    // Делим ветку при переполнении
    if (m_children.size() >= MaxWidth)
    {
        subdivide();

        for (auto &it : m_children)
            insert(it);

        m_children.clear();
        m_children.shrink_to_fit();
    }
}

template <typename T, size_t MaxWidth>
void TreeNode<T, MaxWidth>::clear()
{
    m_children.clear();
    m_firstNode = nullptr;
    m_secondNode = nullptr;
}

template <typename T, size_t MaxWidth>
void TreeNode<T, MaxWidth>::draw(sf::RenderTarget &target) const
{
    target.draw(m_renderingBounds);

    if (auto node = m_firstNode.get())
        node->draw(target);

    if (auto node = m_secondNode.get())
        node->draw(target);
}

template <typename T, size_t MaxWidth>
const sf::FloatRect &TreeNode<T, MaxWidth>::getBounds() const
{
    return m_bounds;
}

template <typename T, size_t MaxWidth>
const std::vector<std::reference_wrapper<T>> &TreeNode<T, MaxWidth>::getNearbyObjects(const sf::FloatRect &bounds) const
{
    if (auto firstNode = m_firstNode.get(); firstNode && bounds.intersects(firstNode->getBounds()))
        return firstNode->getNearbyObjects(bounds);

    if (auto secondNode = m_secondNode.get(); secondNode && bounds.intersects(secondNode->getBounds()))
        return secondNode->getNearbyObjects(bounds);

    return m_children;
}