#pragma once

// internal
#include "HTTP.h"
#include "Messages.h"

namespace fourbune{
    namespace endpoints{
        class Post : public fourbune::http::endpoint{
            fourbune::messages::message_manager* messageManager;
        public:
            [[deprecated("Use Post(fourbune::messages::message_manager*)")]]
            Post(){ throw; };

            Post(fourbune::messages::message_manager* msgmng);

            HTTP_ENDPOINT_FUNC(get);
            HTTP_ENDPOINT_FUNC(post);

            std::string sanitize(std::string msg);
        };
    }
}