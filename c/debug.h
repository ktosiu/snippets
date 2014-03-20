#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>

/*debug("Some error message.")*/
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "[DEBUG] %s:%d:%s " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/*log_err("There are %d problems in %s.", 0, "space")*/
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d:%s errno:%s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

/*log_warn("Maybe consider looking at: %s", "/etc/passwd")*/
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d:%s errno:%s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

/*log_info("It happened %f times today.", 1.1f)*/
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d:%s errno:%s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

/*check(fd, "Failed to open %s", file_name)*/
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

/*sentinel("Should not go here.")*/
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

/*check_mem(p);*/
#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno = 0; goto error; }

#endif
