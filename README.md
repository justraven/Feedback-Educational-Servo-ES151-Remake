# Feedback Educational Servo ES151

<img src="https://img.shields.io/badge/labview-%23FFDB00.svg?&style=for-the-badge&logo=labview&logoColor=black" /> <img src="https://img.shields.io/badge/arduino-%2300979D.svg?&style=for-the-badge&logo=arduino&logoColor=white" />  	<img src="https://img.shields.io/badge/python-%233776AB.svg?&style=for-the-badge&logo=python&logoColor=white" /> 

Repo ini berisi source code microcontroller dan GUI untuk projek kendali kecepatan dan posisi pada alat Feedback Educational Servo ES151.

Demo projek :

[![](https://markdown-videos.deta.dev/youtube/0JrNFHsB_GM)](https://youtu.be/0JrNFHsB_GM)

## Struktur file

Struktur file pada projek ini ditunjukkan sebagai berikut :

```
📦GUI  
 ┣ 📂GUI LabVIEW                # folder untuk GUI LabVIEW ver.2021
 ┃ ┗ 📜GUI.vi                   # GUI LabVIEW ver. 2021 
 ┣ 📂GUI LabVIEW Legacy         # folder untuk GUI LabVIEW ver.2019
 ┗ 📂GUI Python                 # folder GUI Python
 ┃ ┣ 📜GUI_Kelompok1.py         # GUI Python
 
📦Arduino code  
 ┣ 📂Arduino code for LabVIEW   # folder program mikrokontroller untuk GUI LabVIEW
 ┃ ┣ 📂lib
 ┃ ┃ ┣ 📂parsing                # folder untuk custom library
 ┃ ┃ ┃ ┗ 📜parsing.h            # file library parsing
 ┃ ┣ 📂src                      # folder tempat file utama
 ┃ ┃ ┗ 📜main.cpp               # file utama program
 ┃ ┗ 📜platformio.ini           # file konfigurasi platformio
 ┗ 📂Arduino code for Python    # folder mikrokontroller untuk GUI Python
 ┃ ┣ 📜Communication.ino  
 ┃ ┣ 📜Debug.ino  
 ┃ ┣ 📜encoder.ino  
 ┃ ┣ 📜keypad.ino  
 ┃ ┣ 📜Main_Program10.ino  
 ┃ ┣ 📜Menu.ino  
 ┃ ┣ 📜motor.ino  
 ┃ ┣ 📜PID.ino  
 ┃ ┗ 📜pin_declare.ino
 ```
 ## Perangkat Lunak yang Digunakan
 Untuk menjalankan GUI LabView diperlukan perangkat lunak sebagai berikut,
 - VsCode dengan ekstensi PlatformIO
 - LabVIEW
 
 Untuk menjalankan GUI Python, diperlukan perangkat lunak sebagai berikut, 
 - Python
 - Arduino IDE

  ## Pengembang
 - [priyovamr](https://github.com/priyovamr)
 - [justraven](https://github.com/justraven) Pengembang GUI dan Kode Mikrokontroller (LabVIEW)
