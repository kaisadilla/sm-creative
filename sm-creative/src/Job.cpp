#include "Job.h"

Job::Job(const f32 timer, const std::function<void()>& callback) :
    timer(timer),
    callback(callback)
{}
