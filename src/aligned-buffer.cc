/* node-aligned-buffer (C) 2012 Ian Babrou <ibobrik@gmail.com>  */

#include <node_buffer.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace v8;
using namespace node;

void free_aligned_buffer(char * data, void *hint) {
    free(data);
}

Handle<Value> ThrowNodeError(const char* what = NULL) {
    return ThrowException(Exception::Error(String::New(what)));
}

Handle<Value> alignment(const Arguments &args) {
    return Number::New(sysconf(_SC_PAGESIZE));
}

Handle<Value> buffer(const Arguments &args) {
    if (args.Length() < 2) {
        return ThrowNodeError("Not enough arguments passed");
    }

    size_t alignment = (size_t) args[0]->ToNumber()->Value();
    size_t size      = (size_t) args[1]->ToNumber()->Value();

    void *buf;
    int result = posix_memalign(&buf, alignment, size);

    if (result == EINVAL) {
        return ThrowNodeError("Incorrect alignment and size specified");
    }

    if (result == ENOMEM) {
        return ThrowNodeError("Not enough memory to allocate aligned buffer");
    }

    Buffer * Result = Buffer::New((char *) buf, size, free_aligned_buffer, NULL);

    HandleScope scope;

    return scope.Close(Result->handle_);
}

extern "C" void
init (Handle<Object> target) {
    NODE_SET_METHOD(target, "alignment", alignment);
    NODE_SET_METHOD(target, "buffer", buffer);
}

NODE_MODULE(aligned_buffer, init);
