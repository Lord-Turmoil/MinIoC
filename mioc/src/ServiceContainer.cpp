// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#include <mioc/ServiceContainer.h>

MIOC_BEGIN

ServiceContainer::ServiceContainer(bool lazy) : _lazy(lazy)
{
}

// This is a random number, change it as you wish.
int ServiceContainer::_nextTypeId = 75159;

MIOC_END
