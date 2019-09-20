From cd5a917e35bc51ebc5fe10cf226ba124b94f2147 Mon Sep 17 00:00:00 2001
From: Michal Wajdeczko <michal.wajdeczko@intel.com>
Date: Mon, 16 Oct 2017 14:47:15 +0000
Subject: [PATCH] drm/i915/guc: Reorder functions in intel_guc_fw.c
Git-commit: cd5a917e35bc51ebc5fe10cf226ba124b94f2147
Patch-mainline: v4.15-rc1
References: FATE#322643 bsc#1055900

Functions should be defined in their use order.

Signed-off-by: Michal Wajdeczko <michal.wajdeczko@intel.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Reviewed-by: Chris Wilson <chris@chris-wilson.co.uk>
Signed-off-by: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Link: https://patchwork.freedesktop.org/patch/msgid/20171016144724.17244-7-michal.wajdeczko@intel.com
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/intel_guc_fw.c |   81 ++++++++++++++++++------------------
 1 file changed, 41 insertions(+), 40 deletions(-)

--- a/drivers/gpu/drm/i915/intel_guc_fw.c
+++ b/drivers/gpu/drm/i915/intel_guc_fw.c
@@ -56,6 +56,47 @@ MODULE_FIRMWARE(I915_KBL_GUC_UCODE);
 
 #define I915_GLK_GUC_UCODE GUC_FW_PATH(glk, GLK_FW_MAJOR, GLK_FW_MINOR)
 
+/**
+ * intel_guc_fw_select() - selects GuC firmware for uploading
+ *
+ * @guc:	intel_guc struct
+ *
+ * Return: zero when we know firmware, non-zero in other case
+ */
+int intel_guc_fw_select(struct intel_guc *guc)
+{
+	struct drm_i915_private *dev_priv = guc_to_i915(guc);
+
+	intel_uc_fw_init(&guc->fw, INTEL_UC_FW_TYPE_GUC);
+
+	if (i915_modparams.guc_firmware_path) {
+		guc->fw.path = i915_modparams.guc_firmware_path;
+		guc->fw.major_ver_wanted = 0;
+		guc->fw.minor_ver_wanted = 0;
+	} else if (IS_SKYLAKE(dev_priv)) {
+		guc->fw.path = I915_SKL_GUC_UCODE;
+		guc->fw.major_ver_wanted = SKL_FW_MAJOR;
+		guc->fw.minor_ver_wanted = SKL_FW_MINOR;
+	} else if (IS_BROXTON(dev_priv)) {
+		guc->fw.path = I915_BXT_GUC_UCODE;
+		guc->fw.major_ver_wanted = BXT_FW_MAJOR;
+		guc->fw.minor_ver_wanted = BXT_FW_MINOR;
+	} else if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv)) {
+		guc->fw.path = I915_KBL_GUC_UCODE;
+		guc->fw.major_ver_wanted = KBL_FW_MAJOR;
+		guc->fw.minor_ver_wanted = KBL_FW_MINOR;
+	} else if (IS_GEMINILAKE(dev_priv)) {
+		guc->fw.path = I915_GLK_GUC_UCODE;
+		guc->fw.major_ver_wanted = GLK_FW_MAJOR;
+		guc->fw.minor_ver_wanted = GLK_FW_MINOR;
+	} else {
+		DRM_ERROR("No GuC firmware known for platform with GuC!\n");
+		return -ENOENT;
+	}
+
+	return 0;
+}
+
 /*
  * Read the GuC status register (GUC_STATUS) and store it in the
  * specified location; then return a boolean indicating whether
@@ -256,43 +297,3 @@ int intel_guc_fw_upload(struct intel_guc
 
 	return 0;
 }
-
-/**
- * intel_guc_fw_select() - selects GuC firmware for loading
- * @guc:	intel_guc struct
- *
- * Return: zero when we know firmware, non-zero in other case
- */
-int intel_guc_fw_select(struct intel_guc *guc)
-{
-	struct drm_i915_private *dev_priv = guc_to_i915(guc);
-
-	intel_uc_fw_init(&guc->fw, INTEL_UC_FW_TYPE_GUC);
-
-	if (i915_modparams.guc_firmware_path) {
-		guc->fw.path = i915_modparams.guc_firmware_path;
-		guc->fw.major_ver_wanted = 0;
-		guc->fw.minor_ver_wanted = 0;
-	} else if (IS_SKYLAKE(dev_priv)) {
-		guc->fw.path = I915_SKL_GUC_UCODE;
-		guc->fw.major_ver_wanted = SKL_FW_MAJOR;
-		guc->fw.minor_ver_wanted = SKL_FW_MINOR;
-	} else if (IS_BROXTON(dev_priv)) {
-		guc->fw.path = I915_BXT_GUC_UCODE;
-		guc->fw.major_ver_wanted = BXT_FW_MAJOR;
-		guc->fw.minor_ver_wanted = BXT_FW_MINOR;
-	} else if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv)) {
-		guc->fw.path = I915_KBL_GUC_UCODE;
-		guc->fw.major_ver_wanted = KBL_FW_MAJOR;
-		guc->fw.minor_ver_wanted = KBL_FW_MINOR;
-	} else if (IS_GEMINILAKE(dev_priv)) {
-		guc->fw.path = I915_GLK_GUC_UCODE;
-		guc->fw.major_ver_wanted = GLK_FW_MAJOR;
-		guc->fw.minor_ver_wanted = GLK_FW_MINOR;
-	} else {
-		DRM_ERROR("No GuC firmware known for platform with GuC!\n");
-		return -ENOENT;
-	}
-
-	return 0;
-}
