#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

int kayitlisifreler[50], kayitlihesapno[50], sifre, islem, girissifresi, a = 1, ay, hesapno, i, j, k, secim, b = 1, c = 0, yatirimlot, kayitliyatirim[50], x, y, fatura;
float kayitliparalar[50], kayitliborclar[50], kayitlidolar[50], kayitlieuro[50], para, yatirimdeger, yatirimmiktar[5] = {0.05, 0.10, 0.15, 0.20, 0.25};
char kayitlikullanicilar[50][50], isim[30], soyisim[30], girisismi[30], girissoyismi[30], telno[10], kayitlifaturalar[50][50], faturano[6], kayitlisigortalar[50][50], saglik_sigorta[11], arac_sigorta[10], ev_mahalle_sigorta[20], ev_ilce_sigorta[20];
FILE *bilgiler, *yatirimbilgileri, *faturabilgileri, *sigortabilgileri;

int main();
void ana_menu(int i, int index);

void dosyaya_yaz(int index)
{
    bilgiler = fopen("bilgiler.txt", "w");
    for (j = 0; j < index - 1; j++)
    {
        fprintf(bilgiler, "%s %d %.1f %.1f %.1f %.1f %d %d\n", kayitlikullanicilar[j], kayitlisifreler[j], kayitliparalar[j], kayitliborclar[j], kayitlidolar[j], kayitlieuro[j], kayitliyatirim[j], kayitlihesapno[j]);
    }
    fclose(bilgiler);
}

void kayit_ol()
{
    bilgiler = fopen("bilgiler.txt", "a");
    printf("Kayit olmak icin isim ve soyisim giriniz.\n");
    scanf("%s %s", &isim, &soyisim);
    strcat(isim, soyisim);
    printf("Kayit olmak icin 4-6 rakam iceren bir sifre olusturunuz.\n");
    while (1)
    {
        scanf("%d", &sifre);
        if (sifre >= 1000 && sifre <= 999999)
        {
            break;
        }
        else
        {
            printf("Lutfen 4-6 rakam iceren bir sifre giriniz.\n");
        }
    }
    hesapno = 10000 + rand();
    strupr(isim);
    fprintf(bilgiler, "%s %d 0.0 0.0 0.0 0.0 0 %d\n", isim, sifre, hesapno);
    fclose(bilgiler);
    yatirimbilgileri = fopen("yatirim.txt", "w");
    fprintf(yatirimbilgileri, "5.9");
    fclose(yatirimbilgileri);
    printf("Kayit islemi basariyla gerceklesmistir.\n\n");
    sleep(1);
}

void para_yatirma(int i, int index)
{
    printf("Ne kadar para yatirmak istiyorsunuz?(10-50.000TL arasinda para yatirma islemi yapabilirsiniz)\nAna menuye donmek icin '0'a basiniz\n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 0)
        {
            ana_menu(i, index);
        }
        else if (para >= 10 && para <= 50000)
        {
            kayitliparalar[i] += para;
            dosyaya_yaz(index);
            printf("Paraniz basariyla yatirilmistir.");
            ana_menu(i, index);
        }
        else
        {
            printf("Lutfen belirlenen araliklarda bir tutar giriniz.\n");
        }
    }
}

void para_cekme(int i, int index)
{
    printf("Ne kadar para cekmek istiyorsunuz?(10-50.000TL arasinda para cekim islemi yapabilirsiniz)\nAna menuye donmek icin '9'a basiniz\n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 9)
        {
            para = 0;
            ana_menu(i, index);
        }
        else if (para >= 10 && para <= 50000)
        {
            if (kayitliparalar[i] < para)
            {
                printf("Lutfen mevcut bakiyenizden dusuk olucak sekilde bir para cekme isleminde bulununuz.\n");
            }
            else
            {
                kayitliparalar[i] -= para;

                dosyaya_yaz(index);
                printf("Para cekme isleminiz gerceklestirmistir.");
                ana_menu(i, index);
            }
        }
        else
        {
            printf("Lutfen belirlenen araliklarda bir tutar giriniz\n");
        }
    }
}

void kredi_cekme(int i, int index)
{
    printf("Ne kadar kredi cekmek istiyorsunuz?(1.000-50.000TL arasinda kredi cekebilirsiniz)\nFaiz Orani (Yillik): %s\nAna menuye donmek icin '9'a basiniz\n", "%20");
    while (1)
    {
        scanf("%f", &para);
        if (para == 9)
        {
            ana_menu(i, index);
        }
        else if (para >= 1000 && para <= 50000)
        {
            kayitliborclar[i] += para * 1.2;
            kayitliparalar[i] += para;
            printf("Kac ayda odemek istiyosunuz?(12-120 ay arasi secim yapiniz)\n");
            while (1)
            {
                scanf("%d", &ay);
                if (ay >= 12 && ay <= 120)
                {
                    printf("%.1fTL krediniz %d ayin sonunda %.1fTL ve ayda %.1fTL odemesi olacak sekilde verilmistir.", para, ay, para * 1.2, (para * 1.2) / ay);
                    ana_menu(i, index);
                }
                else
                {
                    printf("Lutfen belirtilen araliklar arasinda seciminizi yapiniz\n");
                }
            }

            dosyaya_yaz(index);
            break;
        }
        else
        {
            printf("Lutfen belirlenen araliklarda bir tutar giriniz:\n");
        }
    }
}

