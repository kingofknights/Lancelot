//
// Created by kingofknights on 7/12/23.
//
#include "Lancelot/Security/Security.hpp"

#include <xcd/libxcd.h>

#include <array>
#include <cstring>

#include "Lancelot/Structure.hpp"

namespace Lancelot {
using EncryptMessageT = std::array<unsigned char, ENCRYPT_MESSAGE_MAX_LENGTH>;

CommunicationT Encrypt(const std::string_view order_, uint32_t uid_, uint32_t query_) {
    int             encryptMessageLength = 0;
    EncryptMessageT encryptMessage;

    xcdCompress(reinterpret_cast<const unsigned char*>(order_.data()), static_cast<int>(order_.length()), encryptMessage.data(), &encryptMessageLength);
    CommunicationT communication{ ._user = uid_, ._query = query_, ._encryptLength = encryptMessageLength };
    std::memcpy(communication._encryptMessage.data(), encryptMessage.data(), encryptMessageLength);
    return communication;
}

int Decrypt(const unsigned char* encryptMessage_, int encryptLength_, unsigned char* decryptMessage_, int* decryptLength_) {
    return xcdDecompress(encryptMessage_, encryptLength_, decryptMessage_, decryptLength_);
}
}// namespace Lancelot
