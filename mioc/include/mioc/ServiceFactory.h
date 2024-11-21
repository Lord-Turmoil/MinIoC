// Copyright (C) 2023 - 2024 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MIOC_SERVICE_FACTORY_H_
#define _MIOC_SERVICE_FACTORY_H_

#include <mioc/Macros.h>

#include <functional>
#include <memory>

MIOC_BEGIN

// Abstract representation of service factory.
class ServiceFactory
{
public:
    // A simple trick to make a class abstract.
    virtual ~ServiceFactory() = 0;
};

inline ServiceFactory::~ServiceFactory() = default;

template <typename TService> using ServicePtr = std::shared_ptr<TService>;

template <typename TService> using ServiceProvider = std::function<ServicePtr<TService>()>;

// Transient service factory will create a new instance every time.
template <typename TService> class TransientServiceFactory : public ServiceFactory
{
public:
    explicit TransientServiceFactory(const ServiceProvider<TService>& provider) : _provider(provider)
    {
    }

    explicit TransientServiceFactory(ServiceProvider<TService>&& provider) : _provider(std::move(provider))
    {
    }

    TransientServiceFactory(const TransientServiceFactory&) = default;
    TransientServiceFactory& operator=(const TransientServiceFactory&) = default;

    TransientServiceFactory(TransientServiceFactory&& other) noexcept
    {
        _provider = std::move(other._provider);
    }

    TransientServiceFactory& operator=(TransientServiceFactory&& other) noexcept
    {
        if (this != &other)
        {
            _provider = std::move(other._provider);
        }
        return *this;
    }

    ~TransientServiceFactory() override = default;

    virtual std::shared_ptr<TService> Resolve()
    {
        return _provider ? _provider() : nullptr;
    }

protected:
    // Used by SingletonServiceFactory when instance is directly provided.
    TransientServiceFactory() = default;

private:
    ServiceProvider<TService> _provider;
};

// Singleton service factory will create only one instance.
template <typename TService> class SingletonServiceFactory final : public TransientServiceFactory<TService>
{
public:
    explicit SingletonServiceFactory(const ServiceProvider<TService>& provider)
        : TransientServiceFactory<TService>(provider)
    {
    }

    explicit SingletonServiceFactory(ServiceProvider<TService>&& provider)
        : TransientServiceFactory<TService>(std::move(provider))
    {
    }

    explicit SingletonServiceFactory(const ServicePtr<TService>& instance)
    {
        _instance = instance;
    }

    explicit SingletonServiceFactory(ServicePtr<TService>&& instance) : TransientServiceFactory<TService>()
    {
        _instance = std::move(instance);
    }

    SingletonServiceFactory(const SingletonServiceFactory&) = default;
    SingletonServiceFactory& operator=(const SingletonServiceFactory&) = default;

    SingletonServiceFactory(SingletonServiceFactory&& other) noexcept
        : TransientServiceFactory<TService>(std::move(other))
    {
        _instance = std::move(other._instance);
    }

    SingletonServiceFactory& operator=(SingletonServiceFactory&& other) noexcept
    {
        if (this != &other)
        {
            TransientServiceFactory<TService>::operator=(std::move(other));
            _instance = std::move(other._instance);
        }
        return *this;
    }

    ~SingletonServiceFactory() override = default;

    std::shared_ptr<TService> Resolve() override
    {
        if (_instance == nullptr)
        {
            _instance = TransientServiceFactory<TService>::Resolve();
        }

        return _instance;
    }

private:
    ServicePtr<TService> _instance;
};

MIOC_END

#endif // _MIOC_SERVICE_FACTORY_H_
