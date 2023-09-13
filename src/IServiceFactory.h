#pragma once

#ifndef _MINIOC_ISERVICE_FACTORY_H_
#define _MINIOC_ISERVICE_FACTORY_H_

#include "Macros.h"

MINIOC_BEGIN


// Abstract representation of service factory.
class IServiceFactory
{
public:
    // A simple trick to make a class abstract.
    virtual ~IServiceFactory() = 0;
};

IServiceFactory::~IServiceFactory() = default;


MINIOC_END

#endif // !_MINIOC_ISERVICE_FACTORY_H_