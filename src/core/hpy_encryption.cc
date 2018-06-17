#ifndef HPY_CORE_HPY_ENCRYPTION_
#include "core/hpy_encryption.h"
#endif

bool hpy::Tcp::Encryption::Encrypt(int encryption_algorithm, unsigned char *plain_text, int len, unsigned char key)
{
    switch(encryption_algorithm)
    {
        case hpy::Tcp::Encryption::kCaesarCipher:
            return hpy::Tcp::Encryption::CaesarCipher(plain_text, len, key);
    }
    return false;
}

bool hpy::Tcp::Encryption::CaesarCipher(unsigned char *plain_text, int len, unsigned char key)
{
    for(int i=0; i<len; i++)
    {
        plain_text[i] = (plain_text[i] + key);
    }
    return true;
}