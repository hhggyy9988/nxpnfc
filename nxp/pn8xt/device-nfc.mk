#####
##### NXP NFC Device Configuration makefile
######

NXP_NFC_HOST := $(TARGET_PRODUCT)
NXP_NFC_HW := pn553
NXP_RF_REQ := true
NXP_NFC_PLATFORM := pn8x
NXP_VENDOR_DIR := nxp

NXP_NFC_FW_LIB64 := true

# These are the hardware-specific features
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:system/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/android.hardware.nfc.hcef.xml:system/etc/permissions/android.hardware.nfc.hcef.xml \
    frameworks/native/data/etc/android.hardware.nfc.ese.xml:system/etc/permissions/android.hardware.nfc.ese.xml \
    frameworks/native/data/etc/android.hardware.nfc.uicc.xml:system/etc/permissions/android.hardware.nfc.uicc.xml \
    frameworks/native/data/etc/com.nxp.mifare.xml:system/etc/permissions/com.nxp.mifare.xml \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    vendor/nxp/frameworks/com.nxp.nfc.xml:system/etc/permissions/com.nxp.nfc.xml \
    vendor/nxp/pn8xt/manifest.xml:vendor/manifest.xml

ifeq ($(AGENEW_NXP_NFC_PN553_BEAM),yes)
  PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.sofware.nfc.beam.xml:system/etc/permissions/android.sofware.nfc.beam.xml
endif

# SE config files
PRODUCT_COPY_FILES += \
    hardware/nxp/secure_element/libese-spi/p73/libese-nxp-P73.conf:vendor/etc/libese-nxp.conf


ifeq ($(NXP_NFC_HW),pn81T)
PRODUCT_COPY_FILES += \
    hardware/nxp/nfc/halimpl/libnfc-nci_NCI2_0.conf:system/etc/libnfc-nci.conf \
    hardware/nxp/nfc/halimpl/libnfc-nxp-PN81T_example.conf:vendor/etc/libnfc-nxp.conf

    ifeq ($(NXP_RF_REQ),true)
    PRODUCT_COPY_FILES += \
        hardware/nxp/nfc/halimpl/libnfc-nxp_RF-PN81T_example.conf:vendor/libnfc-nxp_RF.conf
    endif
else ifeq ($(NXP_NFC_HW),pn553)
ifeq ($(AGENEW_NXP_NFC_PN553_EXT_PWR_5V), yes)
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/conf/libnfc-nci.conf:vendor/etc/libnfc-nci.conf \
    vendor/nxp/pn8xt/conf/libnfc-nxp-5V.conf:vendor/etc/libnfc-nxp.conf \
    vendor/nxp/pn8xt/conf/libnfc-nxp_RF.conf:vendor/etc/libnfc-nxp_RF.conf
else
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/conf/libnfc-nci.conf:vendor/etc/libnfc-nci.conf \
    vendor/nxp/pn8xt/conf/libnfc-nxp.conf:vendor/etc/libnfc-nxp.conf \
    vendor/nxp/pn8xt/conf/libnfc-nxp_RF.conf:vendor/etc/libnfc-nxp_RF.conf
endif
else ifeq ($(NXP_NFC_HW),pn557)
ifeq ($(AGENEW_NXP_NFC_PN557_EXT_PWR_5V), yes)
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/conf_557/libnfc-nci.conf:vendor/etc/libnfc-nci.conf \
    vendor/nxp/pn8xt/conf_557/libnfc-nxp-5V.conf:vendor/etc/libnfc-nxp.conf \
    vendor/nxp/pn8xt/conf_557/libnfc-nxp_RF.conf:vendor/etc/libnfc-nxp_RF.conf
else
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/conf_557/libnfc-nci.conf:vendor/etc/libnfc-nci.conf \
    vendor/nxp/pn8xt/conf_557/libnfc-nxp.conf:vendor/etc/libnfc-nxp.conf \
    vendor/nxp/pn8xt/conf_557/libnfc-nxp_RF.conf:vendor/etc/libnfc-nxp_RF.conf
endif
else
PRODUCT_COPY_FILES += \
    hardware/nxp/nfc/halimpl/libnfc-nci.conf:system/etc/libnfc-nci.conf
    hardware/nxp/nfc/halimpl/libnfc-nxp-PN80T_example.conf:vendor/etc/libnfc-nxp.conf \

    ifeq ($(NXP_RF_REQ),true)
    PRODUCT_COPY_FILES += \
        hardware/nxp/nfc/halimpl/libnfc-nxp_RF-PN80T_example.conf:vendor/libnfc-nxp_RF.conf
    endif

