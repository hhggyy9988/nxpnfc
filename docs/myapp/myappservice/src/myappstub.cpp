#include "myappstub.h"
using namespace std;

// #include "iremote_proxy.h"
// #include "ipc_skeleton.h"
// #include "ipc_file_descriptor.h"
// #include "ipc_test_helper.h"
// #include "if_system_ability_manager.h"
// #include "iservice_registry.h"
// #include "system_ability_definition.h"

namespace OHOS {
namespace myapp {

int MyAppStub::OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
    MessageOption &option)
{
    MYAPP_LOGI(LABEL, "%{public}s: code=%{public}d, flags=%{public}d", __func__, code, option.GetFlags());
    int retvalue = 0;
    switch(code)
    {
        case GET_NAME:
        {
            std::string info;
            uint32_t len=data.ReadString(info);
            if(len > 0)
            {
                cout << "GET_NAME: " << info << endl;
                std::string&& name = GetName(); 
                reply.WriteString(name);
            }
        }
            break;
        case SET_BALANCE:
        {
            int32_t value = 0;
            int32_t ret=data.ReadInt32(value);
            if (ret > 0)
            {
                int32_t value2 = SetBalance(value);
                reply.WriteInt32(value2);
            }
        }
            break;
        case GET_BALANCE:
        {
            int32_t value = GetBalance();
            reply.WriteInt32(value);
        }
            break;
        default:
            retvalue = IPCObjectStub::OnRemoteRequest(code, data, reply, option);
            break;
    }

    return retvalue;
}

}
}