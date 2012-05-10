/**
 * Copyright (c) 2012 by Lukas Heidemann <lukasheidemann@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <heap.h>
#include <info.h>
#include <stdint.h>
#include <string.h>

uintptr_t heap_top = 0;

/**
 * Sorts the modules in the info tables by their address in ascending order.
 *
 * This procedure is required in order to prevent clobbering the modules when
 * moving them to an area that is intersecting with the area the modules were
 * originally stored in.
 */
static void heap_modules_sort(void)
{
    size_t count = info_root->module_count;
    size_t i, j;

    if (count > 1) {
        for (i = 0; i < count - 1; ++i) {
            uintptr_t min_addr = 0;
            size_t min_idx = -1;

            for (j = i; i < count; ++j) {
                hy_info_module_t *mod = &info_module[j];
                if (mod->address < min_addr) {
                    min_idx = j;
                    min_addr = mod->address;
                }
            }

            if (i != min_idx) {
                hy_info_module_t tmp;
                memcpy(&tmp, &info_module[i], sizeof(hy_info_module_t));
                memcpy(&info_module[i], &info_module[min_idx], sizeof(hy_info_module_t));
                memcpy(&info_module[min_idx], &tmp, sizeof(hy_info_module_t));
            }
        }
    }
}

/**
 * Moves the modules to the end of the heap.
 */
static void heap_modules_move(void)
{
    size_t i;
    for (i = 0; i < info_root->module_count; ++i) {
        hy_info_module_t *mod = &info_module[i];
        void *buffer = heap_alloc(mod->length);

        memcpy((void *) buffer, (void *) mod->address, mod->length);

        mod->address = (uintptr_t) buffer;
    }
}

void heap_init(void)
{
	extern uint8_t heap_mark;
	heap_top = (uintptr_t) &heap_mark;

	heap_modules_sort();
	heap_modules_move();
}

void *heap_alloc(size_t size)
{
	size = (size + 0xFFF) & ~0xFFF;
	uintptr_t chunk = heap_top;
	heap_top += size;

	return (void *) chunk;
}