endif

######NXP_NFC_FW_LIB
ifeq ($(NXP_NFC_FW_LIB64),true)
ifeq ($(NXP_NFC_HW),pn557)
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/fw/64-bit/libpn557_fw_64bits.so:vendor/lib/libpn557_fw.so \
    vendor/nxp/pn8xt/fw/64-bit/libpn557_fw_64bits.so:vendor/lib64/libpn557_fw.so \
    vendor/nxp/pn8xt/fw/64-bit/libpn557_fw_64bits.so:system/lib/libpn557_fw.so \
    vendor/nxp/pn8xt/fw/64-bit/libpn557_fw_64bits.so:system/lib64/libpn557_fw.so
else
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/fw/64-bit/libpn553_fw_11_01_18_prod_Eval1_SLALM_CFG2_EFM_40x20_64bits.so:vendor/lib/libpn553_fw.so \
    vendor/nxp/pn8xt/fw/64-bit/libpn553_fw_11_01_18_prod_Eval1_SLALM_CFG2_EFM_40x20_64bits.so:vendor/lib64/libpn553_fw.so \
    vendor/nxp/pn8xt/fw/64-bit/libpn553_fw_11_01_18_prod_Eval1_SLALM_CFG2_EFM_40x20_64bits.so:system/lib/libpn553_fw.so \
    vendor/nxp/pn8xt/fw/64-bit/libpn553_fw_11_01_18_prod_Eval1_SLALM_CFG2_EFM_40x20_64bits.so:system/lib64/libpn553_fw.so    
endif
else
PRODUCT_COPY_FILES += \
    vendor/nxp/pn8xt/fw/32-bit/libpn553_fw_11_01_18_prod_Eval1_SLALM_CFG2_EFM_40x20_32bits.so:vendor/lib/libpn553_fw.so
endif

#PRODUCT_COPY_FILES += \
#    vendor/nxp/pn8xt/fw/64-bit/libpn553_fw_11_01_14_prod_Eval1_SLALM_CFG2_EFM_40x20_64bits.so:vendor/lib/libpn553_fw.so \
#    vendor/nxp/pn8xt/fw/64-bit/libpn553_fw_11_01_14_prod_Eval1_SLALM_CFG2_EFM_40x20_64bits.so:vendor/lib64/libpn553_fw.so

# NFC Init Files
PRODUCT_COPY_FILES += \
     vendor/$(NXP_VENDOR_DIR)/pn8xt/hw/init.$(NXP_NFC_PLATFORM).nfc.rc:vendor/etc/init/init.$(NXP_NFC_PLATFORM).nfc.rc \
     vendor/$(NXP_VENDOR_DIR)/pn8xt/hw/init.$(NXP_NFC_PLATFORM).se.rc:vendor/etc/init/init.$(NXP_NFC_PLATFORM).se.rc \

# NFC packages
PRODUCT_PACKAGES += \
    libnfc-nci \
    NfcNci \
    Tag \
    android.hardware.nfc@1.0-impl \
    com.nxp.nfc \
    nfc_nci.$(NXP_NFC_PLATFORM) \

PRODUCT_PACKAGES += \
	android.hardware.nfc@1.2-service 
#android.hardware.secure_element@1.1-service 
#android.hardware.wired_se@1.0-service 

ifeq ($(ENABLE_TREBLE), true)
PRODUCT_PACKAGES += \
	vendor.nxp.nxpnfc@1.0-impl \
	vendor.nxp.nxpnfc@1.0-service
endif

PRODUCT_PROPERTY_OVERRIDES += \
		ro.hardware.nfc_nci=$(NXP_NFC_PLATFORM)


BOARD_SEPOLICY_DIRS += vendor/$(NXP_VENDOR_DIR)/pn8xt/sepolicy \
                       vendor/$(NXP_VENDOR_DIR)/pn8xt/sepolicy/nfc \
                       vendor/$(NXP_VENDOR_DIR)/pn8xt/sepolicy/se \
                       vendor/$(NXP_VENDOR_DIR)/pn8xt/sepolicy/wiredse \
