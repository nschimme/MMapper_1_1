#ifndef CRYPTOPP_SHARK_H
#define CRYPTOPP_SHARK_H

/** \file
*/

#include "config.h"

#ifdef WORD64_AVAILABLE

#include "seckey.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

struct SHARK_Info : public FixedBlockSize<8>, public VariableKeyLength<16, 1, 16>, public VariableRounds<6, 2>
{
	static const char *StaticAlgorithmName() {return "SHARK-E";}
};

/// <a href="http://www.weidai.com/scan-mirror/cs.html#SHARK-E">SHARK-E</a>
class SHARK : public SHARK_Info, public BlockCipherDocumentation
{
	class Base : public BlockCipherBaseTemplate<SHARK_Info>
	{
	public:
		void UncheckedSetKey(CipherDir dir, const byte *key, unsigned int length, unsigned int rounds);

	protected:
		unsigned int m_rounds;
		SecBlock<word64> m_roundKeys;
	};

	class Enc : public Base
	{
	public:
		void ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const;

		// used by Base to do key setup
		void InitForKeySetup();

	private:
		static const byte sbox[256];
		static const word64 cbox[8][256];
	};

	class Dec : public Base
	{
	public:
		void ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const;

	private:
		static const byte sbox[256];
		static const word64 cbox[8][256];
	};

public:
	typedef BlockCipherTemplate<ENCRYPTION, Enc> Encryption;
	typedef BlockCipherTemplate<DECRYPTION, Dec> Decryption;
};

typedef SHARK::Encryption SHARKEncryption;
typedef SHARK::Decryption SHARKDecryption;

NAMESPACE_END

#endif
#endif
