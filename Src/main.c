/*! \file main.c
    \brief Bitmap Dosyas� ��leyen Program.

 Bu kod sabit olarak girilen bitmap dosyas�n� gri tonlamaya �eviren bir programd�r.
 \author    Salih Palamut
 \version   1.0.0
 \date      2015
 \pre       https://drive.google.com/file/d/0B7uyyDOMx0RBc0xxNnlEazBtVjQ/view?pli=1 NOT 10 Dosya Yap�lar� b�l�m� incelenmelidir.
 \bug       Yok.

 \warning   Uygulama terminalden ve direk �al��t�r�labilecek bi�imde d�zenlenmi�tir.

 \copyright GNU Public License.
 */
#include "Headers/bitmap.h"
#include <locale.h>
//Bu tam�n �evirme i�leminin ne kadar s�rede ger�ekle�ti�ini
//ve resim bilgisini g�stermek i�in kullan�lm��t�r.
#ifdef bench
#include <time.h>
#endif // bench
/*!Dosya ad� uzunlu�u*/
#define max_file_name 100

/*! \fn int main()
    \brief ana fonksiyon yap�s� ve i�eri�i
    \param ald��� parametre yok.
    \return �al��ma sonucunu i�letim sistemine d�nd�r�r.0 ise ba�ar�l�.
*/
int main(int komut_sayisi,char*komutlar[])
{
    //Ekran ��kt�s� T�rk�e
    setlocale(LC_ALL,"Turkish");
    //Dosya giri� ��k�� adlar�
    char input_file_name [max_file_name],
         output_file_name[max_file_name];
    //se�ilen �evirme i�lemi
    int process;
    //E�er konsola de�er girilmemi�se
    //veya direk �al��t�rlm��sa
    if(komut_sayisi==1)
    {
        //i�lenecek dosya ad�n� al
        printf("�evrilecek\nDosyan�n Ad�:\n");
        scanf(" %99s",input_file_name);
        //yap�lacak i�lemi al
        printf("�evirim Format�:\n0=gri\n1=negtif\n2=sepya\n");
        scanf(" %d",&process);
        process%=3;
        //kaydedilecek dosya ad�n� al
        printf("Kay�t Ad�:\n");
        scanf(" %99s",output_file_name);
    }
    //e�er konsolda giri�_dosya_ad� �eviri_tipi ��k��_dosya_ad� varsa
    else if(komut_sayisi==4)
    {
        //i�lenecek dosya ad�n� al
        strncpy(input_file_name,komutlar[1],max_file_name);
        //yap�lacak i�lemi al ve tam say� tipine d�n��t�r.
        process=atoi(komutlar[2])%3;
        //kaydedilecek dosya ad�n� al
        strncpy(output_file_name,komutlar[3],max_file_name);
    }
    //e�er bu durumlar d���ndaysa hatal� kullan�m
    //ekrana nas�l kullan�lmas� gerekti�ini g�ster
    else
    {
        printf("Kullan�m K�lavuzu\n");
        printf("1.Komutsuz �al��t�rma:\n\tHi� bir komut girmezseniz ekrana y�nlendirme metinleri gelecektir.");
        printf("\n2.Komutlu  �al��t�rma:\n\tcevrilecek_dosyan�n_ad�.bmp yap�lacak_i�lem_numaras�{0=gri,1=negatif,2=sepya} kay�t_ad�.bmp");
        return 0;
    }
    //i�lencek dosyay� a�
    if(bitmap_open(input_file_name))goto errosrs;

    //ba�l�k i�n yer ay�r
    PBitmap header=(PBitmap)malloc(sizeof(Bitmap));
    //dosyadan ba�l��� oku
    bitmap_read_header(header);
#ifdef bench
    bitmap_print_info(header);
#endif // bench
    //pixeller i�n yer ay�r
    void * data=malloc(header->info.biSizeImage);
    //dosyadan pixelleri oku
    bitmap_readdata(header,data);
#ifdef bench
    clock_t start, end;
    double cpu_time_used;
    start = clock();
#endif // bench
    //bitmap pixel �evirme fonksiyonu
    bitmap_convert2type(data,process,header);
#ifdef bench
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f",cpu_time_used);
#endif // bench
    //i�elen pixelleri dosysya kaydet
    bitmap_save(output_file_name,header,data);
errosrs:
    //dosyay� kapat
    bitmap_close(header,data);
    return 0;
}
