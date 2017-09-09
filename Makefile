# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/27 19:15:03 by dgerard           #+#    #+#              #
#    Updated: 2017/09/08 20:44:05 by dgerard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

FLAGS = -Wall -Werror -Wextra

SRCS = main.c\
		raycaster.c\

LIBFT = libft/ft_power.c\
		libft/ft_atoi.c\

LIBMLX = minilibx/libmlx.a

LIBFTDIR = libft

ODIR = ofiles

FRAMEWORKS = -framework OpenGL -framework AppKit

OFILES = $(addprefix $(ODIR)/,$(SRCS:.c=.o))

LIBFTO = $(LIBFT:.c=.o)

$(ODIR)/%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@
	@/bin/echo -n "❂❂❂❂❂"

%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@
	@/bin/echo -n "❂❂❂❂❂"

all: $(NAME)

$(NAME): $(OFILES) $(LIBFTO)
	@make -C minilibx/
	@gcc $(CFLAGS) -o $@ $(OFILES) $(LIBFTO) $(FRAMEWORKS) $(LIBMLX) libftprintf.a
	@echo "\033[32m[wolf3d created ( ͡° ͜ʖ ͡°)]\033[0m"

$(OFILES): | $(ODIR)

$(ODIR):
	@mkdir $(ODIR)

clean:
	@rm -f $(LIBFT0)
	@rm -rf $(ODIR)
	@echo "\033[31m[.o files deleted (╯°□°）╯︵ ┻━┻ ]\033[0m"
	@make -C minilibx/ clean

fclean: clean
	@/bin/rm -f rm $(NAME)
	@echo "\033[31m[executable deleted ᕙ(⇀‸↼‶)ᕗ ]\033[0m"

re: fclean all
