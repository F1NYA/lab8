//
// Created by George Kobelev on 6/22/17.
//

#include "JsonFormer.h"


std::string JsonFormer::readFile(std::string filename) {
    std::ifstream ifs(filename.c_str());
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
    ifs.close();
    return content;
}

void JsonFormer::formServerInfo() {
    json crudeJson;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string timestr(buffer);

    crudeJson["title"] = "Macbook Pro (15-inch, 2014)";
    crudeJson["developer"] = "George Kobelev";
    crudeJson["time"] = timestr;

    output = crudeJson.dump(4);
}

void JsonFormer::formFile() {
    json crudeJson;
    std::string filename = "data/data.txt";
    crudeJson["filename"] = filename;
    crudeJson["size"] = filesize(filename);
    crudeJson["content"] = readFile(filename).c_str();

    output = crudeJson.dump(4);
    crudeJson.clear();
}

size_t JsonFormer::filesize(std::string filename) {
    std::ifstream in(filename.c_str(), std::ifstream::ate | std::ifstream::binary);
    std::ifstream::pos_type posEnd = in.tellg();
    in.seekg(0, std::ios_base::beg);
    std::ifstream::pos_type posBeg = in.tellg();
    auto size = (size_t)(posEnd - posBeg);

    in.close();

    return size;
}

void JsonFormer::formFileData() {
    json crudeJson;
    std::string filename = "data/data.txt";
    std::string content = readFile(filename);
    crudeJson["letters"] = std::count_if(content.begin(),content.end(),[](char c){return isalpha(c);});
    crudeJson["digits"]  = std::count_if(content.begin(),content.end(),[](char c){return isdigit(c);});

    output = crudeJson.dump(4);
    crudeJson.clear();
}

std::string JsonFormer::formJsonStr(ReqProcessor req) {
    switch (req.type){
        case REQ_DEFAULT:
            formServerInfo();
            break;
        case REQ_FAVORITES_ALL:
            formFavorites();
            break;
        case REQ_FILE:
            formFile();
            break;
        case REQ_FILE_DATA:
            formFileData();
            break;
        case REQ_FAVORITES_BY_ID:
        case REQ_FAVORITES_BY_KEY:
            formFavoritesByKey(req);
            break;
        case REQ_BAD:
            output = "404";
    }

    return output;
}

void JsonFormer::formFavorites() {
    output = readFile("data/favorites.json");
}

void JsonFormer::formFavoritesByKey(ReqProcessor req) {
    json crudeJson = json::parse(readFile("data/favorites.json"));
    if (req.type == REQ_FAVORITES_BY_ID) {

        if (req.id <= 0 || (req.id >= crudeJson.size())) {
            output = "404";
            return;
        }
        json temp = crudeJson[req.id-1];
        output = temp.dump(4);
    } else {
        json outJson;
        json jsonField;
        for (json::iterator it = crudeJson.begin(); it != crudeJson.end(); ++it) {
            try {
                jsonField = (*it).at(req.key);
            } catch (std::exception& e) {
                continue;
            }
            if (jsonField.is_array()) {
                for (json::iterator arItr = jsonField.begin(); arItr != jsonField.end(); ++arItr) {
                    if (arItr.value() == req.value) outJson.push_back((*it));
                }
            }
            else if (jsonField == req.value) outJson.push_back((*it));
        }

        output = (!outJson.empty()) ? outJson.dump(4) : "404";
    }
}
