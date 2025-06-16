#include <openssl/sha.h>
#include <iostream>
int main() {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)"test", 4, hash);
    std::cout << "SHA256 worked\n";
    return 0;
}
