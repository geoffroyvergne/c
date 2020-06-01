/*
https://franckh.developpez.com/tutoriels/posix/pthreads/
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define psleep(sec) sleep ((sec))
#define INITIAL_STOCK   20
#define NB_CLIENTS      5

// Structure to store clients threads informations
typedef struct {
    int stock;

    pthread_t thread_store;
    pthread_t thread_clients [NB_CLIENTS];

    pthread_mutex_t mutex_stock;
    pthread_cond_t cond_stock;
    pthread_cond_t cond_clients;
} store_t;

static store_t store = {
    .stock = INITIAL_STOCK,
    .mutex_stock = PTHREAD_MUTEX_INITIALIZER,
    .cond_stock = PTHREAD_COND_INITIALIZER,
    .cond_clients = PTHREAD_COND_INITIALIZER
};

// Sort a number between 0 and MAX
static int get_random(int max) {
    double val;

    val = (double) max * rand();
    val = val / (RAND_MAX + 1.0);

    return ((int) val);
}

// Store threads
static void *fn_store(void * p_data) {
    while(1) {

        // Begin protected area
        pthread_mutex_lock(&store.mutex_stock);
        pthread_cond_wait(&store.cond_stock, &store.mutex_stock);

        if(store.stock <= 0) {
            store.stock = INITIAL_STOCK;
            printf("Fill storage with %d articles \n", store.stock);
        }

        // end protected area
        pthread_mutex_unlock(&store.mutex_stock);
        pthread_mutex_unlock(&store.mutex_stock);
    }

    return NULL;
}

// Clients threads
static void *fn_clients(void *p_data) {
    int nb = (int) p_data;

    while(1) {
        int val = get_random(6);
        psleep(get_random(3));

        //begin protected area
        pthread_mutex_lock(&store.mutex_stock);

        if(val > store.stock) {
            pthread_cond_signal(&store.cond_stock);
            pthread_cond_wait(&store.cond_clients, &store.mutex_stock);
        }
        //psleep (get_random(3));

        store.stock = store.stock - val;

        printf("Client %d takes %d from stock, stays %d \n", nb, val, store.stock);

        // End protected area
        pthread_mutex_unlock(&store.mutex_stock);
    }

    return NULL;
}

int main(void) {
    int i = 0;
    int ret = 0;

    // Create store thread
    printf("Create store thread\n");
    ret = pthread_create(&store.thread_store, NULL, fn_store, NULL);

    // Create clients threads if store threads success
    if(!ret) {
        printf("Create client threads \n");
        for(i=0; i<NB_CLIENTS; i++) {
            //ret = pthread_create(&store.thread_clients[i], NULL, fn_clients, (void *) (size_t) i);
            ret = pthread_create (&store.thread_clients [i], NULL, fn_clients, (void *) (size_t) i);
        }

        if(ret) {
            printf("%i", ret);
        }
    } else {
        printf("%i", ret);
    }

    // Wait threads end
    i = 0;
    for(i=0; i<NB_CLIENTS; i++) {
        pthread_join(store.thread_clients[i], NULL);
    }
    pthread_join(store.thread_store, NULL);

    return EXIT_SUCCESS;
}
