file(GLOB HEADERS "include/steemit/protocol/*.hpp")
file(GLOB BOOST_LIBS "${BOOST_ROOT}/lib/*.a")
## SORT .cpp by most likely to change / break compile
add_library( steemit_protocol

             types.cpp
             authority.cpp
             operations.cpp
             sign_state.cpp
             operation_util_impl.cpp
             steem_operations.cpp
             transaction.cpp
             block.cpp
             asset.cpp
             version.cpp
             get_config.cpp

             ${HEADERS}
        config.cpp)

target_link_libraries( steemit_protocol fc  ${BOOST_LIBS} )
target_include_directories( steemit_protocol
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include")

INSTALL( TARGETS
   steemit_protocol

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

INSTALL( FILES ${HEADERS} DESTINATION "include/steemit/protocol" )
