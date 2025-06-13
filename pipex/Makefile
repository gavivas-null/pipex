NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS += -fsanitize=address

SRCS =	src/pipex.c \
		src/exec.c \
		src/init.c \
		src/utils.c \

OBJS = $(SRCS:.c=.o)
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
# 🧹 Limpieza
# --------------------------------------------------------------

clean:
	@rm -f $(OBJS) > /dev/null
	@$(MAKE) -C Libft clean > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME) > /dev/null
	@$(MAKE) -C Libft fclean > /dev/null
	@echo "🧼 Todo limpio: binarios y Libft."

re: fclean all

.PHONY: all clean fclean re libft