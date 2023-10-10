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
		ballList.emplace_back(new Ball(mc.getLocalPlayer()->getRenderPositionComponent()->eyePos.add(0.f, -1.5f, 0.f), duration));
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
		ball->startDuration = lerpSync(ball->startDuration, 1.f, 0.05f);
		if (refdef->OWorldToScreen(mc.getClientInstance()->levelRender->levelRenderPlayer->origin, ball->pos, renderPos, mc.getClientInstance()->getFov(), mc.getClientInstance()->guiData->windowSizeReal)) {
			float dist = ball->pos.sub(0.f, -1.5f, 0.f).dist(mc.getLocalPlayer()->getRenderPositionComponent()->eyePos);
			if (dist < 1.5f) {
				Vec3<float> diff = ball->pos.sub(mc.getLocalPlayer()->getRenderPositionComponent()->eyePos.add(0.f, -1.5f, 0.f));
				ball->pos.x = lerpSync(ball->pos.x, ball->pos.x + diff.x, 0.05f);
				ball->pos.y = lerpSync(ball->pos.y, ball->pos.y + diff.y, 0.05f);
				ball->pos.z = lerpSync(ball->pos.z, ball->pos.z + diff.z, 0.05f);
			}
			else if (dist >= 2.f) {
				ball->pos.x = lerpSync(ball->pos.x, ball->RealPos.x, 0.1f);
				ball->pos.y = lerpSync(ball->pos.y, ball->RealPos.y, 0.1f);
				ball->pos.z = lerpSync(ball->pos.z, ball->RealPos.z, 0.1f);
			}
			float size = 1.f / (dist / 2.5f);
			if (size > 1.f) size = 1.f;
			else if (size < 0.25f) size = 0.25f;
			float renderSize = 10.f * size * ball->startDuration;
			if (renderSize < 1.f) renderSize = 4.f;
			d->AddCircleFilled(ImVec2(renderPos.x, renderPos.y), renderSize, ImColor(color.r, color.g, color.b, (int)(225 * duration * ball->startDuration)));
			d->AddShadowCircle(ImVec2(renderPos.x, renderPos.y), renderSize, ImColor(color.r, color.g, color.b, (int)(150 * duration * ball->startDuration)), 80.f * size * ball->startDuration, ImVec2(0.f, 0.f));
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