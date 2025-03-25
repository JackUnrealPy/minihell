/* #include "includes/minishell.h"

void    heredoc(t_hell *hell, t_proc *head, t_redir *redirs)
{
    char	*buffer;
    int     heredoc = 0;
    // put result in pipe
    while (redirs)
    {
        if (redirs->type == 3)
        {
            heredoc = 1;
            break;
        }
        redirs = redirs->next;
    }
    if (!heredoc)
        return ;
    while (1)
    {
        write(0, "> ", 2);
        write(0, redirs->pathordel, ft_strlen(redirs->pathordel));
        buffer = get_next_line(0, 0);
        if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(buffer)) == 0)
        {
            free(buffer);
            get_next_line(0, 1);
            break ;
        }
        ft_putstr_fd(buffer, STDOUT_FILENO); // change to hell->pipe_fd[i]? should be okay if after dup2
        free(buffer);
    }
}

// create scalable redirection function for all cases here
// void    input_redir(t_redir *redirs);
// void    output_redir(t_redir *redirs);

// void	pipe_redirection(t_redir *redirs)
// {
// 	int	input_fd;
// 	int	output_fd;

// 	if (!redirs)
// 		return ;
// 	input_fd = 0;
// 	output_fd = 1;
// 	while (redirs)
// 	{
// 		if (redirs->type == 0)
// 			input_fd = open(redirs->pathordel, O_RDONLY, 0644);
// 		else if (redirs->type == 1)
// 			output_fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
// 					0644);
// 		else if (redirs->type == 2)
// 			output_fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND,
// 					0644);
// 		else
// 			break;
// 		redirs = redirs->next;
// 	}
// 	if (input_fd > 2)
// 	{
// 		dup2(input_fd, STDIN_FILENO);
// 		close(input_fd);
// 	}
// 	if (output_fd > 2)
// 	{
// 		dup2(output_fd, STDOUT_FILENO);
// 		close(output_fd);
// 	}
// }

// void	ft_redirection(t_redir *redirs)
// {
// 	int	input_fd;
// 	int	output_fd;

// 	if (!redirs)
// 		return ;
// 	input_fd = 0;
// 	output_fd = 1;
// 	while (redirs)
// 	{
// 		if (redirs->type == 0)
// 			input_fd = open(redirs->pathordel, O_RDONLY, 0644);
// 		else if (redirs->type == 1)
// 			output_fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
// 					0644);
// 		else if (redirs->type == 2)
// 			output_fd = open(redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND,
// 					0644);
// 		else
// 			continue; // heredoc
// 		redirs = redirs->next;
// 	}
// 	if (input_fd > 2)
// 	{
// 		dup2(input_fd, STDIN_FILENO);
// 		close(input_fd);
// 	}
// 	if (output_fd > 2)
// 	{
// 		dup2(output_fd, STDOUT_FILENO);
// 		close(output_fd);
// 	}
// } */