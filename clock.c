/* 
 * AUTHOR: Jon Rohan, Derek Wisong, Daniel Wetteroth
 * DATE:   4.19.2005
 * PURPOSE: Create a Linux 2.4 kernel module named clock into the /proc/ 
 *          directory
 */

/* Needed for kernel work */
#include <linux/kernel.h>

/* Needed for module work */ 
#include <linux/module.h>

/* Necessary for using the proc filesystem */
#include <linux/proc_fs.h>

/* Necessary for using the xtime function */
#include <asm/atomic.h>

/* This lets people know that the code is non open-source */
MODULE_LICENSE("GPL");

/* Name of this file */
static const char filename[] = "clock";

/* proc info. */
static struct proc_dir_entry *infop;

/* 
 *	Save the contents of the file into	a buffer, which	will 
 *	be used	for	the	result of a	read system	call on	the	file.
 */
static int proc_read(char *	sys_buffer,	char **	my_buffer, off_t file_pos, int count, int *	eof, void *	data)
{
	/* initialize the int we will return */
	int	len;

	/* counter used	to display the number of calls to the program */
	static int counter = 1;

	/*
	 * Increment the use count so that the module can't
	 * be removed while	we are in the middle of	this call.
	 */
	MOD_INC_USE_COUNT;
	
	/*
	 * If the file_pos is equal	to 0 then it is	the	first time the file	is read
	 * so we increment the counter by 1. If	the	file_pos is	greater	than 0
	 * then	we are not doen	reading	the	file so	we return 0
	 */
	if(file_pos	> 0)
		return 0;
	
		
	/*
	 * Get the current time	and	format it.
	 * we directly put the xtime values in the buffer
	 */
	len	= sprintf(sys_buffer,"Call %d: %d %d\n",counter,xtime.tv_sec,xtime.tv_usec);

	/* increment the counter */
	counter++;
	/* Decrement the use count to notify that the module is done */
	MOD_DEC_USE_COUNT;
	
	return len;
}

/*
 * Initalize the module and add the /proc file.
 */
int init_module()
{
	infop = create_proc_entry(filename, 0444, (struct proc_dir_entry *) 0);
	if(infop == 0)
	{
		return -EINVAL;
	}
	infop->owner = THIS_MODULE;
	infop->read_proc = proc_read;
	return 0;
}

/*
 * Unregister the file when the module is closed.
 */
void cleanup_module()
{
	remove_proc_entry(filename, (struct proc_dir_entry *) 0);
}

