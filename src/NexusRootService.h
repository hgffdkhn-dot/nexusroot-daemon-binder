#ifndef NEXUSROOT_SERVICE_H
#define NEXUSROOT_SERVICE_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <android/log.h>

#include <com/nexusroot/manager/INexusRootService.h>
#include <com/nexusroot/manager/INexusRootCallback.h>

using namespace android;
using namespace com::nexusroot::manager;

class NexusRootService : public BnNexusRootService {
public:
    // 接口方法声明（与之前相同）
    Status getSuVersion(std::string* _aidl_return) override;
    Status getSuPath(std::string* _aidl_return) override;
    Status isDaemonAlive(bool* _aidl_return) override;

    Status getWhitelist(std::vector<WhitelistItem>* _aidl_return) override;
    Status addToWhitelist(const WhitelistItem& item) override;
    Status removeFromWhitelist(int32_t uid) override;

    Status requestAuth(int32_t pid, int32_t uid,
                       const std::vector<std::string>& capabilities,
                       bool* _aidl_return) override;

    Status registerCallback(const sp<INexusRootCallback>& callback) override;
    Status unregisterCallback() override;

private:
    std::mutex mWhitelistLock;
    std::map<int32_t, WhitelistItem> mWhitelist;
    sp<INexusRootCallback> mCallback;
    std::mutex mCallbackLock;
};

#endif
