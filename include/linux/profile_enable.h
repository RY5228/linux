#ifndef _LINUX_PROFILE_ENABLE_H
#define _LINUX_PROFILE_ENABLE_H

#include <linux/init.h>
#include <linux/kernel.h>

extern int profile_enable __read_mostly;

void profile_printk(const char *fmt, ...);

#endif  /* _LINUX_PROFILE_ENABLE_H */