/**
 * @file   XmlLoader.h
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Sep  9 00:40:24 2015
 * 
 * @brief  Class XmlLoader declare
 * 
 * 
 */

#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <string>
#include <vector>
#include <memory>
#include "../tinyxml/tinyxml.h"
#include "GlobalInclude.hpp"


class XmlLoader
{
  public:
    XmlLoader();
    XmlLoader(const std::string& xmlfile);
    virtual ~XmlLoader();
    void LoadXml(const std::string& xmlfile);
    virtual std::string GetRootElementNode();
    
  protected:
    virtual void ParseXml(TiXmlElement* rootElement);
  private:
    std::unique_ptr<TiXmlDocument> m_document;
    TiXmlElement* m_rootElement;
    std::string m_xmlfile;
};



#endif /* XMLLOADER_H */
