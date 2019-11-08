#include <iostream>
#include "curl.hpp"

int main() {
    curl::easy easy;
    easy.set_option(CURLOPT_URL, "172.16.200.13");
    std::string contents_172;
    easy.set_option(CURLOPT_WRITEDATA, &contents_172);
    easy.set_option(CURLOPT_WRITEFUNCTION, curl::helper::string_writer);
    easy.perform();
}