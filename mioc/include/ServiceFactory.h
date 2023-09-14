#pragma once

#ifndef _MIOC_SERVICE_FACTORY_H_
#define _MIOC_SERVICE_FACTORY_H_

#include "Macros.h"

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

IServiceFactory::~IServiceFactory() = default;


// ServiceFactory can provide an object of specified type.
template<typename TService>
class ServiceFactory : public IServiceFactory
{
private:
    std::function<std::shared_ptr<TService>()> _provider;

public:
    ServiceFactory(std::function<std::shared_ptr<TService>()> provider) : _provider(std::move(provider)) {}
    ~ServiceFactory() override = default;

    // Get the service of specified type.
    std::shared_ptr<TService> ResolveService()
    {
        return _provider();
    }
};


MIOC_END

#endif // !_MIOC_SERVICE_FACTORY_H_