cmake_minimum_required(VERSION 3.16)
project(bibliotheque C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(bibliotheque
        src/main.c
        src/livres.c
        src/utilisateurs.c
        src/emprunts.c
        src/fichiers.c
        src/stats.c
)
