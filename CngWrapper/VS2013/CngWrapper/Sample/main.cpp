

#include <numeric>
#include <iostream>

#include "../CngWrapper/hash.h"
#include "../CngWrapper/asymmetricsignature.h"
#include "../CngWrapper/asymmetricparameters_instances.h"

using namespace CngWrapper;



void detailedSignAndVerify()
{
	std::vector<unsigned char> content, privateKey, publicKey;


	const size_t payloadlength = 1024;
	AsymmetricSignature asyncmmetric(ecdsa256_sha256);
	auto result = asyncmmetric.generate(privateKey, publicKey);
	if (NtStatusHelper::isError(result))
	{
		std::cout << NtStatusHelper::toString(result);
		return;
	}

	content.resize(payloadlength);
	std::iota(begin(content), end(content), 0);

	{
		std::vector<unsigned char> signature;

		{
			AsymmetricSignature asymmetricSignature(ecdsa256_sha256);

			result = asymmetricSignature.importPrivateKey(privateKey);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
				return;
			}

			//Hash data
			Hash hash(ecdsa256_sha256._hashAlgorithmName);
			result = hash.initialize();
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
				return;
			}

			result = hash.update(content);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
				return;
			}

			result = hash.calculate();
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
				return;
			}

			std::vector<unsigned char> hashData = hash.get();


			//Sign hash
			result = asymmetricSignature.signHash(hashData, signature);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
				return;
			}
		}

		{
			AsymmetricSignature asymmetricSignature2(ecdsa256_sha256);

			result = asymmetricSignature2.importPublicKey(publicKey);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
			}


			//Hash data
			Hash hash(ecdsa256_sha256._hashAlgorithmName);
			result = hash.initialize();
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
			}

			result = hash.update(content);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
			}

			result = hash.calculate();
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
			}

			std::vector<unsigned char> hashData = hash.get();

			result = asymmetricSignature2.verifyHash(hashData, signature);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
			}
			else
			{
				std::cout << "Signature matches";
			}
		}
	}
}

void sinpleSignAndVerify()
{
	std::vector<unsigned char> content, privateKey, publicKey;


	const size_t payloadlength = 1024;
	AsymmetricSignature asyncmmetric(ecdsa256_sha256);
	auto result = asyncmmetric.generate(privateKey, publicKey);
	if (NtStatusHelper::isError(result))
	{
		std::cout << NtStatusHelper::toString(result);
		return;
	}

	content.resize(payloadlength);
	std::iota(begin(content), end(content), 0);

	{
		std::vector<unsigned char> signature;

		{
			AsymmetricSignature asymmetricSignature(ecdsa256_sha256);
			result = asymmetricSignature.sign(privateKey, content, signature);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
				return;
			}
		}

		{
			AsymmetricSignature asymmetricSignature2(ecdsa256_sha256);
			result = asymmetricSignature2.verify(publicKey, content, signature);
			if (NtStatusHelper::isError(result))
			{
				std::cout << NtStatusHelper::toString(result);
			}
			else
			{
				std::cout << "Signature verified";
			}
		}
	}
}

void shouldReturnTheSameHash_whenHashCalculatedMultipleTimes()
{
	const int hashObjectLength = 302, hashLength = 32, dataLength = 100;
	const std::wstring algorithmName(BCRYPT_SHA256_ALGORITHM);
	std::vector<unsigned char> content(dataLength);
	std::iota(begin(content), end(content), 1);

	std::vector<unsigned char> expectedHashResult;
	std::vector<unsigned char> multiUpdateHashResult;

	{
		Hash hash(algorithmName);
		auto ret = hash.initialize(hashLength, hashObjectLength);
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		ret = hash.update(content);
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		ret = hash.calculate();
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		expectedHashResult = hash.get();
	}

	auto part(dataLength / 2);
	{
		Hash hash(algorithmName);
		auto ret = hash.initialize(hashLength, hashObjectLength);
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		ret = hash.update(content.data(), part);
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		ret = hash.calculate();
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		ret = hash.update(content.data() + part, part);
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		ret = hash.calculate();
		if (NtStatusHelper::isError(ret))
		{
			std::cout << NtStatusHelper::toString(ret);
			return;
		}

		multiUpdateHashResult = hash.get();
	}

	if(std::equal(begin(multiUpdateHashResult), end(multiUpdateHashResult), begin(expectedHashResult)))
		std::cout << "Hashes are equal";
	else
		std::cout << "Hashes are different (shouldn't happen)";

}

int main()
{
	sinpleSignAndVerify();

	detailedSignAndVerify();

	shouldReturnTheSameHash_whenHashCalculatedMultipleTimes();

	return 0;
}
