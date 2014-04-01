//
//  MUSFuzzer.h
//  muslFuzzer
//
//  Created by Adam Bradford on 3/27/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MUSFuzzerDelegate <NSObject>

-(void)countIncreased100000;

@end
@interface MUSFuzzer : NSObject


@property (weak,nonatomic) id<MUSFuzzerDelegate> delegate;

-(void)startFuzzing;


@end
