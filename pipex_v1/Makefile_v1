NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS += -fsanitize=address

SRCS =	src/pipex.c \
		src/exec.c \
		src/init.c \
		src/utils.c \
		src/error.c

SRCS_BONUS =	src_bonus/pipex_bonus.c \
				src_bonus/exec_bonus.c \
				src_bonus/init_bonus.c \
				src_bonus/utils_bonus.c \
				src_bonus/error_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INCLUDES = -I include -I Libft
LIBFT = Libft/libft.a

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(NAME)

$(NAME):	$(OBJS)
			@$(MAKE) -C Libft > /dev/null
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "✅ Proyecto compilado correctamente."

# --------------------------------------------------------------
# 🛠 Compilar cada archivo fuente
# --------------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo "🔧 Compilado: $<"

# --------------------------------------------------------------
# Bonus
# --------------------------------------------------------------
bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS)
				@$(MAKE) -C Libft > /dev/null
				@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
				@echo "✅ Bonus compilado correctamente."

# --------------------------------------------------------------
# 🧹 Limpieza
# --------------------------------------------------------------

clean:
	@rm -f $(OBJS) $(OBJS_BONUS) > /dev/null
	@$(MAKE) -C Libft clean > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) > /dev/null
	@$(MAKE) -C Libft fclean > /dev/null
	@echo "🧼 Todo limpio: binarios y Libft."

re: fclean all

.PHONY: all clean fclean re libft bonus