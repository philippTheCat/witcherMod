//
// Created by chatz on 26.06.2019.
//

#ifndef WITCHERMOD_WITCHER_H
#define WITCHERMOD_WITCHER_H

#include <stdint.h>

namespace w3 {
    struct String {
        char32_t* string;
        int32_t length;
    };

    class CScriptStackFrame {
    public:
        unsigned char unknown_0[0x30];
        uint8_t* unk_0x30;
    };

    class IScriptable {

    };

}

#endif //WITCHERMOD_WITCHER_H
