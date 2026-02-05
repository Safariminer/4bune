#pragma once

// stl
#include <iostream>
#include <vector>
#include <map>

#define HTTP_ENDPOINT_FUNC(x) \
::fourbune::http::response x(std::map<std::string, std::string> params, \
    std::map<std::string, std::string> postParams, \
    std::map<std::string, std::string> headers, \
    char* request)

#define HAS_HEADER(x)            (headers.find(x) !=    headers.end())
#define HAS_PARAM(x)              (params.find(x) !=     params.end())
#define HAS_POST_PARAM(x)     (postParams.find(x) != postParams.end())

namespace fourbune{

    namespace http{

        enum event{
            HTTP_GET,
            HTTP_POST
        };
        
        struct header{
            std::string name;
            std::string content;
        };

        struct response{
            unsigned short code;
            std::vector<header> headers;
            std::string data;
        };

        class endpoint{
        public:
            virtual HTTP_ENDPOINT_FUNC(get) = 0;
            virtual HTTP_ENDPOINT_FUNC(post) = 0;
        };

    }

}