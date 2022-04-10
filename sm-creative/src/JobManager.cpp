#include "JobManager.h"

void JobManager::onUpdate () {
    std::list<Job>::iterator it = pendingJobs.begin();

    while (it != pendingJobs.end()) {
        it->timer -= Time::getDeltaTime();
        if (it->timer <= 0) {
            it->callback();
            it = pendingJobs.erase(it);
        }
        else {
            it++;
        }
    }
}
