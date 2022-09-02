#ifndef MYAPP_PROXY_H
#define MYAPP_PROXY_H
#include <functional>
#include <iostream>
#include <map>
#include "imyappservice.h"
#include "message_parcel.h"
#include "parcel.h"
#include "iremote_broker.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace myapp {

class MyAppProxy : public IRemoteProxy<IMyAppService> {
public:
    explicit MyAppProxy(const sptr<IRemoteObject> &impl);
    ~MyAppProxy() = default;
    std::string  GetName() override;

    int32_t SetBalance(int32_t balance) override;

    int32_t GetBalance() override;
private:
    static constexpr OHOS::HiviewDFX::HiLogLabel LABEL = { LOG_CORE, LOG_DOMAIN, "MyAppProxy" };
    static inline BrokerDelegator<MyAppProxy> delegator_;
};

class MyAppDeathRecipient : public IRemoteObject::DeathRecipient {
public:
    virtual void OnRemoteDied(const wptr<IRemoteObject> &remote) override;
    MyAppDeathRecipient();
    virtual ~MyAppDeathRecipient();
    static bool GotDeathRecipient();
    static bool gotDeathRecipient_;
private:
    static constexpr HiviewDFX::HiLogLabel LABEL = { LOG_CORE, LOG_DOMAIN, "MyAppDeathRecipient" };
};

} // namespace myapp
} // namespace OHOS
#endif // MYAPP_STUB_H
