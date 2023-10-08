#include "LevelRenderPlayerUpdateCameraHook.h"
#include "../../Memory.h"
#include "../../../ImGui/imgui.h"
#include "../../../Client/Client.h"
#include "../../GameData/GameData.h"

typedef __int64(__fastcall* updateCamera)(LevelRenderPlayer*, __int64);
updateCamera _updateCamera;

__int64 LevelRenderPlayerUpdateCameraHook::updateCamera(LevelRenderPlayer* a1, __int64 a2) {
	return _updateCamera(a1, a2);
}

void LevelRenderPlayerUpdateCameraHook::init() {
	uintptr_t address = Memory::getBase() + 0x13B6260;  // 40 55 56 57 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48

	Memory::CreateHook("LevelRenderPlayerUpdateCameraHook", address, &LevelRenderPlayerUpdateCameraHook::updateCamera, &_updateCamera);
}