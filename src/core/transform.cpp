#include "transform.hpp"
#include "core/game_object.hpp"

void anjing::core::Transform::OnAdded()
{
	GetOwner()->SetTransform(this);
}
