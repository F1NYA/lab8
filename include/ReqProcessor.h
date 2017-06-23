//
// Created by George Kobelev on 6/22/17.
//

#ifndef LAB8_REQPROCESSOR_H
#define LAB8_REQPROCESSOR_H

#include <evhttp.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

enum ReqType{
    REQ_DEFAULT,         // "/"
    REQ_FAVORITES_ALL,   // "/favorites"
    REQ_FILE,            // "/file"
    REQ_FILE_DATA,       // "/file/data"
    REQ_FAVORITES_BY_ID, // "/favorites/{id}"
    REQ_FAVORITES_BY_KEY,// "/favorites/{key}={value}"
    REQ_BAD
};

typedef struct CrudeReq{
    std::string path; // "/blah-blah/blah"
    std::string query;// "?{key}={value}"
}CrudeReq;

class ReqProcessor {
private:
    CrudeReq crudeReq;

    std::string uri;
    void processCrude();

    std::vector<std::string> split(std::string s, char delim);
    bool is_number(const std::string& s);
    void checkPath();
    void checkQuery();
public:
    ReqProcessor();
    ReqProcessor(evhttp_request *request);
    ReqType type = REQ_BAD;
    int id = 0;
    std::string key;
    std::string value;
    void setUri(evhttp_request *request);
};


#endif //LAB8_REQPROCESSOR_H
