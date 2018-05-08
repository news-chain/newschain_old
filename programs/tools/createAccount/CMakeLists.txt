

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_EXE_LINKER_FLAGS  "-pthread ")


file(GLOB FILES_BOOST_LIB "$ENV{BOOST_ROOT}/lib/*.a")
#message("boost file ---  ${FILES_BOOST_LIB}")
file(GLOB TOOLS_CREATE_SOURCES "*.cpp" "*.h")

add_executable(createAccounts   ${TOOLS_CREATE_SOURCES} )
include_directories("/home/boy/Documents/boost160/include")
target_link_libraries(createAccounts   ${FILES_BOOST_LIB} )
