#ifndef NEXUSROOT_SERVICE_H
#define NEXUSROOT_SERVICE_H

#include <binder/BinderService.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/Vector.h>
#include <map>
#include <mutex>
#include <android/log.h>

#include "com/nexusroot/manager/INexusRootService.h"
#include "com/nexusroot/manager/INexusRootCallback.h"

using namespace android;

class NexusRootService : public BinderService<NexusRootService>,
                         public com::nexusroot::manager::INexusRootService::BnInterface {
public:
    // Binder 服务注册
    static constexpr const char* SERVICE_NAME = "nexusroot";

    // INexusRootService 接口实现
    binder::Status getSuVersion(std::string* _aidl_return) override;
    binder::Status getSuPath(std::string* _aidl_return) override;
    binder::Status isDaemonAlive(bool* _aidl_return) override;

    binder::Status getWhitelist(std::vector<com::nexusroot::manager::WhitelistItem>* _aidl_return) override;
    binder::Status addToWhitelist(const com::nexusroot::manager::WhitelistItem& item) override;
    binder::Status removeFromWhitelist(int32_t uid) override;

    binder::Status requestAuth(int32_t pid, int32_t uid,
                               const std::vector<std::string>& capabilities,
                               bool* _aidl_return) override;

    binder::Status registerCallback(const sp<com::nexusroot::manager::INexusRootCallback>& callback) override;
    binder::Status unregisterCallback() override;

private:
    std::mutex mWhitelistLock;
    std::map<int, com::nexusroot::manager::WhitelistItem> mWhitelist; // uid -> item
    sp<com::nexusroot::manager::INexusRootCallback> mCallback;
    std::mutex mCallbackLock;
};

#endif