// Copyright (C) 2023 - 2024 Tony's Studio. All rights reserved.

#pragma once

#include <mioc/detail/Macros.h>
#include <mioc/detail/ServiceContainer.h>

#include <memory>

MIOC_BEGIN

class SingletonContainer final
{
public:
    SingletonContainer(const SingletonContainer&) = delete;
    SingletonContainer& operator=(const SingletonContainer&) = delete;
    SingletonContainer(SingletonContainer&&) = delete;
    SingletonContainer& operator=(SingletonContainer&&) = delete;

    ~SingletonContainer() = default;

    static ServiceContainerPtr GetContainer()
    {
        return GetContainer(DEFAULT_LAZINESS);
    }

    static ServiceContainerPtr GetContainer(bool lazy)
    {
        static std::shared_ptr<ServiceContainer> container = ServiceContainer::New(lazy);
        return container;
    }

private:
    // Prevent instantiation.
    SingletonContainer() = default;
};

MIOC_END
