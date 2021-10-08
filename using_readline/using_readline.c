// This program is distributed under the GPL-v3
// in order to honor the readline license.

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[])
{
    char *line;
    while (1)
    {
        line = readline("Echo>");
        if (!line)
            break;
        printf("%s \n", line);
    };
    free(line);
    return 0;
}
