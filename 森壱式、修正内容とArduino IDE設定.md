

## 対象Hardware

Plain Text

	Forest Design 森壱式

	ESP32-S3-WROOM-1

	Flash : 8MB

	PSRAM : 8MB Octal

	USB-UART : CP2102N
	
## Arduino IDE ボード設定

Plain Text

	Board
	ESP32S3 Dev Module

	Port
	Silicon Labs CP210x USB to UART Bridge
	※ COM番号はPCによって変わる

	USB CDC On Boot
	Disabled

	CPU Frequency
	240MHz (WiFi)

	Core Debug Level
	None

	USB DFU On Boot
	Disabled

	Erase All Flash Before Sketch Upload
	Disabled

	Events Run On
	Core 1

	Flash Mode
	QIO 80MHz

	Flash Size
	8MB (64Mb)

	JTAG Adapter
	Integrated USB JTAG

	Arduino Runs On
	Core 1

	USB Firmware MSC On Boot
	Disabled

	Partition Scheme
	Default 4MB with spiffs

	※ 現在の動作確認設定
	※ Flash自体は8MBなので、将来8MBを有効利用する場合は再検討

	PSRAM
	OPI PSRAM

	Upload Mode
	UART0 / Hardware CDC

	Upload Speed
	115200

	USB Mode
	Hardware CDC and JTAG

`Upload Speed`は書き込み時の転送速度で、シリアルモニタの通信速度とは別設定。高速書き込みで問題が出る場合は速度を下げることがEspressifからも案内されている。 [[docs.espressif.com]](https://docs.espressif.com/projects/arduino-esp32/en/latest/guides/tools_menu.html)

---

# シリアルモニタ

動作確認時：

Plain Text

	Baud Rate
	115200bps

確認用スケッチ例：

C++

	void setup()
	{
		Serial.begin(115200);
		delay(1000);
		Serial.println("MORI-ICHISHIKI START");
	}

	void loop()
	{
		Serial.println("Forest Design");
		delay(1000);
	}

正常動作確認結果：

Plain Text

	MORI-ICHISHIKI START
	Forest Design
	Forest Design
	Forest Design
	...

---

# RESET / EN回路 Rev.1修正

初版基板ではEN回路にRCがなく、RESETスイッチ周辺へ触れるとESP32-S3が再起動する症状が発生。

### 初版

Plain Text

	EN / RESET
		|
	RESET SW
		|
		GND

### Rev.1修正

Plain Text

	+3.3V
	|
	10kΩ
	|
	+------ EN / RESET
	| 　　　　　|
	1µF 　　RESET SW
	| 　　　　　|
	GND 　　　GND

追加部品：

Plain Text

	EN → +3.3V
	10kΩ Pull-Up
	EN → GND
	1µF

### 実機確認

Plain Text

	1µFのみ仮接続
		↓
	RESETスイッチ周辺へ触れた際の
	誤リセット現象が消失

	さらに10kΩ Pull-Up追加
		↓
	通常起動安定
		↓
	BOOTスイッチを押さず
	Arduino IDEから自動書き込み成功
		↓
	自動RESET後
	スケッチ正常起動

``
### 実際の修正後の写真
![[森壱式初版修正記録]](MORI_ICHI_retouch.jpg)

ESP32-S3ではDTR/RTSからENとGPIO0を制御することで自動的にFirmware Downloadモードへ移行する。この部分はタイミングが重要。 [[docs.espressif.com]](https://docs.espressif.com/projects/esptool/en/latest/esp32s3/advanced-topics/boot-mode-selection.html)

---

# 正常起動ログ

RESETスイッチ操作後：

Plain Text

	ESP-ROM:esp32s3-20210327
	Build:Mar 27 2021
	rst:0x1 (POWERON),boot:0x2b (SPI_FAST_FLASH_BOOT)
	SPIWP:0xee
	mode:DIO, clock div:1
	load:0x3fce2820,len:0x10cc
	load:0x403c8700,len:0xc2c
	load:0x403cb700,len:0x30b0
	entry 0x403c88b8
	MORI-ICHISHIKI START

`SPI_FAST_FLASH_BOOT`はFlashから通常起動するモードに入っていることを示す。GPIO0をLOWにしてリセットした場合はシリアルブートローダー側へ入る。 [[docs.espressif.com]](https://docs.espressif.com/projects/esptool/en/latest/esp32s3/advanced-topics/boot-mode-selection.html)

---

# 初回動作確認結果

Plain Text

	USB Power OK
	+5V 4.74V
	+3.3V 3.29V

	CP2102N USB認識 OK
	COM Port OK

	BOOT Switch OK
	RESET Switch OK

	ESP32-S3 ROM OK
	Flash Write OK
	Flash Verify OK

	Automatic Upload OK

	Serial Output OK

	Application Boot OK

## Rev.1での重要変更

Plain Text

	RESET / ENネットへ

	10kΩ Pull-Up
		+
	1µF to GND

	を追加

次回改版時の変更箇所拡大
シルク「D」の左側の抵抗（黒いチップ）とコンデンサ（茶色のチップ）を追加する。
![[Pasted image 20261024165426.png]]
---


## 設計メモ

> **森壱式初版ではEN回路のRC不足により起動・自動書き込みが不安定になった。  
> EN-GNDへ1µF、EN-3.3Vへ10kΩを追加することで実機上正常動作を確認した。**

この回路は今後ESP32-S3を使用するForest Design基板の設計ノウハウとして流用する。
