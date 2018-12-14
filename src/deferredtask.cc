#include "deferredtask.h"
#include "walletlog.h"

namespace exawallet {

DeferredTask::DeferredTask() {
    ENTER_FUNC();
    v8::Local<v8::Promise::Resolver> value =v8::Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
    resolver.Reset(value);
    EXIT_FUNC();
}

DeferredTask::~DeferredTask() {
    ENTER_FUNC();
    resolver.Reset();
    EXIT_FUNC();
}

void DeferredTask::Resolve(v8::Local<v8::Value> value) {
    ENTER_FUNC();
    Nan::New(resolver)->Resolve(Nan::GetCurrentContext(), value);
    EXIT_FUNC();
}

void DeferredTask::Reject() {
    ENTER_FUNC();
    v8::Local<v8::Context> context = Nan::GetCurrentContext();
    Nan::New(resolver)->Reject(context, Nan::New(errorString.c_str()).ToLocalChecked());
    EXIT_FUNC();
}

v8::Local<v8::Promise> DeferredTask::Enqueue() {
    ENTER_FUNC();
    work.data = this;
    uv_queue_work(uv_default_loop(), &work, DeferredTask::AsyncWork, DeferredTask::AsyncAfterWork);
    return Nan::New(resolver)->GetPromise();
    EXIT_FUNC();
}

void DeferredTask::AsyncWork(uv_work_t* work) {
    ENTER_FUNC();
    DeferredTask* deferred = reinterpret_cast<DeferredTask*>(work->data);
    deferred->errorString = deferred->doWork();
    EXIT_FUNC();
}

void DeferredTask::AsyncAfterWork(uv_work_t* work, int status) {
    ENTER_FUNC();
    //TODO: check if work is cancelled

    Nan::HandleScope scope;

    DeferredTask* deferred = reinterpret_cast<DeferredTask*>(work->data);

    if (!deferred->errorString.empty()) {
        deferred->Reject();
        return;
    }

    v8::Local<v8::Value> value = deferred->afterWork(deferred->errorString);
    if (!deferred->errorString.empty()) {
        deferred->Reject();
        return;
    }

    deferred->Resolve(value);

    delete deferred;
    EXIT_FUNC();
}

}
