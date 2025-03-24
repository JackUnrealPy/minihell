
// loop through list
// for each command, check if pipe, heredoc, simple command, or builtin

#include "../../includes/minishell.h"
#include "execution.h"

void    single_cmd(t_proc *head, char **envp);
void	ft_pipex(t_hell *hell);
int	determine_builtin(t_hell *hell, t_proc *head, int pipe);

int loop_cmds(t_hell *hell)
{
    // create envp -> built into struct
    // hell->new_envp = ft_double_strdup(hell->envp);

    if ((*hell->head) && !(*hell->head)->next)
    {
        if (!determine_builtin(hell, (*hell->head), 0)) // && !heredoc()
            single_cmd((*hell->head), hell->envp);
    }
    else if ((*hell->head) && (*hell->head)->next)
         ft_pipex(hell);
    else
        return (1);
    return (0);
}


// function from chatgpt to fill struct and be able to test
#include "../../includes/minishell.h"

// Initialize the t_hell structure
t_hell *init_hell(char **envp)
{
    t_hell *hell;

    hell = malloc(sizeof(t_hell) + sizeof(int) * 6);
    if (!hell)
        return (NULL);
    hell->freemeglobal = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc *));  // Allocate space for a double pointer
    if (!hell->head)
    {
        free(hell); // Free if head allocation fails
        return (NULL);
    }
    *(hell->head) = NULL; // Initialize the pointer to NULL
    hell->lastexit = 0;
    return (hell);
}

// Function to create and fill the process list for the given command
void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2)
        return;

    // Process 1: `env` with input redirection from Makefile
    proc1->cmd = ft_split("pwd", ' ');
    proc1->cmd_path = NULL;

    proc1->redirs = malloc(sizeof(t_redir));
    if (!proc1->redirs)
    {
        free(proc1);
        free(proc2);
        return;
    }

    // Input Redirection: < Makefile
    proc1->redirs->type = 0; // Input redirection
    proc1->redirs->pathordel = ft_strdup("Makefile");
    proc1->redirs->next = NULL;

    proc1->next = proc2;
    proc1->prev = NULL;

    // Process 2: `cat -e` with output redirection to "out"
    proc2->cmd = ft_split("cat -e", ' ');
    proc2->cmd_path = NULL;

    proc2->redirs = malloc(sizeof(t_redir));
    if (!proc2->redirs)
    {
        free(proc1->redirs);
        free(proc1);
        free(proc2);
        return;
    }

    // Output Redirection: > out
    proc2->redirs->type = 1; // Output redirection
    proc2->redirs->pathordel = ft_strdup("out");
    proc2->redirs->next = NULL;

    proc2->next = NULL;
    proc2->prev = proc1;

    // Assign the head pointer
    *(hell->head) = proc1;
}

int main(int argc, char **argv, char **envp)
{
    t_hell *hell;

    hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell);  // Function to handle execution

    return (0);
}


/* 
// builtins
// Initialize the t_hell structure
t_hell *init_hell(char **envp)
{
    t_hell *hell;

    hell = malloc(sizeof(t_hell) + sizeof(int) * 6);
    if (!hell)
        return (NULL);
    hell->freemeglobal = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc*));  // Allocate space for a double pointer
    if (!hell->head)
    {
        free(hell); // Don't forget to free if head allocation fails
        return (NULL);
    }
    *(hell->head) = NULL; // Initialize the pointer to NULL
    hell->lastexit = 0;
    return (hell);
}

// Function to create and fill the process list for the given command
void fill_hell(t_hell *hell)
{
    t_proc *proc = malloc(sizeof(t_proc));
    if (!proc)
        return;

    // Command: echo "hello there"
    proc->cmd = ft_split("env ", ' ');  // Split the command and arguments
    proc->cmd_path = NULL;

    // Allocate memory for the redirections
    proc->redirs = malloc(sizeof(t_redir) * 2);
    if (!proc->redirs)
    {
        free(proc);
        return;
    }

    // Input Redirection: < Makefile
    proc->redirs[0].type = 0; // Input redirection
    proc->redirs[0].pathordel = ft_strdup("Makefile");
    proc->redirs[0].next = &proc->redirs[1]; // Link to next redirection

    // Output Redirection: > out
    proc->redirs[1].type = 2; // Output redirection
    proc->redirs[1].pathordel = ft_strdup("out");
    proc->redirs[1].next = NULL; // End of redirections

    // This is a single process, so it has no next or prev
    proc->next = NULL;
    proc->prev = NULL;

    // Assign the head using the double pointer
    *(hell->head) = proc; // Set the head pointer to point to proc
}

int main(int argc, char **argv, char **envp)
{
    t_hell *hell;

    hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    loop_cmds(hell);  // Function to handle execution

    return (0);
} */


// testing pipes without builtins
// this works
// Function to initialize the t_hell structure
/* t_hell *init_hell(char **envp)
{
    t_hell *hell;

    hell = malloc(sizeof(t_hell) + sizeof(int) * 6);
    if (!hell)
        return (NULL);
    hell->freemeglobal = NULL;
    hell->argv = NULL;
    hell->argc = 0;
    hell->cmd_count = 0;
    hell->pipe_fd = NULL;
    hell->envp = envp;
    hell->head = malloc(sizeof(t_proc*));  // Allocate space for a double pointer
    if (!hell->head)
    {
        free(hell); // Don't forget to free if head allocation fails
        return (NULL);
    }
    *(hell->head) = NULL; // Initialize the pointer to NULL
    hell->lastexit = 0;
    return (hell);
}


// Function to manually create and fill the process list for testing
void fill_hell(t_hell *hell)
{
    t_proc *proc1 = malloc(sizeof(t_proc));
    t_proc *proc2 = malloc(sizeof(t_proc));
    t_proc *proc3 = malloc(sizeof(t_proc));
    if (!proc1 || !proc2 || !proc3)
        return;

    // Command 1: < in cat -e
    proc1->cmd = ft_split("cat -e", ' ');
    proc1->cmd_path = NULL;
    proc1->redirs = malloc(sizeof(t_redir));
    proc1->redirs->type = 0; // Input redirection
    proc1->redirs->pathordel = ft_strdup("in");
    proc1->redirs->next = NULL;
    proc1->next = proc2;
    proc1->prev = NULL;

    // Command 2: cat -e
    proc2->cmd = ft_split("cat -e", ' ');
    proc2->cmd_path = NULL;
    proc2->redirs = NULL;
    proc2->next = proc3;
    proc2->prev = proc1;

    // Command 3: cat -e > out
    proc3->cmd = ft_split("cat -e", ' ');
    proc3->cmd_path = NULL;
    proc3->redirs = malloc(sizeof(t_redir));
    proc3->redirs->type = 2; // Output redirection
    proc3->redirs->pathordel = ft_strdup("out");
    proc3->redirs->next = NULL;
    proc3->next = NULL;
    proc3->prev = proc2;

    // Assign the head using the double pointer
    *(hell->head) = proc1; // Set the head pointer to point to proc1
}


int main(int argc, char **argv, char **envp)
{
    t_hell *hell;

    hell = init_hell(envp);
    if (!hell)
    {
        perror("Failed to initialize shell");
        return (EXIT_FAILURE);
    }

    fill_hell(hell);
    ft_pipex(hell);

    return (0);
} */




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