//
//  ViewController.m
//  OpenGLiOSDemo
//
//  Created by 刘科 on 2022/5/10.
//

#import "ViewController.h"
#import "OpenGLViewController.h"

@interface ViewController ()
@property (nonatomic, strong) UIButton *openGLBtn;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = UIColor.whiteColor;
    self.openGLBtn = [[UIButton alloc]initWithFrame:CGRectMake(100, 100, 100, 100)];
    [self.view addSubview:self.openGLBtn];
    self.openGLBtn.backgroundColor = [UIColor blueColor];
    [self.openGLBtn addTarget:self action:@selector(clickOpenGL:) forControlEvents:UIControlEventTouchUpInside];
    
}

- (void)clickOpenGL:(id)sender {
    OpenGLViewController *vc = [OpenGLViewController new];
    [self.navigationController pushViewController:vc animated:YES];
}

@end
