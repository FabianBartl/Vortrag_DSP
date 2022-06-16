<!--
version: 0.0.12g

author: Fabian Bartl
email: fabian@informatic-freak.de

title: Digitaler Signalprozessor (DSP)
comment: Funktionsweise des Digitalen Signalprozessors

icon: https://upload.wikimedia.org/wikipedia/commons/d/de/Logo_TU_Bergakademie_Freiberg.svg
logo: ./img/preview.jpg

language: de
narrator: Deutsch Female

mode: Presentation
dark: false

import: https://raw.githubusercontent.com/liascript-templates/plantUML/master/README.md
import: https://github.com/LiaTemplates/AVR8js/main/README.md

script: ./scripts/pyscript_alpha.min.js

link: ./styles/custom.css

translation: English translations/English.md
-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://raw.githubusercontent.com/FabianBartl/DSP-DigSys/main/README.md)

# Digitaler Signalprozessor (DSP) <!-- @title -->

| Parameter            | Kursinformationen                                                                                |
| -------------------- | ------------------------------------------------------------------------------------------------ |
| **Veranstaltung**    | Praktikum Digitale Systeme                                                                       |
| **Hochschule**       | Technische Universität Bergakademie Freiberg                                                     |
| **Inhalte**          | @comment                                                                                         |
| **Link auf GitHub**  | [https://github.com/FabianBartl/DSP-DigSys](https://github.com/FabianBartl/DSP-DigSys/tree/main) |
| **Autoren**          | @author                                                                                          |
| **Version**          | V @version                                                                                       |

<img id="b" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba&query_only" onload='function s(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}function g(e){let o=e+"=",t=document.cookie.split(";");for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}let u="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b"),p=window.location.search.split("/").slice(-1)[0],c=g("v");c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,1,"h");'>

## Gliederung

1. Was ist ein DSP & Wofür ist es gut?
2. Entwicklung
3. Funktionsweise & Features <!-- Funktionsweise: ADC, DAC, Beispiele DSP Algorithmen; Features: MCU, 1-Takt Hardware Multiplizierer / Dividierer -->
4. Low-Pass-Filter Simulation in Simulink
5. Anwendung auf dem STM32F4 Nucleo Board
6. Referenzen

## Was ist ein DSP & Wofür ist es gut?

**Begriff *DSP***

* `digital signal processing` -> algorithmische Verarbeitung digitaler Signale
* `digital signal processor`  -> spezialisierter Mikroprozessor

                    {{1-2}}
********************************************************************************

**Anwendungen**

- Realisierung verschiedener Filter zur Regelung
- Moderne Antriebe: Überwachung vieler analoger Werte durch Sensoren
- Audioverarbeitung: High/Low-Pass-Filter, Noise-Reduction, ...

********************************************************************************

## Entwicklung

## Funktionsweise & Features

* https://www.st.com/content/st_com/en/arm-32-bit-microcontrollers/arm-cortex-m4.html

                    {{0-3}}
********************************************************************************

**Funktionsweise**

1. analoges Signal digitalisieren `ADC`
2. verschiedene Algorithmen bzw. Filter anwenden
3. Ergebnis in analoges Signal umwandeln `DAC`

<!-- ╭╮│╰╯┤─├┴└ -->

```ascii
 │   ╭╮      ╭───     +-----+     +-----*-------*-*     +-------------+     +-------------*-*     +-----+     │           ╭─── 
 │   ││  ╭───╯        |     |     |-----|---*-* | |     |             |     |---------*-* | |     |     |     │       ╭───╯    
 │   │╰──╯        --> | ADC | --> |-----|-* | | | | --> | Algorithmus | --> |-----*-* | | | | --> | DAC | --> │   ╭───╯        
 │───╯                |     |     |-*-* | | | | | |     |             |     |-*-* | | | | | |     |     |     │───╯            
 └───────────────     +-----+     +-+-+-+-+-+-+-+-+     +-------------+     +-+-+-+-+-+-+-+-+     +-----+     └─────────────── 
```

********************************************************************************

## Low-Pass-Filter Simulation in Simulink

* Simulink mit MathWorks (MATLAB)
	* Tutorials anschauen
	* 'Interaktives' Beispiel erstellen

>https://www.mathworks.com/matlabcentral/fileexchange/43155-dsp-system-toolbox-support-package-for-arm-cortex-m-processors

## Anwendung auf dem STM32F4 Nucleo Board

* STM32F4-Serie mit ARM Cortex-M4F-Kern

## Referenzen

### Literatur

                    {{0-3}}
********************************************************************************

* https://de.wikipedia.org/wiki/Digitaler_Signalprozessor
* https://www.ibr.cs.tu-bs.de/courses/ws9798/seminar/haverkamp/seminar.html#385
* http://www.elektro-archiv.de/archiv/d/dsp/
* https://technobyte.org/dsp-advantages-disadvantages-block-diagram-applications/

********************************************************************************

                    {{1-3}}
********************************************************************************

* https://www.sciencedirect.com/topics/engineering/digital-signal-processing-algorithm
	* https://www.sciencedirect.com/science/article/pii/B9780080977683000118
	* https://www.sciencedirect.com/science/article/pii/B9780128207352000196
	* https://www.sciencedirect.com/science/article/pii/B9781558608740500095
	* https://www.sciencedirect.com/science/article/pii/B9780081006290000013
	* https://www.sciencedirect.com/science/article/pii/B9780128045473000012

********************************************************************************

                    {{2-3}}
********************************************************************************

* https://www.sciencedirect.com/topics/computer-science/digital-signal-processing-algorithm
	* https://www.sciencedirect.com/science/article/pii/B9780123914903000114
	* https://www.sciencedirect.com/science/article/pii/B9780127345307500064
	* https://www.sciencedirect.com/science/article/pii/B9780127345307500015
	* https://www.sciencedirect.com/science/article/pii/B9780750689762000043

********************************************************************************

### Bilder und Videos

                    {{0-2}}
********************************************************************************

* https://www.pexels.com/de-de/foto/mann-person-smartphone-zerbrochen-6755091/

********************************************************************************

                    {{1-2}}
********************************************************************************

*

********************************************************************************
