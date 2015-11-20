/*! \file bitmap.h
    \brief Bitmap Dosyas� ile ilgili tan�mlar.

 Bu kod bitmap.c dosyas�n� bildirimmlerini ve bitmap ile ilgili tan�mlar� bar�nd�r�r.
 \author    Salih Palamut
 \version   1.0.0
 \date      2015
 \pre       https://drive.google.com/file/d/0B7uyyDOMx0RBc0xxNnlEazBtVjQ/view?pli=1 NOT 10 Dosya Yap�lar� b�l�m� incelenmelidir.
 \bug       Tespit edilmemi�.

 \copyright GNU Public License.
 */
#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*! \defgroup a #pragma pack(1)
 \brief paketleme boyutudur.

Bu derleyiciye veri i�eri�ini belle�e 1 bayt 1 bayt yerle�tirmesini bildirir.
\{
*/
#pragma pack(1)
/*! \brief Bu yap� dosya bilgilerini bar�nd�r�r.

Bitmap dosyas�n�n dosya ba�l�k tipidir.*/
typedef struct
{
    unsigned short bfType;/*!< Sihirli numara 0x4d42 olmal�.*/
    unsigned int   bfSize;/*!< Bayt cinsinden dosya boyutu*/
    unsigned short bfReserved1;/*!<�ki bayt ayr�lm�� */
    unsigned short bfReserved2;/*!<�ki bayt ayr�lm�� */
    unsigned int   bfOffBits;/*!<Bitmap verilerin ba�lang�c adresi*/
} BITMAPFILEHEADER;
/*! \brief Bu yap� dosya i�erik bilgilerini bar�nd�r�r.

Bitmap dosyas�n�n bilgi ba�l�k tipidir.*/
typedef struct
{
    unsigned int   biSize;           /*!< \brief .

     Ba�l�k boyutu */
    int            biWidth;          /*!< Geni�lik */
    int            biHeight;         /*!< Y�kseklik */
    unsigned short biPlanes;         /*!< renk plan numaras� */
    unsigned short biBitCount;       /*!< Her bir pikselin bit say�s� */
    unsigned int   biCompression;    /*!< S�k��t�rma tipi*/
    unsigned int   biSizeImage;      /*!< Resim veri boyutu */
    int            biXPelsPerMeter;  /*!< Metre ba��na d��en
                                        Yatay (X) piksel say�s� */
    int            biYPelsPerMeter;   /*!<Metre ba��na d��en
                                        Dikey (Y) piksel say�s�*/
    unsigned int   biClrUsed;        /*!< Kullan�lan renk say�s�*/
    unsigned int   biClrImportant;   /*!< �nemli renk say�s�*/
} BITMAPINFOHEADER;
/*! \brief Bu yap� bitmapin t�m ba�l�k de�erleri i�indir.

Bitmap te kaydedilmi� file ve info ile
ifade edilen t�m ba�l�k de�erlerini al�r*/
typedef struct
{
    BITMAPFILEHEADER file;
    BITMAPINFOHEADER info;
} Bitmap,
/*! \brief �n tan�ml� i�aret�i.

Bitmap tipinin i�aret�isidir. H�zl� kullan�m amac�yla tan�mlanm�� tiptir*/
*PBitmap;
/*! \brief Bu yap� renk de�erleri i�indir.

Bitmap te kaydedilmi� yirmi d�rt bitle
ifade edilen renk de�erlerini al�r*/
typedef struct
{
    unsigned char B;/*!<B-0~255 aras� Mavi Renk de�eri*/
    unsigned char G;/*!<G-0~255 aras� Ye�il Renk de�eri*/
    unsigned char R;/*!<R-0~255 aras� K�rm�z� Renk de�eri*/
} colors;

#pragma pack()
/*!\}*/

/*! \enum type
 \brief Bu yap� d���m de�erleri i�indir.

Resmin pixel de�erlerini ilgili de�ere g�re d�n���m�n� sa�lar.*/
typedef enum {GRAY=0,NEGATIVE,SEPIA} type;
/*! \fn unsigned char bitmap_close(PBitmap header,void *data)
    \brief bitmap_open i�lemiyle a��lm�� ve i�lenmi� dosyasy� kapat�r.
    \param header PBitmap tipinde ilgili bitmap'in ba�l���n�n adresini al�r.
    \param data   void i�aret�isi tipinde bitmap verisi.
    \return Ba�ar�l�ysa 0 ba�ar�s�zsa EOF yani �o�u derleyicide -1 de�erini d�nd�r�r.
*/
unsigned char bitmap_close(PBitmap header,void *data);
/*! \fn unsigned char bitmap_open(char * file_name)
    \brief Ad�na g�re bitmap dosyas� a�ar(test.bmp).
    \param file_name dosya ad� metin tipinde.
    \return Ba�ar�l�ysa 0 ba�ar�s�zsa 1 de�erini d�nd�r�r.
*/
unsigned char bitmap_open(char * file_name);
/*! \fn unsigned char bitmap_read_header(PBitmap header)
    \brief A��lm�� dosyan�n ba�l�k bilgilerini okur ilgili de�i�kenin adresine doldurur.
    \param header PBitmap tipinde ilgili bitmap'in ba�l���n�n adresini al�r.
    \return Ba�ar�l�ysa 0 ba�ar�s�zsa 1 de�erini d�nd�r�r.
*/
unsigned char bitmap_read_header(PBitmap header);
/*! \fn unsigned char bitmap_readdata(PBitmap header,void * data)
    \brief A��lm�� dosyan�n veri bilgilerini okur ilgili de�i�kenin adresine doldurur.
    \param header PBitmap tipinde ilgili bitmap'in ba�l���n�n adresini al�r.
    \param data   doldurmak i�in void i�aret�isi tipnde de�i�ken adresi al�r.
    \return Ba�ar�l�ysa 0 ba�ar�s�zsa 1 de�erini d�nd�r�r.
*/
unsigned char bitmap_readdata(PBitmap header,void * data);
/*! \fn int bitmap_save(char*file_name,PBitmap header,void *data)
    \brief ��lenmi� bitmap bilgilerini ilgili dosyaya kay�teder.
    \param file_name    Metin tipinde kaydedilecek dosya ad�.
    \param header       PBitmap tipinde ilgili bitmap'in ba�l���n�n adresini al�r.
    \param data         void i�aret�isi tipnde de�i�ken adresi al�r.
    \return Ba�ar�l�ysa 0 ba�ar�s�zsa EOF yani �o�u derleyicide -1 de�erini d�nd�r�r.
*/
int bitmap_save(char*file_name,PBitmap header,void *data);
/*! \fn unsigned char bitmap_convert2type(void *data,type cnv,PBitmap header)
    \brief Resmi  ilgili se�ime g�re i�ler (0-Gri,1-De�ili,2-Sepya).
    \param data   void i�aret�isi tipnde de�i�ken adresi al�r.
    \param cnv    type tipinde cevrilecek enum de�eri.
    \param header PBitmap tipinde ilgili bitmap'in ba�l���n�n adresini al�r.
    \return Ba�ar�l�ysa 0 ba�ar�s�zsa 1 de�erini d�nd�r�r.
*/
unsigned char bitmap_convert2type(void *data,type cnv,PBitmap header);
/*! \fn void bitmap_print_info(PBitmap header)
    \brief Resmi  ilgili bilgileri ekranda g�sterir.
    \param header PBitmap tipinde ilgili bitmap'in ba�l���n�n adresini al�r.
*/
void bitmap_print_info(PBitmap header);
#endif // BITMAP_H_INCLUDED
