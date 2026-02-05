// internal
#include "Post.h"

fourbune::endpoints::Post::Post(
    fourbune::messages::message_manager* msgmng
){
    messageManager = msgmng;
}


HTTP_ENDPOINT_FUNC(fourbune::endpoints::Post::get){
    fourbune::http::response resp;

    resp.data = "<script>window.location.href=\"/\";</script>";

    return resp;
}

HTTP_ENDPOINT_FUNC(fourbune::endpoints::Post::post){
    fourbune::http::response resp;

    fourbune::messages::message msg;

    // verify validity of post request
    if(!HAS_HEADER("User-Agent") ||
       !HAS_POST_PARAM("message"))
        return resp;



    msg.userAgent = headers["User-Agent"];
    if(HAS_POST_PARAM("ua")){
        msg.userAgent = postParams["ua"];
    }


    
    return resp;
}

std::string fourbune::endpoints::Post::sanitize(std::string msg){
    return msg;
}