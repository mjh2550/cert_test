//
//  KSFileUtil.h
//  CertmanagerLib
//
//  Created by choi sung hoon on 10. 02. 18.
//  Copyright 2010 lumensoft. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface KSFileUtil : NSObject {

}

+ (void)fileWriteToDocumentWithName: (NSString*)fileName contents:(char*)contents length:(int)length;
+ (BOOL)accessToSpecificDirectory: (NSString*)filePath;
+ (int) checkJailBreak;

@end
