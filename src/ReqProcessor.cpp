//
// Created by George Kobelev on 6/22/17.
//

#include "ReqProcessor.h"

ReqProcessor::ReqProcessor() {}

ReqProcessor::ReqProcessor(evhttp_request *request) {
    uri = std::string(request->uri);
    processCrude();
}

void ReqProcessor::processCrude() {
    std::vector<std::string> creq = split(uri, '?');
    crudeReq.path = creq[0];
    if (creq.size() == 2) crudeReq.query = creq[1];

    checkPath();
    checkQuery();
}

void ReqProcessor::setUri(evhttp_request *request) {
    uri = std::string(request->uri);
    processCrude();
}

std::vector<std::string> ReqProcessor::split(std::string s, char delim) {
    std::vector<std::string> elems;
    boost::algorithm::split(elems, s, [=](char c){ return c == delim;});
    return elems;
}

bool ReqProcessor::is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void ReqProcessor::checkPath() {
    char reqs[][11] = {
            "/",
            "/favorites",
            "/file",
            "/file/data"
    };
    for (int i = 0; i < 4; ++i) {
        if (crudeReq.path == reqs[i]) {
            type = static_cast<ReqType>(i);
            return;
        }
    }

    std::vector<std::string> cpath = split(crudeReq.path, '/');
    if (cpath.size() == 3 && cpath.at(0).empty() && cpath.at(1) == "favorites" && is_number(cpath.at(2))) {
        type = REQ_FAVORITES_BY_ID;
        id = std::stoi(cpath.at(2));
    }
}

void ReqProcessor::checkQuery() {
    if (crudeReq.query.empty()) return;
    if (type != REQ_FAVORITES_ALL) {
        id = 0;
        type = REQ_BAD;
    } else {
        std::vector<std::string> cquery = split(crudeReq.query, '=');
        if (cquery.size() != 2 || cquery[0].empty() || cquery[1].empty()) {
            type = REQ_BAD;
        } else {
            if (cquery[0] == "id"){
                if (is_number(cquery[1])){
                    id = std::stoi(cquery[1]);
                    type = REQ_FAVORITES_BY_ID;
                } else {
                    type = REQ_BAD;
                }
            } else {
                type = REQ_FAVORITES_BY_KEY;
                key = cquery[0];
                value = cquery[1];
            }
        }
    }
}


