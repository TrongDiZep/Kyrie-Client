#pragma once
#include <Windows.h>
#include <string>
#include <ostream>
#include <fstream>


class Utils {
public:
	static std::string getRoamPath();
	static std::string getClientFolderPath();
	static std::string getConfigsFolderPath();
	static void DebugF(const char* output, ...);

	template <unsigned int IIdx, typename TRet, typename... TArgs>
	static inline auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
		//if (thisptr == nullptr)
		//return nullptr;
		using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
	}
};