SRC_URI += "file://defconfig"
KBUILD_DEFCONFIG_imx8mn-var-som = ""

SRC_URI += "file://imx8mn-var-som-symphony-m7.dtb"
KBUILD_KERNEL_DEVICETREE_imx8mn-var-som = ""
    
#KERNEL_SRC = "git://github.com/btclark1/linux-imx.git;protocol=git"
KERNEL_SRC = "git://${BSPDIR}/local_repos/linux-imx;protocol=file"

SRCBRANCH = "5.4-2.1.x-imx_var01"

#SRCREV = "d7ba3cf4ab766ceccaf4ab11511ff8ce48477e54"
SRCREV = "${AUTOREV}"

