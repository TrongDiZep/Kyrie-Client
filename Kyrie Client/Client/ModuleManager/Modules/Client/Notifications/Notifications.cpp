#include "Notifications.h"

Notifications::Notifications() : Module(0x0, Category::CLIENT, "Notifications") {
}

const char* Notifications::getModuleName() {
	return "Notifications";
}

bool Notifications::isVisible() {
	return false;
}