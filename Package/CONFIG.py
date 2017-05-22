import ops
import iopc

def MAIN_ENV(args):
    pkg_path = args["pkg_path"]
    output_dir = args["output_path"]
    return False

def MAIN_EXTRACT(args):
    pkg_dir = args["pkg_path"]
    output_dir = args["output_path"]
    iopc.extractSrc(pkg_dir, output_dir)

    return False

def MAIN_CONFIGURE(args):
    output_dir = args["output_path"]
    return True

def MAIN_BUILD(args):
    output_dir = args["output_path"]
    iopc.make(output_dir)
    return False

def MAIN_INSTALL(args):
    output_dir = args["output_path"]
    iopc.installBin(args["pkg_name"], ops.path_join(output_dir, "libiopccommon.so"), "usr/lib")
    iopc.installBin(args["pkg_name"], ops.path_join(output_dir, "include/."), ops.path_join("include", args["pkg_name"]))
    return False

def MAIN_CLEAN_BUILD(args):
    output_dir = args["output_path"]
    return False

def MAIN(args):
    output_dir = args["output_path"]

