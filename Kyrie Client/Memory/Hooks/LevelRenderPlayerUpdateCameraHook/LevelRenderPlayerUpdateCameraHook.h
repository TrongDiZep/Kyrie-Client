#pragma once
#include "../../../SDK/LevelRenderPlayer.h"
class LevelRenderPlayerUpdateCameraHook {
private:
	static __int64 updateCamera(LevelRenderPlayer* a1, __int64 a2);
public:
	static void init();
};
