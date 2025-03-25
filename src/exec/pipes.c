/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/02/01 17:16:38 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
        buffer = get_next_line(STDIN_FILENO, 0);
        if (ft_strncmp(buffer, redirs->pathordel, ft_strlen(buffer)) == 0)
        {
            free(buffer);
            get_next_line(STDIN_FILENO, 1);
            break ;
        }
        ft_putstr_fd(buffer, STDOUT_FILENO); // change to hell->pipe_fd[i]? should be okay if after dup2
        free(buffer);
    }
}

void	ft_close(t_hell *hell)
{
	int	i;
	i = 0;
	while (i < (hell->cmd_count - 1) * 2)
	{
		close(hell->pipe_fd[i]);
		i++;
	}
}

void	ft_wait(t_proc *head)
{
	int wstatus;
	while (head->next)
	{
		if (waitpid(head->pid, &wstatus, 0) == -1)
			exit(WEXITSTATUS(wstatus)); // and free
		head = head->next;
	}
	//free_struct(hell, WEXITSTATUS(wstatus));
}


void	initialise(t_proc *head, t_hell *hell)
{
	hell->cmd_count = 0;
	t_proc *current = head;
	while (current)
	{
		current = current->next;
		hell->cmd_count++;
	}
	
}

void	create_cmd(t_proc *head)
{
	if (ft_strncmp(head->cmd[0], "/bin/", 5) == 0 || ft_strncmp(head->cmd[0], "/usr/bin/", 9) == 0 || ft_strncmp(head->cmd[0], "../", 3) == 0)
		head->cmd_path = ft_strdup(head->cmd[0]);
	else
		head->cmd_path = ft_strjoin("/bin/", head->cmd[0]);
	if (!head->cmd_path)
		; // free, error msg
	if (access(head->cmd_path, R_OK | X_OK) == -1)
		; // free, error msg
}

void	first_child(t_proc *head, t_hell *hell)
{
	int input_fd = 0;
	create_cmd(head);
	head->pid = fork();
	if (head->pid == 0)
	{
		// make while loop here
		if (head->redirs && head->redirs->type == 0)
		{
			input_fd = open(head->redirs->pathordel, O_RDONLY, 0644);
			if (dup2(input_fd, STDIN_FILENO) == -1)
				; // free, error msg
			close(input_fd);
		}
		if (dup2(hell->pipe_fd[1], STDOUT_FILENO) == -1)
			; // free, error msg
		ft_close(hell);
		// heredoc(hell, head, head->redirs);
		if (determine_builtin(hell, head, 1))
		 	exit(0);
		execve(head->cmd_path, head->cmd, hell->envp);
		perror("execve failed");
		exit(errno);
		// free, error msg
	}
}

void	middle_child(t_proc *head, t_hell *hell, int i)
{
	int output_fd;
	create_cmd(head);
	head->pid = fork();
	if (head->pid == 0)
	{
		if (dup2(hell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
			; //free_struct(data, errno);
		if (i == hell->cmd_count - 1)
		{
			if (head->redirs)
			{
				if (head->redirs->type == 1)
					output_fd = open(head->redirs->pathordel, O_CREAT | O_WRONLY | O_TRUNC,
							0644);
				else if (head->redirs->type == 2)
					output_fd = open(head->redirs->pathordel, O_CREAT | O_WRONLY | O_APPEND,
							0644);
				if (dup2(output_fd, STDOUT_FILENO) == -1)
					(perror("wrong"), exit(0)); //free_struct(data, errno);
				close(output_fd);
			}		
		}
		else
		{
			if (dup2(hell->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
				exit(0);
		}
		ft_close(hell);
		// heredoc(hell, head, head->redirs);
		if (determine_builtin(hell, head, 1))
		 	exit(0);
		execve(head->cmd_path, head->cmd, hell->envp);
		perror("execve failed");
		exit(errno);
		//free, error msg
	}
}

void	ft_pipex(t_hell *hell)
{
	initialise((*hell->head), hell);
	hell->pipe_fd = malloc(sizeof(int) * (hell->cmd_count - 1) * 2);
	if (!hell->pipe_fd)
		;// free, error msg
	int i = 0;
	while (i < hell->cmd_count - 1)
	{
		if (pipe(&hell->pipe_fd[i++ *2]) == -1)
			;// free, error msg
	}
	first_child((*hell->head), hell);
	i = 1;
	while (i < hell->cmd_count)
	{
		(*hell->head) = (*hell->head)->next;
		middle_child((*hell->head), hell, i);
		i++;
	}
	ft_close(hell);
	ft_wait((*hell->head));
	// free
}
