#include "Job.h"

Job::Job(const f32 delay, const std::function<void()>& callback) :
    timer(delay),
    callback(callback)
{}
