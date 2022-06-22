#pragma once
#include "GameComponent.h"

#define COLLIDER_CHILD_BODY() \
public: \
virtual const bool doesIntersect(const CollisionComponent& other) const override \
{ \
    return other.doesIntersect(*this); \
} \
private:

class CollisionComponent :
    public GameComponent
{
public:

    virtual const bool doesIntersect(const CollisionComponent& other) const = 0;

    virtual const bool doesIntersect(const class AABBCollisionComponent& other) const {
        return false;
    };

    virtual const bool doesIntersect(const class SphereCollisionComponent& other) const {
        return false;
    }
};

