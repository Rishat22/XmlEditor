/*
  USerialization library incapsulates function to read and write data in
  XML format. It wraps some functions provided by pugi project.

  CTestSerialization is a class to test function of USerialization library and
  to demonstarte the way how USerialization lib can be used.

  The following steps shall be done to Load/Save data from/to xml file:
  1) Include USerializationStable.h and use namespace USerialization;
  2) Use namespace USerialization;
  3) Create a new class that is a child of class CXmlHandler;
  4) Destructor of a new class should be virtual;
  5) Declare function to Save data;
  6) Declare function to Load data;
  7) Declare virtual function XmlNodeBegin();
  8) Declare virtual function XmlNodeDecode();
  9) Declare class variables that shall be stored in XML file;
  10) Define function to Save data;
  11) Define XmlNodeBegin function;
  12) Define XmlNodeDecode function;
  13) In function UnitTestUSerialization specify your strFileName;
*/

/* Step 1: Include USerializationStable.h and use namespace USerialization */
#include "Serialization/CXmlHandler.h"

/* Step 2: Use namespace USerialization */
using namespace USerialization;

/* Step 3: Class CTestSerialization is a child of CXmlHandler */
/**
******************************************************************************
* Class CTestSerialization is intended to test USerialization library.
******************************************************************************
 */
class CTestSerialization : public CXmlHandler
{
public:
    /* Constructor */
    CTestSerialization() = default;
    /* Step 4: Destructor is virtual */
    virtual ~CTestSerialization() = default;

    /* Function to set members of the class to initial values */
    void Clear(void);

    /* Print function */
    void Print(void) const;

    /* Operator != */
    bool operator !=(const CTestSerialization& TS);

    /* Step 5: Declaration of function to Save data */
    bool Save(std::string strFileNameToSave);
    /* Step 6: Declaration of function to Load data */
    bool Load(std::string strFileNameToLoad);

    /* Step 7: Declaration of virtual function XmlNodeBegin */
    virtual bool XmlNodeBegin(void);
    /* Step 8: Declaration of virtual function XmlNodeDecode */
    virtual bool XmlNodeDecode(const std::string& strNodeValue);

    /* Step 9: Declaration class variables that shall be stored in XML file: */
    /* Number of Sensors: */
    char m_u8NumberOfSensors;

    /* String attribute 1 */
    std::string m_strAttribute1;

    /* String attribute 2 */
    std::string m_strAttribute2;

    /* Length of the Runway*/
    int m_s32RunwayLength;

    /* Temperature */
    double  m_f64Temperature;

    /* QNH Flag */
    bool m_bQNHFlag;

    /* Name of the country */
    std::string m_strCountryName;

    /* Vector of city's names */
    std::vector<std::string> m_vCityNames;
};

void CTestSerialization::Clear(void)
{
    m_u8NumberOfSensors = 0;

    m_strAttribute1.clear();

    m_strAttribute2.clear();

    m_s32RunwayLength = 0;

    m_f64Temperature = -273.0;

    m_bQNHFlag = false;

    m_strCountryName.clear();

    m_vCityNames.clear();
}
void CTestSerialization::Print(void) const
{
    printf("Number Of sensors: %d \n", m_u8NumberOfSensors);
    printf("Attribute1: %s \n", m_strAttribute1.data());
    printf("Attribute2: %s \n", m_strAttribute2.data());
    printf("Runway length: %d \n", m_s32RunwayLength);
    printf("Temperature: %lf \n", m_f64Temperature);
    if(m_bQNHFlag)
    {
        printf("QNH Flag: true \n");
    }
    else
    {
        printf("QNH Flag: false \n");
    }
    printf("Country: %s \n", m_strCountryName.data());

    std::vector<std::string>::const_iterator Beg(m_vCityNames.begin());
    std::vector<std::string>::const_iterator End(m_vCityNames.end());
    std::vector<std::string>::const_iterator Iter;
    for(Iter = Beg; Iter != End; ++Iter)
    {
        printf("City: %s \n", Iter->data());
    }

}

