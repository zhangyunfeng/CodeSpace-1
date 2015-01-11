#include <iostream>
#include <stack>
#include <unistd.h>
#include "CountId.hpp"
namespace Ken {
	IdDiscriminator::IdDiscriminator() : m_xmlpath("")
	{
		m_idbitset.reset();
		m_repetitiveids.clear();
	}

	IdDiscriminator::IdDiscriminator(const std::string& xmlpath):
		m_xmlpath(xmlpath)
	{
		// m_xmlpath = xmlpath;
		m_idbitset.reset();
		m_repetitiveids.clear();
	}

	IdDiscriminator::~IdDiscriminator()
	{
		//auto release, do nothing here
	}

	void IdDiscriminator::SetXmlPath(const std::string& xmlpath)
	{
		m_xmlpath = xmlpath;
	}

	void IdDiscriminator::ParseXml(void)
	{
		if (!IsXmlPathExisted()) {
			std::cerr << "path: " << m_xmlpath << " is not existed" << std::endl;
			return;
		}
		if (!LoadXmlFile()) {
			std::cerr << "Load " << m_xmlpath << " failed!" << std::endl;
			return;
		}
		GenerateIdBitSet();
	}
	
	bool IdDiscriminator::LoadXmlFile(void)
	{
		return m_doc.LoadFile(m_xmlpath.c_str());
	}

	void IdDiscriminator::GenerateIdBitSet(void)
	{
		TiXmlElement* root = m_doc.RootElement();
		if (!root) {
			std::cerr << "RootElement() failed." << std::endl;
			return;
		}
		std::stack<TiXmlElement*> elements;
		elements.push(root);
		TiXmlElement* node = elements.top();
		while (!elements.empty()) {
			if (node == NULL) break;
			const char* idvalue = node->Attribute("id");
			if (idvalue) {
				if (m_idbitset.test(atoi(idvalue)))
					m_repetitiveids.push_back(atoi(idvalue));
				else 
					m_idbitset.set(atoi(idvalue));
				std::cout << "id: " << idvalue << std::endl;
			}
			elements.pop();
			//add all siblibing to stack 
			TiXmlElement* tmpElement = node->FirstChildElement();
			while (tmpElement) {
				elements.push(tmpElement);
				tmpElement = tmpElement->NextSiblingElement();
			}
			if (!elements.empty())
				node = elements.top();
		}

	}

	bool IdDiscriminator::HaveRepetitiveids(void)
	{
		if (m_repetitiveids.empty()) return false;
		return true;
	}

	std::vector<int> IdDiscriminator::GetRepetitiveIds(void)
	{
		return m_repetitiveids;
	}
	std::vector<int> IdDiscriminator::GetAvailableIdsInRange(int startid, int endid)
	{
		std::vector<int> availableids;
		availableids.clear();
		for (int i = startid; i <= endid; i++) {
			if (m_idbitset.test(i)) continue;
			availableids.push_back(i);
		}
		return availableids;
	}

	bool IdDiscriminator::IsXmlPathExisted(void)
	{
		if (0 == access(m_xmlpath.c_str(), F_OK)) return true;
		return false;
		
	}
} // Ken
