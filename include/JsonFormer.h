//
// Created by George Kobelev on 6/22/17.
//

#ifndef LAB8_JSONFORMER_H
#define LAB8_JSONFORMER_H

#include <string>
#include "json.hpp"
#include <fstream>
#include "ReqProcessor.h"

using nlohmann::json;

class JsonFormer {
private:
    std::string readFile(std::string filename);
    size_t filesize(std::string filename);

    void formServerInfo();
    void formFavorites();
    void formFileData();
    void formFile();
    void formFavoritesByKey(ReqProcessor req);

public:
    std::string output;
    std::string formJsonStr(ReqProcessor req);

};


#endif //LAB8_JSONFORMER_H
