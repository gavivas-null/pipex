#!/bin/bash

# Colores
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
RESET="\033[0m"

# Crear archivo de entrada con contenido personalizado
create_input_file() {
	echo -e "$1" > in.txt
}

# Función para correr un test con valgrind
run_test() {
	echo -e "${BLUE}==> Test: $1${RESET}"
	echo -e "${YELLOW}Comando: $2${RESET}"
	valgrind --leak-check=full --track-origins=yes $2
	echo -e "${GREEN}------------------------------------------${RESET}\n"
}

# Recompila el proyecto
make re

### 📌 TEST 1: Comandos válidos
create_input_file "Hola Gabi\nEsto es una prueba"
run_test "Comandos válidos (cat | wc -l)" "./pipex in.txt \"cat\" \"wc -l\" out.txt"

### 📌 TEST 2: Primer comando inválido
create_input_file "esto no importa"
run_test "Primer comando inválido" "./pipex in.txt \"noexiste\" \"wc -l\" out.txt"

### 📌 TEST 3: Segundo comando inválido
create_input_file "otra prueba"
run_test "Segundo comando inválido" "./pipex in.txt \"cat\" \"nocomando\" out.txt"

### 📌 TEST 4: Archivo de entrada no existe
rm -f notfound.txt
run_test "Archivo de entrada NO existe" "./pipex notfound.txt \"cat\" \"wc -l\" out.txt"

### 📌 TEST 5: Sin permisos de lectura
create_input_file "contenido privado"
touch secret.txt
chmod 000 secret.txt
run_test "Archivo sin permisos de lectura" "./pipex secret.txt \"cat\" \"wc -l\" out.txt"
chmod 644 secret.txt
rm secret.txt

### 📌 TEST 6: Archivo de salida sin permisos de escritura
create_input_file "texto normal"
touch locked.txt
chmod 444 locked.txt
run_test "Archivo de salida bloqueado (no escribible)" "./pipex in.txt \"cat\" \"wc -l\" locked.txt"
chmod 644 locked.txt
rm locked.txt

# Limpieza final
rm -f in.txt out.txt
