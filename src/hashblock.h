#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "andcoinmath.h"

#include "sph_sha2.h"
#include "sph_keccak.h" 
#include "sph_whirlpool.h"
#include "sph_ripemd.h"

#ifndef QT_NO_DEBUG
#include <string>
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_sha256_context     z_sha256;
GLOBAL sph_sha512_context     z_sha512;
GLOBAL sph_keccak512_context  z_keccak;
GLOBAL sph_whirlpool_context  z_whirlpool;

GLOBAL sph_ripemd160_context  z_ripemd;

#define fillz() do { \
    sph_sha512_init(&z_sha512); \
    sph_sha256_init(&z_sha256); \
    sph_keccak512_init(&z_keccak); \
    sph_whirlpool_init(&z_whirlpool); \
    sph_ripemd160_init(&z_ripemd); \
} while (0) 

#define ZSHA256 (memcpy(&ctx_sha256, &z_sha256, sizeof(z_sha256)))
#define ZSHA512 (memcpy(&ctx_sha512, &z_sha512, sizeof(z_sha512)))
#define ZKECCAK (memcpy(&ctx_keccak, &z_keccak, sizeof(z_keccak)))
#define ZWHIRLPOOL (memcpy(&ctx_whirlpool, &z_whirlpool, sizeof(z_whirlpool)))
#define ZRIPEMD (memcpy(&ctx_ripemd, &z_ripemd, sizeof(z_ripemd)))

#define BITS_PER_DIGIT 3.32192809488736234787
#define EPS (std::numeric_limits<double>::epsilon())

#define NA5A 5
#define SW_DIVS 5

template<typename T1>
inline uint256 Hash_A5A(const T1 pbegin, const T1 pend, const unsigned int nnNonce)
{
    sph_sha256_context       ctx_sha256;
    sph_sha512_context       ctx_sha512;
    sph_keccak512_context    ctx_keccak;
    sph_whirlpool_context    ctx_whirlpool;
    sph_ripemd160_context    ctx_ripemd;
    static unsigned char pblank[1];
    int bytes, nnNonce2 = (int)(nnNonce/2);

    uint512 hash[5];
    uint256 finalhash;
    for(int i=0; i < 5; i++)
	hash[i] = 0;

    const void* ptr = (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0]));
    size_t sz = (pend - pbegin) * sizeof(pbegin[0]);

    sph_sha256_init(&ctx_sha256);
    // ZSHA256;
    sph_sha256 (&ctx_sha256, ptr, sz);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&hash[0]));

    sph_sha512_init(&ctx_sha512);
    // ZSHA512;
    sph_sha512 (&ctx_sha512, ptr, sz);
    sph_sha512_close(&ctx_sha512, static_cast<void*>(&hash[1]));
    
    sph_keccak512_init(&ctx_keccak);
    // ZKECCAK;
    sph_keccak512 (&ctx_keccak, ptr, sz);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[2]));

    sph_whirlpool_init(&ctx_whirlpool);
    // ZWHIRLPOOL;
    sph_whirlpool (&ctx_whirlpool, ptr, sz);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[3]));

    sph_ripemd160_init(&ctx_ripemd);
    // ZRIPEMD;
    sph_ripemd160 (&ctx_ripemd, ptr, sz);
    sph_ripemd160_close(&ctx_ripemd, static_cast<void*>(&hash[4]));

//    printf("%s\n", hash[4].GetHex().c_str());

    mpz_t bns[6];
    //Take care of zeros and load gmp
    for(int i=0; i < 5; i++){
	if(hash[i]==0)
	    hash[i] = 1;
	mpz_init(bns[i]);
	mpz_set_uint512(bns[i],hash[i]);
    }

    mpz_init(bns[5]);
    mpz_set_ui(bns[5],0);
    for(int i=0; i < 5; i++)
	mpz_add(bns[5], bns[5], bns[i]);

    mpz_t product;
    mpz_init(product);
    mpz_set_ui(product,1);
//    mpz_pow_ui(bns[5], bns[5], 2);
    for(int i=0; i < 6; i++){
	mpz_mul(product,product,bns[i]);
    }
    mpz_pow_ui(product, product, 2);

    bytes = mpz_sizeinbase(product, 256);
//    printf("A5A data space: %iB\n", bytes);
    char *data = (char*)malloc(bytes);
    mpz_export(data, NULL, -1, 1, 0, 0, product);

    sph_sha256_init(&ctx_sha256);
    // ZSHA256;
    sph_sha256 (&ctx_sha256, data, bytes);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&finalhash));
//   printf("finalhash = %s\n", hash[6].GetHex().c_str());
    free(data);

    int digits=(int)((sqrt((double)(nnNonce2))*(1.+EPS))/9000+75);
