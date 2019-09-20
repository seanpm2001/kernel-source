From b5a824250e4aac4fb76c5076b6a5e460e52c831a Mon Sep 17 00:00:00 2001
From: Chris Wilson <chris@chris-wilson.co.uk>
Date: Thu, 25 May 2017 21:48:18 +0100
Subject: [PATCH] drm/i915: Add kerneldoc to describe i915_gem_object.vma_list
Git-commit: b5a824250e4aac4fb76c5076b6a5e460e52c831a
Patch-mainline: v4.13-rc1
References: FATE#322643 bsc#1055900

Add kerneldoc for the vma_list stored on the i915_gem_object, in
particular, documenting the expected ordering of elements -- i.e. that
we do expect GGTT VMA first followed by the ppGTT VMA.

Signed-off-by: Chris Wilson <chris@chris-wilson.co.uk>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Link: http://patchwork.freedesktop.org/patch/msgid/20170525204818.12044-1-chris@chris-wilson.co.uk
Reviewed-by: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 drivers/gpu/drm/i915/i915_gem_object.h |   17 ++++++++++++++++-
 1 file changed, 16 insertions(+), 1 deletion(-)

--- a/drivers/gpu/drm/i915/i915_gem_object.h
+++ b/drivers/gpu/drm/i915/i915_gem_object.h
@@ -68,8 +68,23 @@ struct drm_i915_gem_object {
 
 	const struct drm_i915_gem_object_ops *ops;
 
-	/** List of VMAs backed by this object */
+	/**
+	 * @vma_list: List of VMAs backed by this object
+	 *
+	 * The VMA on this list are ordered by type, all GGTT vma are placed
+	 * at the head and all ppGTT vma are placed at the tail. The different
+	 * types of GGTT vma are unordered between themselves, use the
+	 * @vma_tree (which has a defined order between all VMA) to find an
+	 * exact match.
+	 */
 	struct list_head vma_list;
+	/**
+	 * @vma_tree: Ordered tree of VMAs backed by this object
+	 *
+	 * All VMA created for this object are placed in the @vma_tree for
+	 * fast retrieval via a binary search in i915_vma_instance().
+	 * They are also added to @vma_list for easy iteration.
+	 */
 	struct rb_root vma_tree;
 
 	/** Stolen memory for this object, instead of being backed by shmem. */
