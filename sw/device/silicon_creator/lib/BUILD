# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load(
    "@bazel_skylib//lib:dicts.bzl",
    "dicts",
)
load("//rules:autogen.bzl", "autogen_chip_info")
load("//rules:cross_platform.bzl", "dual_cc_device_library_of", "dual_cc_library", "dual_inputs")
load("//rules/opentitan:defs.bzl", "OPENTITAN_CPU")
load(
    "//rules/opentitan:defs.bzl",
    "EARLGREY_TEST_ENVS",
    "fpga_params",
    "opentitan_test",
    "verilator_params",
)

package(default_visibility = ["//visibility:public"])

dual_cc_library(
    name = "boot_data",
    srcs = dual_inputs(
        device = ["boot_data.c"],
        host = ["mock_boot_data.cc"],
    ),
    hdrs = dual_inputs(
        host = ["mock_boot_data.h"],
        shared = ["boot_data.h"],
    ),
    deps = dual_inputs(
        device = [
            "//hw/ip/otp_ctrl/data:otp_ctrl_c_regs",
            "//hw/top_earlgrey/ip_autogen/flash_ctrl:flash_ctrl_c_regs",
            "//hw/top_earlgrey/sw/autogen:top_earlgrey",
            "//sw/device/lib/base:hardened",
            "//sw/device/lib/base:memory",
        ],
        host = [
            "//sw/device/lib/base:global_mock",
            "//sw/device/silicon_creator/testing:rom_test",
            "@googletest//:gtest",
        ],
        shared = [
            ":error",
            ":nonce",
            "//sw/device/lib/base:macros",
            "//sw/device/silicon_creator/lib/drivers:flash_ctrl",
            "//sw/device/silicon_creator/lib/drivers:hmac",
            "//sw/device/silicon_creator/lib/drivers:lifecycle",
            "//sw/device/silicon_creator/lib/drivers:otp",
        ],
    ),
)

cc_test(
    name = "boot_data_unittest",
    srcs = ["boot_data_unittest.cc"],
    deps = [
        dual_cc_device_library_of(":boot_data"),
        "@googletest//:gtest_main",
    ],
)

opentitan_test(
    name = "boot_data_functest",
    srcs = ["boot_data_functest.c"],
    exec_env = dicts.add(
        dicts.omit(
            EARLGREY_TEST_ENVS,
            # Not intended for ROM_EXT environments.
            ["//hw/top_earlgrey:fpga_cw310_sival_rom_ext"],
        ),
        {
            "//hw/top_earlgrey:fpga_cw310_sival": None,
        },
    ),
    verilator = verilator_params(
        timeout = "eternal",
        tags = ["flaky"],
        # test sometimes times out when run in batches in 3600s
    ),
    deps = [
        ":boot_data",
        "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        "//sw/device/lib/testing/test_framework:ottf_main",
        "//sw/device/silicon_creator/lib/drivers:flash_ctrl",
    ],
)

cc_library(
    name = "boot_log",
    srcs = ["boot_log.c"],
    hdrs = ["boot_log.h"],
    deps = [
        ":boot_data",
        ":nonce",
        "//sw/device/lib/base:macros",
        "//sw/device/silicon_creator/lib:chip_info",
        "//sw/device/silicon_creator/lib:error",
        "//sw/device/silicon_creator/lib/drivers:hmac",
        "//sw/device/silicon_creator/lib/ownership:datatypes",
    ],
)