/* Step 10: Definition of function to Save data */
bool CTestSerialization::Save(std::string strFileNameToSave)
{
    /*
        Step 10.a: pDoc shall be a new document. Call a function NewDocument()
        You NEED NOT call delete() function for CXmlNode* object. It will be
        deleted automatically (in its destructor).
        */
    CXmlNode* pDoc = NewDocument(strFileNameToSave);

    /* Step 10.b: You can set any comments for any CXmlNode */
    pDoc->SetComment("Test Commnet #1");

    /*
        Step 10.c: Spesify other CXmlNode* nodes.
        Call a function NewNode("TestParams", pDoc), first parameter is the name of
        the node in XML file, the second parameter is a parent node.
        You NEED NOT call delete() function for CXmlNode* object. It will be
        deleted automatically (in its destructor).
        */
    CXmlNode* pTestParams = NewNode("TestParams", pDoc);

    /* Number of Sensors */
    {
        /*
                Step 10.d: Spesify next CXmlNode* node.
                Call a function NewNode("TestParams", pDoc), first parameter is the name of
                the node in XML file, the second parameter is a parent node.
                You NEED NOT call delete() function for CXmlNode* object. It will be
                deleted automatically (in its destructor).
                */
        CXmlNode* pNumberOfSensors = NewNode("NumberOfSensors", pTestParams);

        /*
                Step 10.e: Add attributr to CXmlNode* node. There are four functions:
                CXmlNode::AddAttribute(std::string strAttributeName, int s32Attribute);
                CXmlNode::AddAttribute(std::string strAttributeName, double f64Attribute);
                CXmlNode::AddAttribute(std::string strAttributeName, std::string strAttribute);
                CXmlNode::AddAttribute(std::string strAttributeName, bool bAttribute);
                */
        pNumberOfSensors->AddAttribute("Attribute1", m_strAttribute1);
        pNumberOfSensors->AddAttribute("Attribute2", m_strAttribute2);

        /*
                Step 10.f: Set value to CXmlNode* node. There are four functions:
                CXmlNode::SetValue(std::string strValue);
                CXmlNode::SetValue(int s32Value);
                CXmlNode::SetValue(double f64Value);
                CXmlNode::SetValue(bool bValue);
                */
        pNumberOfSensors->SetValue(static_cast<int>(m_u8NumberOfSensors));
    }

    /* Runway length */
    {
        CXmlNode* pRunwayLength = NewNode("RunwayLength", pTestParams);
        pRunwayLength->SetValue(m_s32RunwayLength);
    }

    /* Temperature */
    {
        CXmlNode* pTemperature = NewNode("Temperature", pTestParams);
        pTemperature->SetValue(m_f64Temperature);
    }

    /* QNH flag */
    {
        CXmlNode* pQNHFlag = NewNode("QNHFlag", pTestParams);
        pQNHFlag->SetValue(m_bQNHFlag);
    }

    /* Country and cities */
    {
        CXmlNode* pCountry = NewNode("Country", pTestParams);
        CXmlNode* pCountryName = NewNode("CountryName", pCountry);
        pCountryName->SetValue(m_strCountryName);

        /* Vector of cities */
        std::vector<std::string>::iterator Beg(m_vCityNames.begin());
        std::vector<std::string>::iterator End(m_vCityNames.end());
        std::vector<std::string>::iterator Iter;
        for(Iter = Beg; Iter != End; ++Iter)
        {
            CXmlNode* pCity = NewNode("City", pCountry);
            pCity->SetValue(*Iter);
        }
    }

    /*
        Step 10.g: Save xml structure to xml file. Call SaveDocument() function and return its result.
        */
    bool bRes = SaveDocument();
    return bRes;
}

