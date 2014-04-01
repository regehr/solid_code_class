//
//  MUSFuzzer.m
//  muslFuzzer
//
//  Created by Adam Bradford on 3/27/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#import "MUSFuzzer.h"
#import "musl.h"
#import "MUSErrorObject.h"

#define LEN 10000

@interface MUSFuzzer()

@property (nonatomic) long totalCount;
@property (nonatomic, strong)NSOperationQueue *countQueue;

@property (nonatomic, strong)NSNumberFormatter   *formatter;
@property (nonatomic, strong)NSArray * intSpecifiers;
@property (nonatomic, strong)NSArray * floatSpecifiers;


@end

@implementation MUSFuzzer

-(instancetype)init
{
    self = [super init];
    if(self)
    {
        self.countQueue = [[NSOperationQueue alloc]init];
              
        self.countQueue.maxConcurrentOperationCount = 1;
        self.formatter = [[NSNumberFormatter alloc]init];
        
        self.formatter.numberStyle = NSNumberFormatterDecimalStyle;
        
        self.intSpecifiers = @[@"d",@"o",@"x",@"X",@"ld",@"u",@"lu",@"c",@"C",@"p",@"i",@"u",@"h",@"hu",@"n"];
        self.floatSpecifiers = @[@"f",@"g",@"e",@"lf",@"lg",@"le",@"a"];
    }
    return self;
}

-(void)incrementCountBy10000
{
    [_countQueue addOperationWithBlock:^{
        _totalCount+= 10000;
        
        if(_totalCount %100000 == 0)
        {
            _totalCount =0;
            [_delegate countIncreased100000];
           
        }
    }];
}



-(void)startFuzzing
{
    char *muslBuf = calloc(1, LEN);
    char *clibBuf = calloc(1, LEN);
    
    
    
    int count = 0;
    while (YES)
    {
        [self randomTestWith1ArgWithmusBuf:muslBuf clibBuf:clibBuf];
        count++;
        if(count > 10000)
        {
            [self incrementCountBy10000];
            count = 1;
        }
    }
    
    free(muslBuf);
    free(clibBuf);
    
}


