#pragma once

#ifndef _MINIOC_SERVICE_CONTAINER_H_
#define _MINIOC_SERVICE_CONTAINER_H_

#include "Macros.h"
#include "ServiceFactory.h"

#include <map>
#include <memory>

MINIOC_BEGIN

class ServiceContainer;
using ServiceContainerPtr = std::shared_ptr<ServiceContainer>;

class ServiceContainer final
{
public:
    ServiceContainer() = default;

    // Any copy of service container is not allowed.
    ServiceContainer(const ServiceContainer&) = delete;
    ServiceContainer(const ServiceContainer&&) = delete;
    ServiceContainer& operator=(const ServiceContainer&) = delete;
    ServiceContainer& operator=(const ServiceContainer&&) = delete;

    ~ServiceContainer() = default;

    // Create a new service container.
    static ServiceContainerPtr New()
    {
        return std::make_shared<ServiceContainer>();
    }

    // Resolve registered service.
    // nullptr returned if service not registered.
    template<typename TService>
    std::shared_ptr<TService> ResolveService()
    {
        auto typeId = _GetTypeID<TService>();
        auto it = _services.find(typeId);
        if (it != _services.end())
        {
            auto factory = std::static_pointer_cast<ServiceFactory<TService>>(it->second);
            return factory->ResolveService();
        }
        return nullptr;
    }

    // Register a singleton.
    // Will replace old registrations silently.
    template<typename TInterface>
    void RegisterSingleton(std::shared_ptr<TInterface> singleton)
    {
        // std::map::emplace will not replace old value if key already presents.
        _services[_GetTypeID<TInterface>()] =
            std::make_shared<ServiceFactory<TInterface>>([=] { return singleton; });
    }

    // Register a singleton with lazy behavior.
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void RegisterSingleton()
    {
        RegisterSingleton<TInterface>(std::make_shared<TConcrete>(ResolveService<TArguments>()...));
    }

private:
    // Make sure one type is mapped to one id.
    template<typename TService>
    static int _GetTypeID()
    {
        static int typeId = _nextTypeId++;
        return typeId;
    }

    // Lowest level registration is to register a functor directly.
    template<typename TInterface, typename... TDependencies>
    void _RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TDependencies>... dependencies)> functor)
    {
        _services.emplace(
            _GetTypeID<TInterface>(),
            std::make_shared<ServiceFactory<TInterface>>([=] {
                return functor(ResolveService<TDependencies>()...);
                })
        );
    }

private:
    static int _nextTypeId;
    std::map<int, std::shared_ptr<IServiceFactory>> _services;
};

// This is a random number, change it as you wish.
int ServiceContainer::_nextTypeId = 75159;


MINIOC_END

#endif // !_MINIOC_SERVICE_CONTAINER_H_