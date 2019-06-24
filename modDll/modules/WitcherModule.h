//
// Created by chatz on 24.06.2019.
//

#ifndef WITCHERMOD_WITCHERMODULE_H
#define WITCHERMOD_WITCHERMODULE_H

#include "../SPTLib/IHookableNameFilterOrdered.hpp"

class WitcherModule  : public IHookableNameFilterOrdered {

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


};


#endif //WITCHERMOD_WITCHERMODULE_H
