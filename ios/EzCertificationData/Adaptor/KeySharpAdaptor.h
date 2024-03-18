//
//  KeySharpAdaptor.h
//  EzCertificationData
//
//  Created by Jinho Lee on 2022/10/02.
//

#import <Foundation/Foundation.h>
#import "CertManager.h"
#import "ios_Cert.h"
#import "KSBase64.h"
#import "KSutil.h"

@interface KeySharpAdaptor : NSObject {
    NSString *serviceUrl;
    CertManager *certManager;
    NSInteger certIndex;
    NSString *password;
}

@property (nonatomic, retain) NSString *serviceUrl;
@property (nonatomic, retain) CertManager *certManager;
@property (nonatomic, assign) NSInteger certIndex;
@property (nonatomic, retain) NSString *password;

+ (id)shared;
- (id)init;
- (BOOL)downloadWith:(NSString *)userId error:(NSError **)error;
- (NSString *)signWith:(NSString *)password message:(NSString *)message error:(NSError **)error;
- (void)removeAll;

@end
