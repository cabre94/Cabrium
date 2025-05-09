#pragma once

#include "Common/Basic.h"

namespace cabrium {

class CBRM_API Application {
public:
    Application();
    virtual ~Application();

    void run();
};

// To be defined in a client
Application *createApplication();

} // namespace cabrium