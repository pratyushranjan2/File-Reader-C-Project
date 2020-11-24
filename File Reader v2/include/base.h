#ifndef base_h_
#define base_h_
#include<string>
#include<fstream>
using namespace std;
class base{
    public:
        base();
        virtual ~base();
        virtual void fileRead();
        virtual void fileWrite();
        virtual void execute();
};
#endif