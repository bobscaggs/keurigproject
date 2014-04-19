//
//  cocodynViewController.h
//  CoffeeControl
//
//  Created by Bob Scaggs on 3/12/14.
//  Copyright (c) 2014 Cocodyn Software. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface cocodynViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIView *sixOzLed;
@property (weak, nonatomic) IBOutlet UIView *eightOzLed;
@property (weak, nonatomic) IBOutlet UIView *tenOzLed;
@property (weak, nonatomic) IBOutlet UIButton *powerButton;
@property (weak, nonatomic) IBOutlet UIButton *sixOzBrewButton;
@property (weak, nonatomic) IBOutlet UIButton *eightOzBrewButton;
@property (weak, nonatomic) IBOutlet UIButton *tenOzBrewButton;
@property (weak, nonatomic) IBOutlet UIView *mainPowerLed;
@property BOOL isHeating;
@property BOOL isOn;
@property BOOL isBrewing;

@end
