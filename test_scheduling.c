/*Author:Csd4376*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "sched_params.h"

/* System call numbers */
#define __NR_set_scheduling_params 341
#define __NR_get_scheduling_params 342
#define __NR_get_scheduling_score  343

/* Wrapper functions */
static inline long set_scheduling_params(long d1, long d2, long comp_time) {
    return syscall(__NR_set_scheduling_params, d1, d2, comp_time);
}

static inline long get_scheduling_params(struct d_params *params) {
    return syscall(__NR_get_scheduling_params, params);
}

static inline long get_scheduling_score(void) {
    return syscall(__NR_get_scheduling_score);
}

int main() {
    struct d_params params;
    long ret;
    time_t current_time;

    printf("Testing scheduling system calls...\n\n");

    /* Test 1: Invalid parameters */
    printf("Test 1: Setting invalid parameters (d1 > d2)\n");
    ret = set_scheduling_params(10, 5, 1000);
    if (ret == -EINVAL)
        printf("Test 1 passed: Invalid parameters correctly rejected\n\n");
    else
        printf("Test 1 failed: Invalid parameters not detected\n\n");

    /* Test 2: Valid parameters */
    time(&current_time);
    printf("Test 2: Setting valid parameters\n");
    ret = set_scheduling_params(current_time + 10, current_time + 20, 5000);
    if (ret == 0)
        printf("Test 2 passed: Parameters set successfully\n\n");
    else
        printf("Test 2 failed: Could not set parameters\n\n");

    /* Test 3: Get parameters */
    printf("Test 3: Getting scheduling parameters\n");
    ret = get_scheduling_params(&params);
    if (ret == 0) {
        printf("Test 3 passed: Retrieved parameters:\n");
        printf("Deadline 1: %ld\n", params.deadline_1);
        printf("Deadline 2: %ld\n", params.deadline_2);
        printf("Computation time: %ld\n\n", params.computation_time);
    } else {
        printf("Test 3 failed: Could not get parameters\n\n");
    }

    /* Test 4: Get score */
    printf("Test 4: Getting scheduling score\n");
    ret = get_scheduling_score();
    printf("Current scheduling score: %ld\n\n", ret);

    return 0;
}