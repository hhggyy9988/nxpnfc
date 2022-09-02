#ifndef MYAPP_SERVICE_H
#define MYAPP_SERVICE_H
#include "myappservice.h"
#include "myappstub.h"
#include <iostream>
#include "ipc_skeleton.h"
#include "system_ability.h"

namespace OHOS {
namespace myapp {
// 服务端类
class MyappService : public SystemAbility, public MyAppStub {
public:
    DECLARE_SYSTEM_ABILITY(MyappService);
    DISALLOW_COPY_AND_MOVE(MyappService);
    explicit MyappService(int32_t systemAbilityId, bool runOnCreate = true);
    ~MyappService() override;
    // 响应客户端请求的处理函数
    std::string  GetName() override;

    int32_t SetBalance(int32_t balance) override;

    int32_t GetBalance() override;

    void OnStart() override;
    void OnStop() override;
private:
    int32_t m_balance;
    static constexpr HiviewDFX::HiLogLabel LABEL = { LOG_CORE, LOG_DOMAIN, "MyappService" };
};

}
}
#endif // MYAPP_SERVICE_H