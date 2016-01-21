/**
 * @file   HttpError.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Tue Jan 19 01:22:58 2016
 * 
 * @brief  define some err messages for err codes
 * 
 * 
 */

#ifndef HTTPERROR_H
#define HTTPERROR_H

#include <string>

class HttpError {
  public:
    static std::string GetErrMsgByErrCode(int err_code) {
        switch (err_code) {
            case 100:
                return "Continue";
            case 101:
                return "Switching Protocols";
            case 102:
                return "Processing";
            case 200:
                return "Success";
            case 201:
                return "Created";
            case 202:
                return "Accepted";
            case 203:
                return "Non-Authoritative Information";
            case 204:
                return "No Content";
            case 205:
                return "Reset Content";
            case 206:
                return "Partial Content";
            case 207:
                return "Multi-Status";
            case 300:
                return "MMultiple Choices";
            case 301:
                return "Moved Permanently";
            case 302:
                return "Found";
            case 303:
                return "See Other";
            case 304:
                return "Not Modified";
            case 305:
                return "Use Proxy";
            case 306:
                return "Switch Proxy"; // not be used any more
            case 307:
                return "Temporary Redirect";
            case 400:
                return "Bad Request";
            case 401:
                return "Unauthorized";
            case 402:
                return "Payment Required";
            case 403:
                return "Forbidden";
            case 404:
                return "Not Found";
            case 405:
                return "Method Not Allowed";
            case 406:
                return "Not Acceptable";
            case 407:
                return "Proxy Authentication Required";
            case 408:
                return "Request Timeout";
            case 409:
                return "Conflict";
            case 410:
                return "Gone";
            case 411:
                return "Length Required";
            case 412:
                return "Precondition Failed";
            case 413:
                return "Request Entity Too Large";
            case 414:
                return "Request-URI Too Long";
            case 415:
                return "Unsupported Media Type";
            case 416:
                return "Requested Range Not Satisfiable";
            case 417:
                return "Expectation Failed";
            case 418:
                return "I'm a teapot";
            case 421:
                return "There are too many connections from your internet address";
            case 422:
                return "Unprocessable Entity";
            case 423:
                return "Locked";
            case 424:
                return "Failed Dependency";
            case 425:
                return "Unordered Collection";
            case 426:
                return "Upgrade Required";
            case 449:
                return "Retry With";
            case 451:
                return "Unavailable For Legal Reasons";
            case 500:
                return "Internal Server Error";
            case 501:
                return "Not Implemented";
            case 502:
                return "Bad Gateway";
            case 503:
                return "Service Unavailable";
            case 504:
                return "Gateway Timeout";
            case 505:
                return "HTTP Version Not Supported";
            case 506:
                return "Variant Also Negotiates";
            case 507:
                return "Insufficient Storage";
            case 509:
                return "Bandwidth Limit Exceeded";
            case 510:
                return "Not Extended";
            default:
                return "UNKNOWN";
        }
    }
};

#endif /* HTTPERROR_H */

