#ifndef HPY_CORE_HPY_ENCRYPTION_
#define HPY_CORE_HPY_ENCRYPTION_

namespace hpy
{
    namespace Tcp
    {
        namespace Encryption
        {
            //Caesar cipher
            const int kCaesarCipher = 0;
            const unsigned char kCaesarCipherDefaultKey = 8;
            const unsigned char kCaesarCipherMaxValue = 0xff;
            bool Encrypt(int encryption_algorithm, unsigned char *plain_text, int len, unsigned char key);
            bool CaesarCipher(unsigned char *plain_text, int len, unsigned char key);

        }//Encryption
        
    };//Tcp

    
};//hpy


#endif