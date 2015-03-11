#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

uv_async_t* async_handle;
uv_loop_t* loop;

uv_loop_t* create_loop() {
    uv_loop_t* loop = malloc(sizeof(uv_loop_t));
    if (loop) {
        uv_loop_init(loop);
    }
    return loop;
}

void async_callback(uv_async_t* handle) {
    printf("async_callback\n");
    uv_stop(loop);
}

void thread_main(void* arg) {
    printf("thread started\n");
    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
}

int main() {
    uv_thread_t tid;
    loop = create_loop();
    async_handle = malloc(sizeof(uv_async_t));
    uv_async_init(loop, async_handle, async_callback);
    uv_thread_create(&tid, thread_main, NULL);
    uv_async_send(async_handle);
    uv_thread_join(&tid);
}
