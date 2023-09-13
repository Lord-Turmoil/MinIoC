#pragma once

#ifndef _TONIOC_ISERVICE_FACTORY_H_
#define _TONIOC_ISERVICE_FACTORY_H_

#include "Macros.h"

_TONIOC_BEGIN


// Abstract representation of Service factory.
class IServiceFactory
{
public:
    // A simple trick to make a class abstract.
    virtual ~IServiceFactory() = 0;
};

IServiceFactory::~IServiceFactory() = default;


_TONIOC_END

#endif // !_TONIOC_ISERVICE_FACTORY_H_