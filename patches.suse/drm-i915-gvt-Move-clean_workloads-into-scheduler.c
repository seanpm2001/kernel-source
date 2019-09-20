From e2c43c0111d54d4857d052fcfca9f3f16bf1b1b2 Mon Sep 17 00:00:00 2001
From: Zhi Wang <zhi.a.wang@intel.com>
Date: Wed, 13 Sep 2017 01:58:35 +0800
Subject: [PATCH] drm/i915/gvt: Move clean_workloads() into scheduler.c
Git-commit: e2c43c0111d54d4857d052fcfca9f3f16bf1b1b2
Patch-mainline: v4.16-rc1
References: FATE#322643 bsc#1055900

Move clean_workloads() into scheduler.c since it's not specific to
execlist.

V2: 

- Remove clean_workloads in intel_vgpu_select_submission_ops. (Zhenyu)

Signed-off-by: Zhi Wang <zhi.a.wang@intel.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/gvt/execlist.c  |   41 -----------------------------------
 drivers/gpu/drm/i915/gvt/scheduler.c |   37 +++++++++++++++++++++++++++++++
 2 files changed, 38 insertions(+), 40 deletions(-)

--- a/drivers/gpu/drm/i915/gvt/execlist.c
+++ b/drivers/gpu/drm/i915/gvt/execlist.c
@@ -46,8 +46,6 @@
 #define same_context(a, b) (((a)->context_id == (b)->context_id) && \
 		((a)->lrca == (b)->lrca))
 
-static void clean_workloads(struct intel_vgpu *vgpu, unsigned long engine_mask);
-
 static int context_switch_events[] = {
 	[RCS] = RCS_AS_CONTEXT_SWITCH,
 	[BCS] = BCS_AS_CONTEXT_SWITCH,
@@ -397,23 +395,8 @@ static int complete_execlist_workload(st
 	gvt_dbg_el("complete workload %p status %d\n", workload,
 			workload->status);
 
-	if (workload->status || (vgpu->resetting_eng & ENGINE_MASK(ring_id))) {
-		/* if workload->status is not successful means HW GPU
-		 * has occurred GPU hang or something wrong with i915/GVT,
-		 * and GVT won't inject context switch interrupt to guest.
-		 * So this error is a vGPU hang actually to the guest.
-		 * According to this we should emunlate a vGPU hang. If
-		 * there are pending workloads which are already submitted
-		 * from guest, we should clean them up like HW GPU does.
-		 *
-		 * if it is in middle of engine resetting, the pending
-		 * workloads won't be submitted to HW GPU and will be
-		 * cleaned up during the resetting process later, so doing
-		 * the workload clean up here doesn't have any impact.
-		 **/
-		clean_workloads(vgpu, ENGINE_MASK(ring_id));
+	if (workload->status || (vgpu->resetting_eng & ENGINE_MASK(ring_id)))
 		goto out;
-	}
 
 	if (!list_empty(workload_q_head(vgpu, ring_id))) {
 		struct execlist_ctx_descriptor_format *this_desc, *next_desc;
@@ -529,32 +512,11 @@ static void init_vgpu_execlist(struct in
 	vgpu_vreg(vgpu, ctx_status_ptr_reg) = ctx_status_ptr.dw;
 }
 
-static void clean_workloads(struct intel_vgpu *vgpu, unsigned long engine_mask)
-{
-	struct intel_vgpu_submission *s = &vgpu->submission;
-	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
-	struct intel_engine_cs *engine;
-	struct intel_vgpu_workload *pos, *n;
-	unsigned int tmp;
-
-	/* free the unsubmited workloads in the queues. */
-	for_each_engine_masked(engine, dev_priv, engine_mask, tmp) {
-		list_for_each_entry_safe(pos, n,
-			&s->workload_q_head[engine->id], list) {
-			list_del_init(&pos->list);
-			intel_vgpu_destroy_workload(pos);
-		}
-		clear_bit(engine->id, s->shadow_ctx_desc_updated);
-	}
-}
-
 void clean_execlist(struct intel_vgpu *vgpu)
 {
 	enum intel_engine_id i;
 	struct intel_engine_cs *engine;
 
-	clean_workloads(vgpu, ALL_ENGINES);
-
 	for_each_engine(engine, vgpu->gvt->dev_priv, i) {
 		struct intel_vgpu_submission *s = &vgpu->submission;
 
@@ -571,7 +533,6 @@ void reset_execlist(struct intel_vgpu *v
 	struct intel_engine_cs *engine;
 	unsigned int tmp;
 
-	clean_workloads(vgpu, engine_mask);
 	for_each_engine_masked(engine, dev_priv, engine_mask, tmp)
 		init_vgpu_execlist(vgpu, engine->id);
 }
--- a/drivers/gpu/drm/i915/gvt/scheduler.c
+++ b/drivers/gpu/drm/i915/gvt/scheduler.c
@@ -685,6 +685,25 @@ static void update_guest_context(struct
 	kunmap(page);
 }
 
+static void clean_workloads(struct intel_vgpu *vgpu, unsigned long engine_mask)
+{
+	struct intel_vgpu_submission *s = &vgpu->submission;
+	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
+	struct intel_engine_cs *engine;
+	struct intel_vgpu_workload *pos, *n;
+	unsigned int tmp;
+
+	/* free the unsubmited workloads in the queues. */
+	for_each_engine_masked(engine, dev_priv, engine_mask, tmp) {
+		list_for_each_entry_safe(pos, n,
+			&s->workload_q_head[engine->id], list) {
+			list_del_init(&pos->list);
+			intel_vgpu_destroy_workload(pos);
+		}
+		clear_bit(engine->id, s->shadow_ctx_desc_updated);
+	}
+}
+
 static void complete_current_workload(struct intel_gvt *gvt, int ring_id)
 {
 	struct intel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
@@ -748,6 +767,23 @@ static void complete_current_workload(st
 		release_shadow_wa_ctx(&workload->wa_ctx);
 	}
 
+	if (workload->status || (vgpu->resetting_eng & ENGINE_MASK(ring_id))) {
+		/* if workload->status is not successful means HW GPU
+		 * has occurred GPU hang or something wrong with i915/GVT,
+		 * and GVT won't inject context switch interrupt to guest.
+		 * So this error is a vGPU hang actually to the guest.
+		 * According to this we should emunlate a vGPU hang. If
+		 * there are pending workloads which are already submitted
+		 * from guest, we should clean them up like HW GPU does.
+		 *
+		 * if it is in middle of engine resetting, the pending
+		 * workloads won't be submitted to HW GPU and will be
+		 * cleaned up during the resetting process later, so doing
+		 * the workload clean up here doesn't have any impact.
+		 **/
+		clean_workloads(vgpu, ENGINE_MASK(ring_id));
+	}
+
 	workload->complete(workload);
 
 	atomic_dec(&s->running_workload_num);
@@ -947,6 +983,7 @@ void intel_vgpu_reset_submission(struct
 	if (!s->active)
 		return;
 
+	clean_workloads(vgpu, engine_mask);
 	s->ops->reset(vgpu, engine_mask);
 }
 
