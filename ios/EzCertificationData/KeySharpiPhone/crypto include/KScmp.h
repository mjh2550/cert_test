
#ifndef __KS_CMP_H__
#define __KS_CMP_H__

/* CA Name */
#define CMP_CA_XECURE                   100
#define CMP_CA_YESSIGN                  200
#define CMP_CA_SIGNKOREA                300
//#define CMP_CA_SIGNKOREA_WITH_KMCERT    310

/* added by kiyoung 20060207 to support signgate */
#define CMP_CA_SIGNGATE				400
//



#define TIMEOUT						300

/* Option Flag */
#define SETOPT_KEYSIZE_BIT			0xA1
#define SETOPT_MSGDUMP				0xA2

/* Error Code */

#define CMPERR								4000    // 130714 1000->4000
#define _ERR_CMP_INVALID_TYPE				-(CMPERR+1)
#define _ERR_CMP_ERRBUF_OVERFLOW			-(CMPERR+2)
#define _ERR_CMP_INVALID_TAG				-(CMPERR+3)
#define _ERR_CMP_INVALID_LENGTH				-(CMPERR+4)
#define _ERR_CMP_SIGN_FAILED				-(CMPERR+5)
#define _ERR_CMP_CLNTNONCE_MISMATCH			-(CMPERR+6)
#define _ERR_CMP_SRVRNONCE_MISMATCH			-(CMPERR+7)
#define _ERR_CMP_INVALID_CONTEXT			-(CMPERR+8)
#define _ERR_CMP_INVALID_CERTMEM			-(CMPERR+9)
#define _ERR_CMP_INVALID_CERTREQID			-(CMPERR+10)
#define _ERR_CMP_MSG_NOT_SUPPORTED			-(CMPERR+11)
#define _ERR_CMP_INVALID_STATUS				-(CMPERR+13)
#define _ERR_CMP_CONNECT_FAIL				-(CMPERR+14)
#define _ERR_CMP_SEND_FAIL					-(CMPERR+15)
#define _ERR_CMP_RECV_FAIL					-(CMPERR+16)
#define	_ERR_CMP_KEYGENERATE_FAIL			-(CMPERR+17)
#define	_ERR_CMP_PUBKEYENCODE_FAIL			-(CMPERR+18)
#define	_ERR_CMP_PUBKEYDECODE_FAIL			-(CMPERR+19)
#define	_ERR_CMP_PRIKEYENCODE_FAIL			-(CMPERR+20)
#define	_ERR_CMP_EME_ENCRYPT_FAIL			-(CMPERR+21)
#define	_ERR_CMP_TBSCERTDECODE_FAIL			-(CMPERR+22)
#define	_ERR_CMP_USERCERTOPEN_FAIL			-(CMPERR+23)
#define _ERR_CMP_CACERTOPEN_FAIL			-(CMPERR+24)
#define _ERR_CMP_PRIKEYDECODE_FAIL			-(CMPERR+25)
#define _ERR_CMP_SIGN_FAIL					-(CMPERR+26)
#define _ERR_CMP_DESCBC_FAIL				-(CMPERR+27)
#define _ERR_CMP_INVALID_OPTMSG				-(CMPERR+28)
#define _ERR_CMP_INVALID_OPTVAL				-(CMPERR+29)
#define _ERR_CMP_BLOCKENCRYPT_FAIL			-(CMPERR+30)
#define _ERR_CMP_BLOCKDECRYPT_FAIL			-(CMPERR+31)
#define _ERR_CMP_CIPHERINIT_FAIL			-(CMPERR+32)
#define _ERR_CMP_CIPHERUPDATE_FAIL			-(CMPERR+33)
#define _ERR_CMP_CIPHERFINAL_FAIL			-(CMPERR+34)

#define	_ERR_CMP_PKIERROR					-(CMPERR+100)

#ifdef  __cplusplus
extern "C" {
#endif

/* 인증서 발급 */
int 
CMP_Certificate(unsigned char *usrcert,	 int *usrcert_len,	/* out : 발급받을 인증서 */
				unsigned char *prikey,	 int *prikey_len,	/* out : 발급받을 비밀키 (암호화 안됨) */
				unsigned char *usrkmcert,	 int *usrkmcert_len,	/* out : 발급받을 KM 인증서 */
				unsigned char *kmprikey,	 int *kmprikey_len,	/* out : 발급받을 KM 비밀키 (암호화 안됨) */
				unsigned char *cacert,	 int *cacert_len,	/* out : 발급자 인증서 */
				unsigned char *rootcert, int *rootcert_len,	/* out : 루트 인증서 */
				char *passwd,								/* in  : 비밀키를 암호화할 패스워드 */
				int ca_name,								/* in  : CA 이름 : CMP_CA_XECURE 또는 CMP_CA_YESSIGN */
				char *ca_ip, int ca_port,					/* in  : CA 주소 */
				char *ref_num,								/* in  : 참조번호 */
				char *auth_code								/* in  : 인가코드 */
				);

int
CMP_Recovery(unsigned char *usrcert,	 int *usrcert_len,
				unsigned char *prikey,	 int *prikey_len,
				unsigned char *usrkmcert,	 int *usrkmcert_len,
				unsigned char *kmprikey,	 int *kmprikey_len,
				unsigned char *cacert,	 int *cacert_len,
				unsigned char *rootcert, int *rootcert_len,
				char *passwd,
				int ca_name,
				char *ip, int port, 
				char *ref_num,
				char *auth_code);

/* 인증서 갱신 */
int
CMP_Update(		unsigned char *usrcert,	 int *usrcert_len,	/* out : 발급받을 인증서 */
				unsigned char *prikey,	 int *prikey_len,	/* out : 발급받을 비밀키 (암호화 안됨) */
				unsigned char *cacert,	 int *cacert_len,	/* out : 발급자 인증서 */
				unsigned char *rootcert, int *rootcert_len,	/* out : 루트 인증서 */
				unsigned char *oldcert,	 int oldcert_len,	/* in  : 예전 인증서 */
				unsigned char *oldkey,	 int oldkey_len,	/* in  : 예전 비밀키 */
                unsigned char *kmCert,	 int *kmCertLen,
                unsigned char *kmPri,	 int *kmPriLen,
				char *passwd,								/* in  : 비밀키를 암호화할 패스워드 */
				int ca_name,								/* in  : CA 이름 : CMP_CA_XECURE 또는 CMP_CA_YESSIGN */
				char *ip, int port							/* in  : CA 주소 */		
				);

/* 인증서 폐기 */
int
CMP_Revocation(int ca_name,									/* CA 이름 : CMP_CA_XECURE 또는 CMP_CA_YESSIGN */
			   char *ca_ip, int ca_port,					/* CA 주소 */
			   unsigned char *usrcert,	 int usrcert_len,	/* 폐기될 인증서 */ 
			   unsigned char *prikey,	 int prikey_len,	/* 폐기될 비밀키 */ 
			   unsigned char *certadd,	 int certadd_len,	/* CA 인증서 또는 키관리 인증서*/ 
			   char *passwd
			   );

/* 서버에서 보낸 에러메시지 */
char *CMP_GetError(void);

/* 옵션 설정 및 조회 */	
int CMP_Option(int opt_flag, int opt_val, char *opt_msg);

#ifdef  __cplusplus
}
#endif

#endif
