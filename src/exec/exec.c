#include "../../includes/minishell.h"

char    *ft_realloc(char *old, char *new)
{
    char *combine = ft_strjoin(old, new);
    free(old);
    free(new);
    return (combine);
}
void    single_heredoc(t_hell *hell, t_proc *head, t_redir *redirs)
{
    // does not work yet, only with perfect input: cat << eof 
    hell->hdoc_count = 1;
    char *buffer;
    char *txt = NULL;
    int flag = 0;
    while (1)
    {
        write(STDIN_FILENO, "> ", 2);
        buffer = get_next_line(0, &flag);
        if (!buffer)
            return ;
        if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(buffer)-1) == 0)
        {
            free(buffer);
            //ft_close(hell, 1);
            break ;
        }
        txt = ft_realloc(txt, buffer);
    }
    ft_putstr_fd(txt, 1);
    free(txt);
    (void)head;
}

int loop_cmds(t_hell *hell, char **cmd)
{
    if ((*hell->head) && !(*hell->head)->next && !heredoc_check((*(*hell->head)->redirs)))
    {
        if (!determine_builtin(hell, (*hell->head), cmd, 0))
            single_cmd(hell, (*hell->head));
    }
    else if ((*hell->head) && !(*hell->head)->next && heredoc_check((*(*hell->head)->redirs)))
    {
        single_heredoc(hell, (*hell->head), (*(*hell->head)->redirs));
    }
    else if ((*hell->head) && (*hell->head)->next)
         ft_pipex(hell, cmd);
    else
        return (1);
    return (0);
}
