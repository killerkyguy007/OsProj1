/* Name:       Kyran Day
 * Class:      OS Section 1
 * Instructor: Chris Regan
 * Project:    1, Part A, Phase 3
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int winner =0, runner_up =0, mseconds_spent_passing =0;

pthread_mutex_t lane1_contested;
pthread_mutex_t lane2_contested;

void* race_lane1(void* arg) {
    int tid = *(int*)arg;
    printf("Racer %d is has started\n", tid);

    if (lane2_contested) { // Phase 3: Implement deadlock detection
        printf("Deadlock has occurred! Racer %d cannot pass.\n", tid);
        return "";
    }
    pthread_mutex_lock(&lane2_contested);
    // In context of my example, this lane mutex shows that if there is a car in
    // the other lane, it cannot move into the other lane to pass the car ahead

    // Phase 3: Demonstrate how deadlocks can occur (Part 1)
    sleep(1);
    // Here, deadlock occurs. When this line sleeps, the other lane func locks lane 1 (is beside car), and this
    // thread will be waiting indefinitely to move into lane 2, while other car waits for lane 1 to be open.

    if (lane1_contested) { // Phase 3: Implement deadlock detection
        printf("Deadlock has occurred! Racer %d cannot pass.\n", tid);
        return "";
    }
    for (int i =0; i < 80000; i++) mseconds_spent_passing++;

    pthread_mutex_lock(&lane1_contested); // Move back into OG lane and finish race
    // Phase 3: Create scenarios requiring multiple resource locks

    if (winner == 0) winner = tid;
    else if (runner_up == 0) runner_up = tid;

    // Car is done passing another car. It may be in the same new lane, but now since two cars are no longer parallel
    // another car can now go into the other lane safely to attempt to pass
    pthread_mutex_unlock(&lane1_contested);

    printf("Racer %d is has passed the finish line.\n", tid);

    pthread_mutex_unlock(&lane2_contested);
    // Now since one car has finished, another car can now pass the finish line

    return NULL;
}

void* race_lane2(void* arg) {
    int tid = *(int*)arg;
    printf("Racer %d is has started\n", tid);

    if (lane1_contested) { // Phase 3: Implement deadlock detection
        printf("Deadlock has occurred! Racer %d cannot pass.\n", tid);
        return "";
    }
    pthread_mutex_lock(&lane1_contested);

    // Phase 3: Demonstrate how deadlocks can occur (Part 1)
    sleep(1);
    // Here, deadlock occurs. When this line sleeps, the other lane func locks lane 1 (is beside car), and this
    // thread will be waiting indefinitely to move into lane 2, while other car waits for lane 1 to be open.

    if (lane2_contested) { // Phase 3: Implement deadlock detection
        printf("Deadlock has occurred! Racer %d cannot pass.\n", tid);
        return "";
    }
    // Racing Example: Show deadlock in multi-lane transfers

    for (int i =0; i < 80000; i++) mseconds_spent_passing++;

    pthread_mutex_lock(&lane1_contested); // Move back into OG lane and finish race
    // Phase 3: Create scenarios requiring multiple resource locks

    if (winner == 0) winner = tid;
    else if (runner_up == 0) runner_up = tid;

    pthread_mutex_unlock(&lane1_contested);

    printf("Racer %d is has passed the finish line.\n", tid);

    pthread_mutex_unlock(&lane2_contested);
    
    return NULL;
}

int main(void) {
    pthread_t threads[4];

    int tids[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i=i+2) {
        if (pthread_create( &threads[i], NULL, race_lane1, &tids[i]) != 0
        & (pthread_create( &threads[i+1], NULL, race_lane2, &tids[i+1] ) != 0) ) {
            // above, pass create func thread location to make thread i and i+1

            perror("Error creating threads");
            return 1;
        }
    }

    pthread_join(threads[0], NULL); // Start threads as close to each other in cpu time as we can
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

    if (winner == 0) printf("The race was a tie, the cars drove parallel to each other and two pairs crossed"
                                  " the finish line at the same time.");
    else printf("The winner is: %d \nRunner up: %5d", winner, runner_up);

    return 0;
}