//    int iterations=(int)((sqrt((double)(nnNonce2))+EPS)/500+350); // <= 500
//    int digits=100;
    int iterations=20; // <= 500
    mpf_set_default_prec((long int)(digits*BITS_PER_DIGIT+16));

    mpz_t andcoinpi;
    mpz_t andcoinsw;
    mpf_t andcoinfpi;
    mpf_t mpa1, mpb1, mpt1, mpp1;
    mpf_t mpa2, mpb2, mpt2, mpp2;
    mpf_t mpsft;

    mpz_init(andcoinpi);
    mpz_init(andcoinsw);
    mpf_init(andcoinfpi);
    mpf_init(mpsft);
    mpf_init(mpa1);
    mpf_init(mpb1);
    mpf_init(mpt1);
    mpf_init(mpp1);

    mpf_init(mpa2);
    mpf_init(mpb2);
    mpf_init(mpt2);
    mpf_init(mpp2);

    uint32_t usw_;
    usw_ = sw_(nnNonce2, SW_DIVS);
    if (usw_ < 1) usw_ = 1;
//    if(fDebugandcoin) printf("usw_: %d\n", usw_);
    mpz_set_ui(andcoinsw, usw_);
    uint32_t mpzscale=mpz_size(andcoinsw);
for(int i=0; i < NA5A; i++)
{
    if (mpzscale > 1000) {
      mpzscale = 1000;
    }
    else if (mpzscale < 1) {
      mpzscale = 1;
    }
//    if(fDebugandcoin) printf("mpzscale: %d\n", mpzscale);

    mpf_set_ui(mpa1, 1);
    mpf_set_ui(mpb1, 2);
    mpf_set_d(mpt1, 0.25*mpzscale);
    mpf_set_ui(mpp1, 1);
    mpf_sqrt(mpb1, mpb1);
    mpf_ui_div(mpb1, 1, mpb1);
    mpf_set_ui(mpsft, 10);

    for(int i=0; i <= iterations; i++)
    {
	mpf_add(mpa2, mpa1,  mpb1);
	mpf_div_ui(mpa2, mpa2, 2);
	mpf_mul(mpb2, mpa1, mpb1);
	mpf_abs(mpb2, mpb2);
	mpf_sqrt(mpb2, mpb2);
	mpf_sub(mpt2, mpa1, mpa2);
	mpf_abs(mpt2, mpt2);
	mpf_sqrt(mpt2, mpt2);
	mpf_mul(mpt2, mpt2, mpp1);
	mpf_sub(mpt2, mpt1, mpt2);
	mpf_mul_ui(mpp2, mpp1, 2);
	mpf_swap(mpa1, mpa2);
	mpf_swap(mpb1, mpb2);
	mpf_swap(mpt1, mpt2);
	mpf_swap(mpp1, mpp2);
    }
    mpf_add(andcoinfpi, mpa1, mpb1);
    mpf_pow_ui(andcoinfpi, andcoinfpi, 2);
    mpf_div_ui(andcoinfpi, andcoinfpi, 4);
    mpf_abs(mpt1, mpt1);
    mpf_div(andcoinfpi, andcoinfpi, mpt1);

//    mpf_out_str(stdout, 10, digits+2, andcoinfpi);

    mpf_pow_ui(mpsft, mpsft, digits/2);
    mpf_mul(andcoinfpi, andcoinfpi, mpsft);

    mpz_set_f(andcoinpi, andcoinfpi);

//mpz_set_ui(andcoinpi,1);

    mpz_add(product,product,andcoinpi);
    mpz_add(product,product,andcoinsw);
    
    if(finalhash==0) finalhash = 1;
    mpz_set_uint256(bns[0],finalhash);
    mpz_add(bns[5], bns[5], bns[0]);

    mpz_mul(product,product,bns[5]);
    mpz_cdiv_q (product, product, bns[0]);
    if (mpz_sgn(product) <= 0) mpz_set_ui(product,1);

    bytes = mpz_sizeinbase(product, 256);
    mpzscale=bytes;
//    printf("A5A data space: %iB\n", bytes);
    char *bdata = (char*)malloc(bytes);
    mpz_export(bdata, NULL, -1, 1, 0, 0, product);

    sph_sha256_init(&ctx_sha256);
    // ZSHA256;
    sph_sha256 (&ctx_sha256, bdata, bytes);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&finalhash));
    free(bdata);
//    printf("finalhash = %s\n", finalhash.GetHex().c_str());
}
    //Free the memory
    for(int i=0; i < 6; i++){
	mpz_clear(bns[i]);
    }
//    mpz_clear(dSpectralWeight);
    mpz_clear(product);

    mpz_clear(andcoinpi);
    mpz_clear(andcoinsw);
    mpf_clear(andcoinfpi);
    mpf_clear(mpsft);
    mpf_clear(mpa1);
    mpf_clear(mpb1);
    mpf_clear(mpt1);
    mpf_clear(mpp1);

    mpf_clear(mpa2);
    mpf_clear(mpb2);
    mpf_clear(mpt2);
    mpf_clear(mpp2);
    
    return finalhash;
}

#endif // HASHBLOCK_H
