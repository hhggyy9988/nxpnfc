# ��1�� Git��
git clone ssh://root@111.222.69.132/home/dell/nfcgits/nfc
git clone ssh://root@111.222.69.132/home/dell/nfcgits/secure_element
git clone ssh://root@111.222.69.132/home/dell/nfcgits/nxp
git clone ssh://root@111.222.69.132/home/dell/nfcgits/docs

git������
git config --bool core.bare true
���� vm

git�ͻ���
�ύ
git add  ...
git commit ...
git push origin master

<br/>

# ��2�� ��ֲ
|    |  A����   | H����  | ������  |
|----| ---- | ----  | ---- |
| 1  |  sp/wp        | C++ smart pointer | ��   |
| 2  |  hidl         | OpenHarmony ipc   | ��   |
| 3  |  Android.bp   | BUILD.gn          | С   | 

HIDL�а汾�ţ�OpenHarmony ipc�ް汾��������Ҫ�ϲ�HIDLʵ�֡�
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


��Ҫ��ֲ�Ĵ��룺
$(Android_ROOT)/hardware/nxp/nfc
$(Android_ROOT)/hardware/nxp/secure_element
$(Android_ROOT)/nxp/ese_clients

OpenHarmony IPC
�ο�//myappʵ�� OpenHarmony IPC


|    |  (Android_ROOT)/hardware/nxp/nfc ������  |  Ŀ¼ | δ֪���� |
|----| ---- | |  |
| 1  |  nfc_nci_nxp.so       |  | |
| 2  |  hal_libnfc.so        |  | libchrome |
| 3  |  android.hardware.nfc@1.2-service   | | |

|    |  $(Android_ROOT)/nxp/ese_clients ������  | Ŀ¼| δ֪����|
|----| ---- |  | |
| 1  |  ese_spi_nxp.so       | | |
| 2  |  ls_client.so         |  | |
| 3  |  android.hardware.secure_element@1.1-service   | | |

|    |  $(Android_ROOT)/nxp/ese_clients ������  |  Ŀ¼ |  δ֪���� |
|----| ---- |  | 
| 1  |  ese_client.so       | $(nfc_ROOT)/nxp/ese_clients |  libchrome  |


<br/>

# ��3�� �������

== ����1 ==
���
path: $(nfc_ROOT)/nfc/1.2
��ִ���ļ� "android.hardware.nfc@1.2-service",

patch: $(nfc_ROOT)/nfc
�� nfc_nci_nxp

path: $(nfc_ROOT)/nfc/halimpl/src/halLibnfc/src
�� hal_libnfc

HIDL�ӿڣ�
INfc
open��write��coreInitialized��prediscover��close��controlGranted��powerCycle��getConfig

[1]
open/phNxpNciHal_open
  ��NFC_FAST_BOOT_MODE:
		phNxpNciHal_MinInit  //memset(&nxpncihal_ctrl, 0x00, sizeof(nxpncihal_ctrl));
			phTmlNfc_Init
				phTmlNfc_i2c_open_and_configure //open  PN54X  ioctl PN544_SET_PWR
				phTmlNfc_StartThread  //  phTmlNfc_TmlThread & phTmlNfc_TmlWriterThread

  ����NFC_FAST_BOOT_MODE  //memset(&nxpncihal_ctrl, 0x00, sizeof(nxpncihal_ctrl));
	phNxpNciHal_MinOpen
	  phTmlNfc_Init
				phTmlNfc_i2c_open_and_configure //open  PN54X  ioctl PN544_SET_PWR
				phTmlNfc_StartThread  //  phTmlNfc_TmlThread & phTmlNfc_TmlWriterThread
		phNxpNciHal_client_thread // �߳�
	  phTmlNfc_Read	 �ȴ���ʼ�����.

== ����2 ==
ese-clients:

jcDnld ����

registerSeCallback
doUpdate
�߳� osuHandlerThread
		jcDnld.Init();
		jcDnld.StartDownload()
   			osuUpdateSeqHandler
   					GetJcopOsState
   					seqHandler ������
   					mspSeChannelCallback->open();  //callback
   					mspSeChannelCallback->transceive //callback
		jcDnld.DeInit();
  	mspSeEvtCallback->evtCallback((SESTATUS)retstat);

Client1:
DwpEseUpdater  //��ʵ��(eseClient) static DwpEseUpdater sEseClientInstance;

���ã�
NxpNfcService.cpp (hardware_nxp_nfc\nfc\1.2) :   eseClient.checkIfEseClientUpdateReqd();
NxpNfcService.cpp (hardware_nxp_nfc\nfc\1.2) :   eseClient.doEseUpdateIfReqd();

$(secure_element_ROOT)/ese-clients/src/SpiEseUpdater.cpp --> SpiEseUpdater.cpp
$(secure_element_ROOT)/extns/impl/NxpEse.cpp             --> NxpEse.cpp

DwpEseUpdater.cc/h
	jcDnld.registerSeCallback(sDwpSeChannelCallback, sDwpSeEventCallback);

Client2:
SpiEseUpdater  //��ʵ�� static SpiEseUpdater sEseUpdaterInstance;

SpiEseUpdater.cpp/h
	jcDnld.registerSeCallback(seChannelCallback, seEventCallback);

$(nfc_ROOT)/nfc/halimpl/ese-clients/src/HalLibnfcInteface.cc
��� HalNfcAdaptation.h



