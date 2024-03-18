//
//  KeySharpAdaptor.m
//  EzCertificationData
//
//  Created by Jinho Lee on 2022/10/02.
//

#import "KeySharpAdaptor.h"

@implementation KeySharpAdaptor

@synthesize serviceUrl, certManager, certIndex, password;

+ (id)shared {
    static KeySharpAdaptor *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[KeySharpAdaptor alloc] init];
    });
    return instance;
}

- (id)init {
    if (self = [super init]) {
        certManager = [[CertManager alloc] init];
        certIndex = -1;
    }
    return self;
}

- (BOOL)downloadWith:(NSString *)userId error:(NSError **)error {
    if ([serviceUrl isEqualToString:@""]) {
        *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:1001
                                 userInfo:@{ NSLocalizedDescriptionKey:@"Service URL is empty." }];
        return FALSE;
    }

    // 인증서 정보 다운로드
    NSString *urlString = [NSString stringWithFormat:@"%@/GetCertificateForIOS?id=", serviceUrl];
    
    ios_Cert *cert = [[ios_Cert alloc] init];
    CertInformation *certInformation = [cert ParseData:urlString:userId];

    // 인증서 정보 가져오기
    NSString *dnString = [certInformation getCertDN]; // 사용자 인증서 DN
    NSData *certData = [certInformation getCertDer]; // 바이너리 타입의 인증서 데이터
    NSData *keyData = [certInformation getCertKey]; // 바이너리 타입의 개인키 데이터

    if ([dnString isEqualToString:@""] || certData == NULL || keyData == NULL) {
        NSString *errorMessage = [[cert GetErrorMessage] isEqualToString:@""]
            ? @"Failed to download certification."
            : [cert GetErrorMessage];
        NSLog(@"KMI getCert fail: [%@]", errorMessage);
        *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:1002
                                 userInfo:@{ NSLocalizedDescriptionKey:errorMessage }];
        return FALSE;
    }

    NSLog(@"KMI getCert success!");
    NSLog(@"KMI dn: [%@]", dnString);
    NSLog(@"KMI certData length: [%lu]", (unsigned long)certData.length);
    NSLog(@"KMI keyData length: [%lu]", (unsigned long)keyData.length);

    if (dnString.length == 0 || certData.length == 0 || keyData.length == 0) {
        *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:1003
                                 userInfo:@{ NSLocalizedDescriptionKey:@"Failed to download certification." }];
        return FALSE;
    }

    BOOL result = [[self certManager] saveCertToKeyChain:certData key:keyData];
    
    if (!result) {
        *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:1004
                                 userInfo:@{ NSLocalizedDescriptionKey:@"Failed to download certification." }];
        return FALSE;
    }
    
    self.certIndex = [[self certManager] getCertIdxBySubjectDN:dnString];
    return TRUE;
}

- (NSString *)signWith:(NSString *)password message:(NSString *)message error:(NSError **)error {
    char signResult[40960] = {0x00, };
    NSData *signSourceData = [message dataUsingEncoding:NSUTF8StringEncoding];
    
    int ret = [certManager koscomSign:(int)certIndex
                             password:password
                           signSource:signSourceData
                           signResult:signResult];
    
    if (ret > 0) {
        ks_uint8 *encodedSign = (ks_uint8 *)malloc(ret*2+1);
        memset(encodedSign, 0x00, ret*2+1);
        KSH_Msg_Encoding(encodedSign, (ks_uint8 *)signResult, ret, KSH_ENCODING_BASE64);
        NSString *encodedSignString = [NSString stringWithUTF8String:(char *)encodedSign];
        free(encodedSign);
        NSLog(@"encodedSign : %@", encodedSignString);
        
        // 서명검증
        NSString *result = @"";
        NSString *urlString = [NSString stringWithFormat:@"%@/VerifySignDataForIOS?signValue=", serviceUrl];
        ios_Cert *cert = [[ios_Cert alloc] init];
        result = [cert VerifySignData:urlString:encodedSignString];
        
        if (![result isEqualToString:@"OK"]) {
            // 전자서명 검증에 실패하였습니다.
            *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:ret
                                     userInfo:@{ NSLocalizedDescriptionKey:@"Failed to verify." }];
            return nil;
        }

        // SaveSignData 메서드는 BESTCare 1.0 에서만 사용
        // result = [cert SaveSignData:@"http://172.16.40.190/EMR/WEBSERVICE/JJNUHCertService/JJNUHCertService.asmx/SaveSignDataForIOS":@"88888888":@"77777777":encodedSignString];
        
        return encodedSignString;
    } else if (ret == KS_INVALID_PASSWORD) {
        // 인증서 암호가 일치하지 않습니다.(%d)
        NSString *failMessage = [NSString stringWithFormat:@"Certification password is not matched.(%d)", ret];
        *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:ret
                                 userInfo:@{ NSLocalizedDescriptionKey:failMessage }];
        return nil;
    } else {
        // 전자서명이 실패하였습니다.(%d)
        NSString *failMessage = [NSString stringWithFormat:@"Failed to certificate.(%d)", ret];
        *error = [NSError errorWithDomain:@"KeySharpAdaptor" code:ret
                                 userInfo:@{ NSLocalizedDescriptionKey:failMessage }];
        return nil;
    }
}

- (void)removeAll {
    password = nil;
    certIndex = -1;
    
    int count = [self.certManager count];
    for (int index = count - 1; index >= 0; index--) {
        [self.certManager delCert:index];
    }
}

@end
