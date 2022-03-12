#include "client.h"

Client::Client(std::string id, const Server& server):id(id), server(&server)
{
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id()
{
    return id;
}

double Client::get_wallet() const
{
    return server->get_wallet(id);
}

std::string Client::get_publickey() const
{
    return public_key;
}

std::string Client::sign(std::string txt) const
{
    std::string signature = crypto::signMessage(private_key, txt);
    bool authentic = crypto::verifySignature(public_key, txt, signature);
    return signature;
}

bool Client::transfer_money(std::string receiver, double value)
{
    std::string trx{id + '-' + receiver + '-' + std::to_string(value)};
    std::string signature{sign(trx)};
    bool valid {server->add_pending_trx(trx, signature)};
    return valid;
}