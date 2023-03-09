#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>

struct SqlSelectQuery
{
	std::vector<std::string> column;
	std::string from;
	std::map< std::string,std::string> where;
};

class SqlSelectQueryBuilder {
	SqlSelectQuery select;
	std::string get_columns() {
		std::string columns = "";
		if (!select.column.empty()) {
			int count = 1;
			for (auto i = select.column.begin(); i != select.column.end(); ++i){
				columns += *i;
				if (count < select.column.size()) {
					columns = columns + ", ";
					++count;
				}
			}
		}
		else { columns = " * "; }
		return columns;
	}
	std::string get_froms() {
		std::string froms = " FROM " + select.from;		
		return froms;
	}
	std::string get_wheres() {
		std::string wheres = "";
		if (!select.where.empty()) {
			int count = 1;
			for (auto i = select.where.begin(); i != select.where.end(); ++i) {
				wheres = wheres + i->first + "=" + i->second;
				if (count < select.where.size()) {
					wheres = wheres + " AND ";
					++count;
				}
			}
			wheres = " WHERE " + wheres;
		}
		return wheres;
	}
	
public:
	SqlSelectQueryBuilder& AddColumn(std::string column_) noexcept {
		select.column.push_back(column_);
		return *this;
	}
	SqlSelectQueryBuilder AddFrom(std::string from_){
		select.from = from_;
		return *this;
	}
		
	SqlSelectQueryBuilder AddWhere(std::string a, std::string b) {
		select.where.insert(std::pair<std::string, std::string>(a, b));
		return *this;
	}
	
	std::string BuildQuery() {
		std::string out = "\"SELECT " + get_columns() + get_froms() + get_wheres() + " ;\"";
		return out;
	}
};