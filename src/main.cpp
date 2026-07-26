#include "NexusRootService.h"
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <android/log.h>

int main() {
    __android_log_print(ANDROID_LOG_INFO, "nexusrootd", "Starting NexusRoot NDK service...");

    auto service = ndk::SharedRefBase::make<NexusRootService>();
    binder_status_t status = AServiceManager_addService(service->asBinder().get(), "nexusroot");

    if (status == STATUS_OK) {
        __android_log_print(ANDROID_LOG_INFO, "nexusrootd", "Service 'nexusroot' registered.");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "nexusrootd", "Failed to register service: %d", status);
        return 1;
    }

    // 加入 Binder 线程池
    ABinderProcess_setThreadPoolMaxThreadCount(4);
    ABinderProcess_startThreadPool();
    ABinderProcess_joinThreadPool();

    return 0;
}
