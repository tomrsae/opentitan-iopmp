package(default_visibility = ["//visibility:public"])

load(
    "//rules:autogen.bzl",
    "autogen_hjson_c_header",
    "autogen_hjson_rust_header",
)

autogen_hjson_c_header(
    name = "iopmp_c_regs",
    srcs = [
        "iopmp.hjson",
    ],
)

autogen_hjson_rust_header(
    name = "iopmp_rust_regs",
    srcs = [
        "iopmp.hjson",
    ],
)

filegroup(
    name = "all_files",
    srcs = glob(["**"]),
)
