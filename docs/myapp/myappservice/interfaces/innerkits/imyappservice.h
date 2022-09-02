#ifndef IMYAPP_SERVICE_H
#define IMYAPP_SERVICE_H

#include <iostream>
#include <string>
#include "iremote_broker.h"
#include "iremote_proxy.h"
#include "hilog/log.h"
namespace OHOS {
namespace myapp {

#undef LOG_DOMAIN
#define LOG_DOMAIN    0xD000000

#define MYAPP_LOGW(TAG, ...) (void)OHOS::HiviewDFX::HiLog::Warn(TAG, __VA_ARGS__)
#define MYAPP_LOGE(TAG, ...) (void)OHOS::HiviewDFX::HiLog::Error(TAG, __VA_ARGS__)
#define MYAPP_LOGI(TAG, ...) (void)OHOS::HiviewDFX::HiLog::Info(TAG, __VA_ARGS__)


class IMyAppService : public OHOS::IRemoteBroker {
public:
    enum {
        GET_NAME,
        SET_BALANCE,
        GET_BALANCE
    };

    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.MyApp.IMyAppService");
public:
    virtual std::string GetName() = 0;

    virtual int32_t SetBalance(int32_t balance) = 0;

    virtual int32_t GetBalance() = 0;

};
} // namespace myapp
} // namespace OHOS
#endif // IMYAPP_SERVICE_H
