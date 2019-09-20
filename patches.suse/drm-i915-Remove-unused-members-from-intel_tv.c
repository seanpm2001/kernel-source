From 735a9876cf7f5ddda1027942344f31d3a1a4488a Mon Sep 17 00:00:00 2001
From: Maarten Lankhorst <maarten.lankhorst@linux.intel.com>
Date: Mon, 10 Apr 2017 11:07:07 +0200
Subject: [PATCH] drm/i915: Remove unused members from intel_tv.c
Git-commit: 735a9876cf7f5ddda1027942344f31d3a1a4488a
Patch-mainline: v4.13-rc1
References: FATE#322643 bsc#1055900

They have been unused since 2010, after the code for
intel_tv_save/restore was removed in the below commit:

commit 6443170f6d862a1cc89e61e4bb2410b714b875f4
Author: Eric Anholt <eric@anholt.net>
Date: Fri Apr 2 15:24:27 2010 -0700

    drm/i915: Remove dead KMS encoder save/restore code.

    This was brought over from UMS, and used for a while until we decided
    that drm_helper_resume_force_mode was easier and more reliable, since
    it didn't require duplicating all the code deleted here.  We just
    forgot to delete all that junk for a while.

Reviewed-by: Chris Wilson <chris@chris-wilson.co.uk>
Reviewed-by: Daniel Vetter <daniel.vetter@ffwll.ch>
Signed-off-by: Maarten Lankhorst <maarten.lankhorst@linux.intel.com>
Link: http://patchwork.freedesktop.org/patch/msgid/1491815239-10685-2-git-send-email-maarten.lankhorst@linux.intel.com
[mlankhorst: Add commit blurb based on danvet's feedback.]
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/intel_tv.c |   33 ---------------------------------
 1 file changed, 33 deletions(-)

--- a/drivers/gpu/drm/i915/intel_tv.c
+++ b/drivers/gpu/drm/i915/intel_tv.c
@@ -50,39 +50,6 @@ struct intel_tv {
 	int type;
 	const char *tv_format;
 	int margin[4];
-	u32 save_TV_H_CTL_1;
-	u32 save_TV_H_CTL_2;
-	u32 save_TV_H_CTL_3;
-	u32 save_TV_V_CTL_1;
-	u32 save_TV_V_CTL_2;
-	u32 save_TV_V_CTL_3;
-	u32 save_TV_V_CTL_4;
-	u32 save_TV_V_CTL_5;
-	u32 save_TV_V_CTL_6;
-	u32 save_TV_V_CTL_7;
-	u32 save_TV_SC_CTL_1, save_TV_SC_CTL_2, save_TV_SC_CTL_3;
-
-	u32 save_TV_CSC_Y;
-	u32 save_TV_CSC_Y2;
-	u32 save_TV_CSC_U;
-	u32 save_TV_CSC_U2;
-	u32 save_TV_CSC_V;
-	u32 save_TV_CSC_V2;
-	u32 save_TV_CLR_KNOBS;
-	u32 save_TV_CLR_LEVEL;
-	u32 save_TV_WIN_POS;
-	u32 save_TV_WIN_SIZE;
-	u32 save_TV_FILTER_CTL_1;
-	u32 save_TV_FILTER_CTL_2;
-	u32 save_TV_FILTER_CTL_3;
-
-	u32 save_TV_H_LUMA[60];
-	u32 save_TV_H_CHROMA[60];
-	u32 save_TV_V_LUMA[43];
-	u32 save_TV_V_CHROMA[43];
-
-	u32 save_TV_DAC;
-	u32 save_TV_CTL;
 };
 
 struct video_levels {
