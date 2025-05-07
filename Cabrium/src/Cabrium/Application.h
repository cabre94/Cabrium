#pragma once

#include "Core.h"

namespace cabrium {

class CBRM_API Application {
public:
	Application();
	virtual ~Application();

	void Run();

};

// To be defined in a client
Application* CreateApplication();

} // namespace cabrium 