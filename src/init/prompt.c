#include "../../includes/minishell.h"

void	writeprompt(void)
{
	write(1,"PROMPT: ", 8);
}