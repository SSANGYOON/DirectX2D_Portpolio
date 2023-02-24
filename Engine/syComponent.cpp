#include "syComponent.h"

namespace sy
{
	Component::Component(ComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
}