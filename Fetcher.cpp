#include "Fetcher.h"
#include "include/json.hpp"
using json = nlohmann::json;

#define STOPID 37

int32_t main(int32_t argc, char * argv[]) {
    printHello();

    cpr::Response r = cpr::Get(cpr::Url{"https://appalcart.etaspot.net/service.php?service=get_stop_etas&stopID=STOPID&token=TESTING"});
    //std::cout << r.text << std::endl;

    json data = json::parse(r.text);
    std::cout << data["get_stop_etas"][0] << std::endl;

    return 0;
}

void printHello() {
    printf("Hello World\n");
}
