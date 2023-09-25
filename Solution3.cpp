#include <fstream>
#include <sstream>
#include "Solution3.h"

using std::string;
using std::cout;
using std::endl;

/************************************************************************/
/* Function name : bool_to_string                                       */
/* Arguments     : bool booleanValue                                    */
/* Return type   : string                                               */
/* Description   : Function to convert boolean into string              */
/************************************************************************/
std::string bool_to_string(bool booleanValue) {
    return booleanValue ? "true" : "false";
}


/************************************************************************/
/* Function name : string_to_bool                                       */
/* Arguments     : string stringValue                                   */
/* Return type   : bool                                                 */
/* Description   : Function to convert boolean into string              */
/************************************************************************/
bool string_to_bool(string stringValue) {
    return (stringValue == "true") ? true : false;
}

/************************************************************************/
/* Function name : write_file                                           */
/* Arguments     : string& filename                                     */
/* Return type   : void                                                 */
/* Description   : Function to write data to a file in the form of      */
/*                 patterns                                             */
/************************************************************************/
void write_file(string& filename){
    std::fstream stream{filename};
    //Checks for the existence of filename and proceeds into "if" condition if file does not exists, to create a new one
    if(!stream){
        //Creates a new file with the filename
        std::ofstream outfile{filename};

        if(!outfile){
            throw std::runtime_error("Error opening file for writing.");
        }
        outfile.close();

        cout << "Created file" << endl;

        stream.open(filename);
        stream << 41 << ", " << "myPattern1" << " ," << "src/patterns/Functional1.pat" <<" ,"<<"true"<< endl; 
        stream << 42 << ", " << "myPattern1" << " ," << "src/patterns/Functional1.pat" <<" ,"<<"false"<< endl; 
        stream << 43 << ", " << "myPattern2" << " ," << "src/patterns/Functional2.pat" <<" ,"<<"true"<< endl;
        stream << 44 << ", " << "myPattern3" << " ," << "src/patterns/Functional3.pat" <<" ,"<<"false"<< endl;
        stream << 45 << ", " << "myPattern4" << " ," << "src/patterns/Functional4.pat" <<" ,"<<"true"<< endl;
        stream << 46 << ", " << "myPattern5" << " ," << "src/patterns/Functional5.pat" <<" ,"<<"false"<< endl; 
        stream << 47 << ", " << "myPattern6" << " ," << "src/patterns/Functional6.pat" <<" ,"<<"true"<< endl;
        stream << 48 << ", " << "myPattern7" << " ," << "src/patterns/Functional7.pat" <<" ,"<<"false"<< endl;
        stream << 49 << ", " << "myPattern8" << " ," << "src/patterns/Functional8.pat" <<" ,"<<"true"<< endl; 
        stream << 50 << ", " << "myPattern9" << " ," << "src/patterns/Functional9.pat" <<" ,"<<"false"<< endl;  
        stream.close();
    }
    else{
        cout << "File exists already" << endl;
    }
}

/************************************************************************/
/* Function name : read_file                                            */
/* Arguments     : const string& filename                               */
/* Return type   : QueryHandler                                         */
/* Description   : Function to read data from a file that contains the  */
/*                 patterns data and returns it as class that contains  */
/*                 all the patterns                                     */
/************************************************************************/
void read_file(const string& filename, QueryHandler* queryHandler){

    std::ifstream infile(filename);
    if (!infile) {
        throw std::runtime_error("Error opening file for reading.");
    }

    string line;

    // Read the key-value pairs back from the text file
    while (std::getline(infile, line)) {
        std::stringstream iss(line);
        int id;
        char comma;
        string patternName, patternLocation, patternCall;
        bool value3;
        /*This parses each line into separate variables.
        The format is assumed to be consistent throughout the file*/
        iss >> id >> comma >> patternName >> comma >> patternLocation >> comma >> patternCall;
        value3 = string_to_bool(patternCall);
        
        queryHandler->addPatterns(id, patternName, patternLocation, value3);
    }

    infile.close();
    /*for(auto i =0; i < PATTERN_SIZE; ++i){
        cout << std::to_string(queryHandler->patterns[i].id) << "\n";
        cout << queryHandler->patterns[i].patternName << "\n";
        cout << queryHandler->patterns[i].patternLocation<< "\n";
        cout << bool_to_string(queryHandler->patterns[i].patternCall) << "\n";
    }*/   
}

/************************************************************************/
/* Function name : printValue                                           */
/* Arguments     : const int& value                                     */
/* Return type   : const void                                           */
/* Description   : Function to print the query(ID)                      */
/************************************************************************/
const void printValue(const int& value) {
    cout << "Query: " << value << "\n";
}

/************************************************************************/
/* Function name : printValue                                           */
/* Arguments     : const string& value                                  */
/* Return type   : const void                                           */
/* Description   : Function to print the query(Name, location)          */
/************************************************************************/
const void printValue(const string& value) {
    cout << "Query: " << value << "\n";
}

/************************************************************************/
/* Function name : printValue                                           */
/* Arguments     : const bool& value                                    */
/* Return type   : const void                                           */
/* Description   : Function to print the query(Call)                    */
/************************************************************************/
const void printValue(const bool& value) {
    cout << "Query: " << (value ? "true" : "false") << "\n";
}

