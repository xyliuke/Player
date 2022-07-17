//
// Created by 刘科 on 2022/7/12.
//

#ifndef MACOPENGLDEMO_IMAGE_H
#define MACOPENGLDEMO_IMAGE_H

#include <string>

namespace plan9
{
    class image {
    public:
        image(const std::string &path);
        size_t get_data(unsigned char *data);
    private:
        class image_impl;
        std::shared_ptr<image_impl> impl;
    };
}



#endif //MACOPENGLDEMO_IMAGE_H
