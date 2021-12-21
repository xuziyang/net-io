#include <sys/epoll.h>

#define MAX_EVENTS 64
#define MAX_OPEN_FD 1024

int main(int argc, char const *argv[]) {
    struct epoll_event *events;
    int nr_events, i, epfd;

    events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
    if (!events) {
        perror("malloc");
        return 1;
    }

    nr_events = epoll_wait(epfd, events, MAX_EVENTS, 1);
    if (nr_events < 0) {
        perror("epoll_wait");
        free(events);
        return 1;
    }

    for (i = 0; i < nr_events; i++) {
        printf("event=%ld on fd=%d\n",
               events[i].events,
               events[i].data.fd);
        /*
         * We now can, per events[i].events, operate on
         * events[i].data.fd without blocking.
         */
    }
    free(events); /* code */
    return 0;
}
