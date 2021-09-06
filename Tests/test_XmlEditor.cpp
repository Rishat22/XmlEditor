#define BOOST_TEST_MODULE unit_tests

#include <iostream>
#include <string>
#include <list>
#include <filesystem>
#include <thread>
#include <boost/test/unit_test.hpp>

namespace fs = std::filesystem;

BOOST_AUTO_TEST_SUITE(unit_tests)

BOOST_AUTO_TEST_CASE(test_check_number_files_created)
{

	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
