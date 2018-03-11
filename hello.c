#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* Major and Minor number*/

static dev_t first;

static int __init hello_start(void)
{
	printk(KERN_INFO "Loading hello module...\n");
	printk(KERN_INFO "Hello world\n");
	//We will now try to allocate dynamic major and minor number and print it
	printk(KERN_INFO "Getting Device Number");
	int ret;
	if((ret = alloc_chrdev_region(&first,0,3,"scull")) < 0)
	{
		printk(KERN_INFO "Unable to get Device Number");
		return ret;
	}
	//If we are here then we got the device number
	printk(KERN_INFO "<MAJOR , MINOR ><%d %d>\n" , MAJOR(first),MINOR(first));
	return 0;
}

static void __exit hello_end(void)
{
	//We free the device number here
	unregister_chrdev_region(first,3);
	printk(KERN_INFO "Goodbye Mr.\n");
}

module_init(hello_start);
module_exit(hello_end);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hemant Kapoor");
MODULE_DESCRIPTION("Simple Hello Kernel");
