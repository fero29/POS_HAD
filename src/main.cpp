#include <iostream>
#include "ServerLogic.h"
#include "ClientLogic.h"

int main(int argc, char const *argv[])
{
    
    if(argc == 2)
    {
        if (argv[1][0] == 's')
        {
            //Server
            ServerLogic(1);
        }
        if (argv[1][0] == 'c')
        {
            //Client
            ClientLogic();
        }
        
    }  
    
    

    return 0;
}

