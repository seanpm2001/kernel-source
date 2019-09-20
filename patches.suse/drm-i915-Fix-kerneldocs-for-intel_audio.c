From 764b9f2c4d252fd893a07b39b4ab14ae8044c9cb Mon Sep 17 00:00:00 2001
From: =?UTF-8?q?Ville=20Syrj=C3=A4l=C3=A4?= <ville.syrjala@linux.intel.com>
Date: Tue, 14 Nov 2017 21:11:27 +0200
Subject: [PATCH] drm/i915: Fix kerneldocs for intel_audio.c
Mime-version: 1.0
Content-type: text/plain; charset=UTF-8
Content-transfer-encoding: 8bit
Git-commit: 764b9f2c4d252fd893a07b39b4ab14ae8044c9cb
Patch-mainline: v4.16-rc1
References: FATE#322643 bsc#1055900

Fix copy/paste fail in kerneldocs for intel_audio_codec_disable().

Cc: Daniel Vetter <daniel.vetter@ffwll.ch>
Suggested-by: Daniel Vetter <daniel.vetter@ffwll.ch>
Signed-off-by: Ville Syrjälä <ville.syrjala@linux.intel.com>
Link: https://patchwork.freedesktop.org/patch/msgid/20171114191127.16188-1-ville.syrjala@linux.intel.com
Reviewed-by: Dhinakaran Pandiyan <dhinakaran.pandiyan@intel.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/intel_audio.c |    4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

--- a/drivers/gpu/drm/i915/intel_audio.c
+++ b/drivers/gpu/drm/i915/intel_audio.c
@@ -655,8 +655,8 @@ void intel_audio_codec_enable(struct int
 /**
  * intel_audio_codec_disable - Disable the audio codec for HD audio
  * @encoder: encoder on which to disable audio
- * @crtc_state: pointer to the old crtc state.
- * @conn_state: pointer to the old connector state.
+ * @old_crtc_state: pointer to the old crtc state.
+ * @old_conn_state: pointer to the old connector state.
  *
  * The disable sequences must be performed before disabling the transcoder or
  * port.
