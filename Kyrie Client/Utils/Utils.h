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

template <typename Ret, typename Type> Ret& direct_access(Type* type, size_t offset) {
	union {
		size_t raw;
		Type* source;
		Ret* target;
	} u;
	u.source = type;
	u.raw += offset;
	return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name)                                                                                       \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name()

#define BUILD_ACCESS(ptr, type, name, offset)                           \
	AS_FIELD(type, name, get##name);                                    \
	type get##name() const { return direct_access<type>(ptr, offset); } \
	void set##name(type v) const { direct_access<type>(ptr, offset) = v; }