# ClassHub-4.0
ClassHub 4.0, Raspberry Pi tabanlı bir akıllı sınıf yönetim sistemidir. Bu sistem, sınıf içindeki cihazları otomatikleştirmek ve öğretmenlerin ders yönetimini kolaylaştırmak için tasarlanmıştır.

Özellikler 
 - RFID modülü ile yoklama takibi: Öğrenciler, RFID kartlarını okutarak yoklamalarını alabilir.
 - Kapı kilidi kontrolü: Servo motor kullanılarak kapı otomatik olarak kilitlenip açılır.
 - Işık kontrolü: LDR sensörü ile ortam ışığına göre aydınlatma otomatik kontrol edilir.
 - Web tabanlı arayüz: ESP8266 ile bir web sunucusu üzerinden:
 - Yoklama verilerini görüntüleyin.
 - Kapı ve ışık kontrolü sağlayın.
 - Dinamik ders saati ayarı: Kapı, öğretmenin gelişiyle otomatik olarak kilitlenir.

Gereksinimler
Donanım:
 - Raspberry Pi Pico
 - RFID modülü
 - ESP8266 Wi-Fi modülü
 - Servo motor
 - LDR sensörü ve dirençler
Yazılım:
 - MicroPython (Thonny IDE'de yazılmıştır)
 - Arduino IDE

Kurulum 
1. Donanım Bağlantıları
Bağlantıları aşağıdaki gibi yapın:
 - RFID modülü: GPIO pinlerine bağlayın.
 - Servo motor: Kapı mekanizmasına bağlanacak şekilde yerleştirin.
 - LDR sensörü: Ortam ışığını ölçmek için uygun bir konuma yerleştirin.
 - ESP8266: Wi-Fi bağlantısı için Pico'ya bağlayın.

2. Yazılım Yükleme
 - Thonny IDE'yi kullanarak yoklama_isik.py dosyasını Raspberry Pi Pico'ya yükleyin.
 - Arduino IDE ile kapi_isik_kontrol.ino dosyalarını ilgili cihazlara yükleyin.

3. Çalıştırma
 - Sistemi güç kaynağına bağlayın.
 - Web arayüzü üzerinden kontrolleri sağlayın.

Kullanım 
RFID ile Yoklama:
 - Öğrenciler kartlarını okutur.
 - Yoklama bilgileri web arayüzünde görüntülenir.
Kapı Kontrolü:
 - Kapı, öğretmenin gelmesinden 10 dakika sonra otomatik olarak kilitlenir.
 - Manuel kontrol web arayüzünden yapılabilir.
Işık Kontrolü:
 - Ortam ışığı düşükse ışıklar otomatik olarak açılır.

Proje Yapısı 

ClassHub-4.0/

├── yoklama_isik.py          # MicroPython kodu (Pico için)

└── kapi_isik_kontrol.ino    # ESP8266 kodu
