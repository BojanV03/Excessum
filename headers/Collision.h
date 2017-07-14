#pragma once

#ifdef __linux__
	#include <SFML/Graphics.hpp>
  #include <cmath>
#elif defined _WIN32
	#include <SFML\Graphics.hpp>
  #include <cmath>
#endif

// Axis Aligned Bounding Box
struct AABB
{
	sf::Vector2f topLeft;
	sf::Vector2f bottomRight;
};

template <typename T>
T clamp(T const &x, T const &a, T const &b)
{
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

bool AreColliding(sf::Shape *a, sf::Shape *b);

bool AABBvsAABB(const AABB &a, const AABB &b);
bool AABBvsAABB(sf::RectangleShape &a, sf::RectangleShape &b);
bool AABBvsAABB(const sf::Vector2f &topLeftA, const sf::Vector2f &bottomRightA,
	const sf::Vector2f &topLeftB, const sf::Vector2f &bottomRightB);

float Distance(sf::Vector2f &a, sf::Vector2f &b);

bool RectVsCircle(sf::RectangleShape rect, sf::CircleShape circle);
bool CircleVsCircle(const sf::CircleShape &a, const sf::CircleShape &b);
bool CircleVsCircle(sf::Vector2f pointA, float radiusA, sf::Vector2f pointB, float radiusB);
