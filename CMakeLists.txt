# Projet bibliothèque en C (C99)
cmake_minimum_required(VERSION 3.16)
project(bibliotheque C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Dossier des headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Exécutable principal avec tous les fichiers sources
add_executable(bibliotheque
        src/main.c
        src/livres.c
        src/utilisateurs.c
        src/emprunts.c
        src/fichiers.c
        src/stats.c
)

# Optionnel : définition pour le chemin du dossier data
target_compile_definitions(bibliotheque PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")
