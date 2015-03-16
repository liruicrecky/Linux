/*************************************************************************
	> File Name: ./src/query.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 10:41:35 AM CST
 ************************************************************************/

#include"query.h"

//Query

inline Query operator~(const Query &oper)
{
	return new NotQuery(oper);
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return new OrQuery(lhs, rhs);

}

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return new AndQuery(lhs, rhs);
}

inline std::ostream &operator<<(std::ostream &os, const Query &q){
	return q.display(os);
}

//OrQuery

std::set<TextQuery::line_no> OrQuery::eval(const TextQuery & file) const
{
	std::set<line_on> right = rhs.eval(file),
				ret_lines = lhs.eval(file);

	ret_lines.insert(right.begin(), right.end());
	
	return ret_lines;
}

//AndQuery

std::set<TextQuery::line_no> AndQuery::eval(const TextQuery &file) const
{
	std::set<line_no> left = ihs.eval(file),
					  right = rhs.eval(file);

	std::set<line_on> ret_lines;

	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(ret_lines, ret_lines.begin()));

	return ret_lines;

}

//NotQuery

std::set<TextQuery::line_on> NotQuery::eval(const TextQuery &file) const
{
	std::set<TextQuery::line_on> has_val = query.eval(file);
	std::set<line_no> ret_lines;

	for(TextQuery::line_no n = 0;n != file.size();++n)
	{
		if(has_val.find(n) == has_val.end())
			ret_lines.insert(n);
	}

	return ret_lines;
}


