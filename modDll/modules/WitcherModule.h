//
// Created by chatz on 24.06.2019.
//

#ifndef WITCHERMOD_WITCHERMODULE_H
#define WITCHERMOD_WITCHERMODULE_H

#include "../SPTLib/IHookableModule.hpp"
#include "../SPTLib/patterns.hpp"
#include "../SPTLib/sptlib.hpp"
#include "../SPTLib/MemUtils.hpp"
#include "../SPTLib/IHookableNameFilterOrdered.hpp"
#include "../stdafx.h"

#include "patterns.h"

class WitcherModule  : public IHookableNameFilterOrdered {
    HOOK_DECL(int64_t, __stdcall, WITCHER_FactUpdate,int64_t, w3::String *, int32_t, int64_t, int64_t)

public:
    static WitcherModule& GetInstance()
    {
        static WitcherModule instance;
        return instance;
    }

    virtual void Hook(const std::wstring& moduleName, void* moduleHandle, void* moduleBase, size_t moduleLength, bool needToIntercept);
    virtual void Unhook();
    virtual void Clear();

private:
    WitcherModule() : IHookableNameFilterOrdered({  L"witcher3.exe" }) {};


    void FindStuff();
};


#endif //WITCHERMOD_WITCHERMODULE_H
