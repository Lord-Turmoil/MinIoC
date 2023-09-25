// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MIOC_SERVICE_CONTAINER_H_
#define _MIOC_SERVICE_CONTAINER_H_

#include <mioc/Macros.h>
#include <mioc/ServiceFactory.h>

#include <map>
#include <memory>

MIOC_BEGIN


class ServiceContainer;
using ServiceContainerPtr = std::shared_ptr<ServiceContainer>;

class ServiceContainer final
{
public:
    explicit ServiceContainer(bool lazy = DEFAULT_LAZINESS) : _lazy(lazy) {}

    // Any copy of service container is not allowed.
    ServiceContainer(const ServiceContainer&) = delete;
    ServiceContainer(const ServiceContainer&&) = delete;
    ServiceContainer& operator=(const ServiceContainer&) = delete;
    ServiceContainer& operator=(const ServiceContainer&&) = delete;

    ~ServiceContainer() = default;

    // Create a new service container.
    static ServiceContainerPtr New(bool lazy = DEFAULT_LAZINESS)
    {
        return std::make_shared<ServiceContainer>(lazy);
    }

    // Resolve registered service.
    // nullptr returned if service not registered.
    template<typename TService>
    std::shared_ptr<TService> Resolve() const
    {
        auto typeId = _GetTypeId<TService>();
        auto it = _services.find(typeId);
        if (it != _services.end())
        {
            auto factory = std::static_pointer_cast<ServiceFactory<TService>>(it->second);
            return factory->Resolve();
        }
        return nullptr;
    }

    // Register a singleton instance.
    // Will replace old registrations silently.
    template<typename TInterface>
    void AddSingleton(std::shared_ptr<TInterface> singleton)
    {
        // std::map::emplace will not replace old value if key already presents.
        _services[_GetTypeId<TInterface>()] =
            std::make_shared<ServiceFactory<TInterface>>([=] { return singleton; });
    }

    // Register a singleton by passing arguments to constructor.
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void AddSingleton()
    {
        if (_lazy)
        {
            _AddSingletonServiceFactory(
                std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments>... args)>(
                    [](std::shared_ptr<TArguments>... args) -> std::shared_ptr<TInterface> {
                        return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(args)...);
                    }));
        }
        else
        {
            AddSingleton<TInterface>(std::make_shared<TConcrete>(Resolve<TArguments>()...));
        }
    }

    // Register a transient instance.
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void AddTransient()
    {
        _AddTransientServiceFactory(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments>... args)>(
                [](std::shared_ptr<TArguments>... args) -> std::shared_ptr<TInterface> {
                    return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(args)...);
                }));
    }

private:
    // Make sure one type is mapped to one id.
    template<typename TService>
    static int _GetTypeId()
    {
        static int typeId = _nextTypeId++;
        return typeId;
    }

    // Low level registration.
    template<typename TInterface, typename... TDependencies>
    void _AddTransientServiceFactory(
        std::function<std::shared_ptr<TInterface>(std::shared_ptr<TDependencies>... dependencies)> factory)
    {
        _services[_GetTypeId<TInterface>()] =
            std::make_shared<ServiceFactory<TInterface>>([=] { return factory(Resolve<TDependencies>()...); });
    }

    template<typename TInterface, typename... TDependencies>
    void _AddSingletonServiceFactory(
        std::function<std::shared_ptr<TInterface>(std::shared_ptr<TDependencies>... dependencies)> factory)
    {
        _services[_GetTypeId<TInterface>()] =
            std::make_shared<SingletonServiceFactory<TInterface>>([=] { return factory(Resolve<TDependencies>()...); });
    }

private:
    static int _nextTypeId;

    std::map<int, std::shared_ptr<IServiceFactory>> _services;
    bool _lazy;
};


MIOC_END

#endif // !_MIOC_SERVICE_CONTAINER_H_
