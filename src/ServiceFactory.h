#pragma once

#ifndef _MINIOC_SERVICE_FACTORY_H_
#define _MINIOC_SERVICE_FACTORY_H_

#include <functional>
#include <memory>

#include "Macros.h"
#include "IServiceFactory.h"

MINIOC_BEGIN


// ServiceFactory can provide an object of specified type.
template<typename TService>
class ServiceFactory : public IServiceFactory
{
private:
    std::function<std::shared_ptr<TService>> _provider;

public:
    ServiceFactory(std::function<std::shared_ptr<TService>> provider) : _provider(provider) {}
    ~ServiceFactory() override = default;

    // Get the service of specified type.
    std::shared_ptr<TService> GetService()
    {
        return _provider();
    }
};


MINIOC_END

#endif // !_MINIOC_SERVICE_FACTORY_H_