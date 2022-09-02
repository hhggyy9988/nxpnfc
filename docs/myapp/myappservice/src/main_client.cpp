#include "myappproxy.h"
#include "ipc_skeleton.h"
#include "system_ability_definition.h"
#include "iservice_registry.h"
#include <iostream>
using namespace std;
using namespace OHOS;
using namespace OHOS::myapp;
#undef LOG_TAG
#define LOG_TAG "MyAppClient"

static constexpr OHOS::HiviewDFX::HiLogLabel LABEL = { LOG_CORE, LOG_DOMAIN, LOG_TAG };

sptr<IMyAppService> ConnectService()
{
    auto saMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (saMgr == nullptr) {
        MYAPP_LOGE(LABEL, "get registry fail");
        return nullptr;
    }

    sptr<IRemoteObject> object = saMgr->GetSystemAbility(MY_APP_SERVICE_ID);
    sptr<IMyAppService> client = nullptr;
    if (object != nullptr) {
        MYAPP_LOGE(LABEL, "Got MyApp Service object");
        sptr<IRemoteObject::DeathRecipient> death(new MyAppDeathRecipient());
        object->AddDeathRecipient(death.GetRefPtr());
        // client 是一个proxy对象客户端类
        client = iface_cast<IMyAppService>(object);
    }

    if (client == nullptr) {
        MYAPP_LOGE(LABEL, "Could not find MyApp Service!");
        return nullptr;
    }

    return client;
}


int main(int argc, char *argv[])
{
    int result = 0;

    auto client = ConnectService();

    std::string name = client->GetName();
    cout << "name: " << name << endl;
    int32_t ret = client->SetBalance(1024);
    cout << "after setbalance1: " << ret << endl;
    ret = client->SetBalance(1024);
    cout << "after setbalance2: " << ret << endl;
    ret = client->GetBalance();
    cout << "getbalance: " << ret << endl;

    MYAPP_LOGE(LABEL, "get from service: %{public}d", result);
    IPCSkeleton::JoinWorkThread();
    return 0;
}