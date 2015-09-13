/**
 * @file   XmlLoader.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Wed Sep  9 00:46:49 2015
 * 
 * @brief  
 * 
 * 
 */

#include "XmlLoader.hpp"


XmlLoader::XmlLoader() : m_document(new TiXmlDocument()), m_rootElement(nullptr) , m_xmlfile(""){
    
}

XmlLoader::XmlLoader(const std::string& xmlfile) : m_document(new TiXmlDocument()), m_rootElement(nullptr), m_xmlfile(""){
    this->m_xmlfile = xmlfile;
}

XmlLoader::~XmlLoader()
{
    // auto release resources
}


void XmlLoader::LoadXml(const std::string& xmlfile) {
    if (m_document) {
        m_xmlfile = xmlfile;
        m_document->LoadFile(m_xmlfile.c_str());
        m_rootElement = m_document->RootElement();
        if (m_rootElement) {  // root element is not null
            ParseXml(m_rootElement);
        }
    }
}


/** 
 * 可被继承，重写
 * 
 * @param rootElement 
 */
void XmlLoader::ParseXml(TiXmlElement* rootElement) {
    assert(rootElement != nullptr);
}


std::string XmlLoader::GetRootElementNode() {
    return "PDF";
}
