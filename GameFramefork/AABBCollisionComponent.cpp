#include "AABBCollisionComponent.h"

const bool AABBCollisionComponent::doesIntersect(const AABBCollisionComponent& other) const
{

    Transform t = GetWorldTransform();
    Transform otherT = other.GetWorldTransform();


    return doesIntersectRange1D(t.Position.x, t.Scale.x, otherT.Position.x, otherT.Scale.x)
        && doesIntersectRange1D(t.Position.y, t.Scale.y, otherT.Position.y, otherT.Scale.y)
        && doesIntersectRange1D(t.Position.z, t.Scale.z, otherT.Position.z, otherT.Scale.z);
}


const bool AABBCollisionComponent::doesIntersect1D(float a, float b, float c, float d)
{
    return b >= c && a <= d;
}

const bool AABBCollisionComponent::doesIntersectRange1D(float X, float XHalf, float Y, float YHalf) const
{
    return (X - XHalf <= Y + YHalf) && (X + XHalf >= Y - YHalf);
}
