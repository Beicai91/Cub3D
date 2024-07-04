NAME = cub
CC = gcc
CFLAGS = -Wextra -Werror -Wall -MMD -MP
FRAMEWORK = -framework OpenGL -framework AppKit
H_PATH = -I. -I ./libft
LIB_PATH = -L ./libft -L ./minilibx
LDLIBS = -lft -lmlx
LFT = libft/libft.a
LMLX = minilibx/libmlx.a
DODIR = dofile

SRCS = main.c \
	   init.c \
	   parse.c \
	   parse_utils.c \
	   safe_module.c \
	   utils.c \
	   handle_map_content.c \
	   game.c \
	   check_h_intersection.c \
	   check_v_intersection.c \
	   check_intersection_utils.c \
	   render.c \
	   move_player_fb.c \
	   move_player_lr.c

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
	make -C ./libft all
	make -C ./libft bonus

$(LMLX):
	make -C ./minilibx all

clean:
	rm -f $(OBJS) $(DEP)
	rm -rf $(DODIR)
	make -C ./libft fclean
	make -C ./minilibx clean

fclean: clean
	rm -f $(NAME)

re:fclean make

.PHONY: all clean fclean re



