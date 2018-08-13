include(FindProtobuf)
find_package(Protobuf REQUIRED)

file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER ${ProtoFiles})
set(SOURCES record.cpp record.h)
set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${PROTOBUF_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(tbproto SHARED ${PROTO_HEADER} ${PROTO_SRC} ${SOURCES})
target_include_directories(tbproto PUBLIC ${INCLUDE_DIRS})
target_link_libraries(tbproto ${Protobuf_LIBRARIES})


