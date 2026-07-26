#include "NexusRootService.h"
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

using namespace android;

int main() {
    // 设置 Binder 线程池
    ProcessState::self()->setThreadPoolMaxThreadCount(4);
    // 注册服务
    NexusRootService::publishAndJoinThreadPool();
    return 0;
}