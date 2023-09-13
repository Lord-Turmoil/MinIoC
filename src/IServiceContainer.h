// Copyright (C) 2018 - 2023 Tony's Studio. All rights reserved.

#pragma once

#ifndef _TONIOC_ISERVICE_CONTAINER_H_
#define _TONIOC_ISERVICE_CONTAINER_H_

#include "Macros.h"

_TONIOC_BEGIN


class IServiceContainer
{
public:
    virtual ~IServiceContainer() = 0;
};

IServiceContainer::~IServiceContainer() = default;


_TONIOC_END

#endif // !_TONIOC_ISERVICE_CONTAINER_H_
