#include "NexusRootService.h"
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>


using namespace android;

binder::Status NexusRootService::getSuVersion(std::string* _aidl_return) {
    *_aidl_return = "NexusRoot v2.0.0 (Binder)";
    return binder::Status::ok();
}

binder::Status NexusRootService::getSuPath(std::string* _aidl_return) {
    *_aidl_return = "/data/adb/nxr/bin/nr-su";
    return binder::Status::ok();
}

binder::Status NexusRootService::isDaemonAlive(bool* _aidl_return) {
    *_aidl_return = true;
    return binder::Status::ok();
}

binder::Status NexusRootService::getWhitelist(std::vector<com::nexusroot::manager::WhitelistItem>* _aidl_return) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    for (const auto& pair : mWhitelist) {
        _aidl_return->push_back(pair.second);
    }
    return binder::Status::ok();
}

binder::Status NexusRootService::addToWhitelist(const com::nexusroot::manager::WhitelistItem& item) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    mWhitelist[item.uid] = item;
    return binder::Status::ok();
}

binder::Status NexusRootService::removeFromWhitelist(int32_t uid) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    mWhitelist.erase(uid);
    return binder::Status::ok();
}

binder::Status NexusRootService::requestAuth(int32_t pid, int32_t uid,
                                             const std::vector<std::string>& capabilities,
                                             bool* _aidl_return) {
    // 简化实现：检查白名单是否允许
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    auto it = mWhitelist.find(uid);
    if (it != mWhitelist.end() && it->second.allowed) {
        // 这里将来实现真实的能力注入（setns/prctl）
        *_aidl_return = true;
    } else {
        *_aidl_return = false;
    }
    return binder::Status::ok();
}

binder::Status NexusRootService::registerCallback(const sp<com::nexusroot::manager::INexusRootCallback>& callback) {
    std::lock_guard<std::mutex> lock(mCallbackLock);
    mCallback = callback;
    return binder::Status::ok();
}

binder::Status NexusRootService::unregisterCallback() {
    std::lock_guard<std::mutex> lock(mCallbackLock);
    mCallback.clear();
    return binder::Status::ok();
}
