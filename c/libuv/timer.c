#include <stdio.h>
#include <uv.h>

int counter = 0;

void on_time_callback(uv_timer_t* handle) {
    ++counter;
    printf("counter is %d\n", counter);
    if (counter > 100)
        uv_timer_stop(handle);
}

int main() {
    uv_timer_t timer;
    uv_timer_init(uv_default_loop(), &timer);
    uv_timer_start(&timer, on_time_callback, 1000, 5000);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    return 0;
}
