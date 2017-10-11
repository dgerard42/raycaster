# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/27 19:15:03 by dgerard           #+#    #+#              #
#    Updated: 2017/10/02 15:40:44 by dgerard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c\
		raycaster.c\
		key_controls.c\
		maps.c\
		draw_maze.c\

LIBFT =	libft/ft_atoi.c\
		libft/ft_memdel.c\
		libft/ft_putchar.c\
		libft/ft_putstr.c\
		libft/ft_strequ.c\

PRINTF = printf/ft_printf.c\
		printf/check_flags.c\
		printf/outputs.c\
		printf/parse_args.c\
		printf/print_letters.c\
		printf/print_numbers.c\
		printf/ft_isdigit.c\
		printf/ft_numlen_ll.c\
		printf/ft_numlen_ull.c\
		printf/ft_power_ll.c\
		printf/ft_power_ull.c\
		printf/ft_strlen.c\

LIBMLX = minilibx/libmlx.a

ODIR = ofiles

FRAMEWORKS = -framework OpenGL -framework AppKit

OFILES = $(addprefix $(ODIR)/,$(SRCS:.c=.o))

LIBFTO = $(LIBFT:.c=.o)

PRINTFO = $(PRINTF:.c=.o)

$(ODIR)/%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@
	@/bin/echo -n "❂❂❂❂❂"

%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@
	@/bin/echo -n "❂❂❂❂❂"

all: $(NAME)

$(NAME): $(OFILES) $(LIBFTO) $(PRINTFO)
	@make -C minilibx/
	@gcc $(FLAGS) -o $@ $(OFILES) $(LIBFTO) $(PRINTFO) $(FRAMEWORKS) $(LIBMLX)
	@echo "\033[32m[wolf3d created ( ͡° ͜ʖ ͡°)]\033[0m"

$(OFILES): | $(ODIR)

$(ODIR):
	@mkdir $(ODIR)

clean:
	@rm -f $(LIBFTO)
	@rm -f $(PRINTFO)
	@rm -rf $(ODIR)
	@echo "\033[31m[.o files deleted (╯°□°）╯︵ ┻━┻ ]\033[0m"
	@make -C minilibx/ clean

fclean: clean
	@/bin/rm -f rm $(NAME)
	@echo "\033[31m[executable deleted ᕙ(⇀‸↼‶)ᕗ ]\033[0m"

re: fclean all
