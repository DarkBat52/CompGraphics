#include "SphereCollisionComponent.h"

const bool SphereCollisionComponent::doesIntersect(const SphereCollisionComponent& other) const
{
    return (GetWorldTransform().Position - other.GetWorldTransform().Position).Length() < radius + other.getCollisionRadius();
}

void SphereCollisionComponent::setCollisionRadius(float r)
{
    radius = r;
}

float SphereCollisionComponent::getCollisionRadius() const
{
    return radius;
}
