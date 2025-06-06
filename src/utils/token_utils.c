#include "../../includes/minishell.h"

t_token	*new_token(t_hell *hell, char *val)
{
	t_token	*token;

	if (!val)
		jump_ship(hell, 1);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		ft_terminate(1, &val);
		jump_ship(hell, 1);
	}
	token->expansion = malloc(sizeof(int));
	if (!token->expansion)
	{
		ft_terminate(1, &val);
		ft_terminate(1, &token);
		jump_ship(hell, 1);
	}
	token->expansion[0] = -1;
	token->qoute = NULL;
	token->token = val;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(t_hell *hell, t_token **tokens, char *val)
{
	t_token	*token;
	t_token	*node;

	token = new_token(hell, val);
	node = (*tokens);
	if (!node)
	{
		*tokens = token;
		return ;
	}
	while (node->next)
		node = node->next;
	token->prev = node;
	node->next = token;
}

t_token	*cut_token(t_token **tokens, t_token *token)
{
	t_token	*next;
	t_token	*prev;

	next = token->next;
	prev = token->prev;
	if (*tokens == token)
		*tokens = next;
	else
		prev->next = next;
	if (next)
		next->prev = prev;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

static void	cp_exp_nums(t_hell *hell, t_token *token, t_token *node, int pos)
{
	int		i;

	i = 0;
	while (token->expansion[i] != -1)
	{
		if ((token->expansion[i + 1] - pos > 0))
		{
			if (token->expansion[i] - pos < 0)
				add_num(hell, &(node->expansion), 0);
			else
				add_num(hell, &(node->expansion), token->expansion[i] - pos);
			add_num(hell, &(node->expansion), token->expansion[i + 1] - pos);
		}
		i += 2;
	}
}

void	divide_tokens(t_hell *hell, t_token *token, int pos, int spaces)
{
	t_token	*node;
	t_token	*next;
	char	*str;

	next = token->next;
	str = ft_strdup(token->token + pos + spaces);
	if (!str)
		jump_ship(hell, 1);
	node = new_token(hell, str);
	node->prev = token;
	node->next = next;
	token->next = node;
	if (next)
		next->prev = node;
	((char *)token->token)[pos] = 0;
	if (token->expansion)
		cp_exp_nums(hell, token, node, pos + spaces);
}
