SRC_URI_remove = "git://github.com/varigit/freertos-variscite.git;protocol=git;branch=${MCUXPRESSO_BRANCH};"
#
#SRC_URI_append = "git://github.com/btclark1/freertos-variscite.git;protocol=git;branch=${MCUXPRESSO_BRANCH};"
SRC_URI_append = "git://${BSPDIR}/local_repos/freertos-variscite/;protocol=file;branch=${MCUXPRESSO_BRANCH};"

#SRCREV = "392e27fd2d2639113c7f7e3a950c02020dba7894"
SRCREV = "${AUTOREV}"         

#CM_DEMOS_append = " multicore_examples/rpmsg_lite_str_echo_bm"
CM_DEMOS_append = " driver_examples/gpio/led_output"



