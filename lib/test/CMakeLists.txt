
set (CHECK_ENVIRONMENT)

set (CHECK_TO_BE_RUN)
macro (ot_check_test TESTNAME)
  set (TEST_TARGET t_${TESTNAME})
  add_executable (${TEST_TARGET} EXCLUDE_FROM_ALL ${TEST_TARGET}.cxx)
  add_dependencies(tests ${TEST_TARGET})
  target_include_directories (${TEST_TARGET} PRIVATE ${INTERNAL_INCLUDE_DIRS})
  target_link_libraries (${TEST_TARGET} PRIVATE otvine)
  set_target_properties (${TEST_TARGET} PROPERTIES
                         UNITY_BUILD OFF
                         INSTALL_RPATH "${PROJECT_BINARY_DIR}/lib/src;${CMAKE_INSTALL_RPATH}")
  set (_IGNOREOUT OFF)
  foreach (_ARG ${ARGN})
    if (${_ARG} MATCHES IGNOREOUT)
      set (_IGNOREOUT ON)
    endif ()
  endforeach ()

  if (_IGNOREOUT)
    add_test (NAME cppcheck_${TESTNAME} COMMAND ${TEST_TARGET})
  else ()
    set (OUTFILE_LOC ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_TARGET}.expout)
    if (NOT EXISTS ${OUTFILE_LOC})
      message (SEND_ERROR "Missing file ${OUTFILE_LOC}")
    endif ()
    add_test (NAME cppcheck_${TESTNAME} COMMAND "sh" "-c" "(${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:${TEST_TARGET}> > ${CMAKE_CURRENT_BINARY_DIR}/${TEST_TARGET}.out) && diff -u --strip-trailing-cr ${OUTFILE_LOC} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_TARGET}.out")
  endif ()
  set_tests_properties (cppcheck_${TESTNAME} PROPERTIES ENVIRONMENT "${CHECK_ENVIRONMENT}")
  list (APPEND CHECK_TO_BE_RUN ${TEST_TARGET})
endmacro ()


ot_check_test (VineCopulaFactory_std IGNOREOUT)


add_custom_target ( cppcheck COMMAND ${CMAKE_CTEST_COMMAND} -R "^cppcheck_"
                    DEPENDS ${CHECK_TO_BE_RUN}
                    COMMENT "Run C++ pre-installation tests" )
