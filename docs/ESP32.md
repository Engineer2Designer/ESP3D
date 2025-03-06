# *ESP32*
![ESP32](./ESP32-DOIT-DEV-KIT-v1-pinout-mischianti.png)

##
|GPIO	|輸入    |輸出	|備註   |
|---    |---    |---    |---   |      
|0	    |OK	    |OK	    |啟動時輸出 PWM 訊號
|1	    |TX0    |OK		|
|2	    |OK	    |OK	    |與板上 LED 相連接
|3	    |OK	    |RX0    |啟動時輸出高電位
|4	    |OK	    |OK	    |
|5	    |OK	    |OK	    |啟動時輸出 PWM 訊號
|6	    |NO	    |NO	    |系統使用 （SPI 快閃記憶體）
|7	    |NO	    |NO	    |系統使用 （SPI 快閃記憶體）
|8	    |NO	    |NO	    |系統使用 （SPI 快閃記憶體）
|9	    |NO	    |NO	    |系統使用 （SPI 快閃記憶體）
|10	    |NO	    |NO	    |系統使用 （SPI 快閃記憶體）
|11	    |NO	    |NO	    |系統使用 （SPI 快閃記憶體）
|12	    |OK	    |OK	    |MTDI、LDO （啟動失敗時輸出高電位）
|13	    |OK	    |OK	    |
|14	    |OK	    |OK	    |啟動時輸出 PWM 訊號
|15	    |OK	    |OK	    |啟動時輸出 PWM 訊號
|16	    |OK	    |OK	    |
|17	    |OK	    |OK	    |
|18	    |OK	    |OK	    |
|19	    |OK	    |OK	    |
|21	    |OK	    |OK	    |
|22	    |OK	    |OK	    |
|23	    |OK	    |OK	    |
|25	    |OK	    |OK	    |
|26	    |OK	    |OK	    |
|27	    |OK	    |OK	    |
|32	    |OK	    |OK	    |
|33	    |OK	    |OK	    |
|34	    |OK	    |NO	    |
|35	    |OK	    |NO	    |
|36	    |OK	    |NO	    |
|39	    |OK	    |NO     |    

## 只允許輸入的腳位
GPIO 34 到 39 由於內部沒有上拉電阻以及下拉電阻，所以是不允許當成輸出腳位來使用的。

## SPI 快閃記憶體腳位
GPIO 6-11 這六個腳位已經連接至 ESP32 內部的 SPI 快閃記憶體來使用了。所以一般來說，也不允許當作輸入輸出來使用。

- GPIO 6 (SCK/CLK)
- GPIO 7 (SDO/SD0)
- GPIO 8 (SDI/SD1)
- GPIO 9 (SHD/SD2)
- GPIO 10 (SWP/SD3)
- GPIO 11 (CSC/CMD)

## UART 串口 (TX RX)
ESP32 提供 3 組的 UART。其中 TX0 RX0 與 USB 共連，以及 TX1 RX1 由於 預設連接 SPI 快閃記憶體的關係，所以要使用的話需要將其設定到其他的 GPIO 上，才可以正常使用。

- GPIO 1 (TX0)
- GPIO 3 (RX0)
- GPIO 9 (RX1)
- GPIO 10 (TX1)
- GPIO 16 (RX2)
- GPIO 17 (TX2)
## 類比數位轉換器 (ADC)
ESP32 內部共有 18 組 ADC 頻道可以使用。以下為 ADC 可以使用的腳位，也可以參考最上面腳位圖的橘色區塊。

`ESP32 內部有分為兩組 ADC，分別為 ADC1 及 ADC2。而如果使用 WiFi 功能時，ADC2 就會無法使用，可以改使用 ADC1。`

- ADC1_CH0 (GPIO 36)
- ADC1_CH1 (GPIO 37)
- ADC1_CH2 (GPIO 38)
- ADC1_CH3 (GPIO 39)
- ADC1_CH4 (GPIO 32)
- ADC1_CH5 (GPIO 33)
- ADC1_CH6 (GPIO 34)
- ADC1_CH7 (GPIO 35)
- ADC2_CH0 (GPIO 4)
- ADC2_CH1 (GPIO 0)
- ADC2_CH2 (GPIO 2)
- ADC2_CH3 (GPIO 15)
- ADC2_CH4 (GPIO 13)
- ADC2_CH5 (GPIO 12)
- ADC2_CH6 (GPIO 14)
- ADC2_CH7 (GPIO 27)
- ADC2_CH8 (GPIO 25)
- ADC2_CH9 (GPIO 26)

## 數位類比轉換器 (DAC)
ESP32 提供 2 組的 DAC。以下為該 DAC 腳位

- DAC1 (GPIO25)
- DAC2 (GPIO26)

## 電容式感應腳位
ESP32 提供 10 組電容式感應觸摸通道的腳位。該腳位功用可以感知任何在有電荷的東西(例如:皮膚)。

- T0 (GPIO 4)
- T1 (GPIO 0)
- T2 (GPIO 2)
- T3 (GPIO 15)
- T4 (GPIO 13)
- T5 (GPIO 12)
- T6 (GPIO 14)
- T7 (GPIO 27)
- T8 (GPIO 33)
- T9 (GPIO 32)

## PWM
ESP32 提供 16 個 PWM 通道。除了只允許輸入的腳位以外（GPIO 34-39），其他均可輸出 PWM 訊號。

## 積體匯流排電路 (I2C)
I2C 最常見的應用就是連接 LCD ，可以減少 LCD 所需要連接的 GPIO，只需要四條線即可實現，非常方便。

- GPIO 21 (SDA)
- GPIO 22 (SCL)

## 動時特殊做動 Pin
以下 GPIO 會在 ESP32 啟動或是重置時會輸出高電位或是輸出 PWM 訊號。

- GPIO 1
- GPIO 3
- GPIO 5
- GPIO 6 – 11
- GPIO 14
- GPIO 15

## GPIO 最高電流
在 ESP32 內部，每個 GPIO 最高輸出電流為 40mA。

## 跳過的 GPIO
以下腳位在 WROOM 和 WROVER 通常不會被引出，除非使用裸晶片

- GPIO 20
- GPIO 24
- GPIO 28
- GPIO 29
- GPIO 30
- GPIO 31
- GPIO 37
- GPIO 38

## 功能腳位總結
|功能	|GPIO	|備註   |
|-     |-      |-      |
|UART(串口)|TX0:1 RX0:3 TX1:10 RX1:9 TX2:17 RX2:16 |TX1 RX1 使用時需將腳位移至其他 GPIO|
|ADC    |32, 33, 34, 35, 36, 39	
|DAC    |25, 26	
|SPI    |HSPI: 14,12,13,15
|VSPI:  |23,19,18,5	
|I2C    |SDA:21 SCL:22	
|電容式感應腳位  |0, 2, 4, 12, 13, 14, 15, 27, 32, 33|	 