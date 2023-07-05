#include "profile.h"
// #include <x86intrin.h>
// #include "stdint.h"
// #include <linux/kernel.h>
// #include <linux/string.h>
// #include <linux/printk.h>
#include <linux/profile_enable.h>

/* profile with rdtsc */
uint32_t start_high = 0, start_low = 0;
uint32_t end_high = 0, end_low = 0;

INLINE void profile_start_rdtsc() {
   asm volatile("lfence\n\t"
                "RDTSC\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r"(start_high), "=r"(start_low)::"%rdx", "%rax");
   asm volatile("lfence\n\t");
}

INLINE void profile_end_rdtsc(char *loc) {
   asm volatile("lfence\n\t"
                "RDTSC\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t"
                : "=r"(end_high), "=r"(end_low)::"%rdx", "%rax");
   if (start_high == 0 && start_low == 0) return;
   uint64_t elapsed = (((uint64_t)end_high << 32) | end_low) - (((uint64_t)start_high << 32) | start_low);
   if (profile_enable)
      profile_printk("[PF] %s %lu\n", loc, elapsed);
   profile_reset_rdtsc();
   asm volatile("lfence\n\t");
}

void profile_reset_rdtsc() {
   start_high = 0;
   start_low = 0;
   end_high = 0;
   end_low = 0;
}

NO_INLINE void profile_flush_rdtsc(void *addr) {
   asm volatile("clflush (%0)\n\t" ::"r"(addr));
   for (volatile size_t z = 0; z < 50; ++z) {}
   asm volatile("lfence\n\t");
}

/* profile with jmp (LBR) */
INLINE void profile_start_jmp() {
   asm goto("lfence\n\t"
            "jmp %l0\n\t" :: ::label);
label:;
}
INLINE void profile_end_jmp() {
   asm goto("jmp %l0\n\t" :: ::label);
label:;
   asm volatile("lfence\n\t");
}
INLINE void profile_reset_jmp() {
   asm goto("jmp %l0\n\t" :: ::label);
label:;
}
NO_INLINE void profile_flush_jmp(void *addr) {
   asm volatile("clflush (%0)\n\t" ::"r"(addr));
   INSERT_NOPS(3, 2, 0);
   asm volatile("lfence\n\t");
}
