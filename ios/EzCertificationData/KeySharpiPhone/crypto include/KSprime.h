
#ifndef __KS_PRIME_H
#define __KS_PRIME_H

#include "KSbigint.h"
#include "KSdefine.h"
#include "KSrand.h"

/* ============================
 *		Basic Types
 * ============================ */

typedef struct{
	BigInt	*phiInput;
	BigInt	*oddPart;
	BigInt	*challenge;
	BigInt	*testValue;
	BigInt	*temp;
} MillerRabin_CTX;


/* =============================
 *		Function Prototypes
 * ============================= */

#ifdef __cplusplus
extern "C" {
#endif

void		Big_RandomInt		(BigInt	*randomInt, int	byteLength, LfsrContext *pContext );
KS_WORD		Big_ExpoWindow		(BigInt	*result, BigInt	*input, BigInt *exponent, BigInt *mod, BigInt *rSqr, KS_WORD modInv );
KS_BOOL		Big_TrialDivision	(BigInt *input, MillerRabin_CTX *millerRabin, int iteration );
KS_BOOL		Big_MillerRabin		(BigInt *input, BigInt *rSqr, KS_WORD modInv, MillerRabin_CTX *millerRabin, LfsrContext *lfsrContext );
KS_WORD		Big_ProbablePrime	(BigInt *input, BigInt *rSqr, KS_WORD *modInv, int byteLength, MillerRabin_CTX *millerRabin, LfsrContext *pContext, int sieveSize );
KS_WORD		Big_StrongPrime		(BigInt *input, int byteLength, int sieveSize );
int			Big_IsPrime			(BigInt* input);

#ifdef __cplusplus
} // of extern "C"
#endif


#endif
