<!--
version: 0.16

author: Fabian Bartl
email: fabian@informatic-freak.de

title: Digitaler Signalprozessor (DSP)
comment: Funktionsweise des Digitalen Signalprozessors

icon: https://upload.wikimedia.org/wikipedia/commons/d/de/Logo_TU_Bergakademie_Freiberg.svg
logo: ./img/preview.jpg

language: de
narrator: Deutsch Female

mode: Presentation
dark: true
link: ./styles/improvements.css

import: https://raw.githubusercontent.com/liascript-templates/plantUML/master/README.md
import: https://github.com/LiaTemplates/AVR8js/main/README.md

script: ./scripts/pyscript_alpha.min.js
-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://raw.githubusercontent.com/FabianBartl/DSP-DigSys/main/README.md)

# Digitaler Signalprozessor (DSP)

| Parameter            | Kursinformationen                                                                                |
| -------------------- | ------------------------------------------------------------------------------------------------ |
| **Veranstaltung**    | Praktikum Digitale Systeme                                                                       |
| **Hochschule**       | Technische Universität Bergakademie Freiberg                                                     |
| **Inhalte**          | @comment                                                                                         |
| **Link auf GitHub**  | [https://github.com/FabianBartl/DSP-DigSys](https://github.com/FabianBartl/DSP-DigSys/tree/main) |
| **Autoren**          | @author                                                                                          |
| **Version**          | V @version                                                                                       |

<img id="b" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba&query_only" onload='function s(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}function g(e){let o=e+"=",t=document.cookie.split(";");for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}let u="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b"),p=window.location.search.split("/").slice(-1)[0],c=g("v");c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h");'>

<img src="img/hidden_pixel.png" onload='console.log("hidden script loaded");' style="width:0px;height:0px;overflow:hidden;">

## Gliederung

1. DSP?
3. Entwicklung
2. AVR- und ARM-Assembly
3. FPU-Assembly
4. Anwendung auf dem STM32F4 Nucleo Board
5. Referenzen
6. Tools, Issues & Tricks

## DSP?

- `digital signal processing` -> algorithmische Verarbeitung digitaler Signale
- `digital signal processor`  -> spezialisierter Mikroprozessor

  {{1}}
********************************************************************************

**Anwendungen**

- Ersatz für aufwendigere analoge Filtertechnik
- Realisierung von Steuer-/Regelungstechnik
- Audioverarbeitung

********************************************************************************

  {{2}}
********************************************************************************

**Kategorien**

1. Floating-Point DSP
2. Fixed-Point DSP

********************************************************************************

  {{3-5}}
********************************************************************************

**Funktionsweise**

<ol style="color:transparent !important;"><li><br></li></ol>

1. (externes) analoges Signal mit `ADC` digitalisieren
2. verschiedene Algorithmen bzw. Filter anwenden
3. Ergebnis in analoges Signal umwandeln mit `DAC`

<ol style="color:transparent !important;"><li><br></li></ol>

********************************************************************************

  {{5}}
********************************************************************************

**Funktionsweise**

1. analoger Low-Pass-Filter, um Frequenzen unterhalb der *Nyquist-Frequenz*[^1] zu entfernen
2. (externes) analoges Signal mit `ADC` digitalisieren
3. verschiedene Algorithmen bzw. Filter anwenden
4. Ergebnis in analoges Signal umwandeln mit `DAC`
5. analoger Low-Pass-Filter, um Ergebnisfrequenzen einzugrenzen 

********************************************************************************

<img data="╭╮│╰╯┤─├┴└" src="img/hidden_pixel.png" style="width:0px;height:0px;overflow:hidden;">

  {{4}}
********************************************************************************

