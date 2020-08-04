#include "strFunction.h"

vector<string> strFunction::split_str(const string &str, char ch)
{
	vector<string> result;
	string newstr;
	for (auto c : str)
	{
		if (c != ch)
		{
			newstr += c;
		}
		else
		{
			result.push_back(newstr);
			newstr = "";
		}
	}
	result.push_back(newstr);
	return result;
}

