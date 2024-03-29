add_executable( NEWS main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling steemd with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

if( STEEM_STATIC_BUILD )
   target_link_libraries( steemd PRIVATE
      "-static-libstdc++ -static-libgcc"
      steemit_plugins
      steemit_mf_plugins
      steemit_app
      steemit_witness
      steemit_account_history
      steemit_chain
      steemit_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
else( STEEM_STATIC_BUILD )
   target_link_libraries( NEWS PRIVATE
      steemit_plugins
      steemit_mf_plugins
      steemit_app
      steemit_witness
      steemit_account_history
      steemit_chain
      steemit_protocol
      fc
      ${CMAKE_DL_LIBS}
      ${PLATFORM_SPECIFIC_LIBS}
   )
endif( STEEM_STATIC_BUILD )

install( TARGETS
   NEWS

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
