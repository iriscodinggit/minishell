#include "../../minishell.h"

int len_token(char *cmd)
{
	// WORK IN PROGRESS //
	int in_quotes;
	int space;
	int i;

	in_quotes = 0;
	space = 0;
	i = 0;
	while(cmd[i])
	{
		if(cmd[i] == '"' && in_quotes == 0)
			in_quotes = 1;
		else if(cmd[i] == '"' && in_quotes == 1)
			in_quotes = 0;
		if(cmd[i] == ' ' && in_quotes == 0)
		{	
			while(cmd[i] == ' ')
				i++;
			space++;
		}
		else
			i++;
	}
	return(space + 1);

}

int len_for_token(char *cmd, int i)
{
	int j = 0;
	int in_quotes;

	in_quotes = 0;
	while(cmd[i] == ' ')
		i++;
	while(cmd[i])
	{
		if (cmd[i] == ' ' && in_quotes == 0)
			break;
		else if(cmd[i] == '"' && in_quotes == 0)
			in_quotes = 1;
		else if(cmd[i] == '"' && in_quotes == 1)
			in_quotes = 0;

		i++;
		j++;
	}
	return(j);
}
// echo "hello WOLRD" H"e"llo wolrd

void free_all(t_token *token, int len)
{
	int i;

	i = 0;
	while(i < len)
	{
		free(token[i].str);
		i++;
	}
	free(token);

}

void token_copy(t_token *token, char *cmd, int i, int j)
{
	int in_quotes;
	int flag;
	int k;

	k = 0;
	flag = 0;
	in_quotes = 0;
	// echo test      0     1 
	while(cmd[j] == ' ')
		j++;
	while(cmd[j])
	{
		if (cmd[j] == ' ' && in_quotes == 0)
			break;
		else if(cmd[j] == '"' && in_quotes == 0)
		{
			j++;
			in_quotes = 1;
		}
		else if(cmd[j] == '"' && in_quotes == 1)
		{
			j++;
			in_quotes = 0;
		}
		else
		{ 
			token[i].str[k] = cmd[j];
			k++;
			j++;
		}
	}
	token[i].str[k] = '\0';
}
