#include "Image.h"

float clip(float n, float lower, float upper){
    if(n<=lower) return lower;
    else if(n>=upper) return upper;
    return n;
}


Color::Color(int red, int green, int blue){
    R=static_cast<short>(clip(red,0,255));
    G=static_cast<short>(clip(green,0,255));
    B=static_cast<short>(clip(blue,0,255));
}

Image::Image(unsigned int width, unsigned int height)
    :width{width},height{height}{
        data=new Color[width*height];
    }

Image::Image(const Image &other)
    :width{other.width},height{other.height}{
        data=new Color[width*height];
        for(unsigned int n{0};n<width*height;++n){
            data[n]=other.data[n];
        }
    }

Image::~Image(){
    delete[] data;
    data=nullptr;
}

//Tilordningsopperatøren vil by default gi shallow copy, slik at vi ved tilordning etterfulgt av destruksjon vil slette minneaddressen til data flere ganger. Etter at vi har gitt det fra oss, som betyr at vi kommer til å slette noe vi ikke eier.



Color Image::getPixel(unsigned int x, unsigned int y){
    return(data[x+y*width]);
}
void Image::setPixel(unsigned int x, unsigned int y, Color c){
    data[x+y*width]=c;
}
Image Image::grayscale(){
    Image grayImage{width,height};
    short grey;
    for(unsigned int n{0};n<width*height;++n){
            grey=(data[n].R+data[n].G+data[n].B)/3;
            grayImage.data[n]=Color{grey,grey,grey};
        }
    return grayImage;   
}
Image Image::threshold(unsigned int t){
    Image tImage{width,height};
    short T=static_cast<short>(t);
    short red;
    short green;
    short blue;
    for(unsigned int n{0};n<width*height;++n){
            if(data[n].R>=T) red=255;
            else red=0;
            if(data[n].G>=T) green=255;
            else green=0;
            if(data[n].B>=T) blue=255;
            else blue=0;
            
            tImage.data[n]=Color{red,green,blue};
        }
    return tImage; 
}
Image Image::operator+(Image other){
    if(height!=other.height||width!=other.width){
        throw "Could not merge pictures of differen size";
    }
    
    Image avgImage{width,height};
    short red;
    short green;
    short blue;
    for(unsigned int n{0};n<width*height;++n){
            red=(data[n].R+other.data[n].R)/2;
            green=(data[n].G+other.data[n].G)/2;
            blue=(data[n].B+other.data[n].B)/2;
            avgImage.data[n]=Color{red,green,blue};
        }
    return avgImage;
}
Color Image::applyKernel(unsigned int x, unsigned int y, Kernel k){
    short red{0};
    short green{0};
    short blue{0};
    for(short dx=-1;dx<2;++dx){
        for(short dy=-1;dy<2;++dy){
            red+=data[(x+dx)+(y+dy)*width].R*k[1+dx][1+dy];
            green+=data[(x+dx)+(y+dy)*width].G*k[1+dx][1+dy];
            blue+=data[(x+dx)+(y+dy)*width].B*k[1+dx][1+dy];
        }
    }
    return Color{red,green,blue};


}
Image Image::convolve(Kernel k){
    Image conImage{*this};

    for(unsigned int x{1};x<width-1;++x){
        for(unsigned int y{1};y<height-1;++y){
            conImage.data[x+y*width]=applyKernel(x,y,k);
        }    
    }
    return conImage;
}

