// Copyright (C) 2023 - 2024 Tony's Studio. All rights reserved.

#pragma once

#define MIOC_BEGIN                                                                                                     \
    namespace mioc                                                                                                     \
    {
#define MIOC_END }
#define MIOC     ::mioc::

constexpr bool DEFAULT_LAZINESS = true;

#define MIOC_VERSION_MAJOR 1
#define MIOC_VERSION_MINOR 3
#define MIOC_VERSION_PATCH 0

#define MIOC_TO_VERSION(major, minor, patch) (major * 10000 + minor * 100 + patch)
#define MIOC_VERSION                         MINET_TO_VERSION(DGEX_VERSION_MAJOR, DGEX_VERSION_MINOR, DGEX_VERSION_PATCH)
