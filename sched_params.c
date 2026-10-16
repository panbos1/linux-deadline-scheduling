/*Author:Csd4376*/
#ifndef _LINUX_SCHED_PARAMS_H
#define _LINUX_SCHED_PARAMS_H

struct d_params {
    long deadline_1;        /* First deadline in seconds */
    long deadline_2;        /* Second deadline in seconds */
    long computation_time;  /* Expected computation time in milliseconds */
};

#endif /* _LINUX_SCHED_PARAMS_H */