bool CTestSerialization::operator !=(const CTestSerialization& TS)
{
    if(m_u8NumberOfSensors != TS.m_u8NumberOfSensors)
    {
        return true;
    }
    if(m_strAttribute1 != TS.m_strAttribute1)
    {
        return true;
    }
    if(m_strAttribute2 != TS.m_strAttribute2)
    {
        return true;
    }
    if(m_s32RunwayLength != TS.m_s32RunwayLength)
    {
        return true;
    }
    if(std::abs(m_f64Temperature - TS.m_f64Temperature) > 0.000001)
    {
        return true;
    }
    if(m_bQNHFlag != TS.m_bQNHFlag)
    {
        return true;
    }
    if(m_strCountryName != TS.m_strCountryName)
    {
        return true;
    }
    if(m_vCityNames != TS.m_vCityNames)
    {
        return true;
    }

    return false;
}

/*
Step 11: Definition of XmlNodeBegin function.
This function is called from CXmlHandler::begin when node begins.
m_vStrOfNodes - consists of Node's Names.
*/
bool CTestSerialization::XmlNodeBegin(void)
{
    if(m_vStrOfNodes[0] == "TestParams")
    {
        if(m_vStrOfNodes[1] == "NumberOfSensors")
        {
            if(m_vStrOfNodes[2] == "")
            {
                /*Step 11.a: If we are here it means that this is a start of Node TestParams/NumberOfSensors
                                (m_vStrOfNodes[2] == ""). We have to read attributes here */
                std::vector<Attribute>::iterator begin = m_vAttributes.begin();
                std::vector<Attribute>::iterator end = m_vAttributes.end();
                std::vector<Attribute>::iterator iter;
                for(iter = begin; iter != end; ++iter)
                {
                    if(iter->m_strName == "Attribute1")
                    {
                        m_strAttribute1 = iter->m_strValue;
                    }
                    if(iter->m_strName == "Attribute2")
                    {
                        m_strAttribute2 = iter->m_strValue;
                    }
                }
            }
        }
        if(m_vStrOfNodes[1] == "Country")
        {
            if(m_vStrOfNodes[2] == "City")
            {
                if(m_vStrOfNodes[3] == "")
                {
                    /*Step 11.b: If we are here it means that this is a start of Node TestParams/Country/City
                                        (m_vStrOfNodes[3] == "") .
                                        Add an empty string to the vector (reserve a memory for new city name) */
                    m_vCityNames.push_back(std::string());
                }
            }
        }
    }

    return true;
}
/*
Step 12: Definition of XmlNodeDecode function.
This function is called from CXmlHandler::for_each
m_vStrOfNodes - consists of Node's Names,
strNodeValue - is value of specified node
*/
bool CTestSerialization::XmlNodeDecode(const std::string& strNodeValue)
{
    if(m_vStrOfNodes[0] == "TestParams")
    {
        if(m_vStrOfNodes[1] == "NumberOfSensors")
        {
            m_u8NumberOfSensors = atol(strNodeValue.data());
        }
        if(m_vStrOfNodes[1] == "RunwayLength")
        {
            m_s32RunwayLength = atol(strNodeValue.data());
        }
        if(m_vStrOfNodes[1] == "Temperature")
        {
            m_f64Temperature = std::atof(strNodeValue.data());
        }
        if(m_vStrOfNodes[1] == "QNHFlag")
        {
            m_bQNHFlag = (strNodeValue == "TRUE") ? true : false;
        }
        if(m_vStrOfNodes[1] == "Country")
        {
            if(m_vStrOfNodes[2] == "CountryName")
            {
                m_strCountryName = strNodeValue;
            }

            if(m_vStrOfNodes[2] == "City")
            {
                if(m_vCityNames.empty() == false)
                {
                    m_vCityNames.back() = strNodeValue;
                }
            }
        }

    }

    return true;
}

/* Step 13: Definition of Load function. */
bool CTestSerialization::Load(std::string strFileNameToLoad)
{
    /* Step 13.a: Clear all members. */
    Clear();

    /* Step 13.b: Call function CXmlHandler::Load(). */
    if(CXmlHandler::Load(strFileNameToLoad) == false)
    {
        return false;
    }

    return true;
}
