#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

  struct rsa_32_public_key {
    uint64_t modulus;
    uint64_t public_key_exponent;
  };

  struct rsa_32_private_key {
    int version;
    uint64_t modulus;
    uint64_t public_key_exponent;
    uint64_t private_key_exponent;
    uint64_t prime_p;
    uint64_t prime_q;
  };

  int cryptics_rsa_32_generate_keys(struct rsa_32_public_key *, struct rsa_32_private_key *);

#endif // RSA_H_INCLUDED
