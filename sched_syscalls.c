/*Author:Csd4376*/

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include "sched_params.h"

asmlinkage long sys_set_scheduling_params(long deadline_1, long deadline_2, long computation_time)
{
    struct task_struct *current_task = current;
    
    /* Validate parameters */
    if (deadline_1 <= 0 || deadline_2 <= 0 || computation_time <= 0)
        return -EINVAL;
    
    if (deadline_1 >= deadline_2)
        return -EINVAL;
        
    /* Convert computation_time from ms to seconds for comparison */
    if ((computation_time / 1000) > deadline_1)
        return -EINVAL;
    
    /* Set the scheduling parameters */
    current_task->deadline_1 = deadline_1;
    current_task->deadline_2 = deadline_2;
    current_task->computation_time = computation_time;
    
    return 0;
}

asmlinkage long sys_get_scheduling_params(struct d_params __user *params)
{
    struct task_struct *current_task = current;
    struct d_params kernel_params;
    
    if (!params)
        return -EINVAL;
    
    /* Copy parameters to kernel space structure */
    kernel_params.deadline_1 = current_task->deadline_1;
    kernel_params.deadline_2 = current_task->deadline_2;
    kernel_params.computation_time = current_task->computation_time;
    
    /* Copy data back to user space */
    if (copy_to_user(params, &kernel_params, sizeof(struct d_params)))
        return -EFAULT;
    
    return 0;
}

asmlinkage long sys_get_scheduling_score(void)
{
    struct task_struct *current_task = current;
    struct timespec current_time;
    long D3, score;
    
    /* Get current time */
    getnstimeofday(&current_time);
    D3 = current_time.tv_sec;
    
    /* Calculate score based on current time and deadlines */
    if (D3 < current_task->deadline_1)
        return 100;
    else if (D3 > current_task->deadline_2)
        return 0;
    else
        return ((current_task->deadline_2 - D3) * 100) / 
               (current_task->deadline_2 - current_task->deadline_1);
}