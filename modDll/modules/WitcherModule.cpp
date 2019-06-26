//
// Created by chatz on 24.06.2019.
//

#include "WitcherModule.h"

void WitcherModule::Hook(const std::wstring &moduleName, void *moduleHandle, void *moduleBase, size_t moduleLength,
                         bool needToIntercept) {
    Clear(); // Just in case.

    m_Handle = moduleHandle;
    m_Base = moduleBase;
    m_Length = moduleLength;
    m_Name = moduleName;
    m_Intercepted = needToIntercept;

    FindStuff();


    if (needToIntercept)
    {

        MemUtils::Intercept(moduleName,
                            ORIG_WITCHER_FactUpdate, HOOKED_WITCHER_FactUpdate);
    }
}

void WitcherModule::Unhook() {
    if (m_Intercepted)
    {
        MemUtils::RemoveInterception(m_Name,
                                     ORIG_WITCHER_FactUpdate);
    }

    Clear();
}

void WitcherModule::Clear() {
    IHookableNameFilterOrdered::Clear();
    ORIG_WITCHER_FactUpdate = nullptr;

    m_Intercepted = false;
}

void WitcherModule::FindStuff() {
    #define DEF_FUTURE(name) auto f##name = FindAsync(ORIG_##name, patterns::name);
    #define GET_FUTURE(future_name) \
			{ \
				auto pattern = f##future_name.get(); \
				if (ORIG_##future_name) { \
					EngineDevMsg("[witcher.exe] Found " #future_name " at %p (using the %s pattern).\n", ORIG_##future_name, pattern->name()); \
				} else { \
					EngineDevWarning("[witcher.exe] Could not find " #future_name ".\n"); \
				} \
			}


    DEF_FUTURE(WITCHER_FactUpdate);
    GET_FUTURE(WITCHER_FactUpdate);
}

HOOK_DEF_5(WitcherModule, int64_t , __stdcall, WITCHER_FactUpdate, int64_t, unk, w3::String *  ,factName, int32_t, factValue, int64_t ,unk2, int64_t, validity){
    EngineMsg("called factUpdate: %i %ls (length %i) %i %i %i\n", unk, factName->string, factName->length, factValue, unk2, validity);
    return ORIG_WITCHER_FactUpdate(unk, factName, factValue, unk2, validity);
}
