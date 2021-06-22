# Copyright (C) 2021 Variscite
DESCRIPTION = "Variscite i.MX Cortex M4/M7 Firmware Demos"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://COPYING-BSD-3;md5=0858ec9c7a80c4a2cf16e4f825a2cc91"
SECTION = "BSP"

SRC_URI = " \
    file://variscite-rproc-linux \
    file://variscite-rproc-u-boot \
    file://variscite-rproc-common.sh \
    file://variscite-rproc.conf \
"

# inherit cmake
DEPENDS = "cmake-native"

S = "${WORKDIR}/git"

MCUXPRESSO_BRANCH = "mcuxpresso_sdk_${PV}-var01"

CM_BOARD="INVALID"
CM_BOARD_mx8mn="som_mx8mn"

# If remoteproc is used to reload ddr firmware, special disable_cache firmware
# must be reloaded between stop and start comments
# For Example:
#   echo cm_rpmsg_lite_pingpong_rtos_linux_remote.elf.ddr_debug > /sys/class/remoteproc/remoteproc0/firmware
#   echo start > /sys/class/remoteproc/remoteproc0/state
#   echo stop > /sys/class/remoteproc/remoteproc0/state

#   echo cm_disable_cache.elf.debug > /sys/class/remoteproc/remoteproc0/firmware
#   echo start > /sys/class/remoteproc/remoteproc0/state
#   echo stop > /sys/class/remoteproc/remoteproc0/state

#   echo cm_rpmsg_lite_str_echo_rtos_imxcm4.elf.ddr_debug > /sys/class/remoteproc/remoteproc0/firmware
#   echo start > /sys/class/remoteproc/remoteproc0/state
#   echo stop > /sys/class/remoteproc/remoteproc0/state
CM_DEMOS_DISABLE_CACHE = ""

DISABLE_CACHE_PATCH="disable_cache.patch"

do_compile() {
    # Configure ARMGCC
    export ARMGCC_DIR="${WORKDIR}/${CM_GCC}"

    # Copy and patch hello_world demo to disable_cache demo
    if [ -e "${WORKDIR}/${DISABLE_CACHE_PATCH}" ]; then
        # Copy hello_world demo
        cp -r ${S}/boards/${CM_BOARD}/demo_apps/hello_world/ ${S}/boards/${CM_BOARD}/demo_apps/disable_cache
        # Rename hello_world strings to disable_cache
        grep -rl hello_world ${S}/boards/${CM_BOARD}/demo_apps/disable_cache | xargs sed -i 's/hello_world/disable_cache/g'
        # Rename hello_world files to disable_cache
        find ${S}/boards/${CM_BOARD}/demo_apps/disable_cache/ -name '*hello_world*' -exec sh -c 'mv "$1" "$(echo "$1" | sed s/hello_world/disable_cache/)"' _ {} \;
    fi

    # Build firmware to reset cache
    if [ -e "${WORKDIR}/${DISABLE_CACHE_PATCH}" ]; then
        # Apply patch to disable cache for machine
        cd ${S} && git apply ${WORKDIR}/${DISABLE_CACHE_PATCH}

        # Build the firmware
        for CM_DEMO in ${CM_DEMOS_DISABLE_CACHE}; do
                compile_fw "${S}/boards/${CM_BOARD}/${CM_DEMO}/armgcc"
        done
    fi
}

do_install() {
    readonly CM_BUILD_TARGETS=" \
        debug \
        ddr_debug \
    "


}

FILES_${PN} = " \
	${sysconfdir}/remoteproc \
	${nonarch_base_libdir}/firmware \
	/boot \
"

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

# Firmware files are run on M4/M7
INSANE_SKIP = "arch"
