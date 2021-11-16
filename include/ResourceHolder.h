#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	ResourceHolder();

	void load(Identifier id, const std::string& filename);

	const Resource& get(Identifier id) const;

private:

	void insertResouce(Identifier id, std::unique_ptr<Resource> resource);

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

#include "ResourceHolder.inl"

