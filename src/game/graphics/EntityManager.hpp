#pragma once
#include <memory>
#include <unordered_map>
#include "Entity.hpp"
#include "graphics/EventDispatcher.hpp"

class EntityManager
{
   public:
    void HandleInputs(std::shared_ptr<EventDispatcher> eventDispatcher,
                      const std::optional<sf::Event>& event, const sf::RenderWindow& window);

    void registerEntity(std::shared_ptr<IEntity> entity)
    {
        entities[entity->getId()] = entity;
    }

    void unregisterEntity(int id)
    {
        entities.erase(id);
    }

    void updateAll(float dt)
    {
        for (auto& [id, entity] : entities) entity->update(dt);
    }

    void drawAll(sf::RenderTarget& target)
    {
        for (auto& [id, entity] : entities) target.draw(*entity);
    }

    std::shared_ptr<IEntity> getEntity(int id)
    {
        auto it = entities.find(id);
        return (it != entities.end()) ? it->second : nullptr;
    }

   private:
    std::unordered_map<int, std::shared_ptr<IEntity>> entities;
};