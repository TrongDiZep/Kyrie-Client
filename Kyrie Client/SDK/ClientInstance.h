#pragma once
#include "GuiData.h"
#include "../Utils/Utils.h"
#include "Player.h"

class ClientInstance {
private:
	uintptr_t** VTable;
public:
	
	glmatrixf* getbadrefdef() {
		return (glmatrixf*)((uintptr_t)(this) + 0x330);
	}
	
	GuiData* getGuiData() {
		return *reinterpret_cast<GuiData**>(reinterpret_cast<__int64>(this) + 0x560);
	}

	Vec2<float>* getMousePos() {
		return reinterpret_cast<Vec2<float>*>((uintptr_t)this + 0x498);
	}

	Vec2<float> getFov() {
		Vec2<float> fov;
		fov.x = *reinterpret_cast<float*>((uintptr_t)(this) + 0x6D0);
		fov.y = *reinterpret_cast<float*>((uintptr_t)(this) + 0x6DC);
		return fov;
	}

	Player* getLocalPlayer() {
		return Utils::CallVFunc<27, Player*>(this);
	}

	void grabMouse() {
		Utils::CallVFunc<322, void>(this);
	}

	void releasebMouse() {
		Utils::CallVFunc<323, void>(this);
	}
};