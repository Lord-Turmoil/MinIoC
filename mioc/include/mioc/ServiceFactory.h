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


// Transient service factory will create a new instance every time.
template<typename TService>
class ServiceFactory : public IServiceFactory
{
public:
    explicit ServiceFactory(const std::function<std::shared_ptr<TService>()>& provider)
        : _provider(provider)
    {
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
class SingletonServiceFactory : public ServiceFactory<TService>
{
public:
    explicit SingletonServiceFactory(const std::function<std::shared_ptr<TService>()>& provider)
        : ServiceFactory<TService>(provider)
    {
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
