#pragma once

#ifdef __linux__
#include <SFML/Graphics.hpp>
#elif defined _WIN32
#include <SFML\Graphics.hpp>
#endif
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template<typename Identifier, typename Resource>
class ResourceManager
{
public:

	void Load(Identifier id, const std::string& filepath);

	const Resource& Get(Identifier id) const;

private:

	std::map<Identifier, std::unique_ptr<Resource>> m_resources;
};

template<typename Identifier, typename Resource>
void ResourceManager<Identifier, Resource>::Load(Identifier id, const std::string& filepath)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filepath)) {
		throw std::runtime_error("Failed to load: " + filepath);
	}

	auto goodInsert = m_resources.insert(std::make_pair(id, std::move(resource)));
	assert(goodInsert.second);

}

template<typename Identifier, typename Resource>
const Resource& ResourceManager<Identifier, Resource>::Get(Identifier id) const
{
	auto found = m_resources.find(id);
	assert(found != m_resources.end());

	return *(found->second);
}

typedef ResourceManager<std::string, sf::Texture> TextureManager;
typedef ResourceManager<std::string, sf::Font> FontManager;
