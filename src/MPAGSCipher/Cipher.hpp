#ifndef MPAGSCIPHER_CIPHER_HPP
#define MPAGSCIPHER_CIPHER_HPP

#include "CipherMode.hpp"
#include <string>

/**
 * \file Cipher.hpp
 * \brief Contains the declaration of the purely abstract Cipher base class
 * 
*/

/**
 * \class Cipher
 * \brief Defines the interface for a cipher
 * 
 * A purely abstract base class that defines the interface for a cipher
 * 
 * It can be used as follows:
 * \code{.cpp}
 * class MyCipher : public Cipher {...};
 * \endcode
*/

class Cipher {
    public:
    /** \brief Apply the cipher to the provided text
     * 
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     * 
    */
   virtual std::string applyCipher( const std::string& input,
                                    const CipherMode mode ) const = 0;
    /// Default constructor
    Cipher() = default;
    ///Default copy constructor
    Cipher(const Cipher& rhs) = default;
    /// Default move constructor
    Cipher(Cipher&& rhs) = default;
    // Default copy assignment operator
    Cipher& operator=(const Cipher& rhs) = default;
    //default move assignment operator
    Cipher& operator=(Cipher&& rhs) = default;
    //make the default destructor virtual
    virtual ~Cipher() = default;
};


#endif // MPAGSCIPHER_CIPHER_HPP
