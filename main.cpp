/**
* This is our display code.
*
*  
*/


// #include "led-matrix.h"
#include "cpr/cpr.h"
#include <unistd.h>
// #include <math.h>
// #include <stdio.h>
// #include <signal.h>
#include <iostream>


int main(int argc, char *argv[]) {
    cpr::Response r = cpr::Get(
        cpr::Url{"https://appalcart.etaspot.net/service.php"},
        cpr::Parameters{
            {"service", "get_vehicles"},
            {"includeETAData", "1"},
            {"inService", "1"},
            {"orderedETAArray", "1"},
            {"token", "TESTING"}
        }
    );
    
    std::cout << "Status Code: " << r.status_code << std::endl;

    std::cout << "Response Body:\n" << r.text << std::endl;
    return 0;
}
