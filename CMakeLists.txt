# Projet bibliothèque en C (C99)
cmake_minimum_required(VERSION 3.16)
project(bibliotheque_raylib C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Dossier des headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# === Chercher Raylib ===
find_package(raylib REQUIRED)   # on utilise REQUIRED pour s'assurer que raylib est trouvé

# Exécutable principal avec tous les fichiers sources
add_executable(bibliotheque
        src/main.c
        src/livres.c
        src/utilisateurs.c
        src/emprunts.c
        src/fichiers.c
        src/stats.c
)

# Lier Raylib à ton exécutable
target_link_libraries(bibliotheque raylib)

