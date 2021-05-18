
NAME = minishell

CC = clang

CFLAGS = -I includes/ -I libft/includes/

LIBFT = -L libft -lft

MAIN_MAC = shell_mac shell2
MAIN_LINUX = shell_linux shell2

ALLOCATE = allocate_env allocate_history

BUILTINS = absolute_path cd debugger echo echo2 env error exit export history pwd testing unset

EXEC = complicated_exec complicated_exec2 complicated_exec3 complicated_exec4 exec

PARSING = add_to_list add_to_list2 add_to_list3 add_to_list4 add_to_list5\
          add_to_list6 add_to_simple_cmd add_to_simple_cmd2 add_to_simple_cmd3\
          add_to_simple_cmd4 command_tables command_tables2 command_tables3\
		  command_tables4

TERMCAPS = termcaps termcaps2 termcaps3

UTILS = env_func env_func2 env_func3 free signals utils utils2

SRC = $(addsuffix .c, $(addprefix srcs/allocate/, $(ALLOCATE))) \
	  $(addsuffix .c, $(addprefix srcs/builtin/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/termcaps/, $(TERMCAPS))) \
	  $(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

SRC_MAC = $(addsuffix .c, $(addprefix , $(MAIN_MAC)))
SRC_LINUX = $(addsuffix .c, $(addprefix , $(MAIN_LINUX)))

OBJ_MAC = $(SRC:c=o) $(SRC_MAC:c=o)
OBJ_LINUX = $(SRC:c=o) $(SRC_LINUX:c=o)

all: $(NAME)

$(NAME): $(OBJ_MAC)
	@echo "\n"
	@make bonus -C libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAC) $(LIBFT) -lncurses
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

linux: $(OBJ_LINUX)
	@echo "\n"
	@make bonus -C libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_LINUX) $(LIBFT) -lncurses
	@echo "\n\033[0mDone !"

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ_MAC)
	@rm -f $(OBJ_LINUX)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ_MAC)
	@rm -f $(OBJ_LINUX)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re test norm
