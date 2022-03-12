#include "TCPClient.h"
#include "iostream"
#include <chrono>
#include <thread>
constexpr int BufferSize = 1024;


void Client::GetEncryptionKey()
{
	ByteArray EncryptionKey = Client::ReceiveRawBytes();

	Client::EncryptionKey = EncryptionKey;
}
ByteArray Client::EKey()
{


	return Client::EncryptionKey;
}
void Client::SendRawBytes(ByteArray& Bytes)
{

	int32_t Result = send(Client::Socket, (char*)Bytes.data(), (int)Bytes.size(), 0);

}
ByteArray Client::ReceiveRawBytes()
{
	ByteArray	ReceivedBytes;
	uint8_t		RecvBuffer[BufferSize];

	while (true)
	{
		int32_t Received = recv(Client::Socket, (char*)RecvBuffer, BufferSize, 0);

		if (Received < 0)
			break;

		for (int n = 0; n < Received; ++n)
		{
			ReceivedBytes.push_back(RecvBuffer[n]);
		}

		if (Received < BufferSize)
			break;

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return ReceivedBytes;
}
void Client::SendBytes(ByteArray& Bytes)
{
	ByteArray Encrypted = Encryption.Encrypt(Bytes, Client::EKey());

	SendRawBytes(Encrypted);
}

ByteArray Client::ReceiveBytes()
{
	ByteArray ReceivedBytes = ReceiveRawBytes();
	ByteArray Decrypted = Encryption.Decrypt(ReceivedBytes, Client::EKey());

	return Decrypted;
}
void Client::SendText(std::string Text)
{
	std::string Send = Text;
	ByteArray plaintext(Send.begin(), Send.end());
	Client::SendBytes(plaintext);

}

std::string Client::ReceiveText()
{
	ByteArray rray = Client::ReceiveBytes();

	std::string str(rray.begin(), rray.end());

	return str;
}
