set(DOC_COMPILER "doxygen")
set(DOC_LOCATION "${CMAKE_SOURCE_DIR}/docs")
set(DOC_CONFIG_LOCATION "${DOC_LOCATION}/assignment.doxygen")

ADD_CUSTOM_TARGET("docs"
    COMMAND "${DOC_COMPLIER} ${DOC_CONFIG_LOCATION}"
    WORKING_DIRECTORY ${DOC_LOCATION}
    COMMENT "Generating Docs..."
    VERBATIM
)
