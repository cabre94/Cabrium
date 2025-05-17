#pragma once

#ifdef CBRM_PLATFORM_WINDOWS

extern cabrium::Application *cabrium::createApplication();

int main(int argc, char **argv) {

    cabrium::Log::init();
    CBRM_CORE_INFO("Core Logger");
    CBRM_INFO("Client Logger var = {0}", 42);

    cabrium::Application *app = cabrium::createApplication();

    app->run();

    delete app;

    return 0;
}

#endif // CBRM_PLATFORM_WINDOWS
