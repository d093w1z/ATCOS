#pragma once

class Event
{
public:
    virtual ~Event() = default;
};

class WindowClosedEvent : public Event {};
class EntitySelectedEvent : public Event
{
public:
    explicit EntitySelectedEvent(int entityId) : entityId(entityId) {}
    int entityId;
};