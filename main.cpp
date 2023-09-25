/************************************************************************/
/* Author     : Niranjan Ravi                                           */
/* Description: Program to handle information about pattern calls and   */
/*              display the patterns to the user based on queries       */
/************************************************************************/
#include "Solution3.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

/************************************************************************/
/* Function name : main                                                 */
/* Arguments     : int argc, char* argv[]                               */
/* Usage         : ./Test <input_file>                                  */
/* Return type   : int                                                  */
/* Description   : Main function of the program                         */
/************************************************************************/
int main(int argc, char* argv[]) {
    // Check if at least one command-line argument is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string filename = argv[1];

    // To write pattern data to a file
    write_file(filename);

    QueryHandler* queryHandler = new QueryHandler;
    // To read pattern data from a file
    read_file(filename, queryHandler);

    CheckID checkID;
    CheckName checkName;
    CheckLocation checkLocation;
    CheckFlag checkFlag;

    // Test Values Intialisation
    const vector<int> targetIdentifier = {50, 51, 45};
    const vector<string> targetName = {"myPattern10", "myPattern1"};
    const vector<string> targetLocation = {"src/patterns/Functional5.pat"};
    const vector<bool> targetCall = {false};
    vector<Pattern> matchedPatterns;

    queries(queryHandler->patterns, &checkID, targetIdentifier, matchedPatterns);
    queries(queryHandler->patterns, &checkName, targetName, matchedPatterns);
    queries(queryHandler->patterns, &checkLocation, targetLocation, matchedPatterns);
    queries(queryHandler->patterns, &checkFlag, targetCall, matchedPatterns);

    delete queryHandler;
    
    return 0;
}
