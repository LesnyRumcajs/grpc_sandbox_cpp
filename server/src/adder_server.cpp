#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "adder.grpc.pb.h"
#include "adder.pb.h"

class AdderServiceImpl : public Adder::Service {
public:
    grpc::Status
    AddNumbers(::grpc::ServerContext *context, const ::AddRequest *request, ::AddResult *response) override {
        const auto result = request->first() + request->second();
        response->set_result(result);
        return grpc::Status::OK;
    }
};

void run_server(std::string_view address) {
    AdderServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(address.data(), grpc::InsecureServerCredentials())
           .RegisterService(&service);

    auto server = builder.BuildAndStart();
    std::cout << "Server listening on " << address << '\n';

    server->Wait();
}

int main() {
    run_server("0.0.0.0:50051");
}
