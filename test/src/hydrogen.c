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

#include <hydrogen.h>
#include <isr.h>
#include <keyboard.h>

hy_header_root_t hydrogen_header = {
        HY_MAGIC,                               // magic
        HY_HEADER_FLAG_IOAPIC_BSP,              // flags
        0xFFFFFF0000200000,                     // stack_vaddr
        0xFFFFFF0000100000,                     // info_vaddr
        0,                                      // ap_entry
        0,                                      // syscall_entry
        (uintptr_t) &isr_gates,                 // isr_entry_table

        {
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ0
                {0, KEYBOARD_IRQ_VECTOR},       // IRQ1
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ2
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ3
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ4
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ5
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ6
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ7
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ8
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ9
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ10
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ11
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ12
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ13
                {HY_HEADER_IRQ_FLAG_MASK, 0},   // IRQ14
                {HY_HEADER_IRQ_FLAG_MASK, 0}    // IRQ15
        }
};
