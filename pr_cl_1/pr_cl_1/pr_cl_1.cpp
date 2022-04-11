
#include <iostream>
#include "Conectare_Srv.h"

int main()
{
    Conectare_Srv::Connect();
    std::cout<<Conectare_Srv::Recvs();
    Conectare_Srv::SendToServer("1$ionpop$hash$pop$ion$pop@ion$arges$0754649523$client$");
}

