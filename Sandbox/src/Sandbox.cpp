#include "Cabrium.h"

class Sandbox : public cabrium::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

cabrium::Application* cabrium::CreateApplication() {
	return new Sandbox();
}
