// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: example.proto
#ifndef GRPC_example_2eproto__INCLUDED
#define GRPC_example_2eproto__INCLUDED

#include "example.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace example {

class ResNet final {
 public:
  static constexpr char const* service_full_name() {
    return "example.ResNet";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status ClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::example::ClassifyResult* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::ClassifyResult>> AsyncClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::ClassifyResult>>(AsyncClassifyImageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::ClassifyResult>> PrepareAsyncClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::example::ClassifyResult>>(PrepareAsyncClassifyImageRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void ClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ClassifyImage(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::example::ClassifyResult* response, std::function<void(::grpc::Status)>) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::example::ClassifyResult>* AsyncClassifyImageRaw(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::example::ClassifyResult>* PrepareAsyncClassifyImageRaw(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status ClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::example::ClassifyResult* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::ClassifyResult>> AsyncClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::ClassifyResult>>(AsyncClassifyImageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::ClassifyResult>> PrepareAsyncClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::example::ClassifyResult>>(PrepareAsyncClassifyImageRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void ClassifyImage(::grpc::ClientContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response, std::function<void(::grpc::Status)>) override;
      void ClassifyImage(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::example::ClassifyResult* response, std::function<void(::grpc::Status)>) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::example::ClassifyResult>* AsyncClassifyImageRaw(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::example::ClassifyResult>* PrepareAsyncClassifyImageRaw(::grpc::ClientContext* context, const ::example::ImageMatrix& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_ClassifyImage_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_ClassifyImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_ClassifyImage() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_ClassifyImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestClassifyImage(::grpc::ServerContext* context, ::example::ImageMatrix* request, ::grpc::ServerAsyncResponseWriter< ::example::ClassifyResult>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_ClassifyImage<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_ClassifyImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_ClassifyImage() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::example::ImageMatrix, ::example::ClassifyResult>(
          [this](::grpc::ServerContext* context,
                 const ::example::ImageMatrix* request,
                 ::example::ClassifyResult* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->ClassifyImage(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_ClassifyImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_ClassifyImage<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_ClassifyImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_ClassifyImage() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_ClassifyImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_ClassifyImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_ClassifyImage() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_ClassifyImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestClassifyImage(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_ClassifyImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_ClassifyImage() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->ClassifyImage(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_ClassifyImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void ClassifyImage(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ClassifyImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_ClassifyImage() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::example::ImageMatrix, ::example::ClassifyResult>(std::bind(&WithStreamedUnaryMethod_ClassifyImage<BaseClass>::StreamedClassifyImage, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_ClassifyImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ClassifyImage(::grpc::ServerContext* context, const ::example::ImageMatrix* request, ::example::ClassifyResult* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedClassifyImage(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::example::ImageMatrix,::example::ClassifyResult>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_ClassifyImage<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_ClassifyImage<Service > StreamedService;
};

}  // namespace example


#endif  // GRPC_example_2eproto__INCLUDED