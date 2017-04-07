################################################################################
#
# libiopccommon
#
################################################################################

LIBIOPCCOMMON_VERSION       = <BUILDROOT_VERSION>
LIBIOPCCOMMON_VERSION_MAJOR = 1
LIBIOPCCOMMON_VERSION_MINOR = 0
LIBIOPCCOMMON_SITE          = $(call github,YuanYuLin,libiopccommon,$(LIBIOPCCOMMON_VERSION))
#LIBIOPCCOMMON_SITE          = file:///tmp
#LIBIOPCCOMMON_SOURCE        = libiopccommon.tar.bz2
LIBIOPCCOMMON_LICENSE       = GPLv2+
LIBIOPCCOMMON_LICENSE_FILES = COPYING
LIBIOPCCOMMON_INSTALL_STAGING = YES

LIBIOPCCOMMON_PACKAGE_DIR	= $(BASE_DIR)/packages/libiopccommon

LIBIOPCCOMMON_DEPENDENCIES  = host-pkgconf json-c

LIBIOPCCOMMON_EXTRA_CFLAGS =                                        \
	-DTARGET_LINUX -DTARGET_POSIX                           \


LIBIOPCCOMMON_MAKE_ENV =                       \
	CROSS_COMPILE=$(TARGET_CROSS)       \
	BUILDROOT=$(TOP_DIR)                \
	SDKSTAGE=$(STAGING_DIR)             \
	TARGETFS=$(LIBIOPCCOMMON_PACKAGE_DIR)  \
	TOOLCHAIN=$(HOST_DIR)/usr           \
	HOST=$(GNU_TARGET_NAME)             \
	SYSROOT=$(STAGING_DIR)              \
	JOBS=$(PARALLEL_JOBS)               \
	$(TARGET_CONFIGURE_OPTS)            \
	CFLAGS="$(TARGET_CFLAGS) $(LIBIOPCCOMMON_EXTRA_CFLAGS)"

define LIBIOPCCOMMON_BUILD_CMDS
	$(LIBIOPCCOMMON_MAKE_ENV) $(MAKE) -C $(@D)
endef

define LIBIOPCCOMMON_INSTALL_STAGING_CMDS
	$(INSTALL) -m 0755 -D $(@D)/libiopccommon.so* $(STAGING_DIR)/usr/lib/
	@mkdir -p $(STAGING_DIR)/usr/include/iopccommon
	$(INSTALL) -m 0644 -D $(@D)/include/*.h $(STAGING_DIR)/usr/include/iopccommon
endef

define LIBIOPCCOMMON_INSTALL_TARGET_DIR
	cp -avr $(LIBIOPCCOMMON_PACKAGE_DIR)/usr/lib/* $(TARGET_DIR)/usr/lib/
endef

define LIBIOPCCOMMON_INSTALL_TARGET_CMDS
	rm -rf $(LIBIOPCCOMMON_PACKAGE_DIR)
	mkdir -p $(LIBIOPCCOMMON_PACKAGE_DIR)/usr/lib/
	$(INSTALL) -m 0755 -D $(@D)/libiopccommon.so $(LIBIOPCCOMMON_PACKAGE_DIR)/usr/lib/libiopccommon.so.$(LIBIOPCCOMMON_VERSION_MAJOR).$(LIBIOPCCOMMON_VERSION_MINOR)
	ln -s libiopccommon.so.$(LIBIOPCCOMMON_VERSION_MAJOR).$(LIBIOPCCOMMON_VERSION_MINOR) $(LIBIOPCCOMMON_PACKAGE_DIR)/usr/lib/libiopccommon.so.$(LIBIOPCCOMMON_VERSION_MAJOR)
	ln -s libiopccommon.so.$(LIBIOPCCOMMON_VERSION_MAJOR) $(LIBIOPCCOMMON_PACKAGE_DIR)/usr/lib/libiopccommon.so
	$(LIBIOPCCOMMON_INSTALL_TARGET_DIR)
endef

$(eval $(generic-package))
