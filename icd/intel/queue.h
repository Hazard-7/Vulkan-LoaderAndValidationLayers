/*
 * XGL
 *
 * Copyright (C) 2014 LunarG, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *   Chia-I Wu <olv@lunarg.com>
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "kmd/winsys.h"
#include "intel.h"
#include "gpu.h"
#include "obj.h"

#define INTEL_QUEUE_ATOMIC_COUNTER_COUNT 1024

struct intel_dev;

struct intel_queue {
    struct intel_base base;

    struct intel_dev *dev;
    enum intel_ring_type ring;

    struct intel_bo *atomic_bo;
    struct intel_bo *select_graphics_bo;
    struct intel_bo *select_compute_bo;

    struct intel_bo *seqno_bo;
    int last_pipeline_select;
};

static inline struct intel_queue *intel_queue(XGL_QUEUE queue)
{
    return (struct intel_queue *) queue;
}

XGL_RESULT intel_queue_create(struct intel_dev *dev,
                              enum intel_gpu_engine_type engine,
                              struct intel_queue **queue_ret);
void intel_queue_destroy(struct intel_queue *queue);

XGL_RESULT intel_queue_wait(struct intel_queue *queue, int64_t timeout);

#endif /* QUEUE_H */
