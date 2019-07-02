//
// Created by chatz on 27.06.2019.
//

#ifndef WITCHERMOD_STRUCTS_H
#define WITCHERMOD_STRUCTS_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#ifdef _WIN32
#define MAKE_PADDED_STRUCT(type, name, sanityName, padding, is_priv, priv)      \
__pragma(pack(push, 1))                                             \
struct                                                              \
{                                                                   \
    is_priv: char __pad##sanityName##__[padding];                         \
    public: type name;                                              \
} priv;                                                             \
__pragma(pack(pop))

#else
#define MAKE_PADDED_STRUCT(type, name,sanityName, padding, is_priv, priv)      \
struct __attribute__((packed))                                      \
{                                                                   \
    is_priv: char __pad##sanityName##__[padding];                         \
    public: type name;                                              \
} priv;

#endif

#define MAKE_PADDED_VAR(type, name, sanityName, padding) MAKE_PADDED_STRUCT(type, name, sanityName, padding, public, )
#define MAKE_PRIVATE_PADDED_VAR(type, name, sanityName, padding) MAKE_PADDED_STRUCT(type, val, sanityName, padding, private, name)



#endif //WITCHERMOD_STRUCTS_H
