//
//  BaseOpenGLView.m
//  OpenGLiOSDemo
//
//  Created by 刘科 on 2022/5/11.
//

#import "BaseOpenGLView.h"
#import <OpenGLES/ES3/gl.h>

@implementation BaseOpenGLView {
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        //设置图层
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        eaglLayer.opaque = NO; //这个一定要设置  不然无法透明
        eaglLayer.backgroundColor = [UIColor clearColor].CGColor;
        /*kEAGLDrawablePropertyRetainedBacking  是否需要保留已经绘制到图层上面的内容
        kEAGLDrawablePropertyColorFormat 绘制对象内部的颜色缓冲区的格式 kEAGLColorFormatRGBA8 4*8 = 32*/
        eaglLayer.drawableProperties = @{
            kEAGLDrawablePropertyRetainedBacking : [NSNumber numberWithBool:NO],
            kEAGLDrawablePropertyColorFormat     : kEAGLColorFormatRGBA8
        };
        
        _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        if (!_context) {
            NSLog(@"Failed to initialize OpenGLES 3.0 context");
        }
        
        // 将当前上下文设置为我们创建的上下文
        if (![EAGLContext setCurrentContext:_context]) {
            NSLog(@"Failed to set current OpenGL context");
        }
    }
    return self;
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}


- (void)layoutSubviews {
    [EAGLContext setCurrentContext:self.context];
    [self destoryRenderAndFrameBuffer];
    [self setupFrameAndRenderBuffer];
    [self render];
}

- (void)destoryRenderAndFrameBuffer {
    glDeleteFramebuffers(1, &_frameBuffer);
    _frameBuffer = 0;
    glDeleteRenderbuffers(1, &_colorRenderBuffer);
    _colorRenderBuffer = 0;
}

- (void)setupFrameAndRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    // 为 color renderbuffer 分配存储空间
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
    
    glGenFramebuffers(1, &_frameBuffer);
    // 设置为当前 framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    // 将 _colorRenderBuffer 装配到 GL_COLOR_ATTACHMENT0 这个装配点上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, _colorRenderBuffer);
    
    
}

- (void)render {
    glClearColor(1.0, 0.5, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //将指定 renderbuffer 呈现在屏幕上，在这里我们指定的是前面已经绑定为当前 renderbuffer 的那个，在 renderbuffer 可以被呈现之前，必须调用renderbufferStorage:fromDrawable: 为之分配存储空间。
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}


@end
