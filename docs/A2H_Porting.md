# 第1节 Git库
git clone ssh://root@111.222.69.132/home/dell/nfcgits/nfc
git clone ssh://root@111.222.69.132/home/dell/nfcgits/secure_element
git clone ssh://root@111.222.69.132/home/dell/nfcgits/nxp
git clone ssh://root@111.222.69.132/home/dell/nfcgits/docs

git服务器
git config --bool core.bare true
密码 vm

git客户端
提交
git add  ...
git commit ...
git push origin master

<br/>

# 第2节 移植
|    |  A特性   | H特性  | 工作量  |
|----| ---- | ----  | ---- |
| 1  |  sp/wp        | C++ smart pointer | 中   |
| 2  |  hidl         | OpenHarmony ipc   | 大   |
| 3  |  Android.bp   | BUILD.gn          | 小   | 

HIDL有版本号，OpenHarmony ipc无版本，可能需要合并HIDL实现。
::android::hardware::nfc::V1_0::INfc
::android::hardware::nfc::V1_1::INfc
::android::hardware::nfc::V1_2::INfc
::android::hardware::nfc::V1_0::INfcClientCallback
::android::hardware::nfc::V1_1::INfcClientCallback

::android::hardware::secure_element::V1_0::ISecureElement
::android::hardware::secure_element::V1_1::ISecureElement
::android::hardware::secure_element::V1_0::ISecureElementHalCallback
::android::hardware::secure_element::V1_1::ISecureElementHalCallback

::vendor::nxp::nxpnfc::V1_0::INxpNfc


需要移植的代码：
$(Android_ROOT)/hardware/nxp/nfc
$(Android_ROOT)/hardware/nxp/secure_element
$(Android_ROOT)/nxp/ese_clients

OpenHarmony IPC
参考//myapp实现 OpenHarmony IPC


|    |  (Android_ROOT)/hardware/nxp/nfc 的内容  |  目录 | 未知依赖 |
|----| ---- | |  |
| 1  |  nfc_nci_nxp.so       |  | |
| 2  |  hal_libnfc.so        |  | libchrome |
| 3  |  android.hardware.nfc@1.2-service   | | |

|    |  $(Android_ROOT)/nxp/ese_clients 的内容  | 目录| 未知依赖|
|----| ---- |  | |
| 1  |  ese_spi_nxp.so       | | |
| 2  |  ls_client.so         |  | |
| 3  |  android.hardware.secure_element@1.1-service   | | |

|    |  $(Android_ROOT)/nxp/ese_clients 的内容  |  目录 |  未知依赖 |
|----| ---- |  | 
| 1  |  ese_client.so       | $(nfc_ROOT)/nxp/ese_clients |  libchrome  |


<br/>

# 第3节 代码分析

== 分析1 ==
入口
path: $(nfc_ROOT)/nfc/1.2
可执行文件 "android.hardware.nfc@1.2-service",

patch: $(nfc_ROOT)/nfc
库 nfc_nci_nxp

path: $(nfc_ROOT)/nfc/halimpl/src/halLibnfc/src
库 hal_libnfc

HIDL接口：
INfc
open、write、coreInitialized、prediscover、close、controlGranted、powerCycle、getConfig

[1]
open/phNxpNciHal_open
  是NFC_FAST_BOOT_MODE:
		phNxpNciHal_MinInit  //memset(&nxpncihal_ctrl, 0x00, sizeof(nxpncihal_ctrl));
			phTmlNfc_Init
				phTmlNfc_i2c_open_and_configure //open  PN54X  ioctl PN544_SET_PWR
				phTmlNfc_StartThread  //  phTmlNfc_TmlThread & phTmlNfc_TmlWriterThread

  不是NFC_FAST_BOOT_MODE  //memset(&nxpncihal_ctrl, 0x00, sizeof(nxpncihal_ctrl));
	phNxpNciHal_MinOpen
	  phTmlNfc_Init
				phTmlNfc_i2c_open_and_configure //open  PN54X  ioctl PN544_SET_PWR
				phTmlNfc_StartThread  //  phTmlNfc_TmlThread & phTmlNfc_TmlWriterThread
		phNxpNciHal_client_thread // 线程
	  phTmlNfc_Read	 等待初始化完成.

== 分析2 ==
ese-clients:

jcDnld 对象

registerSeCallback
doUpdate
线程 osuHandlerThread
		jcDnld.Init();
		jcDnld.StartDownload()
   			osuUpdateSeqHandler
   					GetJcopOsState
   					seqHandler 操作？
   					mspSeChannelCallback->open();  //callback
   					mspSeChannelCallback->transceive //callback
		jcDnld.DeInit();
  	mspSeEvtCallback->evtCallback((SESTATUS)retstat);

Client1:
DwpEseUpdater  //单实例(eseClient) static DwpEseUpdater sEseClientInstance;

引用：
NxpNfcService.cpp (hardware_nxp_nfc\nfc\1.2) :   eseClient.checkIfEseClientUpdateReqd();
NxpNfcService.cpp (hardware_nxp_nfc\nfc\1.2) :   eseClient.doEseUpdateIfReqd();

$(secure_element_ROOT)/ese-clients/src/SpiEseUpdater.cpp --> SpiEseUpdater.cpp
$(secure_element_ROOT)/extns/impl/NxpEse.cpp             --> NxpEse.cpp

DwpEseUpdater.cc/h
	jcDnld.registerSeCallback(sDwpSeChannelCallback, sDwpSeEventCallback);

Client2:
SpiEseUpdater  //单实例 static SpiEseUpdater sEseUpdaterInstance;

SpiEseUpdater.cpp/h
	jcDnld.registerSeCallback(seChannelCallback, seEventCallback);

$(nfc_ROOT)/nfc/halimpl/ese-clients/src/HalLibnfcInteface.cc
入口 HalNfcAdaptation.h



