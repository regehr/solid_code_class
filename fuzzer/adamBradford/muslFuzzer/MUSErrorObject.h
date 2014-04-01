//
//  MUSErrorObject.h
//  muslFuzzer
//
//  Created by Adam Bradford on 3/27/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MUSErrorObject : NSObject
@property (nonatomic,strong) NSString *formatString;
@property (nonatomic,strong) NSString *clibOutput;
@property (nonatomic,strong) NSString *muslOutput;
@property (nonatomic,strong) NSString *hexArgument;
@end
