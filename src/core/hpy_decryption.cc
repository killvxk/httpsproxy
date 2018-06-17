#ifndef HPY_CORE_HPY_DECRYPTION_
#include "core/hpy_decryption.h"
#endif

#ifndef HPY_CORE_HPY_ENCRYPTION_
#include "core/hpy_encryption.h"
#endif

bool hpy::Tcp::Decryption::Decrypt(int encryption_algorithm, unsigned char *cipher_test, int len, unsigned char key)
{
    switch(encryption_algorithm)
    {
        case hpy::Tcp::Encryption::kCaesarCipher:
            return hpy::Tcp::Decryption::CaesarCipher(cipher_test, len, key);
    }
    return false;
}

bool hpy::Tcp::Decryption::CaesarCipher(unsigned char *cipher_test, int len, unsigned char key)
{
    for(int i=0; i<len; i++)
    {
        cipher_test[i] = (cipher_test[i] - key);
    }
    return true;
}