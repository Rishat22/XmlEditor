#include <sstream>
#include <QColor>
#include <Tools/TypeExceptions.h>
#include "MathFunc.h"

namespace Tools
{

QColor MathFunc::StringToColor(const std::string& strColor)
{
	const auto colorSegments = SplitString(strColor, ',');
	if(colorSegments.size() != 4)
		throw ColorException();
	std::stringstream ss;
	std::copy(colorSegments.begin(), colorSegments.end(), std::ostream_iterator<std::string>(ss,"\n"));
	int r, g, b, a;
	ss >> r >> g >> b >> a;
	return QColor(r, g, b, a);
}

std::vector<std::string> MathFunc::SplitString(const std::string& strText, char delimiter)
{
	std::vector<std::string> substringsSet;

	std::string::size_type start = 0;
	std::string::size_type stop = strText.find_first_of(delimiter);
	while(stop != std::string::npos)
	{
		substringsSet.push_back(strText.substr(start, stop - start));

		start = stop + 1;
		stop = strText.find_first_of(delimiter, start);
	}

	substringsSet.push_back(strText.substr(start));

	if(substringsSet.size() == 1)
		throw SplitStringException();

	return substringsSet;
}

}
