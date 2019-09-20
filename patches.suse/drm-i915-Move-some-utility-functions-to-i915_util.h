From b74eeeb6b1ab6e09311cc4a78c60309f1461dac8 Mon Sep 17 00:00:00 2001
From: Michal Wajdeczko <michal.wajdeczko@intel.com>
Date: Thu, 21 Dec 2017 21:57:29 +0000
Subject: [PATCH] drm/i915: Move some utility functions to i915_util.h
Git-commit: b74eeeb6b1ab6e09311cc4a78c60309f1461dac8
Patch-mainline: v4.16-rc1
References: FATE#322643 bsc#1055900

We have dedicated header file for utility functions and macros.

Signed-off-by: Michal Wajdeczko <michal.wajdeczko@intel.com>
Cc: Chris Wilson <chris@chris-wilson.co.uk>
Cc: Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Reviewed-by: Chris Wilson <chris@chris-wilson.co.uk>
Acked-by: Rodrigo Vivi <rodrigo.vivi@intel.com>
Link: https://patchwork.freedesktop.org/patch/msgid/20171221185334.17396-2-michal.wajdeczko@intel.com
Signed-off-by: Chris Wilson <chris@chris-wilson.co.uk>
Link: https://patchwork.freedesktop.org/patch/msgid/20171221215735.30314-1-chris@chris-wilson.co.uk
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/i915_drv.h   |   15 ---------------
 drivers/gpu/drm/i915/i915_utils.h |   15 +++++++++++++++
 2 files changed, 15 insertions(+), 15 deletions(-)

--- a/drivers/gpu/drm/i915/i915_drv.h
+++ b/drivers/gpu/drm/i915/i915_drv.h
@@ -243,21 +243,6 @@ static inline uint_fixed_16_16_t add_fix
 	return clamp_u64_to_fixed16(interm_sum);
 }
 
-static inline const char *yesno(bool v)
-{
-	return v ? "yes" : "no";
-}
-
-static inline const char *onoff(bool v)
-{
-	return v ? "on" : "off";
-}
-
-static inline const char *enableddisabled(bool v)
-{
-	return v ? "enabled" : "disabled";
-}
-
 enum pipe {
 	INVALID_PIPE = -1,
 	PIPE_A = 0,
--- a/drivers/gpu/drm/i915/i915_utils.h
+++ b/drivers/gpu/drm/i915/i915_utils.h
@@ -140,4 +140,19 @@ static inline void drain_delayed_work(st
 	} while (delayed_work_pending(dw));
 }
 
+static inline const char *yesno(bool v)
+{
+	return v ? "yes" : "no";
+}
+
+static inline const char *onoff(bool v)
+{
+	return v ? "on" : "off";
+}
+
+static inline const char *enableddisabled(bool v)
+{
+	return v ? "enabled" : "disabled";
+}
+
 #endif /* !__I915_UTILS_H */
