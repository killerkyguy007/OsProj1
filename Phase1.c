/* Name:       Kyran Day
 * Class:      OS Section 1
 * Instructor: Chris Regan
 * Project:    1, Part A, Phase 1
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int winner =0, runner_up =0;

pthread_mutex_t lane_contested;

// Phase 1: Racing Example: Implement threads for individual cars racing in a lane
void* race_lane(void* arg) {
    int id = *(int*)arg;
    printf("Racer %d is has started\n", id);

    // Phase 1 Show basic thread safety principles
    pthread_mutex_lock(&lane_contested);
    // In context of my example, this lane mutex shows that if there is a car in
    // front of one car, it cannot advance in the race. We only have one lane function
    // within this phase, so the first car (thread) deployed will win.

    sleep(1); // Racing

    if (winner == 0) winner = id;
    else if (runner_up == 0) runner_up = id;

    printf("Racer %d is has passed the finish line.\n", id);

    pthread_mutex_unlock(&lane_contested); // Now since one car has passed, (one lane), another car can now pass the
                                           // finish line
    return NULL;
}

int main(void) {
    pthread_t threads[3];

    int tids[3] = {1, 2, 3};
    
    // Phase 1: Demonstrate proper thread creation and management
    for (int i = 0; i < 3; i++) {
        if (pthread_create( &threads[i], NULL, race_lane, &tids[i]) != 0) {
            // above, pass create func thread location,

            perror("Error creating thread");
            return 1;
        }
    }
    
    // Phase 1: Create threads that perform concurrent operations
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The winner is: %d \nRunner up: %5d", winner, runner_up);

    return 0;
}