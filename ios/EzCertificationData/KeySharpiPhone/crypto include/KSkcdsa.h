//
//	ks_kcdsa.h
//

#ifndef _KS_KDSA_H_
#define _KS_KDSA_H_

#include "KSbigint.h"


#define KS_KCDSA_HASHID_SHA1		100   //KS_HASH_SHA1
#define KS_KCDSA_HASHID_SHA256	    200   //KS_HASH_SHA256

/**
 *	Struct
 */

typedef struct {
	BigInt		*p;			// prime modulus p = 2jq+1
	BigInt		*q;			// prime divisor of p-1
	BigInt		*g;			// base (generator)
	
	BigInt		*j;			// subgroup factor (optional)
	struct {
		KS_BYTE		*seed;		// 160/8 ~ 256/8 bytes
		KS_WORD		seedLength;
		BigInt	*counter;
	} validation;				// (optional)
} KS_KCDSA_Parameters;

typedef struct {
	KS_BYTE		r[32];
	KS_WORD		rLength;
	BigInt		*s;
} KS_KCDSA_Signature;



/**
 *	Prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

KS_KCDSA_Parameters *
			KS_KCDSA_Parameters_New			(void);

void		KS_KCDSA_Parameters_Free		(KS_KCDSA_Parameters *params);

KS_KCDSA_Signature *
			KS_KCDSA_Signature_New			(void);

void		KS_KCDSA_Signature_Free			(KS_KCDSA_Signature *signature);

int	KS_KCDSA_GenerateParameters		(KS_KCDSA_Parameters *params, 
											  KS_WORD primeByteLength);

int	KS_KCDSA_VerifyParameters		( KS_KCDSA_Parameters *params, KS_WORD hashID);


int	KS_KCDSA_GenerateKey			(BigInt *privKey, 
											 BigInt *pubKey,
											  KS_KCDSA_Parameters *params);

int	KS_KCDSA_VerifyPublicKey		( BigInt *pubKey,
											  KS_KCDSA_Parameters *params);

int	KS_KCDSA_ProveKeyPair			( BigInt *privKey, 
											  BigInt *pubKey,
											  KS_KCDSA_Parameters *params);

int	KS_KCDSA_Hash					(KS_BYTE *hash, 
											 KS_WORD *hashLength,
											  KS_BYTE *message,
											  KS_WORD messageLength,
											  int hashID,
											  BigInt *pubKey);

int	KS_KCDSA_Sign					(KS_KCDSA_Signature *signature, 
											  int hashID,
											  KS_BYTE *hash, 
											  KS_WORD hashLength,
											  KS_KCDSA_Parameters *params, 
											  BigInt *privKey);

int	KS_KCDSA_Verify					( KS_KCDSA_Signature *signature, 
											  int hashID,
											  KS_BYTE *hash, 
											  KS_WORD hashLength,
											  KS_KCDSA_Parameters *params, 
											  BigInt *pubKey);

// asn.1

int	KS_KCDSA_Parameters_Encode		(KS_BYTE *output, 
											 KS_WORD *outputLength,
											  KS_KCDSA_Parameters *params);

int	KS_KCDSA_Parameters_Decode		(KS_KCDSA_Parameters *params,
											  KS_BYTE *input, 
											  KS_WORD inputLength);

int	KS_KCDSA_Signature_Encode		(KS_BYTE *output, 
											 KS_WORD *outputLength,
											  KS_KCDSA_Signature *signature);

int	KS_KCDSA_Signature_Decode		(KS_KCDSA_Signature *signature,
											  KS_BYTE *input, 
											  KS_WORD inputLength);

int	KS_KCDSA_PublicKey_Encode		(KS_BYTE *output, 
											 KS_WORD *outputLength,
											  BigInt *pubKey);

int	KS_KCDSA_PublicKey_Decode		(BigInt *pubKey,
											  KS_BYTE *input, 
											  KS_WORD inputLength);

#ifdef __cplusplus
}
#endif

#endif
