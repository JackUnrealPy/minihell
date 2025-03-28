#include "../../includes/minishell.h"

int loop_cmds(t_hell *hell, char **envp)
{
    ft_double_strdup(hell, envp); // create envp before
    if ((*hell->head) && !(*hell->head)->next)
    {
        if (!determine_builtin(hell, (*hell->head), 0)) // && !heredoc()
            single_cmd(hell, (*hell->head));
    }
    else if ((*hell->head) && (*hell->head)->next)
         ft_pipex(hell);
    else
        return (1);
    return (0);
}


static void	ft_freeme(char **arr, int a)
{
	while (a >= 0)
	{
		free(arr[a]);
		a--;
	}
	free(arr);
}

static char	**ft_nbarr(const char *s, char c)
{
	int		i;
	char	**arr;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (arr);
}

static char	**ft_charlen(const char *s, char c, char **arr, int count)
{
	int	a;

	a = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			count++;
			s++;
		}
		if (count != 0)
		{
			arr[a] = (char *)malloc(count + 1);
			if (arr[a] == NULL)
			{
				ft_freeme(arr, a);
				return (NULL);
			}
			a++;
			count = 0;
		}
	}
	return (arr);
}

static char	**ft_assign(const char *s, char c, char **arr)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	a = 0;
	b = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
		{
			arr[a][b] = s[i];
			b++;
			i++;
		}
		arr[a][b] = '\0';
		a++;
		b = 0;
		while (s[i] && s[i] == c)
			i++;
	}
	arr[a] = NULL;
	return (arr);
}

char	**split(char const *s, char c)
{
	char	**arr;
	int		count;

	arr = NULL;
	count = 0;
	if (s != NULL)
	{
		arr = ft_nbarr(s, c);
		if (arr == NULL)
			return (NULL);
		arr = ft_charlen(s, c, arr, count);
		if (arr == NULL)
			return (NULL);
		arr = ft_assign(s, c, arr);
	}
	return (arr);
}

t_hell *init_hell(char **envp)
{
    t_hell *hell = malloc(sizeof(t_hell));
    if (!hell)
        return (NULL);
    hell->freeme = malloc(sizeof(t_free *));
    if (!hell->freeme)
    {
        free(hell);
        return (NULL);
    }
    hell->freeme[0] = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->hdoc_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));
    if (!hell->head)
    {
        free(hell->freeme);
        free(hell);
        return (NULL);
    }
    *(hell->head) = NULL;
    hell->lastexit = 0;
    return (hell);
}

void fill_hell(t_hell *hell)
{
    t_proc *proc = malloc(sizeof(t_proc));
    if (!proc)
        return;

    proc->freeme = hell->freeme;
    proc->cmd = split("echo -n hello", ' ');
    proc->cmd_path = NULL;
    proc->redirs = malloc(sizeof(t_redir *));
    if (!proc->redirs)
    {
        free(proc);
        return;
    }
    proc->redirs[0] = malloc(sizeof(t_redir));
    if (!proc->redirs[0])
    {
        free(proc->redirs);
        free(proc);
        return;
    }
    proc->redirs[0]->type = 0;
    proc->redirs[0]->pathordel = ft_strdup("Makefile");
    proc->redirs[0]->next = malloc(sizeof(t_redir));
    if (!proc->redirs[0]->next)
    {
        free(proc->redirs[0]);
        free(proc->redirs);
        free(proc);
        return;
    }
    proc->redirs[0]->next->type = 1;
    proc->redirs[0]->next->pathordel = ft_strdup("out");
    proc->redirs[0]->next->next = NULL;
    proc->next = NULL;
    proc->prev = NULL;

    *(hell->head) = proc;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_hell *hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell, envp);

    return (0);
}


