#include <vector>
#include <string>
#pragma once
using namespace std;

class StringUtility {
    public:
        
        static string removeFromString(string s, string str) {  // s will be rmeoved from string
            size_t pos = str.find(s);
            if (pos == string::npos) {
                return str;
            }
            return str.substr(0,pos);
        }

        static vector<string> splitBySpace(string str) {
            vector<string> parts;
            string delimiter = " ";
            size_t pos = 0;
            string token;

            while ((pos = str.find(delimiter)) != string::npos) {
                token = str.substr(0,pos);
                parts.push_back(token);
                str.erase(0,pos+delimiter.length());
            }
            parts.push_back(str);
            return parts;
        }

        static string trim(string str) {
            string whiteSpace = " ";
            size_t start = str.find_first_not_of(whiteSpace);
            if (start == string::npos) {
                start = 0;
            }
            str = str.substr(start);
            size_t end = str.find_last_not_of(whiteSpace);
            if (end == string::npos) {
                end = str.size()-1;
            }
            str = str.substr(0,end+1);
            return str;
        }
};