//
// Created by chatz on 24.06.2019.
//

#include "WitcherModule.h"
#include "../witcher/witchertypes.h"

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

struct TypeDescriptor {
    void * pVFTable;
    void * spare;
    char* name;
};


struct RTTICompleteObjectLocator
{
    DWORD signature; //always zero ?
    DWORD offset;    //offset of this vtable in the complete class
    DWORD cdOffset;  //constructor displacement offset
    struct TypeDescriptor* pTypeDescriptor; //TypeDescriptor of the complete class
    struct RTTIClassHierarchyDescriptor* pClassDescriptor; //describes inheritance hierarchy
};

struct RTTIClassHierarchyDescriptor
{
    DWORD signature;      //always zero?
    DWORD attributes;     //bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
    DWORD numBaseClasses; //number of classes in pBaseClassArray
    struct RTTIBaseClassArray* pBaseClassArray;
};

struct PMD
{
    int mdisp;  //member displacement
    int pdisp;  //vbtable displacement
    int vdisp;  //displacement inside vbtable
};

struct RTTIBaseClassDescriptor
{
    struct TypeDescriptor* pTypeDescriptor; //type descriptor of the class
    DWORD numContainedBases; //number of nested classes following in the Base Class Array
    struct PMD where;        //pointer-to-member displacement info
    DWORD attributes;        //flags, usually 0
};

void printRTTIName(intptr_t * type){
    if (nullptr == type){
        EngineDevMsg("couldnt print RTTI name: nullptr\n");
        return;
    }

    intptr_t * vtableAddr = type;
    RTTICompleteObjectLocator * rttiInfo = (RTTICompleteObjectLocator*)(vtableAddr - 8);

    EngineDevMsg("RTTIInfo pointer: %p\n", rttiInfo );
    EngineDevMsg("RTTIInfo location: %p\n", *rttiInfo );
    EngineDevMsg("RTTIInfo typedescriptor pointer: %p\n", rttiInfo->pTypeDescriptor );

    if (rttiInfo->pTypeDescriptor != nullptr) {
        EngineDevMsg("typeName: %s\n", rttiInfo->pTypeDescriptor->name);
    }
}
#define DEBUG_PARAM(param) EngineMsg("\t " #param " => %i (%s)\n", param, param)

HOOK_DEF_5(WitcherModule, int64_t , __stdcall, WITCHER_FactUpdate, int64_t, unk, w3::String *  ,factName, int32_t, factValue, int64_t ,unk2, int64_t, validity){
    EngineMsg("called factUpdate: %i %ls (length %i) %i %i %i\n", unk, factName->string, factName->length, factValue, unk2, validity);
    return ORIG_WITCHER_FactUpdate(unk, factName, factValue, unk2, validity);
}

HOOK_DEF_3(WitcherModule, void , __thiscall, WITCHER_ScriptFunc_loadProgress, IScriptable*, thiz, w3::CScriptStackFrame *, stackFrame, void*, ret){
    ORIG_WITCHER_ScriptFunc_loadProgress(thiz, stackFrame, ret);
    EngineMsg("called WITCHER_ScriptFunc_loadProgress: %f, %f\n", ret, (float *)ret );
	EngineMsg("called WITCHER_ScriptFunc_loadProgress called on 1: %s\n", typeid(thiz).name());
	EngineMsg("called WITCHER_ScriptFunc_loadProgress called on 2: %s\n", typeid(*thiz).name());
	EngineMsg("called WITCHER_ScriptFunc_loadProgress called on 2: %s\n", typeid(thiz[0]).name());
	EngineMsg("called WITCHER_ScriptFunc_loadProgress called on 3: %s\n", typeid(thiz->m_object).name());
	EngineMsg("called WITCHER_ScriptFunc_loadProgress called on 4: %s\n", typeid(*thiz->m_object).name());
	printRTTIName(reinterpret_cast<intptr_t *>(thiz));
    //printRTTIName(reinterpret_cast<intptr_t *>(thiz->m_object));
}

HOOK_DEF_6(WitcherModule, int64_t , __fastcall, WITCHER_ScriptFunc_soundEvent,int64_t, param_1,int64_t, param_2,intptr_t *,param_3,
           char * ,param_4,int64_t ,param_5,intptr_t,param_6){
    //EngineMsg("called WITCHER_ScriptFunc_soundEvent: \n");
    //DEBUG_PARAM(param_1);
    //DEBUG_PARAM(param_2);
    //DEBUG_PARAM(param_3);
    //DEBUG_PARAM(param_4);
    //DEBUG_PARAM(param_5);
    //DEBUG_PARAM(param_6);
    return ORIG_WITCHER_ScriptFunc_soundEvent(param_1, param_2, param_3,param_4,param_5,param_6);
}