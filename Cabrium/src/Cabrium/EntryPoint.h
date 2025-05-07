#pragma once

#ifdef CABRIUM_PLATFORM_WINDOWS

extern cabrium::Application* cabrium::CreateApplication();

int main(int argc, char** argv) {

	cabrium::Application* app = cabrium::CreateApplication();

	app->Run();

	delete app;

	return 0;
}

#endif // CABRIUM_PLATFORM_WINDOWS
