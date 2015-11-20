/*! \file main.c
    \brief Bitmap Dosyasý Ýþleyen Program.

 Bu kod sabit olarak girilen bitmap dosyasýný gri tonlamaya çeviren bir programdýr.
 \author    Salih Palamut
 \version   1.0.0
 \date      2015
 \pre       https://drive.google.com/file/d/0B7uyyDOMx0RBc0xxNnlEazBtVjQ/view?pli=1 NOT 10 Dosya Yapýlarý bölümü incelenmelidir.
 \bug       Yok.

 \warning   Uygulama terminalden ve direk çalýþtýrýlabilecek biçimde düzenlenmiþtir.

 \copyright GNU Public License.
 */
#include "Headers/bitmap.h"
#include <locale.h>
//Bu tamýn çevirme iþleminin ne kadar sürede gerçekleþtiðini
//ve resim bilgisini göstermek için kullanýlmýþtýr.
#ifdef bench
#include <time.h>
#endif // bench
/*!Dosya adý uzunluðu*/
#define max_file_name 100

/*! \fn int main()
    \brief ana fonksiyon yapýsý ve içeriði
    \param aldýðý parametre yok.
    \return Çalýþma sonucunu iþletim sistemine döndürür.0 ise baþarýlý.
*/
int main(int komut_sayisi,char*komutlar[])
{
    //Ekran Çýktýsý Türkçe
    setlocale(LC_ALL,"Turkish");
    //Dosya giriþ çýkýþ adlarý
    char input_file_name [max_file_name],
         output_file_name[max_file_name];
    //seçilen çevirme iþlemi
    int process;
    //Eðer konsola deðer girilmemiþse
    //veya direk çalýþtýrlmýþsa
    if(komut_sayisi==1)
    {
        //iþlenecek dosya adýný al
        printf("Çevrilecek\nDosyanýn Adý:\n");
        scanf(" %99s",input_file_name);
        //yapýlacak iþlemi al
        printf("Çevirim Formatý:\n0=gri\n1=negtif\n2=sepya\n");
        scanf(" %d",&process);
        process%=3;
        //kaydedilecek dosya adýný al
        printf("Kayýt Adý:\n");
        scanf(" %99s",output_file_name);
    }
    //eðer konsolda giriþ_dosya_adý çeviri_tipi çýkýþ_dosya_adý varsa
    else if(komut_sayisi==4)
    {
        //iþlenecek dosya adýný al
        strncpy(input_file_name,komutlar[1],max_file_name);
        //yapýlacak iþlemi al ve tam sayý tipine dönüþtür.
        process=atoi(komutlar[2])%3;
        //kaydedilecek dosya adýný al
        strncpy(output_file_name,komutlar[3],max_file_name);
    }
    //eðer bu durumlar dýþýndaysa hatalý kullaným
    //ekrana nasýl kullanýlmasý gerektiðini göster
    else
    {
        printf("Kullaným Kýlavuzu\n");
        printf("1.Komutsuz çalýþtýrma:\n\tHiç bir komut girmezseniz ekrana yönlendirme metinleri gelecektir.");
        printf("\n2.Komutlu  çalýþtýrma:\n\tcevrilecek_dosyanýn_adý.bmp yapýlacak_iþlem_numarasý{0=gri,1=negatif,2=sepya} kayýt_adý.bmp");
        return 0;
    }
    //iþlencek dosyayý aç
    if(bitmap_open(input_file_name))goto errosrs;

    //baþlýk içn yer ayýr
    PBitmap header=(PBitmap)malloc(sizeof(Bitmap));
    //dosyadan baþlýðý oku
    bitmap_read_header(header);
#ifdef bench
    bitmap_print_info(header);
#endif // bench
    //pixeller içn yer ayýr
    void * data=malloc(header->info.biSizeImage);
    //dosyadan pixelleri oku
    bitmap_readdata(header,data);
#ifdef bench
    clock_t start, end;
    double cpu_time_used;
    start = clock();
#endif // bench
    //bitmap pixel çevirme fonksiyonu
    bitmap_convert2type(data,process,header);
#ifdef bench
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f",cpu_time_used);
#endif // bench
    //iþelen pixelleri dosysya kaydet
    bitmap_save(output_file_name,header,data);
errosrs:
    //dosyayý kapat
    bitmap_close(header,data);
    return 0;
}