// for command cat << eof | cat << eof1 | cat -e << eof2 | cat -e > outfile
/* t_hell *init_hell(char **envp)
{
    t_hell *hell = malloc(sizeof(t_hell));
    if (!hell)
        return (NULL);
    hell->freeme = malloc(sizeof(t_free *));
    if (!hell->freeme)
    {
        free(hell);
        return (NULL);
    }
    hell->freeme[0] = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->hdoc_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));
    if (!hell->head)
    {
        free(hell->freeme);
        free(hell);
        return (NULL);
    }
    *(hell->head) = NULL;
    hell->lastexit = 0;
    return (hell);
}

void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    t_proc *proc3 = malloc(sizeof(t_proc));
    t_proc *proc4 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2 || !proc3 || !proc4)
    {
        free(proc1);
        free(proc2);
        free(proc3);
        free(proc4);
        return;
    }
    
    proc1->freeme = hell->freeme;
    proc1->cmd = split("cat", ' ');
    proc1->cmd_path = NULL;
    proc1->redirs = malloc(sizeof(t_redir *));
    proc1->hpid = 0;
    proc1->redirs[0] = malloc(sizeof(t_redir));
    proc1->redirs[0]->type = 3;
    proc1->redirs[0]->pathordel = ft_strdup("eof\n");
    proc1->redirs[0]->next = NULL;
    proc1->next = proc2;
    proc1->prev = NULL;

    proc2->freeme = hell->freeme;
    proc2->cmd = split("cat", ' ');
    proc2->cmd_path = NULL;
    proc2->redirs = malloc(sizeof(t_redir *));
    proc2->hpid = 0;
    proc2->redirs[0] = malloc(sizeof(t_redir));
    proc2->redirs[0]->type = 3;
    proc2->redirs[0]->pathordel = ft_strdup("eof1\n");
    proc2->redirs[0]->next = NULL;
    proc2->next = proc3;
    proc2->prev = proc1;
    
    proc3->freeme = hell->freeme;
    proc3->cmd = split("cat -e", ' ');
    proc3->cmd_path = NULL;
    proc3->redirs = malloc(sizeof(t_redir *));
    proc3->hpid = 0;
    proc3->redirs[0] = malloc(sizeof(t_redir));
    proc3->redirs[0]->type = 3;
    proc3->redirs[0]->pathordel = ft_strdup("eof2\n");
    proc3->redirs[0]->next = NULL;
    proc3->next = proc4;
    proc3->prev = proc2;

    proc4->freeme = hell->freeme;
    proc4->cmd = split("cat -e", ' ');
    proc4->cmd_path = NULL;
    proc4->redirs = malloc(sizeof(t_redir *));
    proc4->hpid = 0;
    proc4->redirs[0] = malloc(sizeof(t_redir));
    proc4->redirs[0]->type = 1;
    proc4->redirs[0]->pathordel = ft_strdup("outfile");
    proc4->redirs[0]->next = NULL;
    proc4->next = NULL;
    proc4->prev = proc3;
    
    *(hell->head) = proc1;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_hell *hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell, envp);

    return (0);
} */



// for command cat << eof | cat << hell > outfile
/* t_hell *init_hell(char **envp)
{
    t_hell *hell = malloc(sizeof(t_hell));
    if (!hell)
        return (NULL);
    hell->freeme = malloc(sizeof(t_free *));
    if (!hell->freeme)
    {
        free(hell);
        return (NULL);
    }
    hell->freeme[0] = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->hdoc_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));
    if (!hell->head)
    {
        free(hell->freeme);
        free(hell);
        return (NULL);
    }
    *(hell->head) = NULL;
    hell->lastexit = 0;
    return (hell);
}

void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2)
    {
        free(proc1);
        free(proc2);
        return;
    }

    proc1->freeme = hell->freeme;
    proc1->cmd = split("cat", ' ');
    proc1->cmd_path = NULL;
    proc1->redirs = malloc(sizeof(t_redir *));
    if (!proc1->redirs)
    {
        free(proc1);
        free(proc2);
        return;
    }
    
    // First heredoc redirection
    proc1->redirs[0] = malloc(sizeof(t_redir));
    if (!proc1->redirs[0])
    {
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0]->type = 3;
    proc1->redirs[0]->pathordel = ft_strdup("eof\n");
    proc1->redirs[0]->next = NULL;
    proc1->next = proc2;
    proc1->prev = NULL;

    proc2->freeme = hell->freeme;
    proc2->cmd = split("cat", ' ');
    proc2->cmd_path = NULL;
    proc2->redirs = malloc(sizeof(t_redir *));
    if (!proc2->redirs)
    {
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    
    proc2->hpid = 0;
    proc2->redirs[0] = malloc(sizeof(t_redir));
    if (!proc2->redirs[0])
    {
        free(proc2->redirs);
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->redirs[0]->type = 3;
    proc2->redirs[0]->pathordel = ft_strdup("hell\n");
    
    // Second redirection (output to file)
    proc2->redirs[0]->next = malloc(sizeof(t_redir));
    if (!proc2->redirs[0]->next)
    {
        free(proc2->redirs[0]);
        free(proc2->redirs);
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->redirs[0]->next->type = 1;
    proc2->redirs[0]->next->pathordel = ft_strdup("outfile");
    proc2->redirs[0]->next->next = NULL;
    
    proc2->next = NULL;
    proc2->prev = proc1;

    *(hell->head) = proc1;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_hell *hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell, envp);

    return (0);
} */

