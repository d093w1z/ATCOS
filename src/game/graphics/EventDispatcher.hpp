#pragma once
#include "Event.hpp"
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <vector>

class EventDispatcher
{
public:
    template<typename EventType>
    using Handler = std::function<void(const EventType&)>;

    template<typename EventType>
    void subscribe(Handler<EventType> handler)
    {
        auto& handlers = listeners[typeid(EventType)];
        handlers.push_back([handler](const Event& e) {
            handler(static_cast<const EventType&>(e));
        });
    }

    template<typename EventType>
    void dispatch(const EventType& event)
    {
        auto it = listeners.find(typeid(EventType));
        if (it != listeners.end())
        {
            for (auto& handler : it->second)
                handler(event);
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> listeners;
};