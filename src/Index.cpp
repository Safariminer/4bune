// stl
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// internal
#include "Index.h"

HTTP_ENDPOINT_FUNC(fourbune::endpoints::Index::get){
    fourbune::http::response response;

    std::ifstream fileHandle("www/index.html");
    std::stringstream contentHandle; contentHandle << fileHandle.rdbuf();
    response.data = contentHandle.str();
    fileHandle.close();

    return response;
}

HTTP_ENDPOINT_FUNC(fourbune::endpoints::Index::post){
    fourbune::http::response response;

    std::ifstream fileHandle("www/index.html");
    std::stringstream contentHandle; contentHandle << fileHandle.rdbuf();
    response.data = contentHandle.str();
    fileHandle.close();

    return response;
}