/************************************************************************/
/* Function name : addPatterns                                          */
/* Class         : QueryHandler                                         */
/* Arguments     : const int& id, const string& patternName,            */
/*                 const string& patternLocation,                       */
/*                 const bool& patternCall                              */
/* Return type   : void                                                 */
/* Description   : Function to add the patterns to a vector             */
/************************************************************************/
void QueryHandler::addPatterns(const int& id, const string& patternName, const string& patternLocation, const bool& patternCall){
    Pattern pattern(id, patternName, patternLocation, patternCall);
    static int COUNT_SIZE = 0;
    if (COUNT_SIZE < PATTERN_SIZE) {
        /*printValue(pattern.id);
        printValue(pattern.patternName);
        printValue(pattern.patternLocation);
        printValue(pattern.patternCall);*/
        patterns[COUNT_SIZE] = pattern;
        ++COUNT_SIZE;
    } else {
        throw std::runtime_error("Array is already full");
    }
}

/************************************************************************/
/* Function name : displayPatterns                                      */
/* Class         : QueryHandler                                         */
/* Arguments     : const vector<Pattern>& patterns                      */
/* Return type   : const void                                           */
/* Description   : Function to display the patterns                     */
/************************************************************************/
const void QueryHandler::displayPatterns(const vector<Pattern>& patterns) const{
    for(auto &pattern: patterns){
        std::cout << pattern.id << ", " << pattern.patternName << ", " << pattern.patternLocation << ", " << bool_to_string(pattern.patternCall) << "\n";
    }
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : QueryHandler                                         */
/* Arguments     : const int& queryId                                   */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching queries                   */
/************************************************************************/
const vector<Pattern> QueryHandler::queryMatch(const int& queryId) const{
    vector<Pattern> matchingPatterns{};
    return matchingPatterns;
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : QueryHandler                                         */
/* Arguments     : const string& queryPattern                           */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching queries                   */
/************************************************************************/
const vector<Pattern> QueryHandler::queryMatch(const string& queryPattern) const{
    vector<Pattern> matchingPatterns{};
    return matchingPatterns;
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : QueryHandler                                         */
/* Arguments     : const bool& queryPatternCall                         */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching queries                   */
/************************************************************************/
const vector<Pattern> QueryHandler::queryMatch(const bool& queryPatternCall) const{
    vector<Pattern> matchingPatterns{};
    return matchingPatterns;
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : CheckID                                              */
/* Arguments     : const int& queryId                                   */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching query IDs                 */
/************************************************************************/
const vector<Pattern> CheckID::queryMatch(const int& queryId) const{
    vector<Pattern> matchingPatterns;
    for(auto i=0; i<PATTERN_SIZE; ++i){
        if(match<int>(patterns[i].id, queryId)){
            matchingPatterns.push_back(patterns[i]);
        }
    }
    return matchingPatterns;
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : CheckName                                            */
/* Arguments     : const string& queryPatternName                       */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching query names               */
/************************************************************************/
const vector<Pattern> CheckName::queryMatch(const string& queryPatternName) const{
    vector<Pattern> matchingPatterns;
    for(auto i=0; i<PATTERN_SIZE; ++i){
        if(match<string>(patterns[i].patternName, queryPatternName)){
            matchingPatterns.push_back(patterns[i]);
        }
    }
    return matchingPatterns;
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : CheckLocation                                        */
/* Arguments     : const string& queryPatternLocation                   */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching query location            */
/************************************************************************/
const vector<Pattern> CheckLocation::queryMatch(const string& queryPatternLocation) const{
    vector<Pattern> matchingPatterns;
    for(auto i=0; i<PATTERN_SIZE; ++i){
        if(match<string>(patterns[i].patternLocation, queryPatternLocation)){
            matchingPatterns.push_back(patterns[i]);
        }
    }
    return matchingPatterns;
}

/************************************************************************/
/* Function name : queryMatch                                           */
/* Class         : CheckFlag                                            */
/* Arguments     : const bool& queryPatternCall                         */
/* Return type   : const vector<Pattern>                                */
/* Description   : Function to check matching query Calls               */
/************************************************************************/
const vector<Pattern> CheckFlag::queryMatch(const bool& queryPatternCall) const{
    vector<Pattern> matchingPatterns;
    for(auto i=0; i<PATTERN_SIZE; ++i){
        if(match<bool>(patterns[i].patternCall, queryPatternCall)){
            matchingPatterns.push_back(patterns[i]);
        }
    }
    return matchingPatterns;
}

QueryHandler::QueryHandler():patterns(new Pattern[PATTERN_SIZE]()){
}

QueryHandler::QueryHandler(Pattern *patterns):patterns(patterns){
}

QueryHandler::~QueryHandler(){
    if(patterns != nullptr)
        delete[] patterns;
        patterns = nullptr;
}

QueryHandler::QueryHandler(const QueryHandler& queryHandler){
    patterns = new Pattern[PATTERN_SIZE];
    for (int i = 0; i < PATTERN_SIZE; ++i) {
        patterns[i] = queryHandler.patterns[i];
    }
}

QueryHandler::QueryHandler(QueryHandler&& queryHandler) noexcept {
    patterns = queryHandler.patterns;
    queryHandler.patterns = nullptr;
}

QueryHandler & QueryHandler::operator = (const QueryHandler& queryHandler){
    if(this != &queryHandler){
        delete[] patterns;
        patterns = new Pattern[PATTERN_SIZE];
        for (int i = 0; i < PATTERN_SIZE; ++i) {
            patterns[i] = queryHandler.patterns[i];
        }
    }
    return *this;
}

QueryHandler & QueryHandler::operator = (QueryHandler&& queryHandler) noexcept {
    if(this != &queryHandler){
        delete[] patterns;
        patterns = queryHandler.patterns;
        queryHandler.patterns = nullptr;
    }
    return *this;
}
