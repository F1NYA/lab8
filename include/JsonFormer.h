/** @file
 *  @brief JSON former object, to form server replies in JSON format
 */

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

/**
 * @class JsonFormer
 * @brief Class for forming JSON-formatted output string for server reply to client request
 */
class JsonFormer {
private:

    /**
     * @brief Read whole file to std::string and return it
     * @param filename Name of file to read
     * @return std::string of file content
     */
    std::string readFile(std::string filename);

    /**
     * @brief Check size of file in bytes
     * @param filename Name of file to check size
     * @return size_t size of file in bytes
     */
    size_t filesize(std::string filename);

    /**
     * @brief Forming JSON string of server info and write to output
     *
       ```json
        {
            "title": "%SERVER_NAME%",
            "developer": "%YOUR_NAME_SURNAME%",
            "time": "%SERVER_TIME%"
        }
        ```
     */
    void formServerInfo();

    /**
     * @brief Forming JSON string of favorites plants and write to output
     *
     *  ```json
        [
            {
                "id": 1,
                "name": "Asparagus",
                "type": "Vegetable",
                "companions": ["Tomato", "Aster", "Dill"],
                "foes": ["Onion", "Garlic", "Potato"],
                "description": "Description..."
            },

            {
                "id": 2,
                "name": "Anise",
                "type": "Herb",
                "companions": ["Coriander", "Cilantro"],
                "foes": [],
                "description": "Description..."
            },

            ...

            {
                "id": 50,
                "name": "Watercress",
                "type": "Vegetable",
                "companions": ["Onion", "Chive", "Peppermint", "Spearmint"],
                "foes": [],
                "description": "Description..."
            }
       ]
       ```
     */
    void formFavorites();

    /**
     * @brief Forming JSON string of data about file <code>data.txt</code> (num of letters, digits) and write to output
     *
     *  ```json
        {
            "letters": 1234,
            "digits": 4321
        }
        ```
     */
    void formFileData();

    /**
     * @brief Forming JSON string about file <code>data.txt</code> (size, name, content) and write to output
     *
     *  ```json
        {
            "filename": "%FILE_NAME%",
            "size": 1234,
            "content": "%FILE_CONTENT"
        }
        ```
     */
    void formFile();

    /**
     * @brief Forming JSON string of favorite plants with needed <code>{key}={value}</code> from req and write to output
     * @param[in] req Processed request from client for key, value
     *
     *  ```json
        http://localhost:8080/favorites?name=SummerSavory

        {
            "id": 45,
            "name": "SummerSavory",
            "type": "Herb",
            "companions": ["Green Bean", "Onion"],
            "foes": [],
            "description": "Description..."
        }
        ```
     */
    void formFavoritesByKey(ReqProcessor req);

public:

    /**
     * @brief Output string that contains JSON formatted data or <code>404 Not Found</code> status/ for server  reply.
     */
    std::string output;

    /**
     * @brief Method to form output JSON formatted string from processed client req for server reply
     * @param[in] req Processed request from client for request type, key, value
     * @return output
     */
    std::string formJsonStr(ReqProcessor req);

};


#endif //LAB8_JSONFORMER_H
