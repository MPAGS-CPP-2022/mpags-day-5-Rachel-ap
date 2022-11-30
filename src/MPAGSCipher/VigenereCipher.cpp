#include "VigenereCipher.hpp"
#include "Alphabet.hpp"

#include <algorithm>
#include <string>
#include <iostream>

VigenereCipher::VigenereCipher(const std::string& key)
{
    this->setKey(key);
}

void VigenereCipher::setKey(const std::string& key)
{
    // store the original key
    key_ = key;

    //Make sure the key is upper case
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                    ::toupper);

    //remove non-alphabet characters
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),
                        [](char c) {return !std::isalpha(c); }),
                std::end(key_));

    //check that the key is not now empty
    if (key_.empty()) {
        //set it to some default value and print warning
        key_ = "VIGENEREEXAMPLE";
        std::cerr 
            << "[warning] key provided to VigenereCipher is empty, setting it to the default: "
            << key_ << std::endl;
    }

    //Loop through the key
    charLookup_.clear();
    for (const char letter : key_) {
        // check if we've already seen this letter before
        if (charLookup_.find(letter) != charLookup_.end()) {
            continue;
        }
        // find the position of the letter in the alphabet
        const std::size_t index{Alphabet::alphabet.find(letter)};

        //construct a caesar cipher object using the position as the key

         // store the Caesar cipher object so that it can be retrieved based on the character in the key
        charLookup_.emplace(std::piecewise_construct, std::make_tuple(letter),
                            std::make_tuple(index));
    }
}

std::string VigenereCipher::applyCipher(const std::string& inputText,
                                        const CipherMode cipherMode) const
{
    //store the size of the input text and of the key
    const std::size_t inputSize{inputText.size()};
    const std::size_t keySize{key_.size()};

    // create the output string, reserving space for
    // as many characters as are in the input text
    std::string outputText;

    // loop through the text
    for (std::size_t i{0}; i < inputSize; ++i){
        // determine the corresponding character in the key based on the position
        // (repeating the key if necessary)
        const char keyChar{key_[i % keySize]};

        // find the corresponding caesar cipher
        const CaesarCipher& cipher{charLookup_.at(keyChar)};

        //use it to encrypt/decrypt the character of the text
        // and put the new character into the output
        const std::string oldChar{inputText[i]};
        outputText += cipher.applyCipher(oldChar, cipherMode);
    }
    //return the output text
    return outputText;
}   