From b247c211ee367cfe975dd54e381094083adfd8d3 Mon Sep 17 00:00:00 2001
From: "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>
Date: Tue, 19 Sep 2017 02:43:13 +0200
Subject: [PATCH] PM: docs: Drop an excess character from devices.rst
Git-commit: b247c211ee367cfe975dd54e381094083adfd8d3
Patch-mainline: v4.14-rc2
References: bsc#1051510

Drop an excess "`" from Documentation/driver-api/pm/devices.rst.

Fixes: 2728b2d2e5be (PM / core / docs: Convert sleep states API document to reST)
Signed-off-by: Rafael J. Wysocki <rafael.j.wysocki@intel.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 Documentation/driver-api/pm/devices.rst |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- a/Documentation/driver-api/pm/devices.rst
+++ b/Documentation/driver-api/pm/devices.rst
@@ -675,7 +675,7 @@ sub-domain of the parent domain.
 
 Support for power domains is provided through the :c:member:`pm_domain` field of
 |struct device|.  This field is a pointer to an object of type
-|struct dev_pm_domain|, defined in :file:`include/linux/pm.h``, providing a set
+|struct dev_pm_domain|, defined in :file:`include/linux/pm.h`, providing a set
 of power management callbacks analogous to the subsystem-level and device driver
 callbacks that are executed for the given device during all power transitions,
 instead of the respective subsystem-level callbacks.  Specifically, if a
