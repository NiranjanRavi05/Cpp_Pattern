#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::vector;

const int PATTERN_SIZE = 10;

struct Pattern{
    int id=0;
    string patternName="";
    string patternLocation="";
    bool patternCall=false;
    Pattern():id(0), patternName(""), patternLocation(""), patternCall(false){}
    Pattern(int id, string patternName, string patternLocation, bool patternCall) : id(id), patternName(patternName), patternLocation(patternLocation), patternCall(patternCall) {}
};


class QueryHandler{
public:
    Pattern *patterns = new Pattern[PATTERN_SIZE]();
    QueryHandler();
    QueryHandler(Pattern *patterns);
    QueryHandler(const QueryHandler& queryHandler);
    QueryHandler(QueryHandler&& queryHandler) noexcept;
    QueryHandler & operator = (const QueryHandler& queryHandler);
    QueryHandler & operator = (QueryHandler&& queryHandler) noexcept;
    void addPatterns(const int& id, const string& patternName, const string& patternLocation, const bool& patternCall);
    const void displayPatterns(const vector<Pattern>& patterns) const;
    virtual const vector<Pattern> queryMatch(const int& queryId) const;
    virtual const vector<Pattern> queryMatch(const string& queryPattern) const;
    virtual const vector<Pattern> queryMatch(const bool& queryPatternCall) const;
    ~QueryHandler();
};


class CheckID: public QueryHandler{
public:
    const vector<Pattern> queryMatch(const int& queryId) const override;
};


class CheckName: public QueryHandler{
public:
    const vector<Pattern> queryMatch(const string& queryPatternName) const override;
};


class CheckLocation: public QueryHandler{
public:
    const vector<Pattern> queryMatch(const string& queryPatternLocation) const override;
};


class CheckFlag: public QueryHandler{
public:
    const vector<Pattern> queryMatch(const bool& queryPatternCall) const override;
};


//Function declarations
void write_file(string& filename);
void read_file(const string& filename, QueryHandler* queryHandler);
std::string bool_to_string(bool booleanValue);
bool string_to_bool(string stringValue);
const void printValue(const int& value);
const void printValue(const string& value);
const void printValue(const bool& value);


template<typename T>
void queries(Pattern *patterns, QueryHandler *queryHandlerQuery, const T& targetQuery, vector<Pattern>& matchedPatterns){
    queryHandlerQuery->patterns = patterns;
    cout << "\n /***************** Query *******************/\n\n";
    // To perform checking of ID
    for(const auto& targetValue : targetQuery){
        matchedPatterns = queryHandlerQuery->queryMatch(targetValue);
        printValue(targetValue);
        if(matchedPatterns.size()){
            queryHandlerQuery->displayPatterns(matchedPatterns);
        }
        else{
            cout << " -> Not found in the data"<< endl;
        }
    }
    queryHandlerQuery->patterns = nullptr;
}

template<typename T>
bool match(T originalValue, T QueryValue){
    if(originalValue == QueryValue) return true;
    else return false;
}

#endif // SOLUTION_H