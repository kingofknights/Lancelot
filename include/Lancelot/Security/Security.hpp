//
// Created by kingofknights on 7/12/23.
//

#ifndef LANCELOT_INCLUDE_LANCELOT_SECURITY_SECURITY_HPP_
#define LANCELOT_INCLUDE_LANCELOT_SECURITY_SECURITY_HPP_
#pragma once

#include <cstdint>
#include <string_view>

namespace Lancelot {
struct CommunicationT;

[[nodiscard]] CommunicationT Encrypt(const std::string_view order_, uint32_t uid_, uint32_t query_);

int Decrypt(const unsigned char* encryptMessage_, int encryptLength_, unsigned char* decryptMessage_, int* decryptLength_);
}// namespace Lancelot

#endif// LANCELOT_INCLUDE_LANCELOT_SECURITY_SECURITY_HPP_
