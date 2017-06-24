/**
 * @file
 * @brief Contains ReqProcessor class, ReqType enumeration and CrudeReq structure
 */

//
// Created by George Kobelev on 6/22/17.
//

#ifndef LAB8_REQPROCESSOR_H
#define LAB8_REQPROCESSOR_H

#include <evhttp.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

///@brief The enumeration of client request types.
enum ReqType{
    REQ_DEFAULT,         ///< <code>/</code> request JSON with server information.
    REQ_FAVORITES_ALL,   ///< <code>/favorites</code> request JSON-list of objects, indicating the list of favorite plants.
    REQ_FILE,            ///< <code>/file</code> request the contents, filename and size of the file <code>data.txt</code>.
    REQ_FILE_DATA,       ///< <code>/file/data</code> request JSON object with information about the number of all digits and letters in a file (file <code>data.txt</code>).
    REQ_FAVORITES_BY_ID, ///< <code>/favorites/{id}</code> request JSON object from the list <code>/</code> favorites by identifier with numeric value <code>{id}</code>.
    REQ_FAVORITES_BY_KEY,///< <code>/favorites?{key}={value}</code> request JSON-sublist of objects from the list <code>/</code> favorites in which the <code>{key}</code> field has a value of <code>{value}</code>.
    REQ_BAD              ///< Bad request: <code>404 Not Found</code>.
};

/**
 * @struct CrudeReq
 * @brief Structure that contains sliced crude request (path, query).
 */
typedef struct CrudeReq{
    std::string path; ///< <code>/blah-blah/blah</code>.
    std::string query;///< <code>?{key}={value}</code>.
}CrudeReq;

/**
 * @class ReqProcessor
 * @brief Class for processing client request to identify request type and parse path and query.
 */
class ReqProcessor {
private:
    CrudeReq crudeReq;

    std::string uri;///< crude non-sliced client uri.

    /**
     * @brief Slice uri for CrudeReq, check if is right uri and parse.
     */
    void processCrude();

    /**
     * @brief Split std::string by delimiter delim to std::vector<std::string>.
     * @param[in] s String to split.
     * @param[in] delim Delimiter on which to split string.
     * @return vector of s substring.
     */
    std::vector<std::string> split(std::string s, char delim);

    /**
     * @brief Check if s string is number.
     * @param[in] s String to check.
     * @return true if s is number and false if not.
     */
    bool is_number(const std::string& s);

    /**
     * @brief Check if path is right, identify request type and parse.
     */
    void checkPath();

    /**
     * @brief Check if query is right, identify request type and parse.
     */
    void checkQuery();
public:
    ReqProcessor();
    ReqProcessor(evhttp_request *request);
    ReqType type = REQ_BAD;///< client request type (REQ_BAD by default).
    int id = 0;///< <code>{id}</code> of JSON object from <code>favorites.json</code>.
    std::string key;///< <code>{key}</code> on which JsonFromer formFavoritesByKey.
    std::string value;///< <code>{value}</code> to find and reply in JsonFromer formFavoritesByKey.

    /**
     * @brief Set uri string and process request.
     * @param request Request to process.
     */
    void setUri(evhttp_request *request);
};


#endif //LAB8_REQPROCESSOR_H
