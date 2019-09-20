From 9cf8f5802f39d9991158b29033c852bccfc3a4d4 Mon Sep 17 00:00:00 2001
From: Tomi Valkeinen <tomi.valkeinen@ti.com>
Date: Tue, 16 May 2017 15:34:45 +0300
Subject: [PATCH] drm: add missing declaration to drm_blend.h
Git-commit: 9cf8f5802f39d9991158b29033c852bccfc3a4d4
Patch-mainline: v4.13-rc1
References: FATE#322643 bsc#1055900

drm_blend.h is missing declaration for 'struct drm_plane'. Add it.

Signed-off-by: Tomi Valkeinen <tomi.valkeinen@ti.com>
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
Link: http://patchwork.freedesktop.org/patch/msgid/1494938085-21805-1-git-send-email-tomi.valkeinen@ti.com
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 include/drm/drm_blend.h |    1 +
 1 file changed, 1 insertion(+)

--- a/include/drm/drm_blend.h
+++ b/include/drm/drm_blend.h
@@ -28,6 +28,7 @@
 
 struct drm_device;
 struct drm_atomic_state;
+struct drm_plane;
 
 /*
  * Rotation property bits. DRM_ROTATE_<degrees> rotates the image by the
