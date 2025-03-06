#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *input = NULL;
    while (1)
    {
        input = readline("minishell> ");
        add_history(input);
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        free(input);
    }
    rl_clear_history();
}