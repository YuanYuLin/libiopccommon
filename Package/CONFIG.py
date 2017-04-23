import ops
import iopc

def copy_dev_libjsonc(dst_includes, dst_lib, dst_pc):
    src_includes = iopc.getBaseRootFile("/usr/include/json-c")
    ops.copyto(src_includes, dst_includes)
    src_lib = iopc.getBaseRootFile("/lib/arm-linux-gnueabihf/libjson-c.so.2.0.0")
    ops.copyto(src_lib, dst_lib)
    ops.ln(dst_lib, "libjson-c.so.2.0.0", "libjson-c.so.2")
    ops.ln(dst_lib, "libjson-c.so.2.0.0", "libjson-c.so")
    src_pc = iopc.getBaseRootFile("/usr/lib/arm-linux-gnueabihf/pkgconfig/json-c.pc")
    ops.copyto(src_pc, dst_pc)

def copy_dev_libdb53(dst_includes, dst_lib, dst_pc):
    src_includes = iopc.getBaseRootFile("/usr/include/db.h")
    ops.copyto(src_includes, dst_includes)
    src_includes = iopc.getBaseRootFile("/usr/include/db_185.h")
    ops.copyto(src_includes, dst_includes)
    src_lib = iopc.getBaseRootFile("/usr/lib/arm-linux-gnueabihf/libdb.so")
    ops.copyto(src_lib, dst_lib)
    ops.ln(dst_lib, "libdb-5.3.so", "libdb.so")

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
    dst_includes = iopc.getSdkInclude()
    dst_lib = iopc.getSdkLib()
    dst_pc = iopc.getSdkPkgConfig()

    copy_dev_libjsonc(dst_includes, dst_lib, dst_pc)
    copy_dev_libdb53(dst_includes, dst_lib, dst_pc)
    return True

def MAIN_BUILD(args):
    output_dir = args["output_path"]
    iopc.make(output_dir)
    return False

def MAIN_INSTALL(args):
    output_dir = args["output_path"]
    pkg_dir=ops.getEnv("PACKAGES_DIR")
    iopc.installBin(args["pkg_name"], ops.path_join(output_dir, "libiopccommon.so"), "/usr/lib")
    iopc.packPkg(args["pkg_name"])
    iopc.installPkg(ops.path_join(pkg_dir, args["pkg_name"]))
    return False

def MAIN_CLEAN_BUILD(args):
    output_dir = args["output_path"]
    return False

def MAIN(args):
    output_dir = args["output_path"]

