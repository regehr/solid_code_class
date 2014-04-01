//
//  MUSFuzzController.m
//  muslFuzzer
//
//  Created by Adam Bradford on 3/28/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#import "MUSFuzzController.h"
#import "MUSFuzzer.h"

@interface MUSFuzzController()<MUSFuzzerDelegate>

@property (nonatomic) long count;
@property (nonatomic, strong) NSOperationQueue *countQueue;
@property (nonatomic, strong) NSOperationQueue *fuzzQueue;

@property (nonatomic, strong) NSMutableArray *fuzzers;
@property (nonatomic, strong) NSMutableArray *fuzzerQueues;
@end
@implementation MUSFuzzController

-(instancetype)init
{
    self = [super init];
    if(self)
    {
        self.countQueue = [NSOperationQueue new];
        self.countQueue.maxConcurrentOperationCount = 1;
        
        self.fuzzQueue = [NSOperationQueue new];
        
        self.fuzzers = [NSMutableArray new];
    }
    return self;
}


-(void)beginFuzzing
{
    int threads=   (int) [NSProcessInfo processInfo].processorCount;
    NSLog(@"Creating %d threads",threads);
    
    self.fuzzQueue.maxConcurrentOperationCount = threads;
    
    for(int i = 0; i < 1; i++)
    {
        NSOperationQueue *queue = [NSOperationQueue new];
        [queue addOperationWithBlock:^{
        
            MUSFuzzer *fuzzer = [[MUSFuzzer alloc]init];
            fuzzer.delegate = self;
            [self.fuzzers addObject:fuzzer];
            [fuzzer startFuzzing];
        }];
        [self.fuzzerQueues addObject:queue];
    }
}

-(void)countIncreased100000
{
    [self.countQueue addOperationWithBlock:^{
        self.count += 100000;
        __gcov_flush();
        NSLog(@"Count: %ld",self.count);
       
       
    }];
    
}

@end
