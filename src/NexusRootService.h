#ifndef NEXUSROOT_SERVICE_H
#define NEXUSROOT_SERVICE_H

#include <com/nexusroot/manager/INexusRootService.h>
#include <android/binder_ibinder.h>
#include <android/log.h>
#include <mutex>
#include <map>
#include <string>

class NexusRootService : public com::nexusroot::manager::INexusRootService {
public:
    // 必须实现的纯虚函数
    ndk::ScopedAStatus getSuVersion(std::string* _aidl_return) override;
    ndk::ScopedAStatus getSuPath(std::string* _aidl_return) override;
    ndk::ScopedAStatus isDaemonAlive(bool* _aidl_return) override;

    ndk::ScopedAStatus getWhitelist(std::vector<com::nexusroot::manager::WhitelistItem>* _aidl_return) override;
    ndk::ScopedAStatus addToWhitelist(const com::nexusroot::manager::WhitelistItem& item) override;
    ndk::ScopedAStatus removeFromWhitelist(int32_t uid) override;

    ndk::ScopedAStatus requestAuth(int32_t pid, int32_t uid,
                                   const std::vector<std::string>& capabilities,
                                   bool* _aidl_return) override;

    ndk::ScopedAStatus registerCallback(const std::shared_ptr<com::nexusroot::manager::INexusRootCallback>& callback) override;
    ndk::ScopedAStatus unregisterCallback() override;

private:
    std::mutex mWhitelistLock;
    std::map<int32_t, com::nexusroot::manager::WhitelistItem> mWhitelist;
    std::shared_ptr<com::nexusroot::manager::INexusRootCallback> mCallback;
    std::mutex mCallbackLock;
};

#endif
