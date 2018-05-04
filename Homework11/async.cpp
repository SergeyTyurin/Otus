#include <future>
#include <memory>
#include <map>
#include <iostream>

#include "async.h"
#include "context.h"

std::map<async::handle_t, std::shared_ptr<Context>> ContextMap;

namespace async {
    handle_t connect(std::size_t bulk) {
        auto h  = std::make_shared<Context>(bulk);
        ContextMap.emplace(std::make_pair(h.get(),h));
        return h.get();
    }

    void receive(handle_t handle, const char *data, std::size_t size) {
        ContextMap[handle]->Receive(data,size);
    }

    void disconnect(handle_t handle) {
        ContextMap[handle]->Disconnect();
    }

}
