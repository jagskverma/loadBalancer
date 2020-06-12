//simple request object
//using struct instead of class because object is relatively simple

#include<string>
using namespace std;

#define REQUEST_CPP

struct request{
    string source;
    string destination;
};