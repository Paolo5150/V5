#include <V5/Scene/Entity.h>

using namespace V5Core;

Entity::Entity(entt::entity ent, Scene* scene) :
	m_enttHandle(ent) ,
	m_scene(scene)
{

}

