//
//  BaseOpenGLView.h
//  OpenGLiOSDemo
//
//  Created by 刘科 on 2022/5/11.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseOpenGLView : UIView
@property (nonatomic, readonly) EAGLContext *context;
@end

NS_ASSUME_NONNULL_END
