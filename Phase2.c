/* Name:       Kyran Day
 * Class:      OS Section 1
 * Instructor: Chris Regan
 * Project:    1, Part A, Phase 2
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int winner =0, runner_up =0;

// Phase 2: Implement mutex locks for shared resource protection
pthread_mutex_t lane_contested;

void* race_lane(void* arg) {
    int id = *(int*)arg;
    printf("Racer %d is has started\n", id);

    // Phase 2: Demonstrate proper lock acquisition...
    pthread_mutex_lock(&lane_contested);
    // In context of my example, this lane mutex shows that if there is a car in
    // front of one car, it cannot advance in the race. We only have one lane function
    // within this phase, so the first car (thread) deployed will win.

    sleep(1); // Racing
    
    // Phase 2: Show synchronized access to shared resources
    // Phase 2: Racing Example: Protect finish line access with mutexes
    if (winner == 0) winner = id;
    else if (runner_up == 0) runner_up = id;

    printf("Racer %d is has passed the finish line.\n", id);

    // ... and release
    pthread_mutex_unlock(&lane_contested);
    // Now since one car has passed, (one lane), another car can now pass the finish line
     
    return NULL;
}

int main(void) {
    pthread_t threads[3];

    int tids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        if (pthread_create( &threads[i], NULL, race_lane, &tids[i]) != 0) {
            // above, pass create func thread location,

            perror("Error creating thread");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) { // Start race
        pthread_join(threads[i], NULL);
    }

    printf("The winner is: %d \nRunner up: %5d", winner, runner_up);

    return 0;
}