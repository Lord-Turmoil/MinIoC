// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MIOC_SERVICE_FACTORY_H_
#define _MIOC_SERVICE_FACTORY_H_

#include <mioc/Macros.h>

#include <functional>
#include <memory>

MIOC_BEGIN

// Abstract representation of service factory.
class IServiceFactory
{
public:
    // A simple trick to make a class abstract.
    virtual ~IServiceFactory() = 0;
};

inline IServiceFactory::~IServiceFactory() = default;

template<typename TService>
using ServiceProvider = std::function<std::shared_ptr<TService>()>;

// Transient service factory will create a new instance every time.
template<typename TService>
class ServiceFactory : public IServiceFactory
{
public:
    explicit ServiceFactory(const ServiceProvider<TService>& provider)
        : _provider(provider)
    {
    }

    ServiceFactory(const ServiceFactory&) = default;
    ServiceFactory& operator=(const ServiceFactory&) = default;

    ServiceFactory(ServiceFactory&& other) noexcept
    {
        _provider = std::move(other._provider);
    }

    ServiceFactory& operator=(ServiceFactory&& other) noexcept
    {
        if (this != &other)
        {
            _provider = std::move(other._provider);
        }
        return *this;
    }

    ~ServiceFactory() override = default;

    virtual std::shared_ptr<TService> Resolve()
    {
        return _provider();
    }

private:
    std::function<std::shared_ptr<TService>()> _provider;
};


// Singleton service factory will create only one instance.
template<typename TService>
class SingletonServiceFactory final : public ServiceFactory<TService>
{
public:
    explicit SingletonServiceFactory(const ServiceProvider<TService>& provider)
        : ServiceFactory<TService>(provider)
    {
    }

    SingletonServiceFactory(const SingletonServiceFactory&) = default;
    SingletonServiceFactory& operator=(const SingletonServiceFactory&) = default;

    SingletonServiceFactory(SingletonServiceFactory&& other) noexcept
        : ServiceFactory<TService>(std::move(other))
    {
        _instance = std::move(other._instance);
    }

    SingletonServiceFactory& operator=(SingletonServiceFactory&& other) noexcept
    {
        if (this != &other)
        {
            ServiceFactory<TService>::operator=(std::move(other));
            _instance = std::move(other._instance);
        }
        return *this;
    }


    ~SingletonServiceFactory() override = default;

    std::shared_ptr<TService> Resolve() override
    {
        if (_instance == nullptr)
        {
            _instance = ServiceFactory<TService>::Resolve();
        }
        return _instance;
    }

private:
    std::shared_ptr<TService> _instance;
};


MIOC_END

#endif // !_MIOC_SERVICE_FACTORY_H_
