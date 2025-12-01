# Projet bibliothèque en C (C99)

cmake_minimum_required(VERSION 3.16)
project(bibliotheque_raylib C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Dossier des headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# === Chercher Raylib ===
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

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
target_link_libraries(bibliotheque PRIVATE raylib)



