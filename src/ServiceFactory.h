#pragma once

#ifndef _TONIOC_SERVICE_FACTORY_H_
#define _TONIOC_SERVICE_FACTORY_H_

#include <functional>
#include <memory>

#include "Macros.h"
#include "IServiceFactory.h"

_TONIOC_BEGIN


// ServiceFactory can provide an object of specified type.
template<typename TService>
class ServiceFactory : public IServiceFactory
{
private:
    std::function<std::shared_ptr<TService>> _provider;

public:
    ServiceFactory(std::function<std::shared_ptr<TService>> provider) : _provider(provider) {}
    ~ServiceFactory() override = default;

    /// <summary>
    /// Get service of specified type.
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<TService> GetService()
    {
        return _provider();
    }
};


_TONIOC_END

#endif // !_TONIOC_SERVICE_FACTORY_H_