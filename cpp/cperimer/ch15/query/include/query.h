/*************************************************************************
	> File Name: ./include/query.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 10:41:44 AM CST
 ************************************************************************/

#ifndef __QUERY_H__
#define __QUERY_H__

#include<iostream>
#include<string>
#include<stream>

class Query_base
{
	friend class Query;
protected:
	typedef TextQuery::line_no line_no;
	virtual ~Query_base() { }
private:
	virtual std::set<line_no> 
		eval(const TextQuery &) const = 0;
	virtual std::ostream &
		display(std::ostream &= std::cout) const = 0;
};

class Query
{
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);

public:
	Queryz(const std::string &);
	Query(const Query &c) : q(c.q), use(c.use) { ++*use; }
	~Query() { decr_use(); }
	Query &operator=(const Query &);

	std::set<TextQuery::line_no>
		eval(const TextQuery &t) const { return q -> eval(t); }
	std::ostream &display(std::ostream &os) const { return q -> display(os); }
	std::ostream &operator<<(std::ostream &, const Query &);

private:
	Query(Query_base *query) : q(query), use(new std::size_t(1)) { }

	Query_base *q;
	std::size_t *use;
	void decr_use()
	{
		if(--*use == 0)
		{
			delete q;
			delete use;
		}
	}
};

class WordQuery: public Query_base
{
	friend class Query;
	WordQuery(const std::string &s) : query_word(s) { }

	std::set<line_no> eval(const TextQuery &t) const { return t.run_query(query_word); }
	std::ostream &display(std::osteram &os) const { return os << query_word; }
	std::string query_word;
};

class NotQuery: public Query_base
{
	friend Query operator~(const Query &);
	NotQuery(Query q) : query(q) { }

	std::set<line_no> eval(const TextQuery &) const;
	std::ostream &displat(std::ostream &os) const
	{
		return os << "~(" << query << ")" ;
	}

	const Query query;

};

class BinaryQuery: public Query_base
{
protected:
	BinaryQuery(Query left, Query right, std::string op) :
		ihs(left), rhs(right), oper(op) { }

	std::ostream &display(std::ostream &os) const
	{
		return os << "(" << " " << oper << " " << rhs << ")";
	}

	const Query ihs, rhs;
	const std::string oper;

};

class AndQuery: public BinaryQuery
{
	friend Query operator&(const Query &, const Query &);
	AndQuery(Query left, Query right) :
		BinaryQuery(left, right, "&") { }

	std::set<line_no> eval(const TextQuery &) const;
};

class OrQuery: public BinaryQuery
{
	friend Query operator|(const Query &, const Query &);
	OrQuery(Query left, Query right) :
		BinaryQuery(left, right, "|") { }

	std::set<line_no> eval(const TextQuery &) const;
};




#endif

