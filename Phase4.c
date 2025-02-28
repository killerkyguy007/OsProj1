/* Name:       Kyran Day
 * Class:      OS Section 1
 * Instructor: Chris Regan
 * Project:    1, Part A, Phase 4
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int winner =0, runner_up =0, mseconds_spent_passing =0;

pthread_mutex_t starting_lane;
pthread_mutex_t passing_lane;

void wait_with_timeout(pthread_mutex_t* mutex, int timeout_seconds, int tid) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout_seconds;

    if (pthread_mutex_timedlock(mutex, &ts) != 0) {
        printf("Racer %d cannot acquire lane and is contested with another racer.\n", tid);
        pthread_exit(NULL);
    }
}

void* race(void* arg) { // Phase 4: Add proper resource ordering cars now start in the same lane
    int  tid = *(int*)arg;
    printf("Racer %d is has started\n", tid);

    if (passing_lane) sleep(3); // Phase 4: Show deadlock prevention...

    // ... And recovery
    wait_with_timeout(&passing_lane, 4, tid); // Phase 4: Implement timeout mechanisms

    for (int i =0; i < 70000; i++) mseconds_spent_passing++;
    pthread_mutex_unlock(&passing_lane); // Phase 4: Add proper resource ordering

    if (starting_lane) sleep(2); // Phase 4: Racing Example: Resolve deadlocks through ordered lane access

    wait_with_timeout(&starting_lane, 4, tid); // try to get in front of car passed

    if (winner == 0) winner = tid;
    else if (runner_up == 0) runner_up = tid;

    pthread_mutex_unlock(&starting_lane);

    printf("Racer %d is has passed the finish line.\n", tid);

    return NULL;
}

int main(void) {
    pthread_t threads[10];

    int tids[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        if (pthread_create( &threads[i], NULL, race, &tids[i]) != 0) {
            // above, pass create func thread location to make thread i and i+1

            perror("Error creating threads");
            return 1;
        }
    }

    pthread_join(threads[0], NULL); // Start threads as close to each other in cpu time as we can
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);
    pthread_join(threads[5], NULL);
    pthread_join(threads[6], NULL);
    pthread_join(threads[7], NULL);
    pthread_join(threads[8], NULL);
    pthread_join(threads[9], NULL);

    pthread_mutex_destroy(&starting_lane); // "Clean-up, clean-up, everybody do your share"
    pthread_mutex_destroy(&passing_lane);

    if (winner == 0) printf("The race was a tie, the cars drove parallel to each other and two pairs crossed"
                                  " the finish line at the same time."); // Tie case
    else printf("The winner is: %d \nRunner up: %5d", winner, runner_up);

    return 0;
}