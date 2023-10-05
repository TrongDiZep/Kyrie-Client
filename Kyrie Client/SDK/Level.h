#pragma once
#include <string>
#include "../Utils/Utils.h"
class LevelSettings;
class LevelData;
class Experiments;

class Actor;

class Level {
public:

	std::vector<Actor*> getRuntimeActorList() {
		return Utils::CallVFunc<317, std::vector<Actor*>>(this);
	}

};


