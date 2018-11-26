#
# Copyright (C) 2016 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Release name
PRODUCT_RELEASE_NAME := N1

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/Santin/N1/device_N1.mk)
$(call inherit-product, device/Santin/N1/prop.mk)

TARGET_SCREEN_HEIGHT := 1920
TARGET_SCREEN_WIDTH := 1080

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := N1
PRODUCT_NAME := lineage_N1
PRODUCT_BRAND := Santin
PRODUCT_MODEL := Santin_N1
PRODUCT_MANUFACTURER := Santin

# Google client ID property.
PRODUCT_GMS_CLIENTID_BASE := android-Santin

PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_FINGERPRINT=Neffos/TP908A/N1:7.1.1/N4F26M/2434:user/release-keys \
    PRIVATE_BUILD_DESC="full_tk6757_66_n1-user 7.1.1 N4F26M 2434 release-keys"

# Available languages
PRODUCT_LOCALES := ru_RU en_US en_AU en_IN fr_FR it_IT es_ES et_EE de_DE nl_NL cs_CZ pl_PL ja_JP zh_TW zh_CN zh_HK ko_KR nb_NO es_US da_DK el_GR tr_TR pt_PT pt_BR sv_SE bg_BG ca_ES en_GB fi_FI hi_IN hr_HR hu_HU in_ID iw_IL lt_LT lv_LV ro_RO sk_SK sl_SI sr_RS vi_VN tl_PH ar_EG fa_IR th_TH sw_TZ ms_MY af_ZA zu_ZA am_ET en_XA ar_XB fr_CA km_KH lo_LA ne_NP si_LK mn_MN hy_AM az_AZ ka_GE my_MM mr_IN ml_IN is_IS mk_MK ky_KG eu_ES gl_ES bn_BD ta_IN kn_IN te_IN uz_UZ ur_PK kk_KZ sq_AL gu_IN pa_IN be_BY bs_BA
