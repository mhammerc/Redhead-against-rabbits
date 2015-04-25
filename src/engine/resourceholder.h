#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier id, const std::string& filename);

    template <typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter& secondParam);

    Resource& get(Identifier id);
    const Resource& getConst(Identifier id) const;


private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);


private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "resourceholder.inl"

#endif // RESOURCEHOLDER_H

