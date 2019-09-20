From ead92edbd67c5f51dda7ac90136fbd05464203b6 Mon Sep 17 00:00:00 2001
From: Michal Wajdeczko <michal.wajdeczko@intel.com>
Date: Fri, 6 Oct 2017 09:02:09 +0000
Subject: [PATCH] drm/i915/huc: Fix includes in intel_huc.c
Git-commit: ead92edbd67c5f51dda7ac90136fbd05464203b6
Patch-mainline: v4.15-rc1
References: FATE#322643 bsc#1055900

Fix includes order and make sure we only include required headers.
While here, make intel_huc.h header self-contained.

Signed-off-by: Michal Wajdeczko <michal.wajdeczko@intel.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Cc: Chris Wilson <chris@chris-wilson.co.uk>
Link: https://patchwork.freedesktop.org/patch/msgid/20171006090209.67852-1-michal.wajdeczko@intel.com
Reviewed-by: Chris Wilson <chris@chris-wilson.co.uk>
Signed-off-by: Chris Wilson <chris@chris-wilson.co.uk>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/intel_huc.c |    6 ++++--
 drivers/gpu/drm/i915/intel_huc.h |    2 ++
 2 files changed, 6 insertions(+), 2 deletions(-)

--- a/drivers/gpu/drm/i915/intel_huc.c
+++ b/drivers/gpu/drm/i915/intel_huc.c
@@ -21,9 +21,11 @@
  * IN THE SOFTWARE.
  *
  */
-#include <linux/firmware.h>
+
+#include <linux/types.h>
+
+#include "intel_huc.h"
 #include "i915_drv.h"
-#include "intel_uc.h"
 
 /**
  * DOC: HuC Firmware
--- a/drivers/gpu/drm/i915/intel_huc.h
+++ b/drivers/gpu/drm/i915/intel_huc.h
@@ -25,6 +25,8 @@
 #ifndef _INTEL_HUC_H_
 #define _INTEL_HUC_H_
 
+#include "intel_uc_fw.h"
+
 struct intel_huc {
 	/* Generic uC firmware management */
 	struct intel_uc_fw fw;
