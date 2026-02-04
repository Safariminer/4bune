#define FBUNE_ENDPOINT_BUF 2048

// stl
#include <iostream>
#include <map>
#include <optional>
#include <regex>

// libraries
#include <dyad.h>

// internal
#include "HTTP.h"
#include "Index.h"


std::map<std::string, fourbune::http::endpoint*> endpoints;

static void OnData(dyad_Event*e){
    std::optional<fourbune::http::response> r;
    
    fourbune::http::event event;

    char endpoint[FBUNE_ENDPOINT_BUF];
    std::string endpoint_s;

    if(sscanf(e->data, "GET %2047s", endpoint) == 1){
        // get request;
        event = fourbune::http::HTTP_GET;
    }
    else if(sscanf(e->data, "POST %2047s", endpoint) == 1){
        // post request;    
        event = fourbune::http::HTTP_POST;
    }

    // use regex to match url parameters
    std::regex regex("(\\?|&)([^\\?&=]*)(=([^\\?&=]*)|)");
    endpoint_s = std::regex_replace(std::string(endpoint), regex, "");
    
    
    if(endpoints.find(endpoint_s) != endpoints.end()){
    
        std::map<std::string, std::string> arguments;

        std::smatch matches;
        std::string fullendpoint = std::string(endpoint);
        if(std::regex_match(fullendpoint, matches, regex)){
            for(int i = 0; i < matches.size(); i++){
                std::cout << i << " : " << matches[i] << std::endl;
            }
        }
    
        switch(event){
            case fourbune::http::HTTP_GET:
            r = endpoints[endpoint_s]->get(arguments, e->data);
            break;
        case fourbune::http::HTTP_POST:
            r = endpoints[endpoint_s]->post(arguments, e->data);
            break;
        }
    }



    if(r.has_value()){
        fourbune::http::response resp = r.value();

        dyad_writef(e->stream, "HTTP/1.1 200 OK\r\n");

        for(const fourbune::http::header& h : resp.headers){
            dyad_writef(e->stream, "%s: %s\r\n", h.name.c_str(), 
                h.content.c_str());
        }
        
        dyad_writef(e->stream, "\r\n");
        dyad_writef(e->stream, "%s", resp.data.c_str());
    }
    else{
        dyad_writef(e->stream, "HTTP/1.1 404\r\n\r\n<h1>404</h1>");
    }
    dyad_end(e->stream);

}

static void OnAccept(dyad_Event*e){
    dyad_addListener(e->remote, DYAD_EVENT_DATA, OnData, NULL);
}

int main(int argc, char** argv){

    endpoints["/"] = new fourbune::endpoints::Index();

    dyad_init();
    dyad_Stream* stream = dyad_newStream();
    dyad_addListener(stream, DYAD_EVENT_ACCEPT, OnAccept, NULL);
    dyad_listenEx(stream, "0.0.0.0", 9000, NULL);
    while(dyad_getStreamCount() >0){
        dyad_update();
    }

}