void borc_odeme(int i, int index)
{
    a = 1;
    printf("Ne kadar borc odemek istiyorsunuz?\nAna menuye donmek icin '9'a basiniz\n");
    while (1)
    {
        scanf("%f", &para);
        if (para == 9)
        {
            para = 0;
            a = 0;
            ana_menu(i, index);
        }
        else if (kayitliparalar[i] < para)
        {
            printf("Bakiyeniz yetersiz.\n");
            printf("Lutfen odemek istediginiz tutari tekrar giriniz ve ya '9'a basarak ana menuye donunuz\n");
            a = 1;
        }
        else if (para <= 0)
        {
            printf("0 veya daha kucuk tutar giris yapamazsiniz.\n");
            a = 1;
        }
        else
        {
            a = 1;
            break;
        }
    }
    while (a == 1)
    {
        if (para > kayitliborclar[i])
        {
            printf("Guncel borc tutariniz %.1fTL dir.Tum borcunuzu odemek ister misiniz?\n1.Evet\n2.Hayir\n", kayitliborclar[i]);
            scanf("%d", &islem);
            if (islem == 1)
            {
                kayitliparalar[i] -= kayitliborclar[i];
                kayitliborclar[i] = 0;
                dosyaya_yaz(index);
                printf("Borc odeme isleminiz gerceklestirmistir.Ana Menuye donuluyor.\n\n");
                sleep(1);
                break;
            }
            if (islem == 2)
            {
                ana_menu(i, index);
            }
        }
        else
        {
            kayitliborclar[i] -= para;
            kayitliparalar[i] -= para;
            dosyaya_yaz(index);
            printf("Borc odeme isleminiz gerceklestirmistir.");
            ana_menu(i, index);
        }
    }
}

void para_gonderme(int i, int index)
{
    if (kayitliparalar[i] <= 0)
    {
        printf("Gonderebileceginiz bir bakiyeniz bulunmamaktadir...\n");
        sleep(1);
        ana_menu(i, index);
    }
    b = 1;
    printf("\n");
    for (j = 0; j < index - 1; j++)
    {

        if (i == j)
        {
        }
        else if (kayitlikullanicilar[j][0] == '0')
        {
        }
        else
        {
            printf("%s %d\n", kayitlikullanicilar[j], kayitlihesapno[j]);
            c++;
        }
    }
    if (c == 0)
    {
        printf("Gonderebileceginiz bir hesap bulunmamaktadir...\n");
        sleep(1);
        ana_menu(i, index);
    }
    printf("Hangi hesap numarasina para aktarmak istiyorsunuz?\nAna menuye donmek icin '0'a basiniz\n");
    while (1)
    {
        scanf("%d", &islem);
        if (islem == 0)
        {
            b = 0;
            ana_menu(i, index);
        }
        for (k = 0; k < index - 1; k++)
        {
            if (kayitlihesapno[k] == islem)
            {
                a = 1;
                break;
            }
        }
        if (a == 1)
        {
            break;
        }
        else
        {
            printf("Boyle bir hesap bulunamadi.Lutfen tekrar giriniz veya ana menuye donmek icin '9' basiniz\n");
        }
    }
    printf("Ne kadar para gondermek istiyorsunuz?\nCikis yapmak icin 0'a basiniz\n");
    while (b == 1)
    {
        scanf("%f", &para);
        if (para == 0)
        {
            ana_menu(i, index);
        }
        else if (kayitliparalar[i] < para)
        {
            printf("Yeterli bakiyeniz bulunmamaktadir.Tekrar deneyiniz veya ana menuye donmek icin '0'a basiniz.\n");
        }
        else
        {
            break;
        }
    }

    for (j = 0; j < index - 1; j++)
    {

        if (islem == kayitlihesapno[j])
        {
            kayitliparalar[j] += para;
            kayitliparalar[i] -= para;
            dosyaya_yaz(index);
            printf("Paraniz gonderiliyor.Lutfen bekleyiniz.\n");
            sleep(2);
            printf("Para transferiniz basariyla gerceklestirilmistir.\n\n");
            sleep(1);
            break;
        }
    }
}

void doviz_sat(int i, int index)
{

    printf("\n1.Dolar: 6.92\n2.Euro: 7.67\nHangi para birimiyle islem yapmak istiyorsunuz?\nAna menuye donmek icin '9'a basiniz\n");
    scanf("%d", &islem);
    if (islem != 1 && islem != 2 && islem != 9)
    {
        printf("Lutfen belirtilen araliklarda bir secim yapiniz.\n");
        doviz_sat(i, index);
    }
    else if (islem == 9)
    {
        ana_menu(i, index);
    }

    else
    {
        while (1)
        {

            if (islem == 1)
            {

                if (kayitlidolar[i] == 0)
                {
                    printf("Dolariniz bulunmamaktadir\n");
                    sleep(1);
                    doviz_sat(i, index);
                }

                printf("Kac Dolar satmak istiyorsunuz?(Cikmak icin '0' a basin)\n");
                scanf("%f", &para);

                if (para > kayitlidolar[i])
                {

                    printf("Yeterli bakiyeniz bulunmamaktadir. Lutfen tekrar deneyiniz.\n");
                    sleep(1);
                }

                else
                {
                    kayitlidolar[i] -= para;
                    kayitliparalar[i] += (para * 6.92);
                    break;
                }
            }

            else if (islem == 2)
            {

                if (kayitlieuro[i] == 0)
                {
                    printf("Euro'nuz bulunmamaktadir\n");
                    sleep(1);
                    doviz_sat(i, index);
                }
                printf("Kac Euro satmak istiyorsunuz?(Cikmak icin '0' a basin)\n");
                scanf("%f", &para);

                if (para > kayitlieuro[i])
                {

                    printf("Yeterli bakiyeniz bulunmamaktadir. Lutfen tekrar deneyiniz.\n");
                    sleep(1);
                }

                else
                {
                    kayitlieuro[i] -= para;
                    kayitliparalar[i] += (para * 6.92);
                    break;
                }
            }
        }
        dosyaya_yaz(index);
        printf("Doviz isleminiz gerceklesmistir.");
        ana_menu(i, index);
    }
}

