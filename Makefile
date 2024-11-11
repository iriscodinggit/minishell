NAME        = minishell
CC          = cc
CFLAGS      = # -Wall -Werror -Wextra 
LDFLAGS     = -lreadline -g3 -fsanitize=address
RM          = rm -rf

SOURCES     = src/parsing/pars_bin.c src/parsing/pars_cd.c src/parsing/pars_quot.c src/parsing/pars_dolar.c src/parsing/pars_export.c src/parsing/pars_cmd.c src/parsing/pars_syntax.c src/parsing/pars_check.c src/parsing/pars_main.c \
              src/token/token_main.c src/token/token_id.c src/token/token_set.c src/token/token_utils.c src/token/token_pars.c \
              src/executer/exec_main.c src/executer/exec_pipe.c src/executer/exec_pipe_multi.c \
			  src/builtins/echo.c src/builtins/pwd.c src/builtins/cd.c \
              src/micro_lib/ft_split.c src/micro_lib/utils.c src/micro_lib/ft_strjoin.c src/micro_lib/split_basic.c \
              main.c

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	@printf "\033[0;30mGenerating minishell objects... %-33.33s\r" $@
	@$ $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@ $(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME) 
	@echo "\n\033[0;32mDone !"

clean:
	@ $(RM) $(OBJECTS)
	@echo "\033[33;36mClean ✅"

fclean: clean
	@echo "\n\033[33;36mFclean ✅\n"
	@ $(RM) $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re