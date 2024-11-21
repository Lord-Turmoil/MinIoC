// Copyright (C) 2023 - 2024 Tony's Studio. All rights reserved.

#pragma once

#ifndef _MIOC_MACROS_H_
#define _MIOC_MACROS_H_

#define MIOC_VERSION   "1.2.0"
#define MIOC_PROJ_NAME "Tony's Mini IoC"

#define MIOC_BEGIN                                                                                                     \
    namespace mioc                                                                                                     \
    {
#define MIOC_END }
#define MIOC     ::mioc::

constexpr bool DEFAULT_LAZINESS = true;

#endif // _MIOC_MACROS_H_
