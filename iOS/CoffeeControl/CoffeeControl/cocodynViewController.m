//
//  cocodynViewController.m
//  CoffeeControl
//
//  Created by Bob Scaggs on 3/12/14.
//  Copyright (c) 2014 Cocodyn Software. All rights reserved.
//

#import "cocodynViewController.h"

@interface cocodynViewController ()

@end

@implementation cocodynViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self makeRoundRedLEDs];
    self.isHeating = NO;
	// Do any additional setup after loading the view, typically from a nib.
}


- (void)makeRoundRedLEDs
{
    //self.sixOzLed = [[UIView alloc] initWithFrame:CGRectMake(10,20,100,100)];
    
    //self.sixOzLed.alpha = 1.0;
    self.sixOzLed.layer.cornerRadius = 12;
    self.sixOzLed.backgroundColor = [UIColor redColor];
    
    self.eightOzLed.layer.cornerRadius = 12;
    self.eightOzLed.backgroundColor = [UIColor redColor];

    self.tenOzLed.layer.cornerRadius = 12;
    self.tenOzLed.backgroundColor = [UIColor redColor];
    
    self.mainPowerLed.layer.cornerRadius =12;
    self.mainPowerLed.backgroundColor =[UIColor redColor];
    
    
}

-(void)changeLedColor:(UIView *) led

{
    if ([led.backgroundColor isEqual: [UIColor redColor]])
    {
        led.backgroundColor = [UIColor greenColor];
        
    }else if ([led.backgroundColor isEqual: [UIColor greenColor]])
    {
        led.backgroundColor = [UIColor redColor];
    }
}

-(IBAction)sixOzBrewButtonPush:(id)sender

{
    if (self.isOn && !self.isHeating && !self.isBrewing) {
        [self changeLedColor:self.sixOzLed];
        self.isBrewing =YES;

    }
}

-(IBAction)eightOzBrewButtonPush:(id)sender

{
    [self changeLedColor:self.eightOzLed];
}

-(IBAction)tenOzBrewButtonPush:(id)sender

{
    [self changeLedColor:self.tenOzLed];
}

-(IBAction)mainPowerButtonPush:(id)sender

{
    if (!self.isOn) {
        self.isOn = YES;
        [self changeLedColor:self.mainPowerLed];

    }else self.isOn = NO;
}




- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
