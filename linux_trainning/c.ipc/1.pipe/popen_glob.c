#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define POPEN_FMT "/bin/ls -d %s 2> /dev/null"
#define PAT_SIZE 50
#define PCMD_BUF_SIZE (sizeof(POPEN_FMT) + PAT_SIZE)

int main(int argc, char *argv[]) {
    char pat[PAT_SIZE]; // Pattern for globbing
    char popenCmd[PCMD_BUF_SIZE];
    FILE *fp;           // File stream returned by popen()
    bool badPattern;    // Invalid characters in 'pat'?
    int len, status, fileCnt, j;
    char pathname[PATH_MAX];

    for (;;) {  //Read pattern, display results of globbing
        printf("pattern: ");
        fflush(stdout);
        if (fgets(pat, PAT_SIZE, stdin) == NULL) break; // EOF

        len = strlen(pat);
        if (len <= 1)               continue;  // Empty line

        if (pat[len - 1] == '\n')   pat[len - 1] = '\0';

        //check to see if have badPattern
        for (j = 0, badPattern = false; j < len && !badPattern; j++)
            if (!isalnum((unsigned char) pat[j]) && strchr("_*?[^-].", pat[j]) == NULL) badPattern = true;

        if (badPattern) {
            printf("Bad pattern character: %c\n", pat[j - 1]);
            continue;
        }

        // Build and execute command to glob 'pat'
        snprintf(popenCmd, PCMD_BUF_SIZE, POPEN_FMT, pat);
        popenCmd[PCMD_BUF_SIZE - 1] = '\0';

        // opens a process by creating a pipe, forking, and invoking the shell
        fp = popen(popenCmd, "r");

        if (fp == NULL) {
            printf("popen() failed\n");
            continue;
        }

        // Read resulting list of pathnames until EOF
        fileCnt = 0;
        while (fgets(pathname, PATH_MAX, fp) != NULL) {
            printf("%s", pathname);
            fileCnt++;
        }

        status = pclose(fp);
        printf(" %d matching file%s\n", fileCnt, (fileCnt != 1) ? "s" : "");
        printf(" pclose() status == %#x\n", (unsigned int) status);
    }
    exit(EXIT_SUCCESS);
}
