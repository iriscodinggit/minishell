#include "../../minishell.h"

// -- Work in progress -- // 



// -- Work in progress -- //


void child_process(int fd[2], t_token *token, char *file_in) 
{
    int fd_in;
	char **cmd_exec;
	char *path;
	char *cmd_join;
	int i;

	i = 0;
    if (file_in) 
	{
        fd_in = open(file_in, O_RDONLY);
        if (fd_in < 0) 
		{
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    // Duplication de la sortie du pipe vers stdout
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
	i = 0;
	cmd_join = calloc(1, 1);
	while(token[i].id != 6)
	{
		cmd_join = ft_strjoin(cmd_join, token[i].str);
		cmd_join = ft_strjoin(cmd_join, " ");
		i++;
	}
	cmd_exec = ft_split(cmd_join, ' ');

    
	/* Work in progress, 17/10 : -> Implementation de la verification et execution d'un builtin*/
	if(check_cmd_quotes(cmd_exec[0]) > 1)
	{
		//printf("BUILTIN DETECTED\n");
		if(check_cmd_quotes(cmd_exec[0]) == 2)
			echo(token, i);
		else if(check_cmd_quotes(cmd_exec[0]) == 3)
			cd(token[1].str);
		else if(check_cmd_quotes(cmd_exec[0]) == 4)
			pwd();
		exit(0);
	}
	path = make_path(cmd_exec[0]);
    execve(path, cmd_exec, NULL);
}


// Processus parent pour la deuxième commande
void parent_process(int fd[2], t_token *token, char *file_out) 
{
    int fileout;
	char **cmd_exec;
	char *path;
	char *cmd_join;
	int i;
	

	cmd_join = calloc(1, 1);
    wait(0);
    // Duplication de l'entrée du pipe vers stdin
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    close(fd[0]);
    if (file_out) 
	{
        fileout = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (fileout == -1) 
		{
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fileout, STDOUT_FILENO);
        close(fileout);
    }
	
	i = 0;
	while(token[i].id != 6)
		i++;
	i++;
	while(token[i].str)
	{
		//fprintf(stderr, "%d\n", token[i].id);
		if(token[i].id == 4 || token[i].id == 5)
			i++;
		else
		{
			cmd_join = ft_strjoin(cmd_join, token[i].str);
			cmd_join = ft_strjoin(cmd_join, " ");
			i++;
		}
	}

	cmd_exec = ft_split(cmd_join, ' ');
	if(check_cmd_quotes(cmd_exec[0]) > 1)
	{
		//printf("BUILTIN DETECTED\n");
		if(check_cmd_quotes(cmd_exec[0]) == 2)
			echo(token, i);
		else if(check_cmd_quotes(cmd_exec[0]) == 3)
			cd(token[1].str);
		else if(check_cmd_quotes(cmd_exec[0]) == 4)
			pwd();
		free(cmd_join);
		exit(0);
	}
	path = make_path(cmd_exec[0]);
    // Exécution de la commande
    execve(path, cmd_exec, NULL);
}


void pipex_simple(t_token *token, t_shell *shell)
{
	/* IDEE DU  
	
	
	*/



	// il y'a que un pipe -> echo test | pwd  
	// On fait un split avec | comme delimiter. 
	// Apres il suffit de refaire un split  sur le split si la commande est dans le  /bin
	// Ou d'executer le builtin 
	char **cmd_split;
	char *fd_in;
	char *fd_out;
	pid_t pid;
	int id_exec;
	int fd[2];
	int i;

	fd_in = NULL;
	fd_out = NULL;
	i = 0;

	while(token[i].str)
	{
		// Problem ici avec le nom il faut tej > et <  avant le nom
		if(token[i].id == 5)
			fd_in = ft_strdup(token[i].str);
		else if(token[i].id == 4)
			fd_out = ft_strdup(token[i].str);
		i++;
	}
	pipe(fd);
	// Le probleme vient du faite que je fais un split du shell->cmd et pas de token
	// TRY something,
	
	// Bizzare je ne sais pas si il ne va pas falloir changer quelques choses ici 
	// On est fasse a deux fois ou on fait le meme code. About the function clean name 
	/*
	cmd_split = ft_split_basic(shell->cmd, '|');
	
	i = 0;
	while(cmd_split[i])
	{
		// Problem ici avec le nom il faut tej > et <  avant le nom
		cmd_split[i] = clean_name(cmd_split[i]);
		i++;
	}
	*/
	pid = fork();
	if(pid == -1)
		return ; // ERREUR
	// AJOUTER UN CODE D'EXECUTION quand on execute la commande child et parent
	// afin de differencier les builtins des /bin
	
	else if(pid == 0)
		child_process(fd, token, fd_in);
	else
		parent_process(fd, token, fd_out);
	
	// l'un des derniers probleme est que quand on a un infile, si c'est 
	// cat < main.c | grep "if" -> SEGFAULT
	// la on sait que il y'a que un pipe // 

}
// -- Work in progress -- // 