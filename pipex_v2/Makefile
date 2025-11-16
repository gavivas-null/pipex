NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS += -fsanitize=address
INCLUDES = -I include -I Libft
LIBFT = Libft/libft.a
OBJ_DIR = obj

SRC_DIR = src
SRC	=	$(SRC_DIR)/pipex_core.c \
		$(SRC_DIR)/pipex_errors.c \
		$(SRC_DIR)/pipex_handle.c \
		$(SRC_DIR)/pipex_io.c \
		$(SRC_DIR)/pipex_path.c \
		$(SRC_DIR)/pipex_pipeline.c \
		$(SRC_DIR)/pipex_parse.c \
		$(SRC_DIR)/pipex.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJS)
			@$(MAKE) -C Libft > /dev/null
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "✅ Proyecto compilado correctamente."

# --------------------------------------------------------------
# 🛠 Compilar cada archivo fuente
# --------------------------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo "🔧 Compilado: $<"

# --------------------------------------------------------------
# 🧹 Limpieza
# --------------------------------------------------------------

clean:
	@rm -rf $(OBJ_DIR) > /dev/null
	@$(MAKE) -C Libft clean > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean rm
	@rm -f $(NAME) > /dev/null
	@$(MAKE) -C Libft fclean > /dev/null
	@echo "🧼 Todo limpio: binarios y Libft."

rm:
	@rm *.txt > /dev/null 2>&1 || true
	@rm ./outfile > /dev/null 2>&1 || true
	@rm ./infile > /dev/null 2>&1 || true
	@echo "🧼 .txt, infile y outfile eliminados."

re: fclean all

.PHONY: all clean fclean re libft rm