void doviz_al(int i, int index)
{
    a = 0;
    while (a == 0)
    {
        scanf("%d", &islem);
        if (islem == 1)
        {
            printf("Kac Dolar satin almak istiyorsunuz?\n");
            while (1)
            {
                scanf("%f", &para);
                if (kayitliparalar[i] < (para * (6.97)))
                {
                    printf("Bu islemi yapmak icin yeterli bakiyeniz bulunmamaktadir.Lutfen tekrar deneyiniz ve ya '0'a basarak cikis yapiniz.\n");
                }
                else
                {
                    kayitliparalar[i] -= para * (6.97);
                    kayitlidolar[i] += para;
                    dosyaya_yaz(index);
                    printf("Doviz isleminiz gerceklestirilmistir.");
                    a = 1;
                    ana_menu(i, index);
                }
            }
        }
        else if (islem == 2)
        {
            printf("Kac Euro satin almak istiyorsunuz?\n");
            while (1)
            {
                scanf("%f", &para);
                if (kayitliparalar[i] < (para * (7.83)))
                {
                    printf("Bu islemi yapmak icin yeterli bakiyeniz bulunmamaktadir.Lutfen tekrar deneyiniz ve ya '0'a basarak cikis yapiniz.\n");
                }
                else
                {
                    kayitliparalar[i] -= para * (7.83);
                    kayitlieuro[i] += para;
                    dosyaya_yaz(index);
                    printf("Doviz isleminiz gerceklestirilmistir.");
                    a = 1;
                    ana_menu(i, index);
                }
            }
        }
        else if (islem == 9)
        {
            ana_menu(i, index);
        }
        else
        {
            printf("Lutfen belirtilen araliklarda bir secim yapiniz\n");
        }
    }
}

void yatirim(int i, int index)
{
    yatirimbilgileri = fopen("yatirim.txt", "r");
    fscanf(yatirimbilgileri, "%f", &yatirimdeger);
    fclose(yatirimbilgileri);
    a = 1;
    printf("\nTSPOR ~ %.2f\n", yatirimdeger);
    printf("1.Borsa Alis\n2.Borsa Satis\n3.Ana Menuye Don\n");
    while (1)
    {
        scanf("%d", &secim);
        if (secim == 1)
        {
            printf("Kac LOT almak istiyorsunuz?.Ana menu icin '0'a basiniz.\n");
            scanf("%d", &yatirimlot);
            if (yatirimlot == 0)
            {
                ana_menu(i, index);
            }
            else if (kayitliparalar[i] < (yatirimlot * yatirimdeger))
            {
                printf("Bu islemi yapmak icin yeterli bakiyeniz bulunmamaktadir...\nAna menuye donmek icin '0'a basiniz.\n");
            }
            else if (yatirimlot < 0)
            {
                printf("0'dan buyuk bir deger giriniz\n");
            }
            else if (yatirimlot > 0)
            {
                kayitliparalar[i] -= (yatirimlot * yatirimdeger);
                kayitliyatirim[i] += yatirimlot;
                dosyaya_yaz(index);
                printf("Isleminiz tamamlanmistir.");
                ana_menu(i, index);
            }
        }
        else if (secim == 2)
        {

            if (kayitliyatirim[i] == 0)
            {
                printf("Satilacak LOT bulunmamaktadir...\n\n");
                sleep(1);
                break;
            }
            if (a == 1)
            {
                printf("TSPOR ~ %.2f\n", yatirimdeger);
                printf("Sahip oldugunuz LOT sayisi: %d\n", kayitliyatirim[i]);
                printf("Kac LOT satmak istiyorsunuz? Ana menuye donmek icin '0'a basiniz...\n");
            }
            if (kayitliyatirim[i] > 0)
            {
                scanf("%d", &yatirimlot);
                if (kayitliyatirim[i] < yatirimlot)
                {
                    printf("Belirtilen miktarda LOT bulunmamaktadir.Tekrar deneyiniz veya ana menuye donmek icin '0'a basiniz...\n");
                    a = 0;
                }
                else if (yatirimlot == 0)
                {
                    ana_menu(i, index);
                }
                else
                {
                    kayitliyatirim[i] -= yatirimlot;
                    kayitliparalar[i] += (yatirimlot * yatirimdeger);
                    dosyaya_yaz(index);
                    printf("Isleminiz tamamlanmistir.");
                    ana_menu(i, index);
                }
            }
        }
        else if (secim == 3)
        {
            ana_menu(i, index);
        }
        else
        {
            printf("Lutfen belirtilen aralikta secim yapiniz\n");
        }
    }
}

