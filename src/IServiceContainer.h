// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MINIOC_ISERVICE_CONTAINER_H_
#define _MINIOC_ISERVICE_CONTAINER_H_

#include "Macros.h"

MINIOC_BEGIN


class IServiceContainer
{
public:
    virtual ~IServiceContainer() = 0;
};

IServiceContainer::~IServiceContainer() = default;


MINIOC_END

#endif // !_MINIOC_ISERVICE_CONTAINER_H_
