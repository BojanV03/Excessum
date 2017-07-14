#ifdef __linux__
	#include "headers/Entity.h"
#elif defined _WIN32
	#include "headers/Entity.h"
#endif

Entity::Entity()
{

}
Entity::Entity(sf::Vector2f position, sf::Texture texture)
	:m_position(position), m_image(texture)
{

}
Entity::~Entity()
{

}
