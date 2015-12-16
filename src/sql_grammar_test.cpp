
#include <stdio.h>
#include <string>
#include <cstring>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include "SQLParser.h"
#include "sqlhelper.h"
#include <vector>
#include <cstdlib>

using namespace hsql;
using namespace std;

// type: select
// options: null
// distinct: null
// columns: *
// from:
// db: null
// table: nation
// as: null
// where: null
// groupby: null
// having: null
// orderby: null
// limit: null

class PrintToFile{
public:
    string type;
    string options;
    string distinct;
    vector<string> columns;
    string from;
    string table2;
    string db;
    string table;
    string as;
    bool showjoin;
    string join;
    string on1;
    string on2;
    string where;
    string groupby;
    string having;
    string orderby;
    string limit;

    void PrintAll()
    {
    ofstream myfile;
    myfile.open ("sample_query.txt");
    //type
    myfile<<"type: select"<<endl;
    myfile<<"options: null"<<endl;
    myfile<<"distinct: null"<<endl;
    myfile<<"columns: ";
    for (int i = 0; i < columns.size(); ++i)
    {
        myfile<<columns[i] << " ";
    }
    myfile<<endl;
    myfile<<"from:"<<endl;
    if (showjoin)
    {
        myfile<<"table: "<< table2 <<endl;
    }
    myfile<<"db: null"<<endl;
    myfile<<"table: "<< table <<endl;
    myfile<<"as: null"<<endl;
    if(showjoin){
        myfile<<"join: inner join" <<endl;
        myfile<<"on: "<< on1 <<endl;
        myfile<<"on: "<< on2 <<endl;
    }
    myfile<<"where: null"<<endl;
    myfile<<"groupby: null"<<endl;
    myfile<<"having: null"<<endl;
    myfile<<"orderby: null"<<endl;
    myfile<<"limit: null";

    myfile.close();
    }
};

string printExpressionMod(Expr* expr, uint num_indent) {
  switch (expr->type) {
    case kExprStar: return "*";
    case kExprColumnRef:  return expr->name;
    // case kExprTableColumnRef: inprint(expr->table, expr->name, num_indent); break;
    case kExprLiteralFloat: break;
    case kExprLiteralInt:  break;
    case kExprLiteralString:  break;
    case kExprFunctionRef:  break;
    case kExprOperator:  break;
    default: return NULL;
  }
}

std::vector<std::string> readlines(std::string path) {
    std::ifstream infile(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);

        // Skip comments
        if (line[0] != '#') {
            lines.push_back(line);
        }
    }
    return lines;
}

#define STREQ(a, b) (std::string(a).compare(std::string(b)) == 0)

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Usage: grammar_test [--false] [-f path] query, ...\n");
        return -1;
    }
    PrintToFile File1;
    bool expect_false = false;
    bool use_file = false;
    bool joining = false;
    std::string file_path = "";
    
    // Parse command line arguments
    int i = 1;
    for (; i < argc; ++i) {
        if (STREQ(argv[i], "--false")) expect_false = true;
        else if (STREQ(argv[i], "-f")) {
            use_file = true;
            file_path = argv[++i];
        } else {
            break;
        }
    }


    // Read list of queries for this rest
    std::vector<std::string> queries;
    if (use_file) {
        queries = readlines(file_path);
    } else {
        for (; i < argc; ++i) queries.push_back(argv[i]);
    }
    

    // Execute queries
    int num_failed = 0;
    for (std::string sql : queries) {
    // std::cout << queries << std::endl;
        // Measuring the parsing time
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        // Parsing
        SQLStatementList* stmt_list = SQLParser::parseSQLString(sql.c_str());

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        double us = elapsed_seconds.count() * 1000 * 1000;

        if (expect_false == stmt_list->isValid) {
            printf("\033[0;31m{  failed}\033[0m\n");
            printf("\t\033[0;31m%s (L%d:%d)\n\033[0m", stmt_list->parser_msg, stmt_list->error_line, stmt_list->error_col);
            printf("\t%s\n", sql.c_str());
            num_failed++;
        } else {
            // TODO: indicate whether expect_false was set
            printf("\033[0;32m{      ok} (%.1fus)\033[0m %s\n", us, sql.c_str());
                SelectStatement* stmt = (SelectStatement*) stmt_list->getStatement(0);
            //join detection
                if(strstr(sql.c_str(), "JOIN") != NULL) {
                    //cout<<"Join"<<endl;
                    joining = true;
                    File1.showjoin = true;
                }else{
                    // cout<<"Nojoin"<<endl;
                    joining = false;
                    File1.showjoin = false;
                }
            //print tokens
                printSelectStatementInfo(stmt,1);
                // cout << "\033[0;31mselect \033[0m| ";
                // for (Expr* expr : *stmt->select_list) printExpression(expr, 0);
                // cout << endl;
                if (joining)
                {
                    cout << "\033[0;31mtables \033[0m| "<< stmt->from_table->join->left->name << " and " << stmt->from_table->join->right->name << endl;
                    for (Expr* expr : *stmt->select_list) File1.columns.push_back( printExpressionMod(expr, 0));
                    File1.table2 = stmt->from_table->join->left->name;
                    File1.table = stmt->from_table->join->right->name;
                    // File1.on1 = printExpressionMod(stmt->from_table->join->condition->expr,0);
                    // File1.on2 = printExpressionMod(stmt->from_table->join->condition->expr2,0);
                    File1.on1 = "1";//fixed for now
                    File1.on2 = "2";//fixed for now
                }else{
                    cout << "\033[0;31mtable  \033[0m| "<< stmt->from_table->name << endl;
                    // File1.columns = "test";
                    for (Expr* expr : *stmt->select_list) File1.columns.push_back( printExpressionMod(expr, 0));
                    File1.table = stmt->from_table->name;
                }
                // cout << "where | "<< stmt->where_clause->expr->name  << " , " << stmt->where_clause->expr2->name<< endl;

        }
    }

    if (num_failed == 0) {
        printf("\033[0;32m{      ok} \033[0mAll %lu grammar tests completed successfully!\n", queries.size());
    } else {
        fprintf(stderr, "\033[0;31m{  failed} \033[0mSome grammar tests failed! %d out of %lu tests failed!\n", num_failed, queries.size());
    }
    File1.PrintAll();
    system("open sample_query.txt");
	return 0;
}