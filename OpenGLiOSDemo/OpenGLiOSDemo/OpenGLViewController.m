//
//  OpenGLViewController.m
//  OpenGLiOSDemo
//
//  Created by 刘科 on 2022/5/10.
//

#import "OpenGLViewController.h"
#import "BaseOpenGLView.h"

@interface OpenGLViewController ()

@end

@implementation OpenGLViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    // Do any additional setup after loading the view.
    BaseOpenGLView *glview = [[BaseOpenGLView alloc]initWithFrame:self.view.bounds];
    [self.view addSubview:glview];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
