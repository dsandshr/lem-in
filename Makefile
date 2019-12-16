# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlorine <tlorine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 18:21:34 by dsandshr          #+#    #+#              #
#    Updated: 2019/12/16 17:53:57 by tlorine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	lem-in
DIR_SRC				:=	./src
DIR_INCLUDE_LEM_IN	:=	./include
DIR_LIBFT			:=	./lib/libft/
SDL_LIB 			:=	./lib//SDL/
SDL_INCLUDE 		:=	./lib/SDL/SDL2.framework/Headers
DIR_INCLUDE_LIBFT	:=	./lib/libft/include
DIR_BIN				:=	bin/
DIRS_INCLUDE		:= $(DIR_INCLUDE_LEM_IN) $(DIR_INCLUDE_LIBFT) $(SDL_INCLUDE)

SRCS				:= valid_check.c \
						lem_in.c \
						write_ferm.c \
						error_procrssing.c \
						read_file.c \
						delete.c \
						create_matrix.c \
						march_of_ants.c \
						search_paths.c \
						suurbale.c \
						paths_functions.c \
						find_way.c \
						builds_paths.c \
						stack.c \
						update_ferm.c \
						read_main.c \
						split_vertex.c \
						null_go.c \
						vis_main.c \
						drawing.c \
						vis_write_ferm.c \
						vis_march.c \
						draw_traffic.c \
						flags.c \
						add_rooms.c

OBJS				:=	$(SRCS:.c=.o)
OBJ_WITH_DIR		:=	$(addprefix $(DIR_BIN), $(OBJS))
HEADERS				:=	lem_in.h
LIBFT				:=	libft.a

CFLAGS				:=	-Wextra -Werror -Wall -O3
CFLAG				:=	-c
NFLAG				:=	-o
IFLAG				:=	-I
CC					:=	gcc

MAKE_LIBFT			:=	make -C $(DIR_LIBFT)
REMOVE				:=	rm -rf

FRAME 				:= SDL2
SDL2 				:= -Wl,-rpath $(SDL_LIB) -F $(SDL_LIB) -framework $(FRAME)

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE_LEM_IN)
vpath %.a $(DIR_LIBFT)

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJ_WITH_DIR) $(NFLAG) $@ $(DIR_LIBFT)$(LIBFT) $(SDL2)

$(OBJS): %.o:%.c $(HEADERS) | $(DIR_BIN)
		$(CC) $(CFLAG) $(CFLAGS) $< $(addprefix $(IFLAG), $(DIRS_INCLUDE)) $(NFLAG) $(DIR_BIN)$@

$(DIR_BIN):
		mkdir -p $@
$(LIBFT):
		$(MAKE_LIBFT)

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