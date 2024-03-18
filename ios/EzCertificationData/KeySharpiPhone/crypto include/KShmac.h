
#ifndef	__KS_HMAC_H__
#define	__KS_HMAC_H__

#include "KSdefine.h"
#include "KSsha.h"

#define	HMAC_HASHID_MD5					1
#define	HMAC_HASHID_SHA					2

#define	HMAC_MAX_DIGEST_LENGTH			20
#define	HMAC_MAX_CBLOCK					64

typedef struct {
	int			hashId;
	KS_BYTE		key[HMAC_MAX_CBLOCK];
	int			keyLength;
	int			macSize;
	union {
        KS_SHA_CTX		sha;
	} ctx;
} HMAC_CTX;


#ifdef  __cplusplus
extern "C" {
#endif

void KS_HMAC_Init		(HMAC_CTX *ctx, int hashId, KS_BYTE *key, int keyLength);
void KS_HMAC_Update		(HMAC_CTX *ctx, KS_BYTE *data, int dataLength);
void KS_HMAC_Final		(HMAC_CTX *ctx, KS_BYTE *md, int *mdLength);
void KS_HMAC			(KS_BYTE *md, int *mdLength, int hashId, KS_BYTE *key, int keyLength, KS_BYTE *data, int dataLength);
void HMAC_SHA		(KS_BYTE *md, KS_BYTE *key, int keyLength, KS_BYTE *data, int dataLength);

#ifdef  __cplusplus
}
#endif

#endif
