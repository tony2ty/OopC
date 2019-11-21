//MIT License
//
//Copyright(c) 2019 Goodman Tao
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#include "IImage.h"
#include "ImageBmp.h"
#include "ImageGif.h"
#include "ImageJpg.h"
#include "ImagePng.h"
#include "IOprtSys.h"
#include "OprtSysLinux.h"
#include "OprtSysUnix.h"
#include "OprtSysWindows.h"

int main(int argc, char **argv)
{
    RLSLOCALMEMBRA();

    IImage *pImage = NULL;
    {
        //ImageBmp *pBmp = CREATE(ImageBmp)(); TORLS(DELETE(ImageBmp), pBmp);
        //pImage = SWITCH(pBmp, ImageBmp, IImage);//Bmp
        //ImageGif *pGif = CREATE(ImageGif)(); TORLS(DELETE(ImageGif), pGif);
        //pImage = SWITCH(pGif, ImageGif, IImage);//Gif
        ImageJpg *pJpg = NEW(ImageJpg); TORLS(DEL(ImageJpg), pJpg);
        pImage = SWITCH(pJpg, IImage);//Jpg
        //ImagePng *pPng = CREATE(ImagePng)(); TORLS(DELETE(ImagePng), pPng);
        //pImage = SWITCH(pPng, ImagePng, IImage);//Png

        IOprtSys *pOS = NULL;
        {
            //OprtSysLinux *pLinux = CREATE(OprtSysLinux)();
            //pOS = SWITCH(pLinux, OprtSysLinux, IOprtSys);//Linux
            OprtSysUnix *pUnix = NEW(OprtSysUnix); //TORLS(DELETE(OprtSysUnix), pUnix);//pOS实例作为pImage的一部分注入，pImage销毁时随之自动销毁，不需要额外销毁。可以取消注释试试
            pOS = SWITCH(pUnix, IOprtSys);//Unix
            //OprtSysWindows *pWindows = CREATE(OprtSysWindows)();
            //pOS = SWITCH(pWindows, OprtSysWindows, IOprtSys);//Windows
        }

        pImage->Call(pImage, "SetOprtSys", pOS);
    }

    pImage->Call(pImage, "ParseFile", "中国地图");

    RLSLOCALMEMKET();

    return 0;
}