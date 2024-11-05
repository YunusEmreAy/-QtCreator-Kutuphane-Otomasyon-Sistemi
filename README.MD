# Kütüphane Otomasyon Sistemi

Bu proje, **C++** dilinde **Qt Creator** kullanılarak geliştirilmiş bir Kütüphane Otomasyon Sistemi'dir. Sistem, kütüphane üyelerini, kitapları ve ödünç alma/teslim etme işlemlerini yönetmek için tasarlanmıştır ve veri tabanı entegrasyonu içerir.

## Özellikler

### 1. Üye İşlemleri
- **Yeni Üye Ekleme**: Kullanıcılar, sisteme yeni üyeler ekleyebilir. Üye ekleme işlemi sırasında, gerekli bilgilerin eksik olması durumunda kullanıcıya uyarı verilir. Başarılı bir ekleme sonrası, üye listesi güncellenir.
- **Üye Bilgilerini Güncelleme**: Mevcut bir üyenin bilgileri güncellenebilir ve değişiklikler anında listede görüntülenir.
- **Üye Silme**: Bir üye, ödünç aldığı ve henüz iade etmediği kitap olmadığı sürece silinebilir. Silme işlemi başarılı olduğunda üye listesi güncellenir.

### 2. Kitap İşlemleri
- **Yeni Kitap Ekleme**: Kullanıcılar, veri tabanına yeni kitaplar ekleyebilir. Ekleme işlemi sırasında, boş bırakılan alanlar kontrol edilir ve kullanıcıya uyarı verilir. Kitap ekleme sonrası, kitap listesi güncellenir.
- **Kitap Bilgilerini Güncelleme**: Mevcut bir kitabın bilgileri güncellenebilir ve güncel liste anında görüntülenir.
- **Kitap Silme**: Kitap, ödünçte değilse silinebilir. Kitap silme işlemi başarılı olduğunda liste güncellenir.

### 3. Ödünç Alma İşlemleri
- **Kitap Ödünç Verme**: Kullanıcılar, üyelerin kitapları ödünç almasını sağlayabilir. Ödünç alma işlemi sırasında, üyeye aynı kitabın tekrar verilmemesi ve kitabın kütüphane stoğunda bulunup bulunmadığı kontrol edilir. Eğer kitap stoğu tükenmişse ödünç verilemez.
- **Stok Kontrolü**: Kitabın kütüphanede mevcut olup olmadığını kontrol ederek işlemlerin sorunsuz yapılmasını sağlar.

### 4. Ödünç Teslim Etme İşlemleri
- **Kitap Teslim Alma**: Ödünç alınan kitaplar, teslim edildiklerinde kaydedilir. Teslim tarihi girilir ve bu bilgi veri tabanına eklenir. Teslim edilen kitap, ödünç alınanlar listesinden çıkarılır.
- **Gecikme Ücreti Hesaplama**: Kitap, 15 gün içinde teslim edilmezse, gecikilen her gün için 2 TL ceza uygulanır. Bu ceza tutarı otomatik olarak hesaplanır ve teslim edilen kitaplar tablosuna kaydedilir.

## Kullanılan Teknolojiler ve Yapı
Sistem, **Qt Creator** ile geliştirilmiştir ve aşağıdaki bileşenleri içerir:

### Veri Tabanı Yapısı
- **Üyeler Tablosu**: Üye bilgilerini (numara, ad, soyad) tutar.
- **Kitaplar Tablosu**: Kitap bilgilerini (numara, ad, sayısı) içerir.
- **Ödünç Alınan Kitaplar Tablosu**: Ödünç alınan kitapların bilgilerini (üye numarası, kitap numarası, ödünç alma tarihi) tutar.
- **Teslim Edilen Kitaplar Tablosu**: Teslim edilen kitapların bilgilerini (üye numarası, kitap numarası, alış tarihi, teslim tarihi, borç) kaydeder.

### Proje Dosya Yapısı
- **main.cpp**: Uygulamanın başlangıç noktası.
- **mainwindow.cpp & mainwindow.h**: Ana pencere işlevlerini ve arayüz bileşenlerini içerir.
- **kitapislemleri.cpp**: Kitap işlemlerine dair mantık ve fonksiyonlar burada yer alır.
- **uyeislemleri.cpp**: Üye işlemleriyle ilgili tüm operasyonlar bu dosyada tanımlanmıştır.
- **oduncalmaislemleri.cpp**: Kitap ödünç alma işlemlerini yönetir.
- **oduncteslimetmeislemleri.cpp**: Kitap teslim işlemleri ve borç hesaplama işlemlerini içerir.
- **mainwindow.ui**: Kullanıcı arayüzünün görsel düzeni Qt Creator'da tasarlanmıştır.

## Kurulum ve Çalıştırma
1. Qt Creator'da Aç: 
   Qt Creator'ı başlatın ve proje dosyasını açın.

2. Veri Tabanını Ayarla: 
   Veri tabanı dosyasının, kodda belirtilen konumda olduğundan emin olun.

3. Projeyi Derleyip Çalıştır: 
   Projeyi derleyin ve çalıştırarak kütüphane sistemini kullanmaya başlayın.

## Gereksinimler
- Qt Creator (Güncel sürüm)
- C++ Derleyici
- SQLite (Veri tabanı için önerilir)

