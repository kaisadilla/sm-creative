#pragma once

#include <functional>

#include "root.h"

class Job {
    friend class JobManager;

private:
    f32 timer;
    std::function<void()> callback;

public:
    Job(const f32 delay, const std::function<void()>& callback);
};