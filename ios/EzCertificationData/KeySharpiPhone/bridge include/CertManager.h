//
//  CertManager.h
//

#import <Foundation/Foundation.h>
#import "Certificate.h"
#import "KeyChainManager.h"

@class FMDatabase;
@class KS2SidManager;
@interface CertManager : NSObject {
	NSMutableArray* arrCert;
	int currIndex;
    FMDatabase *dbase;
	KSKeyChainManager* keyChainManager;
    NSData* lastCopiedCert;
}


@property (nonatomic, retain) NSMutableArray* arrCert;
@property (nonatomic, retain) KSKeyChainManager* keyChainManager;
@property (nonatomic, retain) NSData* lastCopiedCert;
#ifndef _MAC
@property (nonatomic, retain) NSData *serverCert;
@property (nonatomic, retain) NSString *sid;
#endif
@property (nonatomic, assign) int lastErrCode;
@property (nonatomic, retain) NSString *lastErrMsg;

+ (NSString *) getLibraryVersion; //라이브러리 버전 정보

//[2013.06.11] add
- (id)initWithSofo;

- (id)initWithSharingGroup:(NSString*)sharingGroup;
- (id)initWithSofoSharingGroup:(NSString*)sharingGroup;
- (int) count; //arrCert에 저장되어 있는 인증서 갯수 반환

//인증서암호변경
- (BOOL) changeCertPassword:(int)idx oldPassword:(NSString *)oldPassword newPassword:(NSString *) newPassword;
//인증서암호확인
- (int) checkCertPassword:(int)idx currentPassword:(NSString *)currentPassword;
//인증서본인확인
- (int) selfUserVerify: (int)idx idv:(NSString *)idv password:(NSString *)password;
//인증서삭제
- (BOOL) delCert:(int)idx;
//인증서복사
- (int) copyCertFromPC1_Pod: (char*)cnum SN:(NSString*)SN firstAddr:(char*)addr1 secondAddr:(char*)addr2 port:(int)port;
- (int) copyCertFromPC2_Pod:(int) sock SN:(NSString*) SN;
//전자서명
- (int) cmsSign:(int)idx password:(NSString*)password signSource:(NSData*)signSource signResult:(char*)signResult;
//증권전산 전자서명 (ver1.1.8 subjectDN 뽑아오도록 변경)
- (int) koscomSign:(int)idx password:(NSString*)password signSource:(NSData*)signSource signResult:(char*)signResult;
//축약서명 (xc241에서 검증)
- (int) simpleSign:(int)idx password:(NSString*)password signSource:(NSData*)signSource signResult:(char*)signResult;
//증권전산 축약서명 (ver1.1.8 추가 - 증권전산에서 검증)
- (int) koscomSimpleSign:(int)idx password:(NSString*)password signSource:(NSData*)signSource signResult:(char*)signResult;
//외부 인증서 저장
- (BOOL) saveCertToKeyChain:(NSData*)certData key:(NSData*)keyData;

//added ver3.0.12
- (BOOL) havingKmCert: (int)idx;
- (NSData*) getKmCert: (int)idx;
- (NSData*) getKmKey: (int)idx;

- (Certificate*)getCert:(int)idx; //저장된 인증서를 Certificate 객체 형태로 반환
- (NSData*) getCertificate: (int)idx; //ver2.0.2 (저장된 인증서를 NSData 객체 형태로 반환)
- (int) getPublicKey:(int)idx publicKey:(char*)publicKey; //ver1.1.5 (공개키 반환 API 추가)
- (int) getCertIdxBySubjectDN:(NSString*) dn; //ver1.1.8 (dn에 해당하는 idx 리턴 API 추가)
- (NSData*) getRandomFromKey: (int)idx password:(NSString *)password; //key파일에서 random 값 추출
- (NSData*) getVidFromCert: (int)idx; //인증서 파일에서 vid 값 추출
- (NSString*) getCertAndKeyXML: (int)idx; //xml형태로 인증서와 키를 추출
- (int) envelopIDN_R:(int)idx password:(NSString*)password idn:(NSString*)idn serverCert:(NSData*)aServerCert result:(char*)result; //주민번호 + Random 값을 envelop(deprecated)
- (int) :(int)idx password:(NSString*)password idn:(NSString*)idn serverCert:(NSData*)aServerCert result:(char*)result; //envelopIDN_R와 동일. XecureWeb 연동용

- (int) getVidHashContents: (int)idx idv:(NSString*)idv password:(NSString*)password result:(char*)result; // vid hash 직전 데이터 만드는 함수

//caName: yessign OR koscom
//testFlag: 0-> real 1-> test
- (Certificate *) issueWithRefNum:(NSString*)refNum authCode:(NSString*)authCode password:(NSString*)password caName:(NSString*)caName testFlag:(NSUInteger)testFlag;
- (int) update:(int)idx password:(NSString *) password caName:(NSString*)caName testFlag:(NSUInteger)testFlag;
- (NSString *)issueGetLastError;

+ (BOOL)isFirstRun; //check first run after installed
+ (NSString *)UDID; //get udid

-(void)reloadFromKeychain;


// 130528 : filtering arrCert with given filter
- (void)filterCertListWithIssuer:(NSArray *)issuers;
- (void)filterCertListWithIssuerCN:(NSArray *)issuers;
- (void)filterCertListWithPolicyOid:(NSArray *)policies;
- (void)filterExpiredCert;

- (int)chainVerify:(NSData *)aCert caCert:(NSData *)aCACert;

// 140630 : enhanced password check
// 매뉴얼 참고
+ (int)checkPasswordValidity:(NSString *)password error:(NSError**)error;
@end

#ifndef _MAC
#ifndef KOSCOM
@interface CertManager (KSW2)
// 130402 : ksbiz2 enc,dec
- (int)encrypt:(NSString *)plain encrypted:(char *)cipher;
- (int)encrypt:(char *)plain length:(int)plainLen encrypted:(char *)cipher;
- (int)decrypt:(NSString *)cipher plain:(char *)plain;
- (int)decrypt:(char *)cipher length:(int)cipherLen plain:(char *)plain;
// 130521 : generate sid by client-self
//aValue=null | aValue.length=0, get random data
//else gen hash
- (NSString *)generateSID:(NSString *)aValue;
- (void) keymanagerDeleteDataAll;
@end
#endif
#endif