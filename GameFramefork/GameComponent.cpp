#include "GameComponent.h"

HRESULT GameComponent::SetTransform(Transform t)
{
	this->transform = t;
	
	return E_NOTIMPL;
}

Transform GameComponent::GetWorldTransform() const
{
	if (parent != nullptr && parent != this) {
		return transform.GetTransformMatrix() * parent->GetWorldTransform().GetTransformMatrix();
	}

	return transform;
}

HRESULT GameComponent::SetParent(GameComponent* gc)
{
	if (gc == this) {
		return E_FAIL;
	}

	if (parent != nullptr) {
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
	}

	parent = gc;

	if (parent != nullptr)
	parent->children.push_back(this);

	return 0;
}


