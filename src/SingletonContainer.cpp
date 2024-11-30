// Copyright (C) 2023 - 2024 Tony's Studio. All rights reserved.

#include <mioc/detail/SingletonContainer.h>

MIOC_BEGIN

ServiceContainerPtr SingletonContainer::GetContainer()
{
    return GetContainer(DEFAULT_LAZINESS);
}

ServiceContainerPtr SingletonContainer::GetContainer(bool lazy)
{
    static std::shared_ptr<ServiceContainer> container = ServiceContainer::New(lazy);
    return container;
}

MIOC_END
