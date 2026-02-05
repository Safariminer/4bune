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
#include "Post.h"


std::map<std::string, fourbune::http::endpoint*> endpoints;

std::map<std::string, std::string> 
    parseCompleteParamString(std::string argsList){

    std::map<std::string,std::string> arguments;
    std::string currArg = "", currVal = "";
    bool inVal = false;
    
    for(const char& c : argsList){
        if(c == '?' || c == '&' || c == '\r' || c == '\n'){
            arguments[currArg] = currVal;
            currArg = ""; currVal = "";
            inVal = false;
        }
        else if(c == '='){
            inVal = true;
        }
        else {
            (inVal ? currVal : currArg) += c;
        }
    }

    arguments[currArg] = currVal;
    return arguments;
}

std::map<std::string, std::string> parseHeader(char* data){

    std::map<std::string,std::string> headers;
    std::string currArg = "", currVal = "";
    bool inVal = false;
    
    std::string headerLine = "", dummy = "";
    std::stringstream dataStream(data);

    std::getline(dataStream, dummy); // discard first line, GET/POST line

    while(std::getline(dataStream, headerLine) && headerLine != ""){
        for(const char& c : headerLine){
            if(c == ':'){
                if(inVal) currVal += ':';
                inVal = true;

            }
            else {
                (inVal ? currVal : currArg) += c;
            }
        }

        headers[currArg] = currVal;
        currArg = ""; currVal = "";
    }

    
    return headers;
}

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

    // std::cout << "Getting " << endpoint << "...\n";

    // use regex to match url parameters
    std::regex regex("(\\?|&)([^\\?&=]*)(=([^\\?&=]*)|)");
    endpoint_s = std::regex_replace(std::string(endpoint), regex, "");

    std::cout << (event == fourbune::http::HTTP_GET ? "Accessing " : 
        "Posting to ") << endpoint_s << "...\n";
    
    if(endpoints.find(endpoint_s) != endpoints.end()){
    
        std::map<std::string, std::string> arguments;
        std::map<std::string, std::string> postArgs;
        std::map<std::string, std::string> headers;
        std::string argsList;
        argsList = std::string(endpoint);
        argsList.erase(0, endpoint_s.size() - 1);

        arguments = parseCompleteParamString(argsList);
        postArgs = parseCompleteParamString(std::string(e->data));
        headers = parseHeader(e->data);

        switch(event){
        case fourbune::http::HTTP_GET:
            r = endpoints[endpoint_s]->get(arguments, postArgs, headers, 
                e->data);
            break;
        case fourbune::http::HTTP_POST:
            r = endpoints[endpoint_s]->post(arguments, postArgs, headers,
                e->data);
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

static void OnError(dyad_Event* e){
    std::cerr << "ERROR: " << e->msg << "\n";
}

int main(int argc, char** argv){

    std::cout << "4BUNE BOUCHOT\n-------------\n\n";


    fourbune::messages::message_manager* messageManager
        = new fourbune::messages::message_manager();

    std::cout << "Setting endpoint '/'..." << std::endl;
    endpoints["/"] = new fourbune::endpoints::Index();
    std::cout << "Setting endpoint '/post'..." << std::endl;
    endpoints["/post"] = new fourbune::endpoints::Post(messageManager);

    dyad_init();
    dyad_Stream* stream = dyad_newStream();
    dyad_addListener(stream, DYAD_EVENT_ACCEPT, OnAccept, NULL);
    dyad_addListener(stream, DYAD_EVENT_ERROR, OnError, NULL);
    dyad_listenEx(stream, "0.0.0.0", 9000, NULL);
    
    while(dyad_getStreamCount() >0){
        dyad_update();
    }

}