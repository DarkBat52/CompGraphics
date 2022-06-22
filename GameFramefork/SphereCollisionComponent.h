#pragma once
#include "CollisionComponent.h"
class SphereCollisionComponent :
    public CollisionComponent
{
    COLLIDER_CHILD_BODY();

    virtual const bool doesIntersect(const class SphereCollisionComponent& other) const override;

    float radius = 0.0f;

public:

    void setCollisionRadius(float r);

    float getCollisionRadius() const;
};

