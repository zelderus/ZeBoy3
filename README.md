# ZeBoy 3
Hard-проект. 
Последовательное создание портативной консоли.
[Справочник-описание][lnk_help].

Цель
--------
- Изучение RaspberryPi
- Изучение основ электротехники
- Применение внешних дисплеев. Работа на самом низком уровне
- Программирование микроконтроллеров

Применяемое железо
--------
- RaspberryPi 2 (написание кода, программатор)
- Кучка транзисторов, резисторов и прочего
- LCD Nokia 5110
- Atmel ATmega32
- UT62256CPCL



Программы под RPi
----------
Лежат в папке `src_rpi`. Предназначены для запуска с RaspberryPi2. Как правило в каждом файле указано к каким пинам подключать конкретное устройство.
- 1
- 2


Программы под MK
----------
Лежат в папке `src_mk`. Предназначены для прошивки на микроконтроллер.
- mkram.asm (.hex, .bin) программа (драйвер) для МК (AT89C51RC) для работы с SRAM (UT62256CPCL)
- папка 'fastman3' содержит проект на языке C


[lnk_help]: <http://zedk.ru/ss/zeboy3/index.html>