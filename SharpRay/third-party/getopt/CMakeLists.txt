
ADD_LIBRARY(getopt SHARED getopt.cpp)
SET_TARGET_PROPERTIES(getopt PROPERTIES COMPILE_FLAGS -DEXPORTS_GETOPT)
