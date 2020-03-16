BLUE =\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[1;38;5;110m
GREEN = \033[1;32;111m
LIGHT_GREEN = \033[0;38;5;121m
LIGHT_RED = \033[0;31;5;110m
FLASH_GREEN = \033[33;32m
WHITE_BOLD = \033[37m
GREY = \033[3;90m
ORANGE = \033[3;91m
YELLOW = \033[0;33m

SRCS_PARSING	=	$(addprefix parsing/, parsing.c parsing_allocator.c block_allocation.c set_redirections.c separator_counter.c analyser.c fill_str_with_stars.c)

SRCS_EXEC		=	$(addprefix exec/, exec_cmd.c builtin.c signal.c builtin_export.c builtin_cd.c) 

SRCS_VAR		=	$(addprefix var/, env.c)

SRCS_REDIR		=	$(addprefix redirections/, redirections.c right_redirections.c lonely_command.c left_redirections.c)

SRCS_DISPLAY	=	$(addprefix display/, display.c)

SRCS_UTILS		=	$(addprefix utils/, ft_exit.c)

SRCS_NAME		=	main.c $(SRCS_PARSING) $(SRCS_EXEC) $(SRCS_VAR) $(SRCS_DISPLAY) $(SRCS_REDIR) $(SRCS_UTILS)

SRC_PATH		=	srcs/

SRCS			=	$(addprefix $(SRC_PATH), $(SRCS_NAME))

HEADER			=	includes/

OBJ_NAME		=	${SRCS_NAME:.c=.o}

OBJ_PATH		=	obj/

OBJ				=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

NAME			=	minishell

RM				=	rm -rf

FLAG			=	-Wall -Wextra -g3 -O3 #-Werror -fsanitize=address

LIBFT			=	libft/libft.a

all: $(OBJ_PATH) $(LIBFT) $(NAME) $(HEADER)
	@:

e:	exec

exec:
	@${MAKE} all
	@./minishell

clfd:
	@rm -f bli blo blu ble cat ls env a b c aa bb pouet toto make 2>/dev/null

$(LIBFT): libft/includes/libft.h
	@make -C libft/

libft/includes/libft.h:
	@git submodule update --init --recursive

$(NAME): $(OBJ)
	@gcc $(FLAG) $(OBJ) $(LIBFT) -o $(NAME)
	@printf "	\033[2K\r$(DARK_BLUE)minishell\t: $(LIGHT_GREEN)Updated\n\033[0m"

$(OBJ_PATH):
	@mkdir -p obj/ 2> /dev/null
	@mkdir -p obj/parsing 2> /dev/null
	@mkdir -p obj/exec 2> /dev/null
	@mkdir -p obj/var 2> /dev/null
	@mkdir -p obj/display 2> /dev/null
	@mkdir -p obj/redirections 2> /dev/null
	@mkdir -p obj/utils 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)/minishell.h Makefile
	@printf "\033[2K\r$(LIGHT_RED)Compiling...	\033[37m$<\033[36m \033[0m"
	@gcc $(FLAG) -I $(HEADER) -I libft/includes/ -c $< -o $@

clean:
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/.	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/...	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/.	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/...	\033[37m"
	@sleep 0.1
	@${RM} ${OBJ_PATH} cube3D.dSYM
	@printf "\33[2K\r$(LIGHT_RED)Deleted successfully!\n\033[0m"

fclean: clean
	@${RM} ${NAME}

re:
	@$(MAKE) fclean
	@make -C libft/ re
	@$(MAKE) all

norme:
	@norminette $(SRC_PATH) $(HEADER) | grep -v "42 header"

full_norme: norme
	@make -C libft/ norme

normed:
	@norminette $(SRC_PATH) $(HEADER)
	@$(MAKE) continue
	@echo ""
	@git add .
	@git commit -m "normed" 1>/dev/null
	@printf "\33[2K\r$(YELLOW)Push on repositories ?\n\033[0m"
	@$(MAKE) continue
	@echo ""
	@$(MAKE) push

push:
	@printf "\33[2K\r$(LIGHT_RED)Pushing 	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing .	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ...	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing 	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing .	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ...	\033[37m"
	@sleep 0.1
	@git push origin `git symbolic-ref --short HEAD`
	@printf "\33[2K\r$(FLASH_GREEN)Pushed successfully on vogsphere !\n\033[0m"

update:
	@git request-pull HEAD https://github.com/tclaudel/minishell.git master

lib:
	@make -C libft/

cleanlib:
	@$(MAKE) clean
	@make -C libft/ clean

fcleanlib:
	@$(MAKE) fclean
	@make -C libft/ fclean

relib:
	@$(MAKE) fclean
	@make -C libft/ re
	@$(MAKE) all

continue:
	@echo ""
	@while [ -z "$$CONTINUE" ]; do \
		read -r -p "Press [y/N] to continue : " CONTINUE; \
	done ; \
	[ $$CONTINUE == "y" ] || [ $$CONTINUE == "Y" ] || (echo "Exiting ..." ; exit 1 2> /dev/null)

git-%:
	@$(MAKE) clfd
	# @$(MAKE) norme
	@$(MAKE) continue
	@echo ""
	@$(MAKE) test
	@$(MAKE) continue
	@echo ""
	@git add .
	@git status
	@$(MAKE) continue
	@echo ""
	@printf "\33[2K\r$(FLASH_GREEN)Commit name :\t[$(@:git-%=%)]\n\033[0m"
	@$(MAKE) continue
	@git commit -m "$(@:git-%=%)" 1>/dev/null
	@printf "\33[2K\r$(YELLOW)\nPush on repositories ?\033[0m"
	@echo ""
	@$(MAKE) continue
	@echo ""
	@$(MAKE) push
	@echo ""
	@printf "\33[2K\r$(GREEN)Everything done\n\n\033[0m"

pull:
	@git checkout master
	@git pull origin master
	@gco $USER 2> /dev/null
	@git merge master

call: all
	@nm -g $(addprefix ${OBJ_PATH}, ${OBJ_NAME})

ew:
	@say -v Fiona"Aurelien comment va ton print f ?"

test: all
	@sh tester/test.sh 0.01
	@printf "\33[2K\r$(GREEN)Test done\n\n\033[0m"

full_check: all
	@$(MAKE) full_norme
	@$(MAKE) continue
	@echo ""
	@$(MAKE) call
	@$(MAKE) continue
	@echo ""
	@$(MAKE) relib
	@printf "\33[2K\r$(FLASH_GREEN)\nCommit ?\n\033[0m"
	@$(MAKE) continue
	@echo ""
	@git add .
	@git commit -m "full checked" 1>/dev/null
	@printf "\33[2K\r$(YELLOW)Push on repositories ?\n\033[0m"
	@$(MAKE) continue
	@echo ""
	@$(MAKE) push

.PHONY: all clean fclean re bonus norme push cleanlib fcleanlib relib continue git-% call ew full_check e exec
