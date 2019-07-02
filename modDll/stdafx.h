//
// Created by chatz on 23.06.2019.
//

#ifndef WITCHERMOD_STDAFX_H
#define WITCHERMOD_STDAFX_H
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdarg.h>
#include <future>


/*
	Declare a hook. Does the following:
	- Declares a public static function;
	- Declares a public function;
	- Assigns the type of the function to hook a nice name;
	- Declares a variable of that name.

	Example:
		HOOK_DECL(void, __cdecl, PM_PlayerMove, qboolean server)
	Expands into:
		public:
			static void __cdecl HOOKED_PM_PlayerMove(qboolean server);
			void __cdecl HOOKED_PM_PlayerMove_Func(qboolean server);
		protected:
			typedef void(__cdecl *_PM_PlayerMove) (qboolean server);
			_PM_PlayerMove ORIG_PlayerMove;
*/
#define HOOK_DECL(ret, call, name, ...) \
	public: \
		static ret call HOOKED_##name(__VA_ARGS__); \
		ret HOOKED_##name##_Func(__VA_ARGS__); \
	protected: \
		typedef	ret(call *_##name) (__VA_ARGS__); \
		_##name ORIG_##name;

/*
	Define a hook. Does the following:
	- Defines the static function to call the member function;
	- Inserts the member function definition.

	Example:
		HOOK_DEF_1(ServerDLL, void, __cdecl, PM_PlayerMove, qboolean, server)
		{
			// do stuff
		}
	Becomes:
		void __cdecl ServerDLL::HOOKED_PM_PlayerMove(qboolean server)
		{
			return ServerDLL::GetInstance().HOOKED_PM_PlayerMove_Func(server);
		}
		void __cdecl ServerDLL::HOOKED_PM_PlayerMove_Func(qboolean server)
		{
			// do stuff
		}
*/

#define HOOK_DEF_0(class, ret, call, name) \
	ret call class::HOOKED_##name() { \
		return class::GetInstance().HOOKED_##name##_Func(); \
	} \
	ret class::HOOKED_##name##_Func()

#define HOOK_DEF_1(class, ret, call, name, t1, n1) \
	ret call class::HOOKED_##name(t1 n1) { \
		return class::GetInstance().HOOKED_##name##_Func(n1); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1)

#define HOOK_DEF_2(class, ret, call, name, t1, n1, t2, n2) \
	ret call class::HOOKED_##name(t1 n1, t2 n2) { \
		return class::GetInstance().HOOKED_##name##_Func(n1, n2); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1, t2 n2)

#define HOOK_DEF_3(class, ret, call, name, t1, n1, t2, n2, t3, n3) \
	ret call class::HOOKED_##name(t1 n1, t2 n2, t3 n3) { \
		return class::GetInstance().HOOKED_##name##_Func(n1, n2, n3); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1, t2 n2, t3 n3)

#define HOOK_DEF_4(class, ret, call, name, t1, n1, t2, n2, t3, n3, t4, n4) \
	ret call class::HOOKED_##name(t1 n1, t2 n2, t3 n3, t4 n4) { \
		return class::GetInstance().HOOKED_##name##_Func(n1, n2, n3, n4); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1, t2 n2, t3 n3, t4 n4)

#define HOOK_DEF_5(class, ret, call, name, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5) \
	ret call class::HOOKED_##name(t1 n1, t2 n2, t3 n3, t4 n4, t5 n5) { \
		return class::GetInstance().HOOKED_##name##_Func(n1, n2, n3, n4, n5); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1, t2 n2, t3 n3, t4 n4, t5 n5)

#define HOOK_DEF_6(class, ret, call, name, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6) \
	ret call class::HOOKED_##name(t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6) { \
		return class::GetInstance().HOOKED_##name##_Func(n1, n2, n3, n4, n5, n6); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6)

#define HOOK_DEF_7(class, ret, call, name, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7) \
	ret call class::HOOKED_##name(t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6, t7 n7) { \
		return class::GetInstance().HOOKED_##name##_Func(n1, n2, n3, n4, n5, n6, n7); \
	} \
	ret class::HOOKED_##name##_Func(t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6, t7 n7)


#endif //WITCHERMOD_STDAFX_H
