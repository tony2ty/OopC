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
    IImage *pImage = NULL;
    {
        //ImageBmp *pBmp = CREATE(ImageBmp)();
        //pImage = SWITCH(pBmp, ImageBmp, IImage);//Bmp
        //ImageGif *pGif = CREATE(ImageGif)();
        //pImage = SWITCH(pGif, ImageGif, IImage);//Gif
        ImageJpg *pJpg = CREATE(ImageJpg)();
        pImage = SWITCH(pJpg, ImageJpg, IImage);//Jpg
        //ImagePng *pPng = CREATE(ImagePng)();
        //pImage = SWITCH(pPng, ImagePng, IImage);//Png

        IOprtSys *pOS = NULL;
        {
            //OprtSysLinux *pLinux = CREATE(OprtSysLinux)();
            //pOS = SWITCH(pLinux, OprtSysLinux, IOprtSys);//Linux
            OprtSysUnix *pUnix = CREATE(OprtSysUnix)();
            pOS = SWITCH(pUnix, OprtSysUnix, IOprtSys);//Unix
            //OprtSysWindows *pWindows = CREATE(OprtSysWindows)();
            //pOS = SWITCH(pWindows, OprtSysWindows, IOprtSys);//Windows
        }

        INVOKE(IImage)(pImage, "SetOprtSys", &(IImage_SetOprtSys){pOS});
    }

    INVOKE(IImage)(pImage, "ParseFile", &(IImage_ParseFile){"ÖÐ¹úµØÍ¼"});

    DELETE(IImage)(&pImage);

    return 0;
}