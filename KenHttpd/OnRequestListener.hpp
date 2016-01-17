/**
 * @file   OnRequestListener.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Jan 17 16:23:31 2016
 * 
 * @brief  OnRequestListener
 * 
 * 
 */


#ifndef ONREQUESTLISTENER_H
#define ONREQUESTLISTENER_H

#include <string>

class OnRequestListener
{
  public:
    OnRequestListener() { /*nothing*/ }
    virtual void OnReceived(int id, const std::string& data) = 0;
    virtual void OnFailed(int id, int err_code, const std::string& err_msg) = 0;
};


#endif /* ONREQUESTLISTENER_H */
