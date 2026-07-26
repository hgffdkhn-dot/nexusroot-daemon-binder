#include "NexusRootService.h"

using namespace com::nexusroot::manager;

ndk::ScopedAStatus NexusRootService::getSuVersion(std::string* _aidl_return) {
    *_aidl_return = "NexusRoot v2.0.0 (NDK Binder)";
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::getSuPath(std::string* _aidl_return) {
    *_aidl_return = "/data/adb/nxr/bin/nr-su";
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::isDaemonAlive(bool* _aidl_return) {
    *_aidl_return = true;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::getWhitelist(std::vector<WhitelistItem>* _aidl_return) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    for (const auto& pair : mWhitelist) {
        _aidl_return->push_back(pair.second);
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::addToWhitelist(const WhitelistItem& item) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    mWhitelist[item.uid] = item;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::removeFromWhitelist(int32_t uid) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    mWhitelist.erase(uid);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::requestAuth(int32_t pid, int32_t uid,
                                                 const std::vector<std::string>& capabilities,
                                                 bool* _aidl_return) {
    std::lock_guard<std::mutex> lock(mWhitelistLock);
    auto it = mWhitelist.find(uid);
    *_aidl_return = (it != mWhitelist.end() && it->second.allowed);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::registerCallback(const std::shared_ptr<INexusRootCallback>& callback) {
    std::lock_guard<std::mutex> lock(mCallbackLock);
    mCallback = callback;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NexusRootService::unregisterCallback() {
    std::lock_guard<std::mutex> lock(mCallbackLock);
    mCallback.reset();
    return ndk::ScopedAStatus::ok();
}
