//
// Created by kingofknights on 7/12/23.
//
#include "Lancelot/Security/Security.hpp"

#include <xcd/libxcd.h>

#include <cstring>

#include "Lancelot/Structure.hpp"

namespace Lancelot {
	CommunicationT Encrypt(std::string_view order_, uint32_t uid_, uint32_t query_) {
		int			  encryptMessageLength;
		unsigned char encryptMessage[ENCRYPT_MESSAGE_MAX_LENGTH];
		xcdCompress(reinterpret_cast<const unsigned char *>(order_.data()), order_.length(), encryptMessage, &encryptMessageLength);
		CommunicationT communication{ ._user = uid_, ._query = query_, ._encryptLength = encryptMessageLength};
		std::memcpy(communication._encryptMessage, encryptMessage, encryptMessageLength);
		return communication;
	}

	int Decrypt(const unsigned char *encryptMessage_, int encryptLength_, unsigned char *decryptMessage_, int *decryptLength_) {
		return xcdDecompress(encryptMessage_, encryptLength_, decryptMessage_, decryptLength_);
	}
}  // namespace Lancelot
