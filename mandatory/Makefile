NAME = cub3D
CC = gcc
CFLAGS = -Wextra -Werror -Wall -MMD -MP -g
FRAMEWORK = -framework OpenGL -framework AppKit
H_PATH = -I ./include -I ./lib/libft
LIB_PATH = -L ./lib/libft -L ./lib/minilibx
LDLIBS = -lft -lmlx
LFT = ./lib/libft/libft.a
LMLX = ./lib/minilibx/libmlx.a
DODIR = dofile

SRCS = src/main.c \
	   src/init1.c \
	   src/init2.c \
	   src/parse.c \
	   src/parse_utils1.c \
	   src/parse_utils2.c \
	   src/safe_module.c \
	   src/utils1.c \
	   src/utils2.c \
	   src/handle_map_content1.c \
	   src/handle_map_content2.c \
	   src/game1.c \
	   src/game2.c \
	   src/check_h_intersection1.c \
	   src/check_h_intersection2.c \
	   src/check_v_intersection1.c \
	   src/check_v_intersection2.c \
	   src/check_intersection_utils.c \
	   src/render1.c \
	   src/render2.c \
	   src/move_player_fb.c \
	   src/move_player_lr.c \
	   src/move_utils.c \
	   src/rotate.c

OBJS = $(patsubst %.c,$(DODIR)/%.o,$(SRCS))
DEP = $(patsubst %.o,%.d,$(OBJS))

all:$(NAME)

-include $(DEP)

$(NAME): $(OBJS) $(LFT) $(LMLX)
	$(CC) $(CFLGAS) $(LIB_PATH) $(LDLIBS) $(FRAMEWORK) $(OBJS) -o $@

$(OBJS):$(DODIR)/%.o:%.c | $(DODIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(H_PATH) -c $< -o $@ -MF $(DODIR)/$*.d

$(DODIR):
	mkdir -p $@

$(LFT):
	make -C ./lib/libft all
	make -C ./lib/libft bonus

$(LMLX):
	make -C ./lib/minilibx all

clean:
	rm -f $(OBJS) $(DEP)
	rm -rf $(DODIR)
	make -C ./lib/libft fclean
	make -C ./lib/minilibx clean

fclean: clean
	rm -f $(NAME)

re:fclean all

.PHONY: all clean fclean re



