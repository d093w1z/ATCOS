#pragma once
#include <SFML/Graphics.hpp>

class IEntity : public sf::Drawable
{
   public:
    virtual ~IEntity() = default;
    IEntity(int id) : mId(id) {}
    IEntity(const IEntity&) = delete;
    IEntity& operator=(const IEntity&) = delete;
    IEntity(IEntity&&) = delete;
    IEntity& operator=(IEntity&&) = delete;
    virtual void update(float dt) = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    [[nodiscard]] virtual int getId() const
    {
        return mId;
    }

   protected:
    int mId;
};