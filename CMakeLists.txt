cmake_minimum_required(VERSION 3.26)

# ===========================================================
# 1) Determine LLVM / Clang root path
#    - Priority 1: Environment variable LLVM_HOME
#    - Priority 2: Windows  -> C:/llvm-package  (assuming direct build path)
#                  Linux    -> Empty (use clang from PATH)
# ===========================================================
if(DEFINED ENV{LLVM_HOME})
    get_filename_component(LLVM_ROOT "$ENV{LLVM_HOME}" ABSOLUTE)
else()
    if(WIN32)
        set(LLVM_ROOT "C:/llvm-package")
    else()
        set(LLVM_ROOT "")
    endif()
endif()

# Default compiler names
set(CLANG_C   "clang")
set(CLANG_CXX "clang++")

# Use clang from LLVM_ROOT if available
if(LLVM_ROOT)
    set(CLANG_C   "${LLVM_ROOT}/bin/clang")
    set(CLANG_CXX "${LLVM_ROOT}/bin/clang++")

    if(WIN32)
        set(CLANG_C   "${CLANG_C}.exe")
        set(CLANG_CXX "${CLANG_CXX}.exe")
    endif()
endif()

# ===========================================================
# 2) Force set C / C++ compilers to clang / clang++
#    - Set as CACHE before calling project()
# ===========================================================
set(CMAKE_C_COMPILER
    "${CLANG_C}"
    CACHE FILEPATH "C compiler (clang)" FORCE)

set(CMAKE_CXX_COMPILER
    "${CLANG_CXX}"
    CACHE FILEPATH "C++ compiler (clang++)" FORCE)

# Generate compile_commands.json (for VSCode IntelliSense)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===========================================================
# 3) LLD linker setup (if available) + -fuse-ld=lld
# ===========================================================
set(LLD_PATH "")

if(LLVM_ROOT)
    if(WIN32)
        set(LLD_CANDIDATE "${LLVM_ROOT}/bin/ld.lld.exe")
    else()
        set(LLD_CANDIDATE "${LLVM_ROOT}/bin/ld.lld")
    endif()

    if(EXISTS "${LLD_CANDIDATE}")
        set(LLD_PATH "${LLD_CANDIDATE}")
    endif()
endif()

if(LLD_PATH)
    set(CMAKE_LINKER
        "${LLD_PATH}"
        CACHE FILEPATH "LLD linker" FORCE)
endif()

# Add flags for clang to use lld internally
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS
    "${CMAKE_MODULE_LINKER_FLAGS} -fuse-ld=lld")

# ===========================================================
# 4) Project declaration
# ===========================================================
set(PROJECT_NAME "hello_llvm_clang")
project(${PROJECT_NAME} LANGUAGES C CXX)

set(EXE_NAME "hello")

# ===========================================================
# 5) Sample executable
# ===========================================================

# Collect all .cpp files in current directory
file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(${EXE_NAME} ${CPP_SOURCES})

target_compile_features(${EXE_NAME} PRIVATE cxx_std_26) 
#  Classic(c++98, c++03), Modern(c++11, c++14, c++17, c++20, c++23, c++26)

# NOTE: See .vscode/c_cpp_properties.json for C/C++ standard settings 
#      for VSCode IntelliSense.

# ===========================================================
# 6) Tested compiler versions   
# ===========================================================
# Tested in clang++ 21.1.6 


