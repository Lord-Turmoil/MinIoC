// Copyright (C) 2023 - 2024 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MIOC_SINGLETON_CONTAINER_H_
#define _MIOC_SINGLETON_CONTAINER_H_

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

    static ServiceContainerPtr GetContainer();
    static ServiceContainerPtr GetContainer(bool lazy);

private:
    // Prevent instantiation.
    SingletonContainer() = default;
};

MIOC_END

#endif // _MIOC_SINGLETON_CONTAINER_H_
