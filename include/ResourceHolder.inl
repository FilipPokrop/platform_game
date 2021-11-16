#include "ResourceHolder.h"

template <typename Resource, typename Identifier>
ResourceHolder<Resource,Identifier>::ResourceHolder()
	:m_resource_map()
{}

template<typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	
	insertResouce(id, std::move(resource));
}

template<typename Resource, typename Identifier>
inline const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = m_resource_map.find(id);
	assert(found != m_resource_map.end());

	return *found->second;
	// TODO: tu wstawić instrukcję return
}

template<typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::insertResouce(Identifier id, std::unique_ptr<Resource> resource)
{
	auto insered = m_resource_map.insert(std::make_pair(id, std::move(resource)));
	assert(insered.second);
}
