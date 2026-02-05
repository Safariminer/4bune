// internal
#include "Post.h"

HTTP_ENDPOINT_FUNC(fourbune::endpoints::Post::get){
    fourbune::http::response resp;

    resp.data = "<script>window.location.href=\"/\";</script>";

    return resp;
}

HTTP_ENDPOINT_FUNC(fourbune::endpoints::Post::post){
    fourbune::http::response resp;

    if(postParams.find("test") != postParams.end()){
        resp.data = postParams["test"];
    }
    return resp;
}