```ascii
 │   ╭╮      ╭───     +-----+     +-----*-------*-*     +-------------+     +-------------*-*     +-----+     │           ╭─── 
 │   ││  ╭───╯        |     |     |-----|---*-* | |     |             |     |---------*-* | |     |     |     │       ╭───╯    
 │   │╰──╯        --> | ADC | --> |-----|-* | | | | --> | Algorithmus | --> |-----*-* | | | | --> | DAC | --> │   ╭───╯        
 │───╯                |     |     |-*-* | | | | | |     |             |     |-*-* | | | | | |     |     |     │───╯            
 └───────────────     +-----+     +-+-+-+-+-+-+-+-+     +-------------+     +-+-+-+-+-+-+-+-+     +-----+     └─────────────── 
```

********************************************************************************

[^1]: Die **Nyquist-Frequenz** ist definiert als halbe Abtastfrequenz eines zeitlich diskreten Systems:
  $$f_{nyquist}=\frac12\cdot f_{abtast}$$
  und dient der Verhinderung des Alias-Effekts.<br>
  Nur wenn alle anteiligen Frequenzen des Signals kleiner als die Nyquist-Frequenz sind, kann das abgetastete Signal genau rekontruiert werden.

  -- [Wikipedia](https://de.wikipedia.org/wiki/Nyquist-Frequenz)


### Floating-Point DSP

- großer Zahlenbereich, höhere Genauigkeit
- leichter zu programmieren
- automatische Skalierung der Zahlen (IEEE 754 Format)
- FPU[[^?]](# "Floating Point Unit") erhöht Stromverbrauch und Kosten

  {{1}}
********************************************************************************

**Geeignet für Produkte**

 - in niedriger Stückzahl
 - mit sehr dynamischen Zahlenbereich
 - Bsp: Audioanwendungen, Medizinische oder Militärische Geräte

********************************************************************************

### Fixed-Point DSP

- keine FPU[[^?]](# "Floating Point Unit") verbaut -> Verwendung von Integer Operationen
- besser für Eingebettete Systeme geeignet, da günstiger und stromsparender

  {{1}}
********************************************************************************

**Geeignet für Produkte**

- in großer Strückzahl
- mit abschätzbarem Zahlenbereich
- Videoanwendungen, Spracherkennung, Kabellose Kommunikation

********************************************************************************

## Entwicklung

- 

## AVR- vs. ARM-Assembly

``` c C-Code
int main()
{
	int a=2, b=3, c=4;
	a += b * c;	// Wichtige Zeile
	return a;
}
```

---

``` asm AVR-Assembly für Atmega328P
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
main:
  push r28
  push r29
  rcall .
  rcall .
  rcall .
  in r28,__SP_L__
  in r29,__SP_H__
  ldi r24,lo8(2)
  ldi r25,0
  std Y+2,r25
  std Y+1,r24
  ldi r24,lo8(3)
  ldi r25,0
  std Y+4,r25
  std Y+3,r24
  ldi r24,lo8(4)
  ldi r25,0
  std Y+6,r25
  std Y+5,r24
  ldd r20,Y+3		; Wichtige Zeilen:
  ldd r21,Y+4		;
  ldd r18,Y+5		;
  ldd r19,Y+6		;
  mul r20,r18		;
  movw r24,r0		;
  mul r20,r19		;
  add r25,r0		;
  mul r21,r18		;
  add r25,r0		;
  clr r1				;
  ldd r18,Y+1		;
  ldd r19,Y+2		;
  add r24,r18		;
  adc r25,r19		;
  std Y+2,r25		;
  std Y+1,r24		;
  ldd r24,Y+1
  ldd r25,Y+2
  adiw r28,6
  in __tmp_reg__,__SREG__
  cli
  out __SP_H__,r29
  out __SREG__,__tmp_reg__
  out __SP_L__,r28
  pop r29
  pop r28
  ret
```

[Code at Compiler Explorer](https://godbolt.org/z/q1scMhfvj)

-> 17 ASM Befehle -> xx Takte

---

``` asm ARMv7-Assembly für STM32F401
main:
  sub sp, sp, #16
  mov r0, #0
  str r0, [sp, #12]
  mov r0, #2
  str r0, [sp, #8]
  mov r0, #3
  str r0, [sp, #4]
  mov r0, #4
  str r0, [sp]
  ldr r1, [sp, #4]		; Wichige Zeilen:
  ldr r2, [sp]				;
  ldr r3, [sp, #8]		;
  mla r0, r1, r2, r3	; Multiply-Accumulate
  str r0, [sp, #8]		;
  ldr r0, [sp, #8]
  add sp, sp, #16
  bx lr
```

[Code at Compiler Explorer](https://godbolt.org/z/K8M4rYTqh)

-> 5 ASM Befehle -> xx Takte

## FPU-Assembly

Hardwarebasierte Floating-point Operationen

### Features

- digital signal processing instructions
- floating-point instructions

## Anwendung auf dem Nucleo-64 Board

- STM32F4-Serie mit ARM Cortex-M4F-Kern
- https://www.st.com/content/st_com/en/arm-32-bit-microcontrollers/arm-cortex-m4.html

**Tonsteuerung mittels Ultrashall**

- Entfernung messen und auf Ton mappen (Look-Up, Taylor-Polynom)
- Analoges Signal der Entfernungsmessung filtern: Noise-Reduction
- Analoges Signal für Tonausgabe generieren (kein PWM-Rechteck-Signal)

## Referenzen

### Literatur

  {{0}}
********************************************************************************

- Dr. Yifeng Zhu (Juni 2018). *Embedded Systems with ARM Cortex-M Microcontrollers in Assembly Language and C* (3. Aufl.).<br>
  E-Man Press LLC, 2017. ISBN 978-0-9826926-6-0

********************************************************************************

  {{1}}
********************************************************************************

- https://de.wikipedia.org/wiki/Digitaler_Signalprozessor
- https://www.ibr.cs.tu-bs.de/courses/ws9798/seminar/haverkamp/seminar.html#385
- http://www.elektro-archiv.de/archiv/d/dsp/
- https://technobyte.org/dsp-advantages-disadvantages-block-diagram-applications/
- https://www.wikiwand.com/de/Digitaler_Signalprozessor
- https://liascript.github.io/course/?https://raw.githubusercontent.com/TUBAF-IfI-LiaScript/VL_DigitaleSysteme/main/lectures/11_CortexMController.md#3

********************************************************************************

### Bilder und Videos

  {{0}}
********************************************************************************

- https://www.pexels.com/de-de/foto/mann-person-smartphone-zerbrochen-6755091/

********************************************************************************

  {{1}}
********************************************************************************

- 

********************************************************************************

## Tools, Issues & Tricks

### Tools

- [Compiler Explorer](https://godbolt.org/)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
- [VSC LiaScript Preview Extension](https://marketplace.visualstudio.com/items?itemName=LiaScript.liascript-preview)
- [ASCII to SVG Editor](https://andre-dietrich.github.io/elm-svgbob/)

### Issues

- HTML-Kommentare werden in der VSC-Preview als Inahlt angezeigt
- Eingerückte Anstriche funktionieren nicht
- Links über Einblendungen sind nicht möglich
- Einblendungen werden manchmal nicht erkannt
- Wie kann der Stil von Code-Feldern in der Config festgelegt werden?
- Im Dark-Mode ist die Liste der Editor-Stile in den Einstellungen falsch koloriert
- ASCII-Art wird im Dark-Mode als Weiß-auf-Schwarz angezeigt
- Inline-Code ist im Dark-Mode schlecht lesbar

### Tricks

- Tooltips[[^?]](# "Fancy Tooltip")

- Hidden-Scripts für GitHub
  <img src="img/hidden_pixel.png" onmouseover='alert("script hidden in img tag of 1x1 transparent pixel");' style="width: 10px; height: 10px; overflow: hidden;">

- Cookie-basierte Besucherzähler Badge
  <img id="b" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba&query_only" onload='function s(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}function g(e){let o=e+"=",t=document.cookie.split(";");for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}let u="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b"),p=window.location.search.split("/").slice(-1)[0],c=g("v");c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h");'>
