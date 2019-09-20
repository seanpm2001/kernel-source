From 46f1e8b3de827057cdbeb9a78e6994b1f0386474 Mon Sep 17 00:00:00 2001
From: Michal Wajdeczko <michal.wajdeczko@intel.com>
Date: Mon, 16 Oct 2017 14:47:10 +0000
Subject: [PATCH] drm/i915: Move intel_guc_wopcm_size to intel_guc.c
Git-commit: 46f1e8b3de827057cdbeb9a78e6994b1f0386474
Patch-mainline: v4.15-rc1
References: FATE#322643 bsc#1055900

Function intel_guc_wopcm_size didn't fit well in the old place.
With this move upcoming cleanup will be simpler.

Suggested-by: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Signed-off-by: Michal Wajdeczko <michal.wajdeczko@intel.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Cc: Sagar Arun Kamble <sagar.a.kamble@intel.com>
Reviewed-by: Chris Wilson <chris@chris-wilson.co.uk>
Signed-off-by: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Link: https://patchwork.freedesktop.org/patch/msgid/20171016144724.17244-2-michal.wajdeczko@intel.com
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/intel_guc.c        |   11 +++++++++++
 drivers/gpu/drm/i915/intel_guc_loader.c |   11 -----------
 2 files changed, 11 insertions(+), 11 deletions(-)

--- a/drivers/gpu/drm/i915/intel_guc.c
+++ b/drivers/gpu/drm/i915/intel_guc.c
@@ -263,3 +263,14 @@ err:
 	i915_gem_object_put(obj);
 	return vma;
 }
+
+u32 intel_guc_wopcm_size(struct drm_i915_private *dev_priv)
+{
+	u32 wopcm_size = GUC_WOPCM_TOP;
+
+	/* On BXT, the top of WOPCM is reserved for RC6 context */
+	if (IS_GEN9_LP(dev_priv))
+		wopcm_size -= BXT_GUC_WOPCM_RC6_RESERVED;
+
+	return wopcm_size;
+}
--- a/drivers/gpu/drm/i915/intel_guc_loader.c
+++ b/drivers/gpu/drm/i915/intel_guc_loader.c
@@ -250,17 +250,6 @@ static int guc_ucode_xfer_dma(struct drm
 	return ret;
 }
 
-u32 intel_guc_wopcm_size(struct drm_i915_private *dev_priv)
-{
-	u32 wopcm_size = GUC_WOPCM_TOP;
-
-	/* On BXT, the top of WOPCM is reserved for RC6 context */
-	if (IS_GEN9_LP(dev_priv))
-		wopcm_size -= BXT_GUC_WOPCM_RC6_RESERVED;
-
-	return wopcm_size;
-}
-
 /*
  * Load the GuC firmware blob into the MinuteIA.
  */
