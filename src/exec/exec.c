
// loop through list
// for each command, check if pipe, heredoc, simple command, or builtin

#include "../../includes/minishell.h"
#include "execution.h"

void    single_cmd(t_proc *head, char **envp);
void	ft_pipex(t_hell *hell);

int loop_cmds(t_hell *hell)
{
    ft_pipex(hell);
    // create envp -> built into struct
    // hell->new_envp = ft_double_strdup(hell->envp);

    // if ((*hell->head) && !(*hell->head)->next)
    //     single_cmd((*hell->head), hell->envp);
    // else
    // {
    //     while ((*hell->head))
    //     {
    //         // else if ((*hell->head) && (*hell->head)->redirs->type == 3) // heredoc
    //         //     heredoc();
    //         if ((*hell->head) && (*hell->head)->next) // pipe
    //             ft_pipes((*hell->head), hell->envp);
    //         else
    //             exit(1);
    //         (*hell->head) = (*hell->head)->next;
    //     }
    // }
    return (0);
}





// void setup_ls_redir(t_hell *hell)
// {
//     if (!hell)
//         return;

//     // Allocate t_proc, t_redir, and t_free
//     t_proc *proc = malloc(sizeof(t_proc));
//     t_redir *redir = malloc(sizeof(t_redir));
//     t_free *free_proc = malloc(sizeof(t_free));
//     t_free *free_redir = malloc(sizeof(t_free));

//     if (!proc || !redir || !free_proc || !free_redir)
//     {
//         perror("malloc failed");
//         exit(EXIT_FAILURE);
//     }

//     // Set up the redirection
//     redir->type = 1; // Output redirection
//     redir->pathordel = ft_strdup("out");
//     redir->input_fd = -1; // Not used for output redirection
//     redir->output_fd = -1; // We'll set this later using open()
//     redir->next = NULL;

//     // Set up the process
//     proc->cmd = malloc(sizeof(char *) * 2);
//     if (!proc->cmd)
//     {
//         perror("malloc failed");
//         exit(EXIT_FAILURE);
//     }
//     proc->cmd[0] = ft_strdup("ls");
//     proc->cmd[1] = NULL;
//     proc->cmd_path = NULL;  // To be set later
//     proc->pid = 0;          // Will be set after fork()
//     proc->input = NULL;     // No input redirection
//     proc->redirs = redir;
//     proc->next = NULL;
//     proc->prev = NULL;

//     // Set up free tracking
//     free_proc->freeme = proc;
//     free_proc->next = free_redir;
//     free_redir->freeme = redir;
//     free_redir->next = hell->freemeglobal;
//     hell->freemeglobal = free_proc;

//     // Set the head of the list
//     hell->head = malloc(sizeof(t_proc *));
//     if (!hell->head)
//     {
//         perror("malloc failed");
//         exit(EXIT_FAILURE);
//     }
//     *(hell->head) = proc;
// }


// int main(int argc, char **argv, char **envp)
// {
// 	t_hell *hell = malloc(sizeof(t_hell));
// 	if (!hell)
// 	{
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	hell->freemeglobal = NULL;
// 	hell->argv = argv;
// 	hell->envp = envp;
// 	hell->head = NULL;
// 	hell->lastexit = 0;

// 	setup_ls_redir(hell);
// 	loop_cmds(hell);

// 	return (0);
// }



// int main(int argc, char **argv, char **envp)
// {
//     t_hell *hell = malloc(sizeof(t_hell));
//     setup_ls_redir(hell, argc, argv, envp);
//     loop_cmds(hell);
// }