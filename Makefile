NAME = minishell

CC = cc -Wall -Wextra -Werror -g

SRC = src/main.c \
	src/exec/exec.c src/exec/environment.c src/exec/heredoc.c src/exec/pipes.c src/exec/single_cmd.c src/exec/errors.c src/exec/redir_helpers.c src/exec/helpers.c src/exec/redirection.c src/exec/heredoc_helpers.c src/exec/env_helpers.c src/exec/command.c \
	src/parse/parse.c src/parse/parse_redir.c src/parse/gen_redir.c src/parse/parse_expand.c src/parse/get_expand.c src/parse/quotes.c src/parse/tokenizer.c \
	src/init/init.c \
	src/utils/exit.c src/utils/parse_utils.c src/utils/token_utils.c src/utils/expansion_tracker.c \
	src/utils/string_utils.c src/utils/alloc_utils.c src/utils/process_utils.c src/utils/dealloc_utils.c src/utils/list_utils.c \
	src/builtins/builtins.c src/builtins/echo.c src/builtins/env.c src/builtins/pwd.c src/builtins/export.c src/builtins/unset.c src/builtins/exit.c src/builtins/cd.c

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Linking...$(RESET)"
	make -C includes
	$(CC) $(OBJ) -o $(NAME) includes/libft.a -lreadline -lhistory
	@echo "$(GREEN) MINISHELL compiled.$(NO_COLOR)"

obj/%.o: src/%.c  $(HEADERS)
	@mkdir -p obj
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) -c $< -o $@
obj/exec/%.o: src/exec/%.c 
	@mkdir -p obj/exec
	$(CC) -c $< -o $@
obj/parse/%.o: src/parse/%.c 
	@mkdir -p obj/parse/
	$(CC) -c $< -o $@
obj/init/%.o: src/init/%.c 
	@mkdir -p obj/init/
	$(CC) -c $< -o $@
obj/exit/%.o: src/exit/%.c 
	@mkdir -p obj/exit/
	$(CC) -c $< -o $@
obj/utils/%.o: src/utils/%.c 
	@mkdir -p obj/utils/
	$(CC) -c $< -o $@
obj/builtins/%.o: src/builtins/%.c 
	@mkdir -p obj/builtins/
	$(CC) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning up...$(RESET)"
	$(RM) $(OBJ)
	$(RM) ./obj
	$(RM) includes/*.o
	@echo "$(RED) Object files cleaned.$(NO_COLOR)"

# Clean up everything
fclean: clean
	@echo "$(BLUE) Removing executable...$(RESET)"
	$(RM) $(NAME)
	$(RM) includes/libft.a
	@echo "$(RED) PROJECT cleaned.$(NO_COLOR)"

# Rebuild 
re: fclean all
	@echo "$(BLUE) Rebuilding Project...$(RESET)"

debug:
	make -C includes
	$(CC) $(SRC) includes/libft.a -g

.PHONY: clean fclean re all debug