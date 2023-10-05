#include "GetGammaHook.h"
#include "../../Memory.h"
#include "../../../Client/Client.h"

typedef float(__fastcall* getGamma)(uintptr_t*);
getGamma _getGamma;

float GetGammaHook::getGamma(uintptr_t* a1) {
	static FullBright* fullBrightMod = client->moduleMgr->getModule<FullBright>();
	if (fullBrightMod->isEnabled()) return 12.f;
	return _getGamma(a1);
}

void GetGammaHook::init() {
	uintptr_t address = Memory::getBase() + 0x904900;  // 48 ? ? 48 ? ? ? 4C 8D 05 ? ? ? ? 89

	Memory::CreateHook("GetGammaHook", address, &GetGammaHook::getGamma, &_getGamma);
}