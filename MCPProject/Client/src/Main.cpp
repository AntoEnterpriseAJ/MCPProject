#include <iostream>
#include <cpr/cpr.h>

int main()
{
    cpr::Response greetResponse = cpr::Get(cpr::Url{"http://localhost:18080/greet"});

    auto [statusCode, text] = std::tie(greetResponse.status_code, greetResponse.text);
    if (statusCode == cpr::status::HTTP_OK)
    {
        std::cout << "GET was succesful\n";
        std::cout << text << "\n";
    }
    else
    {
        std::cout << "GET failed, error: " << greetResponse.status_code << "\n";
    }

    return 0;
}