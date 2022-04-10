#pragma once

#include "root.h"
#include "SM_Time.h"
#include "Job.h"

class JobManager {
private:
    inline static std::list<Job> pendingJobs;

public:
    static void onUpdate();

    static inline void addJob (const Job& job) {
        pendingJobs.push_back(job);
    }
};