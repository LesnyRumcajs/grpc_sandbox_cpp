## GRPC Sandbox C++
My discoveries of the gRPC and ProtoBuf3 for C++. Purely for learning purposes. Development OS - Linux Fedora 30.

### GRPC installation
Don't use raw `make` if you want CMake project support (e.g. CLion's).
1. `cd cmake && mkdir build && cd build`
2. `cmake ../.. -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_SSL_PROVIDER=package`
3. `make -j12`
4. `make install`

### Useful links
* https://grpc.io/docs/quickstart/cpp/ - quick-start for C++ with some exemplary code
* https://grpc.io/docs/tutorials/basic/c/ - C++ basics, better thoroughly explained


 
