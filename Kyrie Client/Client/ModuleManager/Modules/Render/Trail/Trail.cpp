#include "Trail.h"
#include "../../../../Client.h"

Trail::Trail() : Module(0x0, Category::RENDER, nullptr) {
	registerFloatSetting("Delay", &delay, delay, 0.f, 2.f);
	registerFloatSetting("Duration", &duration, duration, 1.f, 10.f);
}

Trail::~Trail() {
	ballList.clear();
}

const char* Trail::getModuleName() {
	return "Trail";
}

void Trail::onImGui3DRender(ImDrawList* d, glmatrixf* refdef) {
	
	static Colors* colorsMod = client->moduleMgr->getModule<Colors>();
	if (deltaTime > delay) {
		ballList.emplace_back(new Ball(mc.getLocalPlayer()->getRenderPositionComponent()->eyePos.add(0.f, -1.f, 0.f), duration));
		deltaTime = 0.f;
	}
	else {
		deltaTime += ImGui::GetIO().DeltaTime;
	}
	for (int i = 0; i < ballList.size(); i++) {
		std::shared_ptr<Ball>& ball = ballList[i];

		Vec2<float> renderPos;
		float duration = 1.f;
		if (ball->duration < 1.f) duration = ball->duration;
		Color color = colorsMod->getColor();
		color = ColorUtils::getRainbowColor(3.f, 1.f, 1.f, -i * 30.f);
		if (refdef->OWorldToScreen(mc.getClientInstance()->levelRender->levelRenderPlayer->origin, ball->pos, renderPos, mc.getClientInstance()->getFov(), mc.getClientInstance()->guiData->windowSizeReal)) {
			float dist = ball->pos.dist(mc.getLocalPlayer()->getRenderPositionComponent()->eyePos);
			float size = 1.f / (dist / 4.f);
			if (size > 1.f) size = 1.f;
			else if (size < 0.25f) size = 0.25f;
			d->AddCircleFilled(ImVec2(renderPos.x, renderPos.y), 5.f * size, ImColor(color.r, color.g, color.b, (int)(255 * duration)));
			d->AddShadowCircle(ImVec2(renderPos.x, renderPos.y), 5.f * size, ImColor(color.r, color.g, color.b, (int)(255 * duration)), 100.f * size, ImVec2(0.f, 0.f));
		}

		if (ball->duration >= 0.f) {
			ball->duration -= ImGui::GetIO().DeltaTime;
		}
		else {
			ballList.erase(ballList.begin() + i);
			i--;
		}
	}
}