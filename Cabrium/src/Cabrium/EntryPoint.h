#pragma once

#ifdef CABRIUM_PLATFORM_WINDOWS

extern cabrium::Application* cabrium::CreateApplication();

int main(int argc, char** argv) {

	cabrium::Log::Init();
	CBRM_CORE_WARN("Core Logger");
	CBRM_INFO("Client Logger var = {0}", 42);

	cabrium::Application* app = cabrium::CreateApplication();

	app->Run();

	delete app;

	return 0;
}

#endif // CABRIUM_PLATFORM_WINDOWS
