From 99cdb35e787b277bc66ed9fe7d5f9852de9e0eb0 Mon Sep 17 00:00:00 2001
From: Daniel Vetter <daniel.vetter@ffwll.ch>
Date: Wed, 24 May 2017 16:51:36 +0200
Subject: [PATCH] drm/doc: move printf helpers out of drmP.h
Git-commit: 99cdb35e787b277bc66ed9fe7d5f9852de9e0eb0
Patch-mainline: v4.13-rc1
References: FATE#322643 bsc#1055900

And document them lightly. Unfortunately kernel-doc isn't the most
awesome for documenting #defines that don't look like functions, it
makes functions out of them :-/

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Reviewed-by: Neil Armstrong <narmstrong@baylibre.com>
Link: http://patchwork.freedesktop.org/patch/msgid/20170524145212.27837-2-daniel.vetter@ffwll.ch
Link: http://patchwork.freedesktop.org/patch/msgid/20170524145212.27837-3-daniel.vetter@ffwll.ch
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 include/drm/drmP.h      |   17 -----------------
 include/drm/drm_modes.h |   17 +++++++++++++++++
 include/drm/drm_rect.h  |   27 +++++++++++++++++++++++++++
 3 files changed, 44 insertions(+), 17 deletions(-)

--- a/include/drm/drmP.h
+++ b/include/drm/drmP.h
@@ -292,23 +292,6 @@ struct pci_controller;
 /* Format strings and argument splitters to simplify printing
  * various "complex" objects
  */
-#define DRM_MODE_FMT    "%d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x"
-#define DRM_MODE_ARG(m) \
-	(m)->base.id, (m)->name, (m)->vrefresh, (m)->clock, \
-	(m)->hdisplay, (m)->hsync_start, (m)->hsync_end, (m)->htotal, \
-	(m)->vdisplay, (m)->vsync_start, (m)->vsync_end, (m)->vtotal, \
-	(m)->type, (m)->flags
-
-#define DRM_RECT_FMT    "%dx%d%+d%+d"
-#define DRM_RECT_ARG(r) drm_rect_width(r), drm_rect_height(r), (r)->x1, (r)->y1
-
-/* for rect's in fixed-point format: */
-#define DRM_RECT_FP_FMT "%d.%06ux%d.%06u%+d.%06u%+d.%06u"
-#define DRM_RECT_FP_ARG(r) \
-		drm_rect_width(r) >> 16, ((drm_rect_width(r) & 0xffff) * 15625) >> 10, \
-		drm_rect_height(r) >> 16, ((drm_rect_height(r) & 0xffff) * 15625) >> 10, \
-		(r)->x1 >> 16, (((r)->x1 & 0xffff) * 15625) >> 10, \
-		(r)->y1 >> 16, (((r)->y1 & 0xffff) * 15625) >> 10
 
 /*@}*/
 
--- a/include/drm/drm_modes.h
+++ b/include/drm/drm_modes.h
@@ -197,6 +197,8 @@ enum drm_mode_status {
  * there's the hardware timings, which are corrected for interlacing,
  * double-clocking and similar things. They are provided as a convenience, and
  * can be appropriately computed using drm_mode_set_crtcinfo().
+ *
+ * For printing you can use %DRM_MODE_FMT and DRM_MODE_ARG().
  */
 struct drm_display_mode {
 	/**
@@ -407,6 +409,21 @@ struct drm_display_mode {
 	enum hdmi_picture_aspect picture_aspect_ratio;
 };
 
+/**
+ * DRM_MODE_FMT - printf string for &struct drm_display_mode
+ */
+#define DRM_MODE_FMT    "%d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x"
+
+/**
+ * DRM_MODE_ARG - printf arguments for &struct drm_display_mode
+ * @m: display mode
+ */
+#define DRM_MODE_ARG(m) \
+	(m)->base.id, (m)->name, (m)->vrefresh, (m)->clock, \
+	(m)->hdisplay, (m)->hsync_start, (m)->hsync_end, (m)->htotal, \
+	(m)->vdisplay, (m)->vsync_start, (m)->vsync_end, (m)->vtotal, \
+	(m)->type, (m)->flags
+
 #define obj_to_mode(x) container_of(x, struct drm_display_mode, base)
 
 /**
--- a/include/drm/drm_rect.h
+++ b/include/drm/drm_rect.h
@@ -43,6 +43,33 @@ struct drm_rect {
 };
 
 /**
+ * DRM_RECT_FMT - printf string for &struct drm_rect
+ */
+#define DRM_RECT_FMT    "%dx%d%+d%+d"
+/**
+ * DRM_RECT_ARG - printf arguments for &struct drm_rect
+ * @r: rectangle struct
+ */
+#define DRM_RECT_ARG(r) drm_rect_width(r), drm_rect_height(r), (r)->x1, (r)->y1
+
+/**
+ * DRM_RECT_FP_FMT - printf string for &struct drm_rect in 16.16 fixed point
+ */
+#define DRM_RECT_FP_FMT "%d.%06ux%d.%06u%+d.%06u%+d.%06u"
+/**
+ * DRM_RECT_FP_ARG - printf arguments for &struct drm_rect in 16.16 fixed point
+ * @r: rectangle struct
+ *
+ * This is useful for e.g. printing plane source rectangles, which are in 16.16
+ * fixed point.
+ */
+#define DRM_RECT_FP_ARG(r) \
+		drm_rect_width(r) >> 16, ((drm_rect_width(r) & 0xffff) * 15625) >> 10, \
+		drm_rect_height(r) >> 16, ((drm_rect_height(r) & 0xffff) * 15625) >> 10, \
+		(r)->x1 >> 16, (((r)->x1 & 0xffff) * 15625) >> 10, \
+		(r)->y1 >> 16, (((r)->y1 & 0xffff) * 15625) >> 10
+
+/**
  * drm_rect_adjust_size - adjust the size of the rectangle
  * @r: rectangle to be adjusted
  * @dw: horizontal adjustment
