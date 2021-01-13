#include <iostream>
#include "Server.h"
#include "Client.h"

int main(int argc, char const *argv[])
{
    if(argc == 2)
    {
        if (argv[1][0] == 's')
        {
            //Server
            Server s(8080);

          
            Data str = s.readMsg(0);
            if(sizeof(str) > 0) 
            {
                std::cout<<str.a<<std::endl;
                Data dar(2, 2);
                s.sendToAll(dar);
            }
        }
        if (argv[1][0] == 'c')
        {
            //Client
            Data data(1,1);
            Client client("127.0.0.1", 8080);
            client.sendMsg(data);
            data = client.readMsg();
            std::cout<<data.a<<std::endl;
        }
    }
    
    

    
    
    

    return 0;
}

