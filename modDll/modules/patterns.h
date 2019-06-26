//
// Created by chatz on 26.06.2019.
//

#ifndef WITCHERMOD_PATTERNS_H
#define WITCHERMOD_PATTERNS_H

#include "../stdafx.h"

namespace patterns {
    PATTERNS(WITCHER_FactUpdate,
        "Witcher1.22",
        "4C 89 4C 24 20 44 89 44 24 18 55 57 41"
    );

    PATTERNS(WITCHER_ScriptFunc_loadProgress,
            "Witcher1.22",
            "40 53 48 83 ec 20 48 ff 42 30 48 8b 0d 67 70 4d 02")

            PATTERNS(WITCHER_ScriptFunc_soundEvent,
            "Witcher1.22",
            "48 89 5c 24 08 57 48 81 ec a0 00 00 00 48 83 79 08 00 48 8b fa 48 8b d9 75 1f e8 21 f1 ff ff")
}


#endif //WITCHERMOD_PATTERNS_H