void fatura_odeme(int i, int index)
{
    k = 0;
    b = 1;
    faturabilgileri = fopen("faturabilgileri.txt", "a");
    fclose(faturabilgileri);
    faturabilgileri = fopen("faturabilgileri.txt", "r");
    while (!feof(faturabilgileri))
    {
        fscanf(faturabilgileri, "%s", &kayitlifaturalar[k]);
        k++;
    }
    fclose(faturabilgileri);
    printf("\n1.Telekomunikasyon\n2.Elektrik/Su/Dogalgaz\n3.Ana Menu\n");
    while (1)
    {
        scanf("%d", &islem);
        if (islem == 1)
        {
            printf("Odemesini yapmak istediginiz telefon numarasini basinda '0' olmadan giriniz\n");
            while (1)
            {
                scanf("%s", &telno);
                for (j = 0; j < k; j++)
                {
                    if (strcmp(kayitlifaturalar[j], telno) == 0)
                    {
                        b = 0;
                        break;
                    }
                }
                if (telno[0] == '0')
                {
                    printf("Lutfen basina '0' koymadan yaziniz.Ana menuye donmek icin '1'e basiniz\n");
                }
                else if (telno[0] == '1' && strlen(telno) == 1)
                {
                    ana_menu(i, index);
                }
                else if (strlen(telno) == 10)
                {
                    if (b == 0)
                    {
                        printf("Bu numaraya ait fatura daha once odenmistir...\n");
                        sleep(1);
                        ana_menu(i, index);
                    }
                    else
                    {
                        fatura = rand() % 80 + 20;
                        printf("%s numarali telefonun %d TL odemesi bulunmaktadir\n1.Ode\n2.Ana menuye don\n", telno, fatura);
                        while (1)
                        {
                            scanf("%d", &secim);
                            if (secim == 1)
                            {
                                if (kayitliparalar[i] < fatura)
                                {
                                    printf("Belirtilen islemi yapmak icin yeterli bakiyeniz bulunmamaktadir\n");
                                    sleep(1);
                                    ana_menu(i, index);
                                }
                                else
                                {
                                    faturabilgileri = fopen("faturabilgileri.txt", "a");
                                    printf("Odeme isleminiz gerceklestiriliyor...\n");
                                    kayitliparalar[i] -= fatura;
                                    fprintf(faturabilgileri, "%s\n", telno);
                                    fclose(faturabilgileri);
                                    sleep(1);
                                    printf("Odeme isleminiz basariyla gerceklesmistir.\n");
                                    sleep(1);
                                    ana_menu(i, index);
                                }
                            }
                            else if (secim == 2)
                            {
                                ana_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen belirtilen araliklarda bir secim yapiniz\n");
                            }
                        }
                    }
                }
                else
                {
                    printf("Lutfen 10 karakterden olusan bir telefon numarasi giriniz.Ana menuye donmek icin '1'e basiniz\n");
                }
            }
        }
        else if (islem == 2)
        {
            printf("Lutfen odemek istediginiz faturanin musteri no'sunu giriniz(Orn:A56845,G18632).Ana menuye donmek icin '0'a basiniz.\n");
            while (1)
            {
                scanf("%s", &faturano);
                for (j = 0; j < k; j++)
                {
                    if (strcmp(kayitlifaturalar[j], faturano) == 0)
                    {
                        b = 0;
                        break;
                    }
                }
                if (faturano[0] == '0' && strlen(faturano) == 1)
                {
                    ana_menu(i, index);
                }
                else if (!(faturano[0] >= 'A' && faturano[0] <= 'Z'))
                {
                    printf("Musteri no'sunun en basinda buyuk(A-Z) bir harf olmalidir.Tekrar deneyiniz veya '0'a basarak ana menuye donunuz\n");
                }
                else if (strlen(faturano) != 6 || !(faturano[1] >= '0' && faturano[1] <= '9') || !(faturano[2] >= '0' && faturano[2] <= '9') || !(faturano[3] >= '0' && faturano[3] <= '9') || !(faturano[4] >= '0' && faturano[4] <= '9') || !(faturano[5] >= '0' && faturano[5] <= '9'))
                {
                    printf("Musteri no'su 1 harf ve 5 rakamdan olusmalidir.Tekrar deneyiniz veya '0'a basarak ana menuye donunuz\n");
                }
                else
                {
                    if (b == 0)
                    {
                        printf("Bu numaraya ait fatura daha once odenmistir...\n");
                        sleep(1);
                        ana_menu(i, index);
                    }
                    fatura = rand() % 200 + 50;
                    printf("%s numarali faturanin %d TL odemesi bulunmaktadir\n1.Ode\n2.Ana menuye don\n", faturano, fatura);
                    while (1)
                    {
                        scanf("%d", &secim);
                        if (secim == 1)
                        {
                            if (kayitliparalar[i] < fatura)
                            {
                                printf("Belirtilen islemi yapmak icin yeterli bakiyeniz bulunmamaktadir\n");
                                sleep(1);
                                ana_menu(i, index);
                            }
                            else
                            {
                                faturabilgileri = fopen("faturabilgileri.txt", "a");
                                printf("Odeme isleminiz gerceklestiriliyor...\n");
                                kayitliparalar[i] -= fatura;
                                fprintf(faturabilgileri, "%s\n", faturano);
                                fclose(faturabilgileri);
                                sleep(1);
                                printf("Odeme isleminiz basariyla gerceklesmistir.\n");
                                sleep(1);
                                ana_menu(i, index);
                            }
                        }
                        else if (secim == 2)
                        {
                            ana_menu(i, index);
                        }
                        else
                        {
                            printf("Lutfen belirtilen araliklarda bir secim yapiniz\n");
                        }
                    }
                }
            }
        }
        else if (islem == 3)
        {
            ana_menu(i, index);
        }
        else
        {
            printf("Lutfen belirtilen araliklarda bir secim yapiniz\n");
        }
    }
}

