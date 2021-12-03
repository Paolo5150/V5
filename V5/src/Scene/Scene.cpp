#include <V5/Scene/Scene.h>
#include <V5/Scene/Entity.h>

using namespace V5Core;

Entity Scene::CreateEntity()
{
	Entity e(m_enttRegistry.create(), this);
	return e;
}