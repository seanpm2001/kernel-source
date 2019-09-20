From bf4097ea5762bd90d836df9904594eb4822fefa7 Mon Sep 17 00:00:00 2001
From: Zhi Wang <zhi.a.wang@intel.com>
Date: Sun, 10 Sep 2017 21:36:21 +0800
Subject: [PATCH] drm/i915/gvt: Fix a memory leak in cmd_parser.c
Git-commit: bf4097ea5762bd90d836df9904594eb4822fefa7
Patch-mainline: v4.16-rc1
References: FATE#322643 bsc#1055900

The pointer points to the original memory can never take the return value
of krealloc().

Signed-off-by: Zhi Wang <zhi.a.wang@intel.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/gvt/cmd_parser.c |   10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

--- a/drivers/gpu/drm/i915/gvt/cmd_parser.c
+++ b/drivers/gpu/drm/i915/gvt/cmd_parser.c
@@ -2620,14 +2620,16 @@ static int shadow_workload_ring_buffer(s
 	gma_top = workload->rb_start + guest_rb_size;
 
 	if (workload->rb_len > vgpu->reserve_ring_buffer_size[ring_id]) {
-		void *va = vgpu->reserve_ring_buffer_va[ring_id];
+		void *va, *p;
+
 		/* realloc the new ring buffer if needed */
-		vgpu->reserve_ring_buffer_va[ring_id] =
-			krealloc(va, workload->rb_len, GFP_KERNEL);
-		if (!vgpu->reserve_ring_buffer_va[ring_id]) {
+		va = vgpu->reserve_ring_buffer_va[ring_id];
+		p = krealloc(va, workload->rb_len, GFP_KERNEL);
+		if (!p) {
 			gvt_vgpu_err("fail to alloc reserve ring buffer\n");
 			return -ENOMEM;
 		}
+		vgpu->reserve_ring_buffer_va[ring_id] = p;
 		vgpu->reserve_ring_buffer_size[ring_id] = workload->rb_len;
 	}
 
