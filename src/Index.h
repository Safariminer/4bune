// internal
#include "HTTP.h"

namespace fourbune{
    namespace endpoints{
        class Index : public fourbune::http::endpoint {
        public:
            HTTP_ENDPOINT_FUNC(get);
            HTTP_ENDPOINT_FUNC(post);
        };
    }
}