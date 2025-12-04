# Linux-device-drivers

linux device drivers codes


This repository contains on Linux Device Drivers, covering fundamental driver development concepts, kernel-space programming, and interaction with hardware. The focus is on low-level embedded driver implementation using C and the Linux kernel.

1) Hello wrold program:
    Loading the .ko file adds the module to the kernel and shows “Hello world!” in the log. Using rmmod removes it from the kernel, displaying “Bye hello world” in the log.
2) proc_read_write:
   The command:   sudo sh -c 'echo "hello kernel via proc" > /proc/proc_read_write'   writes data from user space into the kernel module through the /proc/proc_read_write entry. The kernel module’s write function stores this data in kernel space. Later, using command: cat /proc/proc_read_write   reads the stored data back from the kernel, demonstrating two-way communication between user space and the kernel via the /proc file system.

   Makefile:A Makefile tells the kernel build system how to compile driver into a loadable module (.ko).
3) 3_open_and_release:
   This project demonstrates a simple Linux character device driver that implements open and release operations.
Build the module. Run make to compile the kernel module. The .ko file is generated. Load the module.
$: sudo insmod open_release.ko
$: sudo dmesg    (see kernel logs)
 in that kernel log find this like
open_release -Major Device number: 241

later Create the device node

Use the assigned major number to create a device file:

$: sudo mknod /dev/open_release c 241 0

then Compile the test program (file.c) to produce a.out.

Run the program with the device node:

$: ./a.out /dev/open_release
Check kernel logs

View driver output in the kernel buffer:
$: sudo dmesg.
open_release -Major: 241, Minor 0
open_release - filp->f_pos: 0
open_release - filp->f_mode: 0x1d
open_release - filp->f_flags: 0x8000
open_release - file is closed

4) 4_kernal_debug_print : This kernel module demonstrates different log levels using printk and pr_macros. It prints messages during initialization (init) and cleanup (exit) with varying severity.how Linux kernel logging works across info, warning, debug, alert, error, and emergency levels.

   
