//
// Created by 刘科 on 2022/7/12.
//

#include "image.h"
#if (__APPLE__)
#include <ImageIO/ImageIO.h>
#include <CoreFoundation/CoreFoundation.h>
#endif
namespace plan9
{
    class image::image_impl {
    private:
        std::string image_file;
    public:
        image_impl(const std::string &path) {
            image_file = path;
        }

        size_t get_data(unsigned char *data) {
#if (__APPLE__)
            CGImageRef image = getImage(image_file);
            CGDataProviderRef dataProvider = CGImageGetDataProvider(image);
            CFDataRef dataRef = CGDataProviderCopyData(dataProvider);
            CFIndex len = CFDataGetLength(dataRef);
            CFDataGetBytes(dataRef, CFRangeMake(0, len), data);
            CFRelease(dataRef);
            CGDataProviderRelease(dataProvider);
            CGImageRelease(image);
            return len;
#else
            return 0;
#endif

        }

#if (__APPLE__)
        CGImageRef getImage(std::string &path) {
            CFURLRef url = CFURLCreateWithString(kCFAllocatorDefault, reinterpret_cast<CFStringRef>(path.c_str()), nullptr);
            CFStringRef myKeys[2];
            CFTypeRef myValues[2];
            myKeys[0] = kCGImageSourceShouldCache;
            myValues[0] = (CFTypeRef)kCFBooleanTrue;
            myKeys[1] = kCGImageSourceShouldAllowFloat;
            myValues[1] = (CFTypeRef)kCFBooleanTrue;
            CFDictionaryRef myOptions = nullptr;
            myOptions = CFDictionaryCreate(nullptr, (const void **) myKeys,
                                           (const void **) myValues, 2,
                                           &kCFTypeDictionaryKeyCallBacks,
                                           & kCFTypeDictionaryValueCallBacks);
            CGImageSourceRef myImageSource;
            myImageSource = CGImageSourceCreateWithURL((CFURLRef)url, myOptions);
            CFRelease(myOptions);
            if (myImageSource == nullptr) {
                return nullptr;
            }
            CGImageRef myImage = nullptr;
            myImage = CGImageSourceCreateImageAtIndex(myImageSource,
                                                      0,
                                                      nullptr);
            CFRelease(myImageSource);
            return myImage;
        }
#else
#endif
    };

    image::image(const std::string &path) : impl(new image_impl(path)) {

    }

    size_t image::get_data(unsigned char *data) {
        return impl->get_data(data);
    }
}