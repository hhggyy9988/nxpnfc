#ifndef MYAPP_STUB_H
#define MYAPP_STUB_H
#include <functional>
#include <iostream>
#include <map>
#include "iremote_stub.h"
#include "imyappservice.h"
#include "message_parcel.h"
#include "parcel.h"

namespace OHOS {
namespace myapp {

class MyAppStub : public IRemoteStub<IMyAppService> {
public:
    // 响应客户端请求的入口函数
    int OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
        MessageOption &option) override;
private:
    static constexpr HiviewDFX::HiLogLabel LABEL = { LOG_CORE, LOG_DOMAIN, "MyAppStub" };
};

} // namespace myapp
} // namespace OHOS
#endif // MYAPP_STUB_H
