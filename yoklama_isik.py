from mfrc522 import MFRC522
import utime
from machine import Pin, PWM, ADC
from time import sleep
import time

# LED ve LDR pin tanımları
d_led = Pin(12, Pin.OUT)  # Yeşil LED
d_led1 = Pin(13, Pin.OUT)  # Kırmızı LED

ldr = ADC(26)  # GP26 (ADC0)
led = Pin(16, Pin.OUT)

# Servo motor tanımları
servo = PWM(Pin(15))
servo.freq(50)

# Işık eşiği
LIGHT_THRESHOLD = 20000

# Kayıtlı kartların tutulacağı liste
registered_cards = []

#Yoklaması alınan kartların tutulacağı liste
head_count = []

def uidToString(uid):
    mystring = ""
    for i in uid:
        mystring = "%02X" % i + mystring
    return mystring

rc522 = MFRC522(spi_id=0, sck=6, miso=4, mosi=7, cs=5, rst=22)

print("")
print("KART KAYIT MODU:")
print("Lütfen yeni kart okutunuz veya 'q' yazarak çıkınız.")
print("")

def set_angle(angle):
    duty = int(2040 + (angle / 180) * 820)
    servo.duty_u16(duty)

# Kayıt modu
while True:
    # Kullanıcı çıkış yapmak isterse
    exit_choice = input("Yeni kayıt yapamak istiyor musunuz? (e/h): ").lower()
    if exit_choice == "h":
        print("Kayıtlar kapanmıştır.")
        break

    # RFID kart okutma
    (stat, tag_type) = rc522.request(rc522.REQALL)
    if stat == rc522.OK:
        (status, raw_uid) = rc522.SelectTagSN()
        if stat == rc522.OK:
            rfid_data = "{:02x}{:02x}{:02x}{:02x}".format(raw_uid[0], raw_uid[1], raw_uid[2], raw_uid[3])
            print("Kart ID: {}".format(rfid_data))

            if rfid_data in registered_cards:
                print("Bu kart zaten kayıtlı.")
                d_led1.on()
                utime.sleep_ms(500)
                d_led1.off()
            else:
                registered_cards.append(rfid_data)
                print("Kart başarıyla kaydedildi!")
                d_led.on()  # Yeşil ışık yanar
                utime.sleep_ms(500)
                d_led.off()

print("\nKapı kontrol moduna geçiliyor...\n")

start_time = time.time()
timeout_duration = 60  # 60 saniye sonra çıkış

# Kapı ve ışık kontrolü
while True:
    # Zaman kontrolü
    if time.time() - start_time > timeout_duration:
        print("Süre doldu, döngü sonlandırılıyor...")
        break
    
    # LDR değerini oku ve ışık kontrolü yap
    ldr_value = ldr.read_u16()
    print("LDR Değeri:", ldr_value)
    print("")
    utime.sleep(1)

    if ldr_value < LIGHT_THRESHOLD:
        led.value(1)
        print("IŞIK AÇIK")
        print("")
    else:
        led.value(0)
        print("IŞIK KAPALI")
        print("")
    
    # RFID kartını kontrol et
    (stat, tag_type) = rc522.request(rc522.REQALL)
    if stat == rc522.OK:
        (status, raw_uid) = rc522.SelectTagSN()
        if stat == rc522.OK:
            rfid_data = "{:02x}{:02x}{:02x}{:02x}".format(raw_uid[0], raw_uid[1], raw_uid[2], raw_uid[3])
            print("Kart ID: {}".format(rfid_data))

            if rfid_data in registered_cards:
                if rfid_data in head_count:
                    print("Bu kartın yoklaması alınmış")
                    d_led1.on()
                    utime.sleep_ms(500)
                    d_led1.off()
                else:
                    # Kayıtlı kart: Kapıyı aç ve yeşil ışık yak
                    d_led.on()
                    set_angle(700)  # Kapıyı aç
                    sleep(1)
                    print("KAPI AÇILDI")
                    print("")
                    utime.sleep_ms(500)
                
                    for angle in range(90, -1, -15): 
                        set_angle(angle)
                        sleep(0.05) 
                    sleep(0.50)
                    print("KAPI KAPANDI")
                    print("")
                    d_led.off()
                
                    #Kartı yoklama listesine al
                    head_count.append(rfid_data)
            else:
                # Kayıtlı olmayan kart: Kırmızı ışık yak
                print("Bu kart kayıtlı değil.")
                d_led1.on()
                utime.sleep_ms(500)
                d_led1.off()
                

print("Kayıtlı kartlar:", registered_cards)
print("Yoklaması olan kartlar:", head_count)
