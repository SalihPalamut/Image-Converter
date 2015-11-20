/*! \file bitmap.h
    \brief Bitmap Dosyasý ile ilgili tanýmlar.

 Bu kod bitmap.c dosyasýný bildirimmlerini ve bitmap ile ilgili tanýmlarý barýndýrýr.
 \author    Salih Palamut
 \version   1.0.0
 \date      2015
 \pre       https://drive.google.com/file/d/0B7uyyDOMx0RBc0xxNnlEazBtVjQ/view?pli=1 NOT 10 Dosya Yapýlarý bölümü incelenmelidir.
 \bug       Tespit edilmemiþ.

 \copyright GNU Public License.
 */
#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*! \defgroup a #pragma pack(1)
 \brief paketleme boyutudur.

Bu derleyiciye veri içeriðini belleðe 1 bayt 1 bayt yerleþtirmesini bildirir.
\{
*/
#pragma pack(1)
/*! \brief Bu yapý dosya bilgilerini barýndýrýr.

Bitmap dosyasýnýn dosya baþlýk tipidir.*/
typedef struct
{
    unsigned short bfType;/*!< Sihirli numara 0x4d42 olmalý.*/
    unsigned int   bfSize;/*!< Bayt cinsinden dosya boyutu*/
    unsigned short bfReserved1;/*!<Ýki bayt ayrýlmýþ */
    unsigned short bfReserved2;/*!<Ýki bayt ayrýlmýþ */
    unsigned int   bfOffBits;/*!<Bitmap verilerin baþlangýc adresi*/
} BITMAPFILEHEADER;
/*! \brief Bu yapý dosya içerik bilgilerini barýndýrýr.

Bitmap dosyasýnýn bilgi baþlýk tipidir.*/
typedef struct
{
    unsigned int   biSize;           /*!< \brief .

     Baþlýk boyutu */
    int            biWidth;          /*!< Geniþlik */
    int            biHeight;         /*!< Yükseklik */
    unsigned short biPlanes;         /*!< renk plan numarasý */
    unsigned short biBitCount;       /*!< Her bir pikselin bit sayýsý */
    unsigned int   biCompression;    /*!< Sýkýþtýrma tipi*/
    unsigned int   biSizeImage;      /*!< Resim veri boyutu */
    int            biXPelsPerMeter;  /*!< Metre baþýna düþen
                                        Yatay (X) piksel sayýsý */
    int            biYPelsPerMeter;   /*!<Metre baþýna düþen
                                        Dikey (Y) piksel sayýsý*/
    unsigned int   biClrUsed;        /*!< Kullanýlan renk sayýsý*/
    unsigned int   biClrImportant;   /*!< Önemli renk sayýsý*/
} BITMAPINFOHEADER;
/*! \brief Bu yapý bitmapin tüm baþlýk deðerleri içindir.

Bitmap te kaydedilmiþ file ve info ile
ifade edilen tüm baþlýk deðerlerini alýr*/
typedef struct
{
    BITMAPFILEHEADER file;
    BITMAPINFOHEADER info;
} Bitmap,
/*! \brief ön tanýmlý iþaretçi.

Bitmap tipinin iþaretçisidir. Hýzlý kullaným amacýyla tanýmlanmýþ tiptir*/
*PBitmap;
/*! \brief Bu yapý renk deðerleri içindir.

Bitmap te kaydedilmiþ yirmi dört bitle
ifade edilen renk deðerlerini alýr*/
typedef struct
{
    unsigned char B;/*!<B-0~255 arasý Mavi Renk deðeri*/
    unsigned char G;/*!<G-0~255 arasý Yeþil Renk deðeri*/
    unsigned char R;/*!<R-0~255 arasý Kýrmýzý Renk deðeri*/
} colors;

#pragma pack()
/*!\}*/

/*! \enum type
 \brief Bu yapý döþüm deðerleri içindir.

Resmin pixel deðerlerini ilgili deðere göre dönüþümünü saðlar.*/
typedef enum {GRAY=0,NEGATIVE,SEPIA} type;
/*! \fn unsigned char bitmap_close(PBitmap header,void *data)
    \brief bitmap_open iþlemiyle açýlmýþ ve iþlenmiþ dosyasyý kapatýr.
    \param header PBitmap tipinde ilgili bitmap'in baþlýðýnýn adresini alýr.
    \param data   void iþaretçisi tipinde bitmap verisi.
    \return Baþarýlýysa 0 baþarýsýzsa EOF yani çoðu derleyicide -1 deðerini döndürür.
*/
unsigned char bitmap_close(PBitmap header,void *data);
/*! \fn unsigned char bitmap_open(char * file_name)
    \brief Adýna göre bitmap dosyasý açar(test.bmp).
    \param file_name dosya adý metin tipinde.
    \return Baþarýlýysa 0 baþarýsýzsa 1 deðerini döndürür.
*/
unsigned char bitmap_open(char * file_name);
/*! \fn unsigned char bitmap_read_header(PBitmap header)
    \brief Açýlmýþ dosyanýn baþlýk bilgilerini okur ilgili deðiþkenin adresine doldurur.
    \param header PBitmap tipinde ilgili bitmap'in baþlýðýnýn adresini alýr.
    \return Baþarýlýysa 0 baþarýsýzsa 1 deðerini döndürür.
*/
unsigned char bitmap_read_header(PBitmap header);
/*! \fn unsigned char bitmap_readdata(PBitmap header,void * data)
    \brief Açýlmýþ dosyanýn veri bilgilerini okur ilgili deðiþkenin adresine doldurur.
    \param header PBitmap tipinde ilgili bitmap'in baþlýðýnýn adresini alýr.
    \param data   doldurmak için void iþaretçisi tipnde deðiþken adresi alýr.
    \return Baþarýlýysa 0 baþarýsýzsa 1 deðerini döndürür.
*/
unsigned char bitmap_readdata(PBitmap header,void * data);
/*! \fn int bitmap_save(char*file_name,PBitmap header,void *data)
    \brief Ýþlenmiþ bitmap bilgilerini ilgili dosyaya kayýteder.
    \param file_name    Metin tipinde kaydedilecek dosya adý.
    \param header       PBitmap tipinde ilgili bitmap'in baþlýðýnýn adresini alýr.
    \param data         void iþaretçisi tipnde deðiþken adresi alýr.
    \return Baþarýlýysa 0 baþarýsýzsa EOF yani çoðu derleyicide -1 deðerini döndürür.
*/
int bitmap_save(char*file_name,PBitmap header,void *data);
/*! \fn unsigned char bitmap_convert2type(void *data,type cnv,PBitmap header)
    \brief Resmi  ilgili seçime göre iþler (0-Gri,1-Deðili,2-Sepya).
    \param data   void iþaretçisi tipnde deðiþken adresi alýr.
    \param cnv    type tipinde cevrilecek enum deðeri.
    \param header PBitmap tipinde ilgili bitmap'in baþlýðýnýn adresini alýr.
    \return Baþarýlýysa 0 baþarýsýzsa 1 deðerini döndürür.
*/
unsigned char bitmap_convert2type(void *data,type cnv,PBitmap header);
/*! \fn void bitmap_print_info(PBitmap header)
    \brief Resmi  ilgili bilgileri ekranda gösterir.
    \param header PBitmap tipinde ilgili bitmap'in baþlýðýnýn adresini alýr.
*/
void bitmap_print_info(PBitmap header);
#endif // BITMAP_H_INCLUDED
