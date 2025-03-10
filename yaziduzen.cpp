#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

std::string bosluklari_temizle(const std::string& metin) {
  std::stringstream ss(metin);
  std::string kelime;
  std::string sonuc;
  bool onceki_bosluk = false;

  while (ss >> kelime) {
    if (!sonuc.empty()) {
      sonuc += " ";
    }
    sonuc += kelime;
    onceki_bosluk = false;
  }

  // Ardışık boşlukları temizle
  std::string duzeltilmis_sonuc;
  for (size_t i = 0; i < sonuc.length(); ++i) {
    if (sonuc[i] == ' ') {
      if (!onceki_bosluk) {
        duzeltilmis_sonuc += sonuc[i];
        onceki_bosluk = true;
      }
    } else {
      duzeltilmis_sonuc += sonuc[i];
      onceki_bosluk = false;
    }
  }

  return duzeltilmis_sonuc;
}

int main() { // Başlangıç kısmı
  // Dosya sorgusu
  std::string girdi_dosya_adi, cikti_dosya_adi;
  std::cout << "Girdi dosyasinin adini girin(sadece adi yeterli): ";
  std::cin >> girdi_dosya_adi;
//std::cout << "Çikti dosyasinin adini girin(sadece adi yeterli): ";
//std::cin >> cikti_dosya_adi
  cikti_dosya_adi = "sonuc";

  std::ifstream girdi_dosyasi(girdi_dosya_adi + ".txt");
  std::ofstream cikti_dosyasi(cikti_dosya_adi + ".txt");

  // Varlık sorgu yap ve açılmadığında açılmadı de ve dosya oluştur.
  if (!girdi_dosyasi.is_open()) {
    std::cerr << "Girdi dosyasi açilamadi!" << std::endl;
    std::ofstream girdi_dosyasi(girdi_dosya_adi + ".txt");
    std::cerr << (girdi_dosya_adi);
    std::cerr << "Dosya oluşturuldu, Buraya kopyalayip tekrar çaliştirin." << std::endl;
    return 1;
  }
  // Sorgu yap ve açılmadığında açılmadı
  if (!cikti_dosyasi.is_open()) {
    std::cerr << "Çikti dosyasi açilamadi!" << std::endl; 
    return 1;
  }

  std::string tum_metin;
  std::string satir;
  while (std::getline(girdi_dosyasi, satir)) {
    tum_metin += satir + " "; // Satırları birleştir ve aralarına boşluk ekle
  }

  std::string temizlenmis_metin = bosluklari_temizle(tum_metin);
  cikti_dosyasi << temizlenmis_metin;

  girdi_dosyasi.close();
  cikti_dosyasi.close();

  std::cout << "Dosya birleştirme ve temizleme işlemi tamamlandi." << std::endl;

  return 0;
}