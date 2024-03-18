//
//  KeyChainManager.h
//  CertmanagerDemo_Koscom
//
//  Created by choi sung hoon on 10. 04. 22.
//  Copyright 2010 lumensoft. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface KSKeyChainManager : NSObject {
    BOOL shareOption;
    NSString* sharingGroup;
    //[2013.06.11] add
    BOOL isSofo;
}

+ (KSKeyChainManager *) sharedInstance;
- (id) initWithSharingGroup:(NSString*)sahringGroup;
- (id) initSofo;
- (id) initSofoWithSharingGroup:(NSString*)sahringGroup;
- (BOOL) saveToKeyChain:(NSData *)cert key:(NSData *)key;
- (NSArray *) loadCertFromKeyChain;
- (NSData *) loadKeyFromKeyChain: (NSData*) cert;
- (BOOL) delKeyChainItem:(NSData*)certData;
- (BOOL) updateKeyItem:(NSData *)cert newKey:(NSData *)newKey;
- (BOOL) isItemSharable;

@end