void sigorta_islem(int i, int index)
{
    k = 0;
    sigortabilgileri = fopen("sigortabilgileri.txt", "a");
    fclose(sigortabilgileri);
    sigortabilgileri = fopen("sigortabilgileri.txt", "r");
    while (!feof(sigortabilgileri))
    {
        fscanf(sigortabilgileri, "%s", &kayitlisigortalar[k]);
        k++;
    }
    fclose(sigortabilgileri);
    printf("\n1.Arac Sigortasi\n2.Konut Sigortasi\n3.Saglik Sigortasi\n4.Ana Menu\n");
    while (1)
    {
        scanf("%d", &secim);
        if (secim == 1)
        {
            printf("Lutfen arac plakanizi birlesik sekilde giriniz.Ana Menuye donmek icin '0'a basiniz...\n");
            while (1)
            {
                scanf("%s", &arac_sigorta);
                strupr(arac_sigorta);
                x = strlen(arac_sigorta) - 1;
                for (j = 0; j < k; j++)
                {
                    if (strcmp(kayitlisigortalar[j], arac_sigorta) == 0)
                    {
                        printf("Bu plakali araca ait zaten bir sigorta bulunmaktadir.\n");
                        sleep(2);
                        ana_menu(i, index);
                    }
                }

                if (arac_sigorta[0] == '0' && strlen(arac_sigorta) == 1)
                {
                    ana_menu(i, index);
                }

                else
                {
                    if (strlen(arac_sigorta) < 5)
                    {
                        printf("Arac plakasinin minimum uzunlugu 5 karakterdir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if (!(arac_sigorta[0] >= '0' && arac_sigorta[0] <= '9') || !(arac_sigorta[1] >= '0' && arac_sigorta[1] <= '9'))
                    {
                        printf("Plakanizin ilk 2 karakteri il kodu olan sayiyi icermelidir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if ((arac_sigorta[2] >= '0' && arac_sigorta[2] <= '9') || (arac_sigorta[0] > '8') || (arac_sigorta[0] == '8' && arac_sigorta[1] > '1'))
                    {
                        printf("Il kodu maksimum '81' olmadlidir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if (!(arac_sigorta[x] >= '0' && arac_sigorta[x] <= '9') || !(arac_sigorta[x - 1] >= '0' && arac_sigorta[x - 1] <= '9'))
                    {
                        printf("Plakanin son 2 kisminda bir harf bulunamaz.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if ((arac_sigorta[5] >= 'a' && arac_sigorta[5] <= 'z') || (arac_sigorta[5] >= 'A' && arac_sigorta[5] <= 'Z'))
                    {
                        printf("Plakanizin harf kismi 3'ten uzun olmamalidir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if ((arac_sigorta[x - 1] >= 'a' && arac_sigorta[x - 1] <= 'z') || (arac_sigorta[x - 1] >= 'A' && arac_sigorta[x - 1] <= 'Z'))
                    {
                        printf("Plakanizin sayi kismi minimum '10' olabilir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if ((arac_sigorta[x - 4] >= '0' && arac_sigorta[x - 4] <= '9') && strlen(arac_sigorta) > 6)
                    {
                        printf("Plakanizin sayi kismi maksimum '9999' olabilir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else if (strlen(arac_sigorta) > 9)
                    {
                        printf("Arac plakasinin maksimum uzunlugu 9 karakterdir.Tekrar deneyin veya ana menuye donmek icin '0'a basiniz...\n");
                    }
                    else
                    {
                        fatura = rand() % 500 + 500;
                        printf("Aracinizin 1 yillik sigortasi icin odemeniz gereken tutar: %dTL 'dir\n1.Ode\n2.Ana Menuye Don\n");
                        while (1)
                        {
                            scanf("%d", &islem);
                            if (islem == 1)
                            {
                                if (kayitliparalar[i] < fatura)
                                {
                                    printf("Bu islemi yapmak icin yeterli bakiyeniz bulunmamaktadir.\n");
                                    sleep(2);
                                    ana_menu(i, index);
                                }
                                else
                                {
                                    printf("Isleminiz gerceklestiriliyor...\n");
                                    sigortabilgileri = fopen("sigortabilgileri.txt", "a");
                                    kayitliparalar[i] -= fatura;
                                    fprintf(sigortabilgileri, "%s\n", arac_sigorta);
                                    fclose(sigortabilgileri);
                                    sleep(1);
                                    printf("Isleminiz basariyla gerceklestirilmistir.\n");
                                    sleep(1);
                                    ana_menu(i, index);
                                }
                            }
                            else if (islem == 2)
                            {
                                ana_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                            }
                        }
                    }
                }
            }
        }
        else if (secim == 2)
        {
            printf("Lutfen sigortalatmak istediginiz konutun bulundugu ilceyi giriniz.Ana Menuye donmek icin '0'a basiniz...\n");
            scanf("%s", &ev_ilce_sigorta);
            if (ev_ilce_sigorta[0] == '0' && strlen(ev_ilce_sigorta) == 1)
            {
                ana_menu(i, index);
            }
            printf("Lutfen sigortalatmak istediginiz konutun bulundugu mahalleyi giriniz.Ana Menuye donmek icin '0'a basiniz...\n");
            scanf("%s", &ev_mahalle_sigorta);
            strupr(ev_ilce_sigorta);
            strupr(ev_mahalle_sigorta);
            strcat(ev_ilce_sigorta, ev_mahalle_sigorta);
            for (j = 0; j < k; j++)
            {
                if (strcmp(kayitlisigortalar[j], ev_ilce_sigorta) == 0)
                {
                    printf("Bu adrese ait zaten bir sigorta bulunmaktadir.\n");
                    sleep(2);
                    ana_menu(i, index);
                }
            }
            if (ev_mahalle_sigorta[0] == '0' && strlen(ev_mahalle_sigorta) == 1)
            {
                ana_menu(i, index);
            }
            else
            {
                fatura = rand() % 500 + 500;
                printf("Konutunuzun 1 yillik sigortasi icin odemeniz gereken tutar: %dTL 'dir\n1.Ode\n2.Ana Menuye Don\n");
                while (1)
                {
                    scanf("%d", &islem);
                    if (islem == 1)
                    {
                        if (kayitliparalar[i] < fatura)
                        {
                            printf("Bu islemi yapmak icin yeterli bakiyeniz bulunmamaktadir.\n");
                            sleep(2);
                            ana_menu(i, index);
                        }
                        else
                        {
                            printf("Isleminiz gerceklestiriliyor...\n");
                            sigortabilgileri = fopen("sigortabilgileri.txt", "a");
                            kayitliparalar[i] -= fatura;
                            fprintf(sigortabilgileri, "%s\n", ev_ilce_sigorta);
                            fclose(sigortabilgileri);
                            sleep(1);
                            printf("Isleminiz basariyla gerceklestirilmistir.\n");
                            sleep(1);
                            ana_menu(i, index);
                        }
                    }
                    else if (islem == 2)
                    {
                        ana_menu(i, index);
                    }
                    else
                    {
                        printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                    }
                }
            }
        }
        else if (secim == 3)
        {
            printf("Lutfen sigortalatmak icin TCKN numaranizi giriniz.Ana Menuye donmek icin '0'a basiniz...\n");
            while (1)
            {
                a = 1;
                scanf("%s", &saglik_sigorta);
                for (j = 0; j < k; j++)
                {
                    if (strcmp(kayitlisigortalar[j], saglik_sigorta) == 0)
                    {
                        printf("Bu adrese ait zaten bir sigorta bulunmaktadir.\n");
                        sleep(2);
                        ana_menu(i, index);
                    }
                }
                if (saglik_sigorta[0] == '0' && strlen(saglik_sigorta) == 1)
                {
                    ana_menu(i, index);
                }
                else if (strlen(saglik_sigorta) != 11)
                {
                    printf("TCKN'si 11 karakter uzunlugunda olmalidir.Tekrar deneyiniz veya ana menuye donmek icin '0'a basiniz\n");
                }
                else if (!(saglik_sigorta[0] >= '0' && saglik_sigorta[0] <= '9') || !(saglik_sigorta[1] >= '0' && saglik_sigorta[1] <= '9') || !(saglik_sigorta[2] >= '0' && saglik_sigorta[2] <= '9') || !(saglik_sigorta[3] >= '0' && saglik_sigorta[3] <= '9') || !(saglik_sigorta[4] >= '0' && saglik_sigorta[4] <= '9') || !(saglik_sigorta[5] >= '0' && saglik_sigorta[5] <= '9') || !(saglik_sigorta[6] >= '0' && saglik_sigorta[6] <= '9') || !(saglik_sigorta[7] >= '0' && saglik_sigorta[7] <= '9') || !(saglik_sigorta[8] >= '0' && saglik_sigorta[8] <= '9') || !(saglik_sigorta[9] >= '0' && saglik_sigorta[9] <= '9') || !(saglik_sigorta[10] >= '0' && saglik_sigorta[10] <= '9'))
                {
                    printf("TCKN sadece rakamlardan olusmaktadir.Tekrar deneyiniz veya ana menuye donmek icin '0'a basiniz\n");
                }
                else
                {
                    fatura = rand() % 500 + 500;
                    printf("1 yillik saglik sigortasi icin odemeniz gereken tutar: %dTL 'dir\n1.Ode\n2.Ana Menuye Don\n");
                    while (1)
                    {
                        scanf("%d", &islem);
                        if (islem == 1)
                        {
                            if (kayitliparalar[i] < fatura)
                            {
                                printf("Bu islemi yapmak icin yeterli bakiyeniz bulunmamaktadir.\n");
                                sleep(2);
                                ana_menu(i, index);
                            }
                            else
                            {
                                printf("Isleminiz gerceklestiriliyor...\n");
                                sigortabilgileri = fopen("sigortabilgileri.txt", "a");
                                kayitliparalar[i] -= fatura;
                                fprintf(sigortabilgileri, "%s\n", saglik_sigorta);
                                fclose(sigortabilgileri);
                                sleep(1);
                                printf("Isleminiz basariyla gerceklestirilmistir.\n");
                                sleep(1);
                                ana_menu(i, index);
                            }
                        }
                        else if (islem == 2)
                        {
                            ana_menu(i, index);
                        }
                        else
                        {
                            printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                        }
                    }
                }
            }
        }
        else if (secim == 4)
        {
            ana_menu(i, index);
        }
        else
        {
            printf("Lutfen belirtilen araliklarda bir secim yapiniz\n");
        }
    }
}

void borsa_degistir()
{
    x = rand() % 5;
    y = rand() % 2;
    if (y == 0)
    {
        yatirimdeger -= yatirimmiktar[x];
    }
    else if (y == 1)
    {
        yatirimdeger += yatirimmiktar[x];
    }
    yatirimbilgileri = fopen("yatirim.txt", "w");
    fprintf(yatirimbilgileri, "%f", yatirimdeger);
    fclose(yatirimbilgileri);
}

void ana_menu(int i, int index)
{
    printf("Ana menuye donuluyor...\n\n");
    sleep(1);
    borsa_degistir();
    dosyaya_yaz(index);
    system("CLS");
    while (1)
    {
        printf("Mevcut Bakiyeniz: %.1fTL\n", kayitliparalar[i]);
        printf("Guncel Borcunuz: %.1fTL\n", kayitliborclar[i]);
        printf("Dolar: %.1f Euro: %.1f\n", kayitlidolar[i], kayitlieuro[i]);
        printf("Borsa LOT adet:%d Borsa Degeri: %.2f\n\n", kayitliyatirim[i], (kayitliyatirim[i] * yatirimdeger));
        printf("Lutfen Yapmak istediginiz islemi seciniz\n1.Para Yatirma/Cekme\n2.Para Gonderme\n3.Kredi Cekme\n4.Borc Odeme\n5.Doviz Islemleri\n6.Yatirim\n7.Fatura Odeme\n8.Sigorta Islemleri\n9.Cikis\n");
        scanf("%d", &islem);
        if (islem == 1)
        {
            printf("\n1.Para Yatirma\n2.Para Cekme\n3.Ana Menu\n");
            while (1)
            {
                scanf("%d", &secim);
                if (secim == 1)
                {
                    para_yatirma(i, index);
                }
                else if (secim == 2)
                {
                    if (kayitliparalar[i] <= 0)
                    {
                        printf("Bu islemi gerceklestirmek icin yeterli bakiyeniz bulunmamaktadir.\n");
                        sleep(1);
                        printf("Hesaba para yatirmak ister miydiniz?\n1.Evet\n2.Hayir\n");
                        while (1)
                        {
                            scanf("%d", &x);
                            if (x == 1)
                            {
                                printf("Para yatirma islemine yonlendiriliyorsunuz...\n");
                                sleep(1);
                                para_yatirma(i, index);
                            }
                            else if (x == 2)
                            {
                                ana_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                            }
                        }
                    }
                    else
                    {
                        para_cekme(i, index);
                    }
                }
                else if (secim == 3)
                {
                    ana_menu(i, index);
                }
                else
                {
                    printf("Lutfen belirtilen aralikta bir secim yapiniz\n");
                }
            }
        }
        else if (islem == 2)
        {
            para_gonderme(i, index);
        }

        else if (islem == 3)
        {
            kredi_cekme(i, index);
        }
        else if (islem == 4)
        {
            if (kayitliborclar[i] == 0)
            {
                printf("Borcunuz bulunmamaktadir.\n\n");
                sleep(1);
                printf("Avantajli faiz oranlariyla ihtiyac kredisi cekmek ister miydiniz?\n1.Evet\n2.Hayir\n");
                while (1)
                {
                    scanf("%d", &x);
                    if (x == 1)
                    {
                        printf("Kredi cekme islemine yonlendiriliyorsunuz...\n");
                        sleep(1);
                        kredi_cekme(i, index);
                    }
                    else if (x == 2)
                    {
                        ana_menu(i, index);
                    }
                    else
                    {
                        printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                    }
                }
            }
            else
            {
                borc_odeme(i, index);
            }
        }
        else if (islem == 5)
        {
            printf("\n1.Doviz Al\n2.Doviz Sat\n3.Ana Menu\n");
            while (1)
            {
                scanf("%d", &secim);
                if (secim == 1)
                {
                    printf("\n1.Dolar: 6.97\n2.Euro: 7.83\nHangi para birimiyle islem yapmak istiyorsunuz?\nIslemden cikmak icin '9'a basiniz\n");
                    doviz_al(i, index);
                }
                else if (secim == 2)
                {
                    if (kayitlidolar[i] == 0 && kayitlieuro[i] == 0)
                    {
                        printf("Doviziniz bulunmamaktadir.\n");
                        sleep(1);
                        printf("Doviz satin almak ister miydiniz?\n1.Evet\n2.Hayir\n");
                        while (1)
                        {
                            scanf("%d", &x);
                            if (x == 1)
                            {
                                printf("Doviz alma islemine yonlendiriliyorsunuz...\n");
                                sleep(1);
                                doviz_al(i, index);
                            }
                            else if (x == 2)
                            {
                                ana_menu(i, index);
                            }
                            else
                            {
                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                            }
                        }
                    }

                    else
                    {
                        doviz_sat(i, index);
                    }
                }
                else if (secim == 3)
                {
                    ana_menu(i, index);
                }
                else
                {
                    printf("Lutfen belirtilen aralikta bir secim yapiniz\n");
                }
            }
        }
        else if (islem == 6)
        {
            yatirim(i, index);
        }
        else if (islem == 7)
        {
            fatura_odeme(i, index);
        }
        else if (islem == 8)
        {
            sigorta_islem(i, index);
        }
        else if (islem == 9)
        {
            printf("Bizi tercih ettiginiz icin tesekkurler.\nIyi Gunler Dileriz...\n");
            break;
        }
        else
        {
            printf("Lutfen gecerli bir tuslama yapiniz.\n\n");
        }
    }
}

void kayit_sil()
{
    int index = 0;
    a = 1;
    if ((bilgiler = fopen("bilgiler.txt", "r")) != NULL)
    {
        bilgiler = fopen("bilgiler.txt", "r");
        while (!feof(bilgiler))
        {
            fscanf(bilgiler, "%s %d %f %f %f %f %d %d", &kayitlikullanicilar[index], &kayitlisifreler[index], &kayitliparalar[index], &kayitliborclar[index], &kayitlidolar[index], &kayitlieuro[index], &kayitliyatirim[index], &kayitlihesapno[index]);
            index++;
        }
        printf("Silmek istediginiz hesabin ismini ve soyismini giriniz:\n");
        scanf("%s%s", &girisismi, &girissoyismi);
        printf("Silmek istediginiz hesabin sifresini giriniz\n");
        scanf("%d", &girissifresi);
        strcat(girisismi, girissoyismi);
        strupr(girisismi);
        strupr(girissoyismi);
        for (i = 0; i < index - 1; i++)
        {
            if ((strcmp(girisismi, kayitlikullanicilar[i]) == 0) && girissifresi == kayitlisifreler[i])
            {
                k = strlen(kayitlikullanicilar[i]);
                for (j = 0; j < k; j++)
                {
                    kayitlikullanicilar[i][j] = '0';
                }
                kayitlisifreler[i] = 0;
                kayitliborclar[i] = 0;
                kayitlidolar[i] = 0;
                kayitlieuro[i] = 0;
                kayitlihesapno[i] = 0;
                kayitliparalar[i] = 0;
                kayitliyatirim[i] = 0;
                a = 0;
                dosyaya_yaz(index);
                printf("Silme islemi gerceklestirilmistir.Ana menuye donuluyor...\n\n");
                sleep(2);
                main();
            }
        }
        if (a == 1)
        {
            printf("Boyle bir hesap bulunamadi!\n1.Tekrar Dene\n2.Ana Menuye Don\n");
            while (1)
            {
                scanf("%d", &islem);
                if (islem == 1)
                {
                    kayit_sil();
                }
                else if (islem == 2)
                {
                    printf("Ana menuye donuluyor...\n\n");
                    sleep(1);
                    main();
                }
                else
                {
                    printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                }
            }
        }
    }
    else
    {
        printf("Silinecek herhangi bir hesap bulunmamaktadir.\n\n");
        sleep(1);
        main();
    }
}

void giris_yap()
{
    int index = 0;
    yatirimbilgileri = fopen("yatirim.txt", "r");
    fscanf(yatirimbilgileri, "%f", &yatirimdeger);
    fclose(yatirimbilgileri);
    if ((bilgiler = fopen("bilgiler.txt", "r")) != NULL)
    {
        bilgiler = fopen("bilgiler.txt", "r");
        while (!feof(bilgiler))
        {
            fscanf(bilgiler, "%s %d %f %f %f %f %d %d", &kayitlikullanicilar[index], &kayitlisifreler[index], &kayitliparalar[index], &kayitliborclar[index], &kayitlidolar[index], &kayitlieuro[index], &kayitliyatirim[index], &kayitlihesapno[index]);
            index++;
        }
        do
        {
            printf("Isminizi ve soyisminizi giriniz:\n");
            scanf("%s%s", &girisismi, &girissoyismi);
            printf("Sifrenizi giriniz:\n");
            scanf("%d", &girissifresi);
            strcat(girisismi, girissoyismi);
            strupr(girisismi);
            strupr(girissoyismi);
            for (i = 0; i < index - 1; i++)
            {
                if ((strcmp(girisismi, kayitlikullanicilar[i]) == 0) && girissifresi == kayitlisifreler[i])
                {
                    printf("Giris Onaylandi\nHOSGELDINIZ...\n\n");
                    a = 0;
                    while (1)
                    {
                        printf("Mevcut Bakiyeniz: %.1fTL\n", kayitliparalar[i]);
                        printf("Guncel Borcunuz: %.1fTL\n", kayitliborclar[i]);
                        printf("Dolar: %.1f Euro: %.1f\n", kayitlidolar[i], kayitlieuro[i]);
                        printf("Borsa LOT adet:%d Borsa Degeri: %.2f\n\n", kayitliyatirim[i], (kayitliyatirim[i] * yatirimdeger));
                        printf("Lutfen Yapmak istediginiz islemi seciniz\n1.Para Yatirma/Cekme\n2.Para Gonderme\n3.Kredi Cekme\n4.Borc Odeme\n5.Doviz Islemleri\n6.Yatirim\n7.Fatura Odeme\n8.Sigorta Islemleri\n9.Cikis\n");
                        scanf("%d", &islem);
                        if (islem == 1)
                        {
                            printf("\n1.Para Yatirma\n2.Para Cekme\n3.Ana Menu\n");
                            while (1)
                            {
                                scanf("%d", &secim);
                                if (secim == 1)
                                {
                                    para_yatirma(i, index);
                                }
                                else if (secim == 2)
                                {
                                    if (kayitliparalar[i] <= 0)
                                    {
                                        printf("Bu islemi gerceklestirmek icin yeterli bakiyeniz bulunmamaktadir.\n");
                                        sleep(1);
                                        printf("Hesaba para yatirmak ister miydiniz?\n1.Evet\n2.Hayir\n");
                                        while (1)
                                        {
                                            scanf("%d", &x);
                                            if (x == 1)
                                            {
                                                printf("Para yatirma islemine yonlendiriliyorsunuz...\n");
                                                sleep(1);
                                                para_yatirma(i, index);
                                            }
                                            else if (x == 2)
                                            {
                                                ana_menu(i, index);
                                            }
                                            else
                                            {
                                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        para_cekme(i, index);
                                    }
                                }
                                else if (secim == 3)
                                {
                                    ana_menu(i, index);
                                }
                                else
                                {
                                    printf("Lutfen belirtilen aralikta bir secim yapiniz\n");
                                }
                            }
                        }
                        else if (islem == 2)
                        {
                            para_gonderme(i, index);
                        }

                        else if (islem == 3)
                        {
                            kredi_cekme(i, index);
                        }
                        else if (islem == 4)
                        {
                            if (kayitliborclar[i] == 0)
                            {
                                printf("Borcunuz bulunmamaktadir.\n\n");
                                sleep(1);
                                printf("Avantajli faiz oranlariyla ihtiyac kredisi cekmek ister miydiniz?\n1.Evet\n2.Hayir\n");
                                while (1)
                                {
                                    scanf("%d", &x);
                                    if (x == 1)
                                    {
                                        printf("Kredi cekme islemine yonlendiriliyorsunuz...\n");
                                        sleep(1);
                                        kredi_cekme(i, index);
                                    }
                                    else if (x == 2)
                                    {
                                        ana_menu(i, index);
                                    }
                                    else
                                    {
                                        printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                                    }
                                }
                            }
                            else
                            {
                                borc_odeme(i, index);
                            }
                        }
                        else if (islem == 5)
                        {
                            printf("\n1.Doviz Al\n2.Doviz Sat\n3.Ana Menu\n");
                            while (1)
                            {
                                scanf("%d", &secim);
                                if (secim == 1)
                                {
                                    printf("\n1.Dolar: 6.97\n2.Euro: 7.83\nHangi para birimiyle islem yapmak istiyorsunuz?\nIslemden cikmak icin '9'a basiniz\n");
                                    doviz_al(i, index);
                                }
                                else if (secim == 2)
                                {
                                    if (kayitlidolar[i] == 0 && kayitlieuro[i] == 0)
                                    {
                                        printf("Doviziniz bulunmamaktadir.\n");
                                        sleep(1);
                                        printf("Doviz satin almak ister miydiniz?\n1.Evet\n2.Hayir\n");
                                        while (1)
                                        {
                                            scanf("%d", &x);
                                            if (x == 1)
                                            {
                                                printf("Doviz alma islemine yonlendiriliyorsunuz...\n");
                                                sleep(1);
                                                doviz_al(i, index);
                                            }
                                            else if (x == 2)
                                            {
                                                ana_menu(i, index);
                                            }
                                            else
                                            {
                                                printf("Lutfen belirtilen araliklarda bir deger giriniz\n");
                                            }
                                        }
                                    }

                                    else
                                    {
                                        doviz_sat(i, index);
                                    }
                                }
                                else if (secim == 3)
                                {
                                    ana_menu(i, index);
                                }
                                else
                                {
                                    printf("Lutfen belirtilen aralikta bir secim yapiniz\n");
                                }
                            }
                        }
                        else if (islem == 6)
                        {
                            yatirim(i, index);
                        }
                        else if (islem == 7)
                        {
                            fatura_odeme(i, index);
                        }
                        else if (islem == 8)
                        {
                            sigorta_islem(i, index);
                        }
                        else if (islem == 9)
                        {
                            printf("Bizi tercih ettiginiz icin tesekkurler.\nIyi Gunler Dileriz...\n");
                            sleep(1);
                            printf("Ana menuye donuluyor...\n\n");
                            sleep(1);
                            main();
                        }
                        else
                        {
                            printf("Lutfen gecerli bir tuslama yapiniz.\n\n");
                        }
                    }
                }
            }

            if (a == 1)
            {
                printf("Boyle bir banka hesabi bulunamadi\n0.Ana Menuye Don\n1.Tekrar Dene\n");
                while (1)
                {
                    scanf("%d", &secim);
                    if (secim == 0)
                    {
                        printf("Ana menuye donuluyor...\n\n");
                        sleep(1);
                        main();
                    }
                    else if (secim == 1)
                    {
                        break;
                    }
                    else
                    {
                        printf("Lutfen belirtilen araliklarda secim yapiniz\n");
                    }
                }
            }
        } while (a == 1);
        fclose(bilgiler);
    }
    else
    {
        printf("Lutfen oncelikle kayit olunuz.\n\n");
        sleep(1);
        main();
    }
}

int main()
{
    srand(time(NULL));
    while (1)
    {
        printf("1.Kayit Ol\n2.Giris Yap\n3.Kayit Sil\n4.Cikis Yap\n");
        scanf("%d", &islem);
        if (islem == 1)
        {
            kayit_ol();
        }
        else if (islem == 2)
        {
            giris_yap();
            break;
        }
        else if (islem == 3)
        {
            kayit_sil();
        }
        else if (islem == 4)
        {
            printf("Bizi tercih ettiginiz icin tesekkurler.\nIyi Gunler Dileriz...\n");
            break;
        }
        else
        {
            printf("%s", "Hatali giris yaptiniz. Tekrardan giris yapin:\n");
        }
    }
    return 0;
}
