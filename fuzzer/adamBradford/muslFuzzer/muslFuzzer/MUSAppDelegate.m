//
//  MUSAppDelegate.m
//  muslFuzzer
//
//  Created by Adam Bradford on 3/27/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#import "MUSAppDelegate.h"
#import "MUSFuzzer.h"
#import "MUSFuzzController.h"


@implementation MUSAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    MUSFuzzController *fuzzer = [MUSFuzzController new];
    [fuzzer beginFuzzing];
    
}

@end