/* 
t_hell *init_hell(char **envp)
{
    t_hell *hell = malloc(sizeof(t_hell));
    if (!hell)
        return (NULL);
    hell->freeme = malloc(sizeof(t_free *));
    if (!hell->freeme)
    {
        free(hell);
        return (NULL);
    }
    hell->freeme[0] = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->hdoc_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));
    if (!hell->head)
    {
        free(hell->freeme);
        free(hell);
        return (NULL);
    }
    *(hell->head) = NULL;
    hell->lastexit = 0;
    return (hell);
}

void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2)
    {
        free(proc1);
        free(proc2);
        return;
    }

    proc1->freeme = hell->freeme;
    proc1->cmd = split("cat", ' ');
    proc1->cmd_path = NULL;
    proc1->redirs = malloc(sizeof(t_redir *));
    proc1->hpid = 0;
    if (!proc1->redirs)
    {
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0] = malloc(sizeof(t_redir));
    if (!proc1->redirs[0])
    {
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0]->type = 3;
    proc1->redirs[0]->pathordel = ft_strdup("eof\n");
    proc1->redirs[0]->next = NULL;
    proc1->next = proc2;
    proc1->prev = NULL;

    proc2->freeme = hell->freeme;
    proc2->cmd = split("cat", ' ');
    proc2->cmd_path = NULL;
    proc2->redirs = malloc(sizeof(t_redir *));
    if (!proc2->redirs)
    {
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->hpid = 0;
    proc2->redirs[0] = malloc(sizeof(t_redir));
    if (!proc2->redirs[0])
    {
        free(proc2->redirs);
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->redirs[0]->type = 3;
    proc2->redirs[0]->pathordel = ft_strdup("hell\n");
    proc2->redirs[0]->next = NULL;
    proc2->next = NULL;
    proc2->prev = proc1;

    *(hell->head) = proc1;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_hell *hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell, envp);

    return (0);
} */

/* 
t_hell *init_hell(char **envp)
{
    t_hell *hell = malloc(sizeof(t_hell));
    if (!hell)
        return (NULL);
    hell->freeme = malloc(sizeof(t_free *));
    if (!hell->freeme)
    {
        free(hell);
        return (NULL);
    }
    hell->freeme[0] = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->hdoc_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));
    if (!hell->head)
    {
        free(hell->freeme);
        free(hell);
        return (NULL);
    }
    *(hell->head) = NULL;
    hell->lastexit = 0;
    return (hell);
}

void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2)
    {
        free(proc1);
        free(proc2);
        return;
    }

    proc1->freeme = hell->freeme;
    proc1->cmd = split("cat", ' ');
    proc1->cmd_path = NULL;
    proc1->redirs = malloc(sizeof(t_redir *));
    proc1->hpid = 0;
    if (!proc1->redirs)
    {
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0] = malloc(sizeof(t_redir));
    if (!proc1->redirs[0])
    {
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0]->type = 3;  // Set type for heredoc
    proc1->redirs[0]->pathordel = ft_strdup("eof\n");  // Set pathordel for heredoc delimiter
    proc1->redirs[0]->next = NULL;

    proc1->next = proc2;
    proc1->prev = NULL;

    proc2->freeme = hell->freeme;
    proc2->cmd = split("cat -e", ' ');
    proc2->cmd_path = NULL;
    proc2->redirs = malloc(sizeof(t_redir *));
    if (!proc2->redirs)
    {
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->hpid = 0;
    proc2->redirs[0] = malloc(sizeof(t_redir));
    if (!proc2->redirs[0])
    {
        free(proc2->redirs);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->redirs[0]->type = 1;
    proc2->redirs[0]->pathordel = ft_strdup("out");
    proc2->redirs[0]->next = NULL;
    proc2->next = NULL;
    proc2->prev = proc1;

    *(hell->head) = proc1;
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_hell *hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell, envp);

    return (0);
}
 */


/* 
t_hell *init_hell(char **envp)
{
    t_hell *hell;

    hell = malloc(sizeof(t_hell));
    if (!hell)
        return (NULL);
    hell->freeme = malloc(sizeof(t_free));
    if (!hell->freeme)
    {
        free(hell);
        return (NULL);
    }
    hell->freeme[0] = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));
    if (!hell->head)
    {
        free(hell->freeme);
        free(hell);
        return (NULL);
    }
    *(hell->head) = NULL;
    hell->lastexit = 0;
    return (hell);
}

void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2)
    {
        free(proc1);
        free(proc2);
        return;
    }

    proc1->freeme = hell->freeme;
    proc1->cmd = split("cat -e", ' ');
    proc1->cmd_path = NULL;
    proc1->redirs = malloc(sizeof(t_redir *));
    if (!proc1->redirs)
    {
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0] = malloc(sizeof(t_redir));
    if (!proc1->redirs[0])
    {
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc1->redirs[0]->type = 0;
    proc1->redirs[0]->pathordel = ft_strdup("Makefile");
    proc1->redirs[0]->next = NULL;
    proc1->next = proc2;
    proc1->prev = NULL;

    proc2->freeme = hell->freeme;
    proc2->cmd = split("cat -e", ' ');
    proc2->cmd_path = NULL;
    proc2->redirs = malloc(sizeof(t_redir *));
    if (!proc2->redirs)
    {
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->redirs[0] = malloc(sizeof(t_redir));
    if (!proc2->redirs[0])
    {
        free(proc2->redirs);
        free(proc1->redirs[0]);
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }
    proc2->redirs[0]->type = 1;
    proc2->redirs[0]->pathordel = ft_strdup("out");
    proc2->redirs[0]->next = NULL;
    proc2->next = NULL;
    proc2->prev = proc1;
    *(hell->head) = proc1;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_hell *hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell, envp);

    return (0);
}

 */