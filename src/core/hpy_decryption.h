#ifndef HPY_CORE_HPY_DECRYPTION_
#define HPY_CORE_HPY_DECRYPTION_

namespace hpy
{
    namespace Tcp
    {
        namespace Decryption
        {   
            bool Decrypt(int encryption_algorithm, unsigned char *cipher_test, int len, unsigned char key);
            bool CaesarCipher(unsigned char *cipher_test, int len, unsigned char key);

        }//Decryption
        
    };//Tcp

};//hpy


#endif