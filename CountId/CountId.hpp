#ifndef COUNTID_HPP__
#define COUNTID_HPP__ 

#include <string>
#include <bitset>
#include <vector>
#include <cstdint>
#include "./ThirdLib/tinyxml/tinyxml.h"
#include "./ThirdLib/tinyxml/tinystr.h"
//NOTE:
namespace Ken {

// #define ID_MAX    (~0U>>1)
#define ID_MAX    9999999
	class IdDiscriminator
	{
	public:
		IdDiscriminator();
		IdDiscriminator(const std::string& xmlpath);
		~IdDiscriminator();
		void ParseXml(void);
		void SetXmlPath(const std::string& xmlpath);
		std::vector<int> GetRepetitiveIds(void);
		std::vector<int> GetAvailableIdsInRange(int startid, int endid);
			//m_repetetiveids is empty return false, otherwise return true
		bool HaveRepetitiveids(void); // Not nessary

	protected:
		bool IsXmlPathExisted(void);
		bool LoadXmlFile(void);
		void GenerateIdBitSet(void);
		
	private:
		std::string m_xmlpath;
		std::bitset<ID_MAX> m_idbitset;
		std::vector<int> m_repetitiveids;
		TiXmlDocument m_doc;
	};
}

#endif
