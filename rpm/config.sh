# The version of the main tarball to use
SRCVERSION=4.12
# variant of the kernel-source package, either empty or "-rt"
VARIANT=-rt
# Use old style livepatch package names
LIVEPATCH=kgraft
# buildservice projects to build the kernel against
OBS_PROJECT=SUSE:SLE-12-SP5:Update
IBS_PROJECT=SUSE:SLE-12-SP5:Update
# Bugzilla info
BUGZILLA_SERVER="apibugzilla.suse.com"
BUGZILLA_PRODUCT="SUSE Linux Enterprise Server 12 SP5"
# Check the sorted patches section of series.conf
SORT_SERIES=yes
# Use the old way of building kernel-default-base directly from kernel-binary
SPLIT_BASE=Yes
# Do not sign non-efi kernels (not supported by pesign-obs-integration on older SLE)
SB_EFI_ONLY=Yes
# Modules not listed in supported.conf will abort the kernel build
SUPPORTED_MODULES_CHECK=Yes
# build documentation in HTML format
BUILD_HTML=Yes
# build documentation in PDF format
BUILD_PDF=No
