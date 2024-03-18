//
//  ios_Cert.h
//  ios_Cert
//
//  Created by MOON SEONG WOOK on 13. 4. 17..
//  Copyright (c) 2013년 MOON SEONG WOOK. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CertInformation : NSObject
{
    @public
    NSString * cert_dn;
    NSData * cert_der;
    NSData * cert_key;
}

-(void) setCertDN : (NSString *)userDn;
-(NSString *) getCertDN;

-(void) setCertDer : (NSData *)der;
-(NSData *) getCertDer;

-(void) setCertKey : (NSData *)key;
-(NSData *) getCertKey;

@end

@interface resultsigndata : NSObject
{
@public
    NSString * result;
}

-(void) setResult : (NSString *)resultdata;
-(NSString *) getResult;
@end


@interface NSString (NSString_URLEncoding)

- (NSString *)urlEncodeUsingEncoding:(CFStringEncoding)encoding;
- (NSString *)urlEncode;

@end

//  NSString+URLEncoding.m
@implementation NSString (NSString_URLEncoding)

- (NSString *)urlEncodeUsingEncoding:(CFStringEncoding)encoding {
    
    return CFBridgingRelease(CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,
                                                                     (__bridge CFStringRef)self,
                                                                     NULL,
                                                                     CFSTR("!*'();:@&=+$,/?%#[]"),
                                                                     encoding));
}

- (NSString *)urlEncode {
    
    return [self urlEncodeUsingEncoding:kCFStringEncodingUTF8];
}
@end


@interface ios_Cert : NSObject
{
    @public
    CertInformation * certInfo;
    NSData * derData;
    NSData * keyData;
    NSDictionary * xmlData;
}

-(NSString *)VerifySignData : (NSString *) url : (NSString *) input;

-(NSString *) VerifySignDataForLogin : (NSString *) url : (NSString *) input : (NSString *) input2;

-(NSString *) GetServerTime : (NSString *) url;

-(NSString *) SaveSignData : (NSString *) url : (NSString *) wkpers : (NSString *) pt_no : (NSString *) signdata;

-(CertInformation *) ParseData : (NSString *) url : (NSString *) input;

-(NSString *) GetErrorMessage;

@end
