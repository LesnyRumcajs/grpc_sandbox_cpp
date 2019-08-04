cmake_minimum_required(VERSION 3.14)
project(server)

set(CMAKE_CXX_STANDARD 17)

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Proto file
get_filename_component(adder_proto "protos/adder.proto" ABSOLUTE)
get_filename_component(adder_proto_path "${adder_proto}" PATH)

# Generated sources
file(MAKE_DIRECTORY "gen")
set(adder_proto_srcs "../gen/adder.pb.cc")
set(adder_proto_hdrs "../gen/adder.pb.h")
set(adder_grpc_srcs "../gen/adder.grpc.pb.cc")
set(adder_grpc_hdrs "../gen/adder.grpc.pb.h")

# Generate protobuf & grpc sources
add_custom_command(
        OUTPUT "${adder_proto_srcs}" "${adder_proto_hdrs}" "${adder_grpc_srcs}" "${adder_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "../gen"
        --cpp_out "../gen"
        -I "${adder_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${adder_proto}"
        DEPENDS "${adder_proto}")

# Include generated *.pb.h files
include_directories("gen")

# Targets greeter_[async_](client|server)
foreach(_target
        adder_server)
    add_executable(${_target} "src/${_target}.cpp"
            ${adder_proto_srcs}
            ${adder_grpc_srcs})
    target_link_libraries(${_target}
            ${_GRPC_GRPCPP_UNSECURE}
            ${_PROTOBUF_LIBPROTOBUF})
endforeach()

