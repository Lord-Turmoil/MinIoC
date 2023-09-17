// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MIOC_SINGLETON_CONTAINER_H_
#define _MIOC_SINGLETON_CONTAINER_H_

#include "Macros.h"
#include "ServiceContainer.h"

#include <memory>

MIOC_BEGIN


class SingletonContainer
{
public:
    ~SingletonContainer() = default;

    static ServiceContainerPtr GetContainer()
    {
        if (_container == nullptr)
        {
            _container = ServiceContainer::New(_lazy);
        }
        return _container;
    }

    static ServiceContainerPtr GetContainer(bool lazy)
    {
        _lazy = lazy;
        return GetContainer();
    }

private:
    // Prevent instantiation.
    SingletonContainer() = default;

    static std::shared_ptr<ServiceContainer> _container;
    static bool _lazy;
};

std::shared_ptr<ServiceContainer> SingletonContainer::_container;
bool SingletonContainer::_lazy = DEFAULT_LAZINESS;


MIOC_END

#endif // !_MIOC_SINGLETON_CONTAINER_H_