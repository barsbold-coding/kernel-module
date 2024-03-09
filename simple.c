#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void) {
	printk(KERN_INFO "Loading Module\n");
	struct birthday *person;
	int i = 0;
	while (i < 5) {
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = 2 + i;
		person->month = 8 + i;
		person->month = 1995 + i;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
		i++;
	}
	
	list_for_each_entry(person, &birthday_list, list) {
		printk(KERN_INFO "%d %d %d", person->month, person->day, person->year);
	}
	return 0;
}

void simple_exit(void) {
	struct birthday *ptr, *next;
	
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("BARSBOLD");
