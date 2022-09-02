#include "myappservice.h"
#include "system_ability_definition.h"
using namespace std;


namespace OHOS {
namespace myapp {
REGISTER_SYSTEM_ABILITY_BY_ID(MyappService, MY_APP_SERVICE_ID, true)

MyappService::MyappService(int32_t systemAbilityId, bool runOnCreate)
    :SystemAbility(systemAbilityId, runOnCreate)
    , m_balance(0)
{
    MYAPP_LOGI(LABEL, "%{public}s: SaId=%{public}d", __func__, systemAbilityId);
}

MyappService::~MyappService(){
    
}

std::string  MyappService::GetName()
{
    return std::string("myapp_name");
}

int32_t MyappService::SetBalance(int32_t balance)
{
    m_balance += balance;
    return m_balance;
}

int32_t MyappService::GetBalance()
{
    return m_balance;
}

void MyappService::OnStart()
{
    MYAPP_LOGI(LABEL, "%{public}s OnStart", __func__);
    // 这个sa_main调用动态库的时候会调用，用来启动注册
    // 里面调用了samgrProxy->AddSystemAbility(saId_, publishObj_, saExtra);
    bool res = Publish(this);
    if (res == false) {
        MYAPP_LOGE(LABEL, "%{public}s failed", __func__);
    }
    return;
}

void MyappService::OnStop()
{
    MYAPP_LOGI(LABEL, "%{public}s OnStop", __func__);
}

}
}