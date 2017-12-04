/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
void (*myfp)(int a);

using namespace std;


void f1(int a){
    cout<<"f1 called. arg = " << a << "\n";
}
void f2(int a){
    cout<<"f2 called. arg = " << a << "\n";
}


int main()
{
    myfp = f1;
    cout<<"Hello World\n";

    myfp(10);

    void (*exe)(int arg);
    exe = f1;
    
    exe(20);
    
    myfp = f2;
    myfp(30);
    exe(20);
    

    return 0;
}



