cmake_minimum_required(VERSION 3.15)
project(search_engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include/rapidjson)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "")
set (input02 "")
set (input03 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()


# Create the executable for sorting
add_executable(search_engine main.cpp AVLNode.h AVLTree.h HashMap.h IndexHandler.cpp IndexHandler.h QueryEngine.cpp QueryEngine.h document.cpp document.h UserInterface.cpp UserInterface.h)








