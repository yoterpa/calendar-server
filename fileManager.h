#include <cstring>
#include <vector>

using namespace std;


string addEvent ( string fileName, vector<std::string> operation );
string removeEvent ( string fileName, vector<std::string> operation );
string getEvent ( string fileName, vector<std::string> operation );
string updateEvent ( string fileName, vector<std::string> operation );
string execQuery( string query );
string findNumLines ( string fileName );
string getLine ( string fileName, vector<std::string> operation );

