find_package(Flatbuffers CONFIG REQUIRED)

set(FLATBUFFERS_FLATC_EXECUTABLE "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/tools/flatbuffers/flatc")

# flatbuffers
add_library(flatbuffers)
target_sources(flatbuffers PRIVATE flatbuffers.hh flatbuffers.cc)
target_set_options(flatbuffers)
target_link_libraries(flatbuffers PRIVATE common flatbuffers::flatbuffers)
target_include_directories(flatbuffers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Build flatbuffer schemas
include(BuildFlatBuffers.cmake)
build_flatbuffers(
    ${CMAKE_CURRENT_SOURCE_DIR}/monster.fbs
    ${CMAKE_CURRENT_SOURCE_DIR}
    flatbuffers_generation
    ""
    ${CMAKE_CURRENT_BINARY_DIR}
    ""
    ""
)
add_dependencies(flatbuffers flatbuffers_generation)
#add_fbs_header(monster)
#target_include_directories(flatbuffers PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
#target_sources(flatbuffers PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/monster_generated.h)

#set(flatbuffers_SOURCE_DIR ${CMAKE_SOURCE_DIR}/flatbuffers)
#set(flatbuffers_SCHEMA_FILE ${flatbuffers_SOURCE_DIR}/monster.fbs)
#set(flatbuffers_GENERATED_FILE ${flatbuffers_SOURCE_DIR}/monster_generated.h)
#add_custom_command(
#        DEPENDS ${flatbuffers_SCHEMA_FILE}
#        COMMAND ${flatbuffers_GENERATOR}
#        ARGS --cpp -o ${flatbuffers_SOURCE_DIR}/ ${flatbuffers_SCHEMA_FILE}
#        OUTPUT ${flatbuffers_GENERATED_FILE}
#        COMMENT "Executing FlatBuffers compiler")
#set_source_files_properties(${flatbuffers_GENERATED_FILE} PROPERTIES GENERATED TRUE)


#add_executable(flatbuffers flatbuffers.cpp ${SOURCE_FILES} ${flatbuffers_GENERATED_FILE})
#add_dependencies(flatbuffers flatbuffers_dep)
#target_include_directories(flatbuffers PUBLIC ${flatbuffers_INCLUDE})
#target_link_libraries(flatbuffers PRIVATE Testing::core)
#add_test(NAME test_flatbuffers COMMAND flatbuffers)
