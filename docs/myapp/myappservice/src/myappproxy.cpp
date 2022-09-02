#include "myappproxy.h"
#include <iostream>
using namespace std;

namespace OHOS {
namespace myapp {
MyAppProxy::MyAppProxy(const sptr<IRemoteObject> &impl)
    : IRemoteProxy<IMyAppService>(impl)
{
    MYAPP_LOGI(LABEL, "%{public}s", __func__);
}

std::string  MyAppProxy::GetName()
{
    int error;
    MessageParcel dataParcel, replyParcel;
    MessageOption option;

    // 发送请求
    dataParcel.WriteString("get name");
    error = Remote()->SendRequest(GET_NAME, dataParcel, replyParcel, option);
    MYAPP_LOGI(LABEL, "%{public}s: error=%{public}d", __func__, error);
    // 读取回复值
    std::string reply = replyParcel.ReadString();
    return reply;
}

int32_t MyAppProxy::SetBalance(int32_t balance)
{
    int error;
    MessageParcel dataParcel, replyParcel;
    MessageOption option;

    dataParcel.WriteInt32(balance);
    error = Remote()->SendRequest(SET_BALANCE, dataParcel, replyParcel, option);
    MYAPP_LOGI(LABEL, "%{public}s: error=%{public}d", __func__, error);
    int32_t reply = replyParcel.ReadInt32();
    return reply;
}

int32_t MyAppProxy::GetBalance()
{
    int error;
    MessageParcel dataParcel, replyParcel;
    MessageOption option;
    error = Remote()->SendRequest(GET_BALANCE, dataParcel, replyParcel, option);
    MYAPP_LOGI(LABEL, "%{public}s: error=%{public}d", __func__, error);
    int32_t reply = replyParcel.ReadInt32();
    return reply;
}


bool MyAppDeathRecipient::gotDeathRecipient_ = false;

bool MyAppDeathRecipient::GotDeathRecipient()
{
    return gotDeathRecipient_;
}

void MyAppDeathRecipient::OnRemoteDied(const wptr<IRemoteObject> &remote)
{
    gotDeathRecipient_ = true;
    MYAPP_LOGI(LABEL, "%{public}s: recv death notice", __func__);
    cout << "MyAppDeathRecipient::OnRemoteDied" << endl;

}

MyAppDeathRecipient::MyAppDeathRecipient()
{
}

MyAppDeathRecipient::~MyAppDeathRecipient()
{
}

} // namespace myapp
} // namespace OHOS
