/*! \file bitmap.c
    \brief Bitmap Dosyasý ile iþlemleri tanýmlar.

 Bu kod bitmap.h dosyasýný bildirdiði fonksiyonlarý barýndýrýr.
 \author    Salih Palamut
 \version   1.0.0
 \date      2015
 \pre       https://drive.google.com/file/d/0B7uyyDOMx0RBc0xxNnlEazBtVjQ/view?pli=1 NOT 10 Dosya Yapýlarý bölümü incelenmelidir.
 \bug       Yok.

 \copyright GNU Public License.
 */
#include "../Headers/bitmap.h"
static FILE* bmp=NULL;
unsigned char bitmap_close(PBitmap header,void *data)
{
    if(!header)
    free(header);
    if(!data)
    free(data);
    return fclose(bmp);
}
unsigned char bitmap_open(char * file_name)
{
    bmp=fopen(file_name,"rb");
    //2.1.Dosya açma kontrolü
    if(bmp==NULL)
        return 1;
    return 0;
}
unsigned char bitmap_read_header(PBitmap header)
{
    if(!header || !bmp)
        return 1;

    //3.doyadan Bitmap baþlýðý kadar bilgiyi oku.
    fread(header,sizeof(Bitmap),1,bmp);
    //4.Okunan dosya bitmap dosyasýmý kontrol et.
    if(header->file.bfType!=0x4d42)
    {
        fclose(bmp);
        return 1;
    }
    //4.2.Dosya Bitmap dosyasý
    //5.Okunan bilgide piksellerin toplam boyutu var mý?
    if(!header->info.biSizeImage)
        //5.1.Pixel boyutunu hesapla
        header->info.biSizeImage=header->file.bfSize-header->file.bfOffBits;
    return 0;
}
unsigned char bitmap_readdata(PBitmap header,void * data)
{
    if(!header || !bmp || !data)
        return 1;
    fseek(bmp, sizeof(Bitmap),SEEK_SET);
    fread(data,header->info.biSizeImage,1,bmp);
    return 0;
}
int bitmap_save(char*file_name,PBitmap header,void *data)
{
    if(!data)
        return 1;
    FILE* obmp=fopen(file_name,"wb");
    //6.Dosya açma kontrolü
    if(!obmp)
        return 1;
    fwrite(header,sizeof(Bitmap),1,obmp);
    fwrite(data,header->info.biSizeImage,1,obmp);
    return fclose(obmp);
}
unsigned char bitmap_convert2type(void *data,type cnv,PBitmap header)
{
    unsigned int i=0,j=0;
    colors renk,sep;
    int tmp;
    void * p=data;
    //son piksele kadar iþlemleri gerçekleþtir.
    for(i=0; i<header->info.biWidth; i++)
        for(j=0; j<header->info.biHeight; j++)
        {
            memcpy(&renk,p,sizeof(colors));
            switch(cnv)
            {
            case GRAY:
                renk.R=(renk.R*30+renk.G*59+renk.B*11)/100;
                renk.G=renk.R;
                renk.B=renk.R;
                break;
            case NEGATIVE:
                renk.R=~renk.R;
                renk.G=~renk.G;
                renk.B=~renk.B;
                break;
            case SEPIA:
                //Yeni Kýrmýzý Deðeri
                tmp = (int)(0.393 * renk.R + 0.769 * renk.G + 0.189 * renk.B);
                if(tmp>255)sep.R=255;
                else sep.R=tmp;
                //Yeni Yeþil Deðeri
                tmp = (int)(0.349 * renk.R + 0.686 * renk.G + 0.168 * renk.B);
                if(tmp>255)sep.G=255;
                else sep.G=tmp;
                //Yeni Mavi Deðeri
                tmp = (int)(0.272 * renk.R + 0.534 * renk.G + 0.131 * renk.B);
                if(tmp>255)sep.B=255;
                else sep.B=tmp;
                memcpy(&renk,&sep,sizeof(colors));
                break;
            default:
                return 1;
                break;
            }
            //4.3.Piselin yeni deðerlerini gir.
            memcpy(p,&renk,sizeof(colors));
            //4.4.Sonraki piksele git.
            p+=sizeof(colors);
        }

    return 0;
}
void bitmap_print_info(PBitmap header)
{
    printf("Boyutlar\t%dx%d\n",header->info.biWidth,header->info.biHeight);
    printf("Genislik\t%dpiksel\n",header->info.biWidth);
    printf("Yukseklik\t%dpiksel\n",header->info.biHeight);
    printf("Bit Derinligi\t%d\n",header->info.biBitCount);
    printf("Dosya Boyutu\t%.2fKb\n",header->file.bfSize/1024.0);
}
