# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 18:21:34 by dsandshr          #+#    #+#              #
#    Updated: 2019/11/10 12:29:23 by tlorine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	./lem-in
DIR_SRC				:=	src
DIR_INCLUDE_LEM_IN	:=	./include
DIR_LIBFT			:=	./libft/
DIR_INCLUDE_LIBFT	:=	./libft/include
DIR_BIN				:=	bin/
DIRS_INCLUDE		:=	$(DIR_INCLUDE_LEM_IN) $(DIR_INCLUDE_LIBFT)

SRCS				:= valid_check.c \
						lem_in.c \
						write_ferm.c \
						error_procrssing.c \
						read_file.c \
						update_ferm.c \
						delete.c \
						create_matrix.c \

OBJS				:=	$(SRCS:.c=.o)
OBJ_WITH_DIR		:=	$(addprefix $(DIR_BIN), $(OBJS))
HEADERS				:=	lem_in.h
LIBFT				:=	libft.a

CFLAGS				:=	-Wextra -Werror -Wall -g
CFLAG				:=	-c
NFLAG				:=	-o
IFLAG				:=	-I
CC					:=	gcc

MAKE_LIBFT			:=	make -C $(DIR_LIBFT)
REMOVE				:=	rm -rf

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE_FILLER)
vpath %.a $(DIR_LIBFT)

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJ_WITH_DIR) $(NFLAG) $@ $(DIR_LIBFT)$(LIBFT)

$(OBJS): %.o:%.c $(HEADERS) | $(DIR_BIN)
		$(CC) $(CFLAG) $(CFLAGS) $< $(addprefix $(IFLAG), $(DIRS_INCLUDE)) $(NFLAG) $(DIR_BIN)$@

$(DIR_BIN):
		mkdir -p $@
$(LIBFT):
		$(MAKE_LIBFT)
$(FILLER_VIS):
		$(MAKE_FILLER_VIS)

clean:
		$(REMOVE) $(OBJ_WITH_DIR)
		$(REMOVE) $(DIR_BIN)
		$(MAKE_LIBFT) clean

fclean: clean
		$(REMOVE) $(NAME)
		$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: clean fclean re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) $(LIBFT) clean fclean re