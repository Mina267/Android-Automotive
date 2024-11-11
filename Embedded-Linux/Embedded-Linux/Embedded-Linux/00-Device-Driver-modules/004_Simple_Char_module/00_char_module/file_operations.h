#include <linux/fs.h>

extern int driver_open(struct inode *inode, struct file *file);
extern int driver_close(struct inode *inode, struct file *file);
extern ssize_t driver_read(struct file *file, char __user *buf, size_t len, loff_t *off);
extern ssize_t driver_write(struct file *file, const char __user *buf, size_t len, loff_t *off);