cc_test(
    name = "boot_log_unittest",
    srcs = ["boot_log_unittest.cc"],
    deps = [
        ":boot_log",
        "//sw/device/silicon_creator/lib:chip_info",
        "//sw/device/silicon_creator/lib/drivers:hmac",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "cfi",
    hdrs = [
        "cfi.h",
    ],
    deps = [
        "//sw/device/lib/base:hardened",
    ],
)

cc_library(
    name = "epmp_defs",
    hdrs = [
        "epmp_defs.h",
    ],
)

cc_library(
    name = "epmp_state",
    srcs = ["epmp_state.c"],
    hdrs = [
        "epmp_state.h",
    ],
    deps = [
        ":epmp_defs",
        ":error",
        "//sw/device/lib/base:csr",
        "//sw/device/lib/base:hardened",
    ],
)

cc_test(
    name = "epmp_unittest",
    srcs = ["epmp_unittest.cc"],
    deps = [
        ":epmp_state",
        "//sw/device/silicon_creator/testing:rom_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "epmp_test_unlock",
    srcs = ["epmp_test_unlock.c"],
    hdrs = ["epmp_test_unlock.h"],
    target_compatible_with = [OPENTITAN_CPU],
    deps = [
        ":epmp_state",
        "//sw/device/lib/arch:device",
        "//sw/device/lib/base:csr",
    ],
)

cc_library(
    name = "error",
    hdrs = ["error.h"],
    deps = [
        "//sw/device/lib/base:bitfield",
        "//sw/device/lib/base:hardened",
        "//sw/device/lib/base/internal:status",
    ],
)

cc_library(
    name = "error_unittest_util",
    hdrs = ["error_unittest_util.h"],
)

cc_test(
    name = "error_unittest",
    srcs = ["error_unittest.cc"],
    deps = [
        ":error",
        ":error_unittest_util",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "irq_asm",
    srcs = ["irq_asm.S"],
    target_compatible_with = [OPENTITAN_CPU],
    deps = [
        "//hw/ip/aon_timer/data:aon_timer_c_regs",
        "//hw/top_earlgrey/ip_autogen/flash_ctrl:flash_ctrl_c_regs",
        "//hw/top_earlgrey/ip_autogen/pwrmgr:pwrmgr_c_regs",
        "//hw/top_earlgrey/ip_autogen/rstmgr:rstmgr_c_regs",
        "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        "//sw/device/lib/base:multibits",
    ],
)

opentitan_test(
    name = "irq_asm_functest",
    srcs = ["irq_asm_functest.c"],
    broken = fpga_params(tags = ["broken"]),
    exec_env = dicts.add(
        EARLGREY_TEST_ENVS,
        {
            # FIXME broken in sival ROM_EXT, remove this line when fixed. See #21706.
            "//hw/top_earlgrey:fpga_cw310_sival_rom_ext": "broken",
        },
    ),
    verilator = verilator_params(
        timeout = "long",
    ),
    deps = [
        ":error",
        ":irq_asm",
        "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        "//sw/device/lib/base:abs_mmio",
        "//sw/device/lib/testing:rstmgr_testutils",
        "//sw/device/lib/testing/test_framework:ottf_main",
        "//sw/device/silicon_creator/lib/drivers:retention_sram",
        "//sw/device/silicon_creator/lib/drivers:rstmgr",
        "//sw/device/silicon_creator/lib/drivers:watchdog",
    ],
)

cc_library(
    name = "keymgr_binding",
    hdrs = ["keymgr_binding_value.h"],
)

cc_library(
    name = "dbg_print",
    srcs = ["dbg_print.c"],
    hdrs = ["dbg_print.h"],
    deps = [
        ":epmp_defs",
        ":error",
        "//sw/device/lib/base:bitfield",
        "//sw/device/lib/base:csr",
        "//sw/device/lib/base:macros",
        "//sw/device/silicon_creator/lib/drivers:uart",
    ],
)

cc_test(
    name = "dbg_print_unittest",
    srcs = ["dbg_print_unittest.cc"],
    deps = [
        ":dbg_print",
        ":error",
        "//sw/device/silicon_creator/lib/drivers:uart",
        "@googletest//:gtest_main",
    ],
)

dual_cc_library(
    name = "manifest",
    srcs = dual_inputs(
        device = ["manifest.c"],
        host = ["mock_manifest.cc"],
    ),
    hdrs = dual_inputs(
        host = ["mock_manifest.h"],
        shared = ["manifest.h"],
    ),
    deps = dual_inputs(
        device = [
            "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        ],
        host = [
            "//sw/device/lib/base:global_mock",
            "//sw/device/silicon_creator/testing:rom_test",
            "@googletest//:gtest",
        ],
        shared = [
            ":epmp_state",
            ":error",
            ":keymgr_binding",
            "//sw/device/lib/base:macros",
            "//sw/device/silicon_creator/lib/drivers:lifecycle",
            "//sw/device/silicon_creator/lib/sigverify:ecdsa_p256_key",
            "//sw/device/silicon_creator/lib/sigverify:rsa_key",
            "//sw/device/silicon_creator/lib/sigverify:spx_key",
            "//sw/device/silicon_creator/lib/base:chip",
        ],
    ),
)

dual_cc_library(
    name = "manifest_def",
    srcs = dual_inputs(device = ["manifest_def.c"]),
    hdrs = ["manifest_def.h"],
    target_compatible_with = dual_inputs(device = [OPENTITAN_CPU]),
    deps = [
        ":manifest",
        "//sw/device/lib/base:macros",
    ],
    # The manifest section should be populated anytime this is added as a
    # dependency, even if the manifest is not referenced by software.
    alwayslink = True,
)

filegroup(
    name = "english_breakfast_test_framework_manifest_def_srcs",
    srcs = [
        "manifest_def.c",
        "manifest_def.h",
    ],
)

cc_test(
    name = "manifest_unittest",
    srcs = ["manifest_unittest.cc"],
    local_defines = ["MANIFEST_UNIT_TEST_"],
    deps = [
        dual_cc_device_library_of(":manifest"),
        "//sw/device/lib/base:csr",
        "//sw/device/silicon_creator/testing:rom_test",
        "@googletest//:gtest_main",
    ],
)

filegroup(
    name = "english_breakfast_test_rom_manifest_srcs",
    srcs = [
        "manifest.c",
        "manifest.h",
    ],
)

autogen_chip_info(name = "chip_info")

dual_cc_library(
    name = "shutdown",
    srcs = dual_inputs(
        device = ["shutdown.c"],
        host = ["mock_shutdown.cc"],
    ),
    hdrs = dual_inputs(
        host = ["mock_shutdown.h"],
        shared = ["shutdown.h"],
    ),
    deps = dual_inputs(
        host = [
            "//sw/device/lib/base:global_mock",
            "//sw/device/silicon_creator/testing:rom_test",
            "@googletest//:gtest",
        ],
        shared = [
            ":chip_info",
            ":error",
            ":epmp_defs",
            ":stack_utilization",
            "//sw/device/lib/base:hardened",
            "//sw/device/lib/base:macros",
            "//sw/device/silicon_creator/lib/drivers:lifecycle",
            "//hw/ip/keymgr/data:keymgr_c_regs",
            "//hw/ip/lc_ctrl/data:lc_ctrl_c_regs",
            "//hw/ip/otp_ctrl/data:otp_ctrl_c_regs",
            "//hw/ip/rv_core_ibex/data:rv_core_ibex_c_regs",
            "//hw/ip/sram_ctrl/data:sram_ctrl_c_regs",
            "//hw/ip/uart/data:uart_c_regs",
            "//hw/top_earlgrey:alert_handler_c_regs",
            "//hw/top_earlgrey/ip_autogen/flash_ctrl:flash_ctrl_c_regs",
            "//hw/top_earlgrey/ip_autogen/rstmgr:rstmgr_c_regs",
            "//hw/top_earlgrey/sw/autogen:top_earlgrey",
            "//sw/device/silicon_creator/lib/drivers:retention_sram",
            "//sw/device/lib/arch:device",
            "//sw/device/lib/base:abs_mmio",
            "//sw/device/lib/base:bitfield",
            "//sw/device/lib/base:csr",
            "//sw/device/lib/base:memory",
            "//sw/device/lib/base:multibits",
            "//sw/device/lib/base:stdasm",
            "//sw/device/silicon_creator/lib/drivers:alert",
            "//sw/device/silicon_creator/lib/drivers:otp",
        ],
    ),
)

cc_test(
    name = "shutdown_unittest",
    srcs = ["shutdown_unittest.cc"],
    deps = [
        dual_cc_device_library_of(":shutdown"),
        "//sw/device/silicon_creator/testing:rom_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "bootstrap",
    srcs = ["bootstrap.c"],
    hdrs = ["bootstrap.h"],
    deps = [
        ":stack_utilization",
        "//sw/device/lib/base:bitfield",
        "//sw/device/lib/base:hardened",
        "//sw/device/silicon_creator/lib:error",
        "//sw/device/silicon_creator/lib/drivers:flash_ctrl",
        "//sw/device/silicon_creator/lib/drivers:rstmgr",
        "//sw/device/silicon_creator/lib/drivers:spi_device",
    ],
)

filegroup(
    name = "bootstrap_srcs",
    srcs = [
        "bootstrap.c",
        "bootstrap.h",
    ],
)

cc_library(
    name = "bootstrap_fuzzer_util",
    srcs = ["bootstrap_fuzzer_util.cc"],
    hdrs = ["bootstrap_fuzzer_util.h"],
    deps = [
        "//hw/top_earlgrey/ip_autogen/flash_ctrl:flash_ctrl_c_regs",
        "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        "//sw/device/lib/base:hardened",
        "//sw/device/silicon_creator/lib:bootstrap_unittest_util",
        "//sw/device/silicon_creator/lib/drivers:flash_ctrl",
        "//sw/device/silicon_creator/lib/drivers:otp",
        "//sw/device/silicon_creator/lib/drivers:spi_device",
        "@abseil-cpp//absl/types:optional",
        "@abseil-cpp//absl/types:span",
    ],
)

cc_library(
    name = "bootstrap_unittest_util",
    srcs = ["bootstrap_unittest_util.cc"],
    hdrs = ["bootstrap_unittest_util.h"],
    deps = [
        ":bootstrap",
        "//hw/ip/gpio/data:gpio_c_regs",
        "//hw/ip/otp_ctrl/data:otp_ctrl_c_regs",
        "//hw/top_earlgrey/ip_autogen/flash_ctrl:flash_ctrl_c_regs",
        "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        "//sw/device/silicon_creator/lib/base:chip",
    ],
)

cc_library(
    name = "attestation",
    hdrs = ["attestation.h"],
)

cc_library(
    name = "nonce",
    srcs = ["nonce.c"],
    hdrs = ["nonce.h"],
    deps = ["//sw/device/silicon_creator/lib/drivers:rnd"],
)

cc_library(
    name = "otbn_boot_services",
    srcs = ["otbn_boot_services.c"],
    hdrs = ["otbn_boot_services.h"],
    # This target uses OTBN pointers internally, so it cannot work host-side.
    target_compatible_with = [OPENTITAN_CPU],
    deps = [
        ":attestation",
        "//sw/device/lib/base:macros",
        "//sw/device/silicon_creator/lib:dbg_print",
        "//sw/device/silicon_creator/lib:error",
        "//sw/device/silicon_creator/lib/base:sec_mmio",
        "//sw/device/silicon_creator/lib/base:util",
        "//sw/device/silicon_creator/lib/drivers:flash_ctrl",
        "//sw/device/silicon_creator/lib/drivers:hmac",
        "//sw/device/silicon_creator/lib/drivers:keymgr",
        "//sw/device/silicon_creator/lib/drivers:otbn",
        "//sw/device/silicon_creator/lib/sigverify:ecdsa_p256_key",
        "//sw/device/silicon_creator/lib/sigverify:rsa_key",
        "//sw/otbn/crypto:boot",
    ],
)

opentitan_test(
    name = "otbn_boot_services_functest",
    srcs = ["otbn_boot_services_functest.c"],
    broken = fpga_params(tags = ["broken"]),
    exec_env = dicts.add(
        EARLGREY_TEST_ENVS,
        {
            "//hw/top_earlgrey:fpga_cw310_sival": None,
            # See #21706, expects keymgr state 0 so not working after ROM_EXT.
            "//hw/top_earlgrey:fpga_cw310_sival_rom_ext": "broken",
        },
    ),
    # This test can take > 40 minutes, so mark it manual as it shouldn't run
    # in CI/nightlies.
    verilator = verilator_params(tags = ["manual"]),
    # This target uses OTBN pointers internally, so it cannot work host-side.
    deps = [
        ":otbn_boot_services",
        "//hw/top_earlgrey/sw/autogen:top_earlgrey",
        "//sw/device/lib/crypto/drivers:entropy",
        "//sw/device/lib/testing:keymgr_testutils",
        "//sw/device/lib/testing/test_framework:ottf_main",
        "//sw/device/silicon_creator/manuf/lib:flash_info_fields",
    ],
)

cc_library(
    name = "xmodem",
    srcs = ["xmodem.c"],
    hdrs = ["xmodem.h"],
    deps = [
        ":error",
        "//sw/device/lib/base:hardened",
        "//sw/device/silicon_creator/lib/drivers:uart",
    ],
)

cc_library(
    name = "xmodem_testlib",
    srcs = [
        "xmodem.c",
        "xmodem.h",
    ],
    hdrs = ["xmodem_testlib.h"],
    defines = ["XMODEM_TESTLIB=1"],
    deps = [
        ":error",
        "//sw/device/lib/base:hardened",
    ],
)

cc_library(
    name = "stack_utilization",
    srcs = ["stack_utilization.c"],
    hdrs = [
        "stack_utilization.h",
        "stack_utilization_asm.h",
    ],
    deps = [
        "//sw/device/silicon_creator/lib/drivers:uart",
    ],
)
