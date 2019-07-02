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
                            ORIG_WITCHER_FactUpdate, HOOKED_WITCHER_FactUpdate,
                                ORIG_WITCHER_ScriptFunc_loadProgress, HOOKED_WITCHER_ScriptFunc_loadProgress,
                                ORIG_WITCHER_ScriptFunc_soundEvent, HOOKED_WITCHER_ScriptFunc_soundEvent);
    }
}

void WitcherModule::Unhook() {
    if (m_Intercepted)
    {
        MemUtils::RemoveInterception(m_Name,
                                     ORIG_WITCHER_FactUpdate,
                                     ORIG_WITCHER_ScriptFunc_loadProgress,
                                     ORIG_WITCHER_ScriptFunc_soundEvent);
    }

    Clear();
}

void WitcherModule::Clear() {
    IHookableNameFilterOrdered::Clear();
    ORIG_WITCHER_FactUpdate = nullptr;
    ORIG_WITCHER_ScriptFunc_loadProgress = nullptr;
    ORIG_WITCHER_ScriptFunc_soundEvent = nullptr;

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

    DEF_FUTURE(WITCHER_ScriptFunc_loadProgress);
    GET_FUTURE(WITCHER_ScriptFunc_loadProgress);

    DEF_FUTURE(WITCHER_ScriptFunc_soundEvent);
    GET_FUTURE(WITCHER_ScriptFunc_soundEvent);
}

#define DEBUG_PARAM(param) EngineMsg("\t " #param " => %i (%s)\n", param, param)

HOOK_DEF_5(WitcherModule, int64_t , __stdcall, WITCHER_FactUpdate, int64_t, unk, w3::String *  ,factName, int32_t, factValue, int64_t ,unk2, int64_t, validity){
    EngineMsg("called factUpdate: %i %ls (length %i) %i %i %i\n", unk, factName->string, factName->length, factValue, unk2, validity);
    return ORIG_WITCHER_FactUpdate(unk, factName, factValue, unk2, validity);
}

HOOK_DEF_3(WitcherModule, void , __stdcall, WITCHER_ScriptFunc_loadProgress,w3::IScriptable*, thiz, w3::CScriptStackFrame&, stackFrame, void*,  ret){
    ORIG_WITCHER_ScriptFunc_loadProgress(thiz, stackFrame, ret);
    EngineMsg("called WITCHER_ScriptFunc_loadProgress: %f, %f\n", ret, (float *)ret );
}

HOOK_DEF_6(WitcherModule, int64_t , __fastcall, WITCHER_ScriptFunc_soundEvent,int64_t, param_1,int64_t, param_2,intptr_t *,param_3,
           char * ,param_4,int64_t ,param_5,intptr_t,param_6){
    EngineMsg("called WITCHER_ScriptFunc_soundEvent: \n");
    //DEBUG_PARAM(param_1);
    DEBUG_PARAM(param_2);
    //DEBUG_PARAM(param_3);
    //DEBUG_PARAM(param_4);
    //DEBUG_PARAM(param_5);
    //DEBUG_PARAM(param_6);
    return ORIG_WITCHER_ScriptFunc_soundEvent(param_1, param_2, param_3,param_4,param_5,param_6);
}