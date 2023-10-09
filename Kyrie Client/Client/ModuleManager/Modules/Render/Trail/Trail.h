#pragma once
#include "../../Module.h"

struct Ball {
	Vec3<float> pos;
	float duration;
	Ball(const Vec3<float>& Pos, const float& Duration) {
		this->pos = Pos;
		this->duration = Duration;
	}
};

class Trail : public Module {
private:
	std::vector<std::shared_ptr<Ball>> ballList;
	float deltaTime = 0.f;
	float delay = 0.25f;
	float duration = 7.5f;
public:
	Trail();
	~Trail();

	virtual const char* getModuleName() override;
	virtual void onImGui3DRender(ImDrawList* d, glmatrixf* refdef) override;
};