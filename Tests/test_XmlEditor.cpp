#define BOOST_TEST_MODULE unit_tests

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "Tests/CTestSerialization.hpp"

/**
 *******************************************************************************
 *
 *   \par Name:
 *              bool UnitTestUSerialization(void)
 *
 *   \par Purpose:
 * 				Tests USerialization library \n
 *
 *   \par Inputs:
 * 				None \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				true if success, false if fails
 *
 *   \par Notes:
 * 				None
 *
 *******************************************************************************
 */
bool UnitTestUSerialization(void)
{
	/* Test classes */
	CTestSerialization T1, T2;

	/* Step 13: In function UnitTestUSerialization specify your strFileName. */
	std::string strFileName ="/TestUSerialization.xml";

	/* Clear T1 and T2 */
	T1.Clear();
	T2.Clear();

	/* Set initial values to T1: */
	T1.m_u8NumberOfSensors = 12;
	T1.m_strAttribute1 = "KARI";
	T1.m_strAttribute2 = "URANUS";
	T1.m_s32RunwayLength = 3200;
	T1.m_f64Temperature = 33.45;
	T1.m_bQNHFlag = true;
	T1.m_strCountryName = "Russia";
	T1.m_vCityNames.push_back("Saint-Petersburg");
	T1.m_vCityNames.push_back("Novgorod");
	printf("T1: \n");
	T1.Print();

	/* Save T1 */
	if(T1.Save(strFileName) == false)
	{
		printf("Function Save(): Fail \n");
		return false;
	}
	else
	{
		printf("Function Save(): Ok \n");
	}

	if(T2.Load(strFileName) == false)
	{
		printf("Function Load(): Fail \n");
		return false;
	}
	else
	{
		printf("Function Load(): Ok \n");
	}

	printf("T2: \n");
	T2.Print();

	if(T1 != T2)
	{
		printf("UnitTestUSerialization: Fail \n");
		return false;
	}
	else
	{
		printf("UnitTestUSerialization: Ok \n");
	}

	return true;

}

BOOST_AUTO_TEST_SUITE(unit_tests)

BOOST_AUTO_TEST_CASE(test_Serialization)
{
	BOOST_TEST_MESSAGE("USerializationTest");

	bool bRes = UnitTestUSerialization();

	BOOST_CHECK(bRes);
}
BOOST_AUTO_TEST_SUITE_END()
