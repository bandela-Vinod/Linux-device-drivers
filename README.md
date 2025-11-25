# Linux-device-drivers

linux device drivers codes


This repository contains on Linux Device Drivers, covering fundamental driver development concepts, kernel-space programming, and interaction with hardware. The focus is on low-level embedded driver implementation using C and the Linux kernel.

1) Hello wrold program:
    Loading the .ko file adds the module to the kernel and shows “Hello world!” in the log. Using rmmod removes it from the kernel, displaying “Bye hello world” in the log.
2) proc_read_write:
   The command:   sudo sh -c 'echo "hello kernel via proc" > /proc/proc_read_write'   writes data from user space into the kernel module through the /proc/proc_read_write entry. The kernel module’s write function stores this data in kernel space. Later, using command: cat /proc/proc_read_write   reads the stored data back from the kernel, demonstrating two-way communication between user space and the kernel via the /proc file system.

   Makefile:A Makefile tells the kernel build system how to compile driver into a loadable module (.ko).
