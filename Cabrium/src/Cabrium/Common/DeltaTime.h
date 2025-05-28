#pragma once

namespace cabrium {

class DeltaTime {
public:
    DeltaTime(float dt_ = 0.0f) : dt(dt_) {}

    operator float() const { return dt; }

    float getSeconds() const { return dt; }
    float getMilliSeconds() const { return dt * 1000; }

private:
    float dt;
};

} // namespace cabrium