-(MUSErrorObject *)randomTestWith1ArgWithmusBuf:(char *)muslBuf clibBuf:(char *)clibBuf
{
    int testType = arc4random_uniform(3);
    MUSErrorObject *error = nil;
 
    
    @autoreleasepool {
    
    //test int types
    if(testType == 0)
    {
        long arg = [self random64Bits];
    
        int formatIndex = arc4random_uniform((int)self.intSpecifiers.count);
        
        NSString *formatNS = self.intSpecifiers[formatIndex];
        if(arc4random_uniform(2)==0)formatNS = [NSString stringWithFormat:@"*"];
        NSString *savedPrefix = formatNS;
        NSString *prefix = [self randomFormatPrefix];
        formatNS = [NSString stringWithFormat:@"%@%@",prefix,formatNS];
        
        
        
        const char * format = [formatNS cStringUsingEncoding:NSUTF8StringEncoding];
        
        
        int muslReturn = -1;
        int clibReturn = -1;
        
        //test %n
        if([savedPrefix isEqualToString:@"n"])
        {
            int blah = 0;
            muslReturn = musl_snprintf (muslBuf, LEN, format,&blah);
            clibReturn = sprintf(clibBuf,format,&blah);
        }
        else if([savedPrefix characterAtIndex:0] == '*')
        {
            int offset = arc4random_uniform(4);
            muslReturn = musl_snprintf (muslBuf, LEN, format,offset,arg);
            clibReturn = sprintf(clibBuf,format,offset,arg);
        }
        else
        {
            muslReturn = musl_snprintf (muslBuf, LEN, format,arg);
            clibReturn = sprintf(clibBuf,format,arg);
        }
        
        if(muslReturn == clibReturn && muslReturn < 0) return nil;
        
        if(muslReturn != clibReturn || memcmp(muslBuf, clibBuf, LEN) != 0)
        {
            if(strlen(muslBuf)>0 || strlen(clibBuf)> 0)
            {

                NSString *muslString = [NSString stringWithUTF8String:muslBuf];
                NSString *clibString = [NSString stringWithUTF8String:clibBuf];
                
                if(muslString && clibString)
                {
                //clean up extra 0's, and test if strings are equal;
                while([muslString rangeOfString:@"0x0"].location != NSNotFound)
                    muslString = [muslString stringByReplacingOccurrencesOfString:@"0x0" withString:@"0x"];
                
                if(![muslString isEqualToString:clibString])
                     NSLog(@"Musl:%s : clib:%s : format:%s ",muslBuf,clibBuf,format);
                }
            }
            
        }
        
    }
    //float
    else if(testType == 1)
    {
        long bits = [self random64Bits];
        double arg = *(double *)&bits;
        
        int formatIndex = arc4random_uniform((int)self.floatSpecifiers.count);
        
        NSString *formatNS = self.floatSpecifiers[formatIndex];
        NSString *prefix = [self randomFormatPrefix];
        formatNS = [NSString stringWithFormat:@"%@%@",prefix,formatNS];

        
        if(arc4random_uniform(100000) == 1)arg = INFINITY;
        if(arc4random_uniform(100000) == 1)arg = arg/0;
        const char * format = [formatNS cStringUsingEncoding:NSUTF8StringEncoding];
        
        int muslReturn = musl_snprintf (muslBuf, LEN, format,arg);
        int clibReturn = sprintf(clibBuf,format,arg);
        
        if(muslReturn == clibReturn && muslReturn < 0) return nil;
        
        if(muslReturn != clibReturn || memcmp(muslBuf, clibBuf, LEN) != 0)
        {
            if(strlen(muslBuf)>0 || strlen(clibBuf)> 0)
            {
                
                NSString *muslString = [NSString stringWithUTF8String:muslBuf];
                NSString *clibString = [NSString stringWithUTF8String:clibBuf];
                
                if(muslString && clibString)
                {
                    //clean up extra 0's, and test if strings are equal;
                    while([muslString rangeOfString:@"0x0"].location != NSNotFound)
                        muslString = [muslString stringByReplacingOccurrencesOfString:@"0x0" withString:@"0x"];
                    
                    if(![muslString isEqualToString:clibString])
                        NSLog(@"Musl:%s : clib:%s : format:%s ",muslBuf,clibBuf,format);
                }
            }
            
        }
    }
    //string
    else
    {
        char * arg = [self randomStringWithLength:500];
        
      
        NSString *randomPrefix = [self randomFormatPrefix];
        NSString *formatS = @"s";
        if(arc4random_uniform(2)==0)formatS = @"S";
        NSString *formatNS = [NSString stringWithFormat:@"%@%@",randomPrefix,formatS];
        const char *format = [formatNS cStringUsingEncoding:NSUTF8StringEncoding];
        
        int muslReturn = musl_snprintf (muslBuf, LEN, format,arg);
        int clibReturn = sprintf(clibBuf,format,arg);
        
        free(arg);
     
        if(muslReturn == clibReturn && muslReturn < 0) return nil;
        
        if(muslReturn != clibReturn || memcmp(muslBuf, clibBuf, muslReturn) == 0)
        {
            if(strlen(muslBuf)>0 || strlen(clibBuf)> 0)
            {
                
                NSString *muslString = [NSString stringWithUTF8String:muslBuf];
                NSString *clibString = [NSString stringWithUTF8String:clibBuf];
                
                if(muslString && clibString)
                {
                    //clean up extra 0's, and test if strings are equal;
                    while([muslString rangeOfString:@"0x0"].location != NSNotFound)
                        muslString = [muslString stringByReplacingOccurrencesOfString:@"0x0" withString:@"0x"];
                    
                    if(![muslString isEqualToString:clibString])
                        NSLog(@"Musl:%s : clib:%s : format:%s ",muslBuf,clibBuf,format);
                }
            }
        }
    }
    
    }
    
    return error;
}
-(NSString *)randomFormatPrefix
{
    NSString *decimal = @"";
    NSString *number1 = @"";
    NSString *number2 = @"";
    NSString *minus = @"";
    
    if(arc4random_uniform(2)== 0)decimal = @".";
    if(arc4random_uniform(2)==0)number1 = [NSString stringWithFormat:@"%d",arc4random_uniform(4)];
    if(arc4random_uniform(2)==0)number2 = [NSString stringWithFormat:@"%d",arc4random_uniform(4)];
    if(arc4random_uniform(2)==0)minus = @"-";
    
    
    NSString *formatNS = [NSString stringWithFormat:@"%%%@%@%@%@",minus,number1,decimal,number2];
    return formatNS;
}


//you need to free this...
-(char *)randomStringWithLength:(int)length
{
    char *output = malloc(length + 1);
    for(int i = 0; i < length;i++)
    {
        output[i] = [self randomByte];
    }
    output[length] = (char)0;
    return output;
    
}

-(unsigned long long)random64Bits
{
   unsigned long long result = random();
    return result;
}

-(char)randomByte
{
    char randomByte = (arc4random_uniform(255)+1);
    assert(randomByte != (char)0);
    return randomByte;
    
}


@end
