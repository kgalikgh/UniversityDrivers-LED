#include <linux/module.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>


static int my_init(void);
static void my_exit(void);

static const struct of_device_id simple_driver_dt_ids[] = {
	{.compatible = "uwr,led-driver"},
    {}
};


static int simple_driver_probe (struct platform_device *pdev)
{   
	printk(KERN_ERR"LED turned on\n");
	int *ptr = platform_get_resource(pdev, IORESOURCE_MEM, 0)->start;
	*ptr = 1;
    return 0;
}

static int simple_driver_remove (struct platform_device *pdev)
{
    printk(KERN_ERR"LED turned off\n");
	int *ptr = platform_get_resource(pdev, IORESOURCE_MEM, 0)->start;
	*ptr = 0;
    return 0;
}

static struct platform_driver simple_driver = {
    .driver = {
        .name = "my_simple_driver",
        .of_match_table = simple_driver_dt_ids,
    },
    .probe = simple_driver_probe,
    .remove = simple_driver_remove,
};

static int __init my_init()
{
    printk(KERN_ERR"Driver registered\n");
    return platform_driver_register(&simple_driver);
}

static void __exit my_exit()
{
    pr_info("Driver unregistered\n");
    platform_driver_unregister(&simple_driver);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
