#pragma once
#include "CollisionComponent.h"

class AABBCollisionComponent :
    public CollisionComponent
{
    COLLIDER_CHILD_BODY();

    virtual const bool doesIntersect(const class AABBCollisionComponent& other) const override;

public:

    float halfWidth;
    float halfHeight;
    float halfDepth;

    const bool doesIntersect1D(float a, float b, float c, float d);

    const bool doesIntersectRange1D(float X, float XHalf, float Y, float YHalf) const;

};

