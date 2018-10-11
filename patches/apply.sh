#!/bin/sh

echo $1
rootdirectory="$PWD"
# ---------------------------------

dirs="bionic frameworks/av frameworks/base frameworks/native frameworks/opt/telephony system/core system/netd system/sepolicy packages/apps/FMRadio/jni/fmr packages/apps/Settings packages/apps/Snap/res/values"

for dir in $dirs ; do
	cd $rootdirectory
	cd $dir
        echo "\n${RED}Applying ${NC}$dir ${RED}patches...${NC}\n"
	git apply -v $rootdirectory/device/Santin/N1/patches/$dir/*.patch
done

# -----------------------------------
echo "Changing to build directory..."
cd $rootdirectory


### "bionic frameworks/av frameworks/base frameworks/native frameworks/opt/telephony system/core system/netd system/sepolicy packages/apps/FMRadio/jni/fmr packages/apps/Settings packages/apps/Snap/res/values vendor/cmsdk"
