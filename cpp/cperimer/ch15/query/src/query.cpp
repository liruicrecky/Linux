/*************************************************************************
	> File Name: ./src/query.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 10:41:35 AM CST
 ************************************************************************/

#include"query.h"


std::set<TextQuery::line_no> OrQuery::eval(const TextQuery & file) const
{
	std::set<TextQuery::line_no> right = rhs.eval(file),
				ret_lines = lhs.eval(file);

	ret_lines.insert(right.begin(), right.end());
	
	return ret_lines;
}

//AndQuery

std::set<TextQuery::line_no> AndQuery::eval(const TextQuery &file) const
{
	std::set<line_no> left = lhs.eval(file),
					  right = rhs.eval(file);

	std::set<TextQuery::line_no> ret_lines;

	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(ret_lines, ret_lines.begin()));

	return ret_lines;

}

//NotQuery

std::set<TextQuery::line_no> NotQuery::eval(const TextQuery &file) const
{
	std::set<TextQuery::line_no> has_val = query.eval(file);
	std::set<TextQuery::line_no> ret_lines;

	for(TextQuery::line_no n = 0;n != file.size();++n)
	{
		if(has_val.find(n) == has_val.end())
			ret_lines.insert(n);
	}

	return ret_lines;
}


