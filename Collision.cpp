#ifdef __linux__
	#include "headers/Collision.h"
#elif defined _WIN32
	#include "headers/Collision.h"
#endif

bool AreColliding(sf::Shape *a, sf::Shape *b)
{
	if (sf::RectangleShape *rectA = dynamic_cast<sf::RectangleShape*>(a))
	{
		if (sf::RectangleShape *rectB = dynamic_cast<sf::RectangleShape*>(b))
		{
			return AABBvsAABB(*rectA, *rectB);
		}
		else if (sf::CircleShape *circleB = dynamic_cast<sf::CircleShape*>(b))
		{
			return RectVsCircle(*rectA, *circleB);
		}
	}
	else if (sf::CircleShape *circleA = dynamic_cast<sf::CircleShape*>(a))
	{
		if (sf::RectangleShape *rectB = dynamic_cast<sf::RectangleShape*>(b))
		{
			return RectVsCircle(*rectB, *circleA);
		}
		else if (sf::CircleShape *circleB = dynamic_cast<sf::CircleShape*>(b))
		{
			return CircleVsCircle(*circleA, *circleB);
		}
	}
	return false;
}

bool AABBvsAABB(const AABB &a, const AABB &b)
{
	return AABBvsAABB(a.topLeft, a.bottomRight, b.topLeft, b.bottomRight);
}

bool AABBvsAABB(sf::RectangleShape &a, sf::RectangleShape &b)
{
	sf::Vector2f topLeftA = a.getPosition();
	sf::Vector2f topLeftB = b.getPosition();
	sf::Vector2f bottomRightA = sf::Vector2f(a.getPosition().x + a.getSize().x, a.getPosition().y + a.getSize().y);
	sf::Vector2f bottomRightB = sf::Vector2f(b.getPosition().x + b.getSize().x, b.getPosition().y + b.getSize().y);

	return AABBvsAABB(topLeftA, bottomRightA, topLeftB, bottomRightB);
}

bool AABBvsAABB(const sf::Vector2f &topLeftA, const sf::Vector2f &bottomRightA,
	const sf::Vector2f &topLeftB, const sf::Vector2f &bottomRightB)
{
	//    std::cout << topLeftA.x <<  " >= " << bottomRightB.x << " || " << bottomRightA.x << " <= " << topLeftB.x <<'\n';
	if (topLeftA.x >= bottomRightB.x || bottomRightA.x <= topLeftB.x) return false;
	//    std::cout << topLeftA.y <<  " >= " << bottomRightB.y << " || " << bottomRightA.y << " <= " << topLeftB.y <<'\n';
	if (topLeftA.y >= bottomRightB.y || bottomRightA.y <= topLeftB.y) return false;
	return true;
}
float Distance(sf::Vector2f &a, sf::Vector2f &b)
{
	return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

bool CircleVsCircle(const sf::CircleShape &a, const sf::CircleShape &b)
{
	sf::Vector2f centerA = sf::Vector2f(a.getPosition().x + a.getRadius(), a.getPosition().y + a.getRadius());
	sf::Vector2f centerB = sf::Vector2f(b.getPosition().x + b.getRadius(), b.getPosition().y + b.getRadius());

	return CircleVsCircle(centerA, a.getRadius(), centerB, b.getRadius());
}

bool CircleVsCircle(sf::Vector2f centerA, float radiusA, sf::Vector2f centerB, float radiusB)
{
	float r = radiusA + radiusB;
	r *= r;
	return r >= (std::pow((centerA.x - centerB.x), 2) + std::pow((centerA.y - centerB.y), 2));
}

bool RectVsCircle(sf::RectangleShape rect, sf::CircleShape circle)
{
	sf::Vector2f rectCenter = sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
	sf::Vector2f circleCenter = sf::Vector2f(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());

	float closestX = clamp(circleCenter.x, rect.getPosition().x, rect.getPosition().x + rect.getSize().x);
	float closestY = clamp(circleCenter.y, rect.getPosition().y, rect.getPosition().y + rect.getSize().y);

	float circleDistanceX = std::abs(circleCenter.x - closestX);
	float circleDistanceY = std::abs(circleCenter.y - closestY);

	float distanceSquared = (circleDistanceX * circleDistanceX) + (circleDistanceY * circleDistanceY);
	return distanceSquared < (circle.getRadius() * circle.getRadius());

}
