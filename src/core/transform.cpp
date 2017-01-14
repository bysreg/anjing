#include "transform.hpp"
#include "core/game_object.hpp"

anjing::core::Transform::Transform()
{
	mat.SetAsIdentity();
}

void anjing::core::Transform::OnAdded()
{
	GetOwner()->SetTransform(this);
}
