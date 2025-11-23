NAME = libpipex.a

AR = ar
ARFLAG = -rcs
INCLUDES = -I include -I Libft
LIBFT = Libft/libft.a
OBJ_DIR = obj

SRC_DIR = src
SRC	=	$(SRC_DIR)/pipex_errors.c \
		$(SRC_DIR)/pipex_io.c \
		$(SRC_DIR)/pipex_path.c \
		$(SRC_DIR)/pipex_pipeline.c \
		$(SRC_DIR)/pipex.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(OBJ_DIR) libft $(NAME)

libft:
	@$(MAKE) -C Libft > /dev/null

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAG) $(NAME) $(OBJS)
	@echo "✅ Librería libpipex.a creada correctamente."

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
	@echo "🧹 Archivos objeto eliminados."

fclean: clean
	@rm -f $(NAME) > /dev/null
	@$(MAKE) -C Libft fclean > /dev/null
	@echo "🧼 Todo limpio: libpipex.a y libft."

re: fclean all

.PHONY: all clean fclean re libft