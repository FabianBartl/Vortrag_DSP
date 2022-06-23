<!--
version: 1.0a

author: Fabian Bartl
email: fabian@informatic-freak.de

title: Digitaler Signalprozessor (DSP)
comment: Funktionsweise, Entwicklung und Anwendung des Digitalen Signalprozessors

icon: https://upload.wikimedia.org/wikipedia/commons/d/de/Logo_TU_Bergakademie_Freiberg.svg
logo: ./img/preview.jpg

language: de
narrator: Deutsch Female

mode: Presentation
dark: true
link: ./styles/improvements.css

import: https://raw.githubusercontent.com/liascript-templates/plantUML/master/README.md
import: https://github.com/LiaTemplates/AVR8js/main/README.md

@com: <span title='@0'></span>

@ttc: <a title='@0' href="#" class="lia-link"><sup><button aria-describedby='footnote-@1' class="lia-btn lia-btn--transparent text-highlight" id='footnote-key-@1' style="padding: 2px;">[@1]</button></sup></a>
@tt: @ttc(@0, ? )

@hsse: <img src='img/hidden_pixel.png' @2='@0' style='@1'>
@hss: @hsse(@0, @1, onload)
@hse: @hsse(@0, '', @1)
@hs: @hss(@0, '')
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

<img id="b" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys&left_color=%235b5b5b&right_color=%230fb3ba&query_only" onload='function s(e,t,a=1,s="h`){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}function g(e){let o=e+"=",t=document.cookie.split(";`);for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}let u="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b`),p=window.location.search.split("/`).slice(-1)[0],c=g("v`);c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h`);'>

## Gliederung

1. DSP?
3. Entwicklung
3. Aufbau & Funktion
4. ~Anwendung auf dem Nucleo-64 Board~
5. Referenzen
6. Tools, Issues & Tricks

## DSP?

- `digital signal processing` -> algorithmische Verarbeitung digitaler Signale
- `digital signal processor` -> spezialisierter Mikroprozessor (mit Harvard-Architektur)

  {{1}}
********************************************************************************

**Prinzip**

1. analoges Signal digitalisieren
2. Algorithmen verarbeiten
3. Ergebnis in analoges Signal umwandeln

********************************************************************************

  {{2}}
********************************************************************************

**Anforderungen**

- ständige Umwandlung von Signalen von analog in digital und umgekehrt
- schnelle digitale Manipulation der Daten
- harte Echtzeitfähigkeit (sehr geringe Latenz)

********************************************************************************

  {{3}}
********************************************************************************

- die meisten Allzweck-Mikroprozessoren und Betriebssysteme können DSP-Algorithmen erfolgreich ausführen
- aber ein spezialisierter DSP bietet tendenziell eine kostengünstigere Lösung mit besserer Leistung
@com(`geringere Latenz, kleinerer Energieverbrauch`)

********************************************************************************

### Vor- & Nachteile und Anwendungen

  {{0}}
********************************************************************************

**Vorteile**

- Fehlererkennung und -korrektur ist möglich
- einfachere Verarbeitung und Speicherung der Daten
- Verschlüsselung
- einfachere Modifikation / Programmierung

********************************************************************************

  {{1}}
********************************************************************************

**Nachteile gegenüber analoger Verarbeitung**

- höherer Stromverbrauch, da DSP aus aktiven Komponenten besteht
- Verlust von Informationen durch Quantisierung der Daten

********************************************************************************

  {{2}}
********************************************************************************

**Anwendungen**

- Regeltechnik @com(`Motosteuerung`)
- Digitale Bild-, Ton- und Videoverarbeitung @com(`Soundkarten, JPEG-/MP3-Komprimierung`)
- Telekommunikation @com(`Digital Radio, Telefonieren`)
- Ersatz für aufwendigere analoge Filtertechnik

********************************************************************************

### Kategorien

  {{0}}
********************************************************************************

**Floating-Point DSP**

- großer Zahlenbereich, höhere Genauigkeit (`IEEE 754`-Format)
- `FPU`@tt(`Floating-Point Unit`) erhöht Stromverbrauch und Kosten

********************************************************************************

  {{1}}
********************************************************************************

**Geeignet für Produkte**

 - in niedriger Stückzahl
 - mit sehr dynamischen Zahlenbereich

---<comment></comment>

********************************************************************************

  {{2}}
********************************************************************************

**Fixed-Point DSP**

- keine `FPU` verbaut -> Verwendung von Integer Operationen
- kompliziertere Programmierung, da keine automatische Skalierung der Zahlen

********************************************************************************

  {{3}}
********************************************************************************

**Geeignet für Produkte**

- in großer Strückzahl
- mit festem Zahlenbereich
- besser für Eingebettete Systeme geeignet, da günstiger und stromsparender

********************************************************************************

## Entwicklung

  {{0}}
********************************************************************************

**Anfänge in den 1970er**

- TI@tt(`Texas Instruments`) entwickelte von 1976-78 den ersten *Speak & Spell*[^1], der einen `TMS5100` enthielt - der erste DSP der Branche
- AMI@tt(`American Microsystems`) brachte 1978 den DSP `S2811` auf den Markt, dieser verfügte bereits über einen Hardware-Multiplikator
@com(`Wurde als Peripheriegerät für Motorola 6800 entwickelt, musste aber vom Host initialisiert werden. War auf dem Markt nicht erfolgreich.`)
- Intel brachte 1979 den `2920` als "analogen Signalprozessor" auf den Markt, mit On-Chip- `ADC` / `DAC`, aber ohne Hardware-Multiplikator
@com(`War auf dem Markt nicht erfolgreich.`)

********************************************************************************

  {{1}}
********************************************************************************

**1. Generation in den 1980er**

- 1980 stellten AT&T und NEC@tt(`Nippon Electric Corporation`) die ersten eigenständigen und vollständigen DSPs auf der ISSCC@tt(`International Solid-State Circuits Conference`) vor, den `DSP1` und `NEC μPD7720`[^2]
- der `NEC μPD7720` wurde für Sprachband-Anwendungen eingeführt und war einer der kommerziell erfolgreichsten frühen DSPs
@com(`Anwendungen, die Frequenzen der gesprochenen Sprache übermitteln`)
- 1983 stellte TI den DSP `TMS32010` vor, dieser basierte auf der Harward-Architektur, verfügte u.a. über `MAC`@tt(`Multiply-Accumulate Operation`)-Anweisungen und konnte mit 16-Bit-Zahlen arbeiten
- ca. 390 ns Ausführungsdauer für eine `MAC`-Operation

********************************************************************************

  {{2}}
********************************************************************************

**2. Generation ab ca. 1985**

- Hardwarebeschleunigung von Schleifen mittels `AGU`@tt(`Address Generation Unit`)
- teilweise mit 24-Bit-Variablen
- ca. 21 ns Ausführungsdauer für eine `MAC`-Operation
- Bsp.: `AT&T DSP16A`, `Motorola 56000`

********************************************************************************

  {{3}}
********************************************************************************

**3. Generation in den 1990er**

- Anwendungsspezifische DSPs ermöglichten als Coprozessoren direkte Hardwarebeschleunigung sehr spezifischer und komplexer mathematischer Probleme 
@com(`Bsp.: Fourier-Transformation, Matrixoperationen`)
- einige Chips, wie der `Motorola MC68356`, nutzten mehrere Prozessorkerne zur Parallelisierung
- Bsp.: `TI TMS320C541`, `TMS 320C80`

********************************************************************************

  {{4}}
********************************************************************************

**4. Generation**

- `SIMD`[^3]-Erweiterungen wurden hinzugefügt, diese dienen der echten parallelen Ausführung von vielen gleichen Operationen auf Hardware-Ebene
  @com(`VLIW: Very long instruction word`)
- höhere Taktraten
- ca. 3 ns Ausführungsdauer für eine `MAC`-Operation

********************************************************************************

[^1]: **Speak & Spell** war eine Lernspielzeugserie von elektronische Kindercomputern von TI, die aus einem linearen prädiktiv kodierenden Sprachsynthesizer, einer Tastatur und einem Steckplatz für ROMs bestanden. Es war eines der frühesten tragbaren elektronischen Geräte mit Display, dass austauschbare ROMs verwendete.<br><br>
  ![](img/Speak-and-Spell.jpg)
  **Der Speak & Spell Wurde 2009 zum IEEE Milestone ernannt.**

  -- [Wikipedia](https://en.wikipedia.org/wiki/Speak_%26_Spell_(toy)

[^2]: ![](img/ST010_01.jpg)
  Der von NEC 1980 entwickelte DSP `NEC μPD7720` war einer der populärsten DSPs dieser Zeit.

  -- [Wikipedia](https://en.wikipedia.org/wiki/NEC_%C2%B5PD7720)

[^3]: `SIMD` steht für **Single instruction, multiple data**, dieser Befehlssatz implementiert eine echte parallele Ausführung von gleichartigen Rechenoperationen auf Hardware-Ebene, die mit einem Befehlsaufruf mehrere Daten parallel verarbeiten.<br>
  `SIMD` eignet sich besonders gut für die Verarbeitung von Bild-, Ton- und Videodaten, da identische Operationen für zum Beispiel viele einzelne Bildpunkte ausgeführt werden müssen.

  -- [Wikipedia](https://de.wikipedia.org/wiki/Flynnsche_Klassifikation#SIMD_(Single_Instruction,_Multiple_Data)

### Moderne DSPs

  {{0}}
********************************************************************************

- liefern höhere Leistung, u.a. durch schnellen Cache, ein breites Bussystem, und `DMA`@tt(`Direct Memory Access`)
- viele verschiedene Arten, jeder für bestimmte Aufgaben besser geeignet
- DSPs kosten zwischen 1,50 € bis hin zu 300 €
- TI ist heute Marktführer bei Allzweck DSPs

********************************************************************************

  {{1}}
********************************************************************************

**`C6000`-DSP-Serie von TI**

- 1,2 GHz Taktrate
- 8 MB 2nd Level Cache
- 64 `DMA`-Kanäle
- teilweise bis zu 8000 MIPS@tt(`Mio. Instruktionen pro Sekunde`)
- 8 Operationen pro Taktzyklus
- kompatibel und vielen Peripheriegeräten und Bussen
- unterstützen in der neuesten Generation Floating-Point und Fixed-Point Verarbeitung
{{2}}- der Chip `TMS320C6474` enthält drei solcher DSPs und kostet ca. 250 €

********************************************************************************

## Aufbau & Funktion

  {{0-2}}
********************************************************************************

<ol style="color:transparent !important;"><li><br></li></ol>

1. (externes) analoges Signal mit `ADC` digitalisieren
2. verschiedene Algorithmen bzw. Filter anwenden
3. Ergebnis in analoges Signal umwandeln mit `DAC`

<ol style="color:transparent !important;"><li><br></li></ol>

********************************************************************************

  {{2}}
********************************************************************************

1. analoger Low-Pass-Filter, um Frequenzen unterhalb der *Nyquist-Frequenz*[^1] zu entfernen @com(`Anti-Aliasing Filter`)
2. (externes) analoges Signal mit `ADC` digitalisieren
3. verschiedene Algorithmen bzw. Filter anwenden
4. Ergebnis in analoges Signal umwandeln mit `DAC`
5. analoger Low-Pass-Filter, um Hochfrequenzkomponenten zu entfernen @com(`Glättungsfilter`)

********************************************************************************

@com(`╭╮│╰╯┤─├┴└`)

  {{1-2}}
********************************************************************************

```ascii
 │   ╭╮      ╭───     +-----+     +-----*-------*-*     +-------------+     +-------------*-*     +-----+     │           ╭─── 
 │   ││  ╭───╯        |     |     |-----|---*-* | |     |             |     |---------*-* | |     |     |     │       ╭───╯    
 │   │╰──╯        --> | ADC | --> |-----|-* | | | | --> | Algorithmus | --> |-----*-* | | | | --> | DAC | --> │   ╭───╯        
 │───╯                |     |     |-*-* | | | | | |     |             |     |-*-* | | | | | |     |     |     │───╯            
 └───────────────     +-----+     +-+-+-+-+-+-+-+-+     +-------------+     +-+-+-+-+-+-+-+-+     +-----+     └─────────────── 
```

********************************************************************************

  {{2}}
********************************************************************************

```ascii
 │   ╭╮      ╭───     +-----+     +-----*-------*-*     +-------------+     +-------------*-*     +-----+     │           ╭─── 
 │   ││  ╭───╯        |     |     |-----|---*-* | |     |             |     |---------*-* | |     |     |     │       ╭───╯    
 │   │╰──╯        --> | ADC | --> |-----|-* | | | | --> | Algorithmus | --> |-----*-* | | | | --> | DAC | --> │   ╭───╯        
 │───╯             A  |     |     |-*-* | | | | | |     |             |     |-*-* | | | | | |     |     |  A  │───╯            
 └───────────────  |  +-----+     +-+-+-+-+-+-+-+-+     +-------------+     +-+-+-+-+-+-+-+-+     +-----+  |  └─────────────── 
                   |                                                                                       |
                   °                                                                                       °
            Anti-Aliasing Filter                                                                     Glättungsfilter
```

********************************************************************************

[^1]: Die **Nyquist-Frequenz** ist definiert als halbe Abtastfrequenz eines zeitlich diskreten Systems:
  $$f_{nyquist}=\frac12\cdot f_{abtast}$$
  und dient der Verhinderung des Alias-Effekts:<br><br>
  ![](img/signal-aliasing.png)

  Nur wenn alle anteiligen Frequenzen des Signals kleiner als die Nyquist-Frequenz sind, kann das abgetastete Signal genau rekontruiert werden.

  -- [Wikipedia](https://de.wikipedia.org/wiki/Nyquist-Frequenz)

### Komponenten

  {{0}}
********************************************************************************

- `ADC`@tt(`Analog-Digital Converter`) dient Digitalisierung analoger Signale
- `DAC`@tt(`Digital-Analog Converter`) dient der Umwandlung der Daten in analoge Signale

********************************************************************************

  {{1}}
********************************************************************************

- `ALU`@tt(`Arithmetic-Logical Unit`)

  - Rechenwerk für Accumulate-Operationen wie `MAC`
  - `FPU`@tt(`Floating-Point Unit`) für Floating-Point Operationen
  - Hardware-Multiplizierer und -Dividierer
  - weitere `ALU`'s zur parallelen Ausführung von Berechnungen

********************************************************************************

  {{2}}
********************************************************************************

- `PLU`@tt(`Parallel Logic Unit`) dient der von der `ALU` unabhängigen logischen Datenmanipulation

********************************************************************************

  {{3}}
********************************************************************************

- `AGU`@tt(`Address Generation Unit`) dient der von der `ALU` unabhängigen Berechnungen von Adressen für Schleifen und Sprünge mittels programmierbarer Counter und Shifter, etc.

********************************************************************************

  {{4}}
********************************************************************************

>Alle Komponenten können parallel verwendet werden.

********************************************************************************

### Arduino Uno vs. ARMv7

```c C-Code
int main()
{
  int a=2, b=3, c=4;
  a += b * c; // Wichtige Zeile
  return a;
}
```

---@com(`---`)

```asm AVR-Assembly für Atmega328P
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
  ldd r20,Y+3		; Wichtige Zeilen
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
  std Y+1,r24		; -> 17 ASM Instruktionen
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

[Compiler Explorer](https://godbolt.org/z/q1scMhfvj)

---@com(`---`)

```asm ARMv7-Assembly für STM32F401
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
  ldr r1, [sp, #4]		; Wichige Zeilen
  ldr r2, [sp]				;
  ldr r3, [sp, #8]		;
  mla r0, r1, r2, r3	; MAC-Anweisung
  str r0, [sp, #8]		; -> 5 ASM Instruktionen
  ldr r0, [sp, #8]
  add sp, sp, #16
  bx lr
```

[Compiler Explorer](https://godbolt.org/z/K8M4rYTqh)

### Ausgewählte Assembly-Direktiven

-> [STM32 Cortex®-M4 MCUs and MPUs programming manual](docs/stm32-cortex-m4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)

  {{0-1}}
********************************************************************************

```asm Multiply and divide instructions, with optional accumulate (S. 109)
;multiply with accumulate
;R1 = (R2 x R3) + R4
MLA R1, R2, R3, R4

;unsigned long multiply, with accumulate, 32-bit operands, producing a 64-bit result with 32-Top- & 32-Bottom-bits
;R6(T), R3(B) = (R2 x R7) + R6 + R3
UMAAL R3, R6, R2, R7

;signed divide
;R0 = R2 / R4
SDIV R0, R2, R4
```

********************************************************************************

  {{1-2}}
********************************************************************************

```asm Saturating instructions (S. 125)
;logical shift left value in R1 by 4, then saturate it as a signed 16-bit value and write it back to R1
;R1 = sat(R1 << 4, #16)
SSAT R1, #16, R1, LSL #4
```

********************************************************************************

  {{2-3}}
********************************************************************************

```asm Floating-point instructions (S. 149)
;move to arm core register R1 from floating-point system register FPEXC
VMRS R1, FPEXC

;floating-point multiply with negation followed by subtract
;S1 = (S2 x S3) - S1
VNMLS.F32 S1, S2, S3

;floating-point Square root
;S1 = sqrt(S2)
VSQRT.F32 S1, S2
```

********************************************************************************

  {{3-4}}
********************************************************************************

```asm Miscellaneous instructions (S. 180)
;data synchronization barrier
;waits until all explicit memory accesses in front of it are completed
DSB

;instruction synchronization barrier
;clears the processor's pipeline, so that all instructions following the ISB instruction are re-fetched from cache or memory
ISB
```

********************************************************************************

## Anwendung auf dem Nucleo-64 Board

```ascii
                                STM32 F 401 R E T 6
                                  A   A  A  A A A A
                                  |   |  |  | | | |
ARM-based 32-bit microcontroller -.   |  |  | | | |
                                      |  |  | | | |
General-purpose ----------------------.  |  | | | |
                                         |  | | | |
401 family ------------------------------.  | | | |
                                            | | | |
64 pins ------------------------------------. | | |
                                              | | |
512 KB of flash memory -----------------------. | |
                                                | |
LQFP package -----------------------------------. |
                                                  |
–40 to 85 °C -------------------------------------.
```

<br>

- ARMv7E-M[10] Architektur
- ARM Cortex-M4F-Kern

<br>

- 1-Zyklus Hardware-Multiplizierer
- Hardware-Dividierer
- DSP-Erweiterung
- Sättigungsarithmetik
- FPU

  {{1}}
********************************************************************************

**Mini-Projekt DSP**

1. Entfernung messen und digitalisieren -> `ADC`
2. DSP-Algorithmus anwenden -> Noise-Reduction, Frequenzanpassung für Tonausgabe
3. Ton ausgeben -> `DAC`

<br>

- *Fertigstellung bis zur nächsten Übung, am 8. Juli*

********************************************************************************

## Referenzen

### Literatur

  {{0}}
********************************************************************************

- Dr. Yifeng Zhu. *Embedded Systems with ARM Cortex-M Microcontrollers in Assembly Language and C* (3. Aufl.).<br>
  E-Man Press LLC, 2017. ISBN 978-0-9826926-6-0

- Edmund Weitz. *Konkrete Mathematik (nicht nur) für Informatiker* (1. Aufl.).<br>
  Springer Spektrum, 2018. ISBN 978-3-658-2154-4

********************************************************************************

  {{1}}
********************************************************************************

- https://en.wikipedia.org/wiki/Digital_signal_processor
- https://www.ibr.cs.tu-bs.de/courses/ws9798/seminar/haverkamp/seminar.html#385
- https://technobyte.org/dsp-advantages-disadvantages-block-diagram-applications/
- https://www.wikiwand.com/de/Digitaler_Signalprozessor
- https://liascript.github.io/course/?https://raw.githubusercontent.com/TUBAF-IfI-LiaScript/VL_DigitaleSysteme/main/lectures/11_CortexMController.md#3
- https://www.st.com/en/microcontrollers-microprocessors/stm32f401re.html

********************************************************************************

### Bilder

  {{0}}
********************************************************************************

- https://en.wikipedia.org/wiki/NEC_%C2%B5PD7720#/media/File:ST010_01.jpg
- https://www.pexels.com/de-de/foto/mann-person-smartphone-zerbrochen-6755091/
- https://dewesoft.com/upload/news/daq/adc/signal-aliasing.png

********************************************************************************

## Tools, Issues & Tricks

### Tools

- [Compiler Explorer](https://godbolt.org/)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
- [VSC LiaScript Preview Extension](https://marketplace.visualstudio.com/items?itemName=LiaScript.liascript-preview)
- [ASCII to SVG Editor](https://andre-dietrich.github.io/elm-svgbob/)
@com(`- [Serial Plotter](https://github.com/devinaconley/arduino-plotter)`)

### Issues

- HTML-Kommentare werden in der VSC-Preview als Inahlt angezeigt
- Links über Einblendungen sind nicht möglich
- Im Dark-Mode ist die Liste der Editor-Stile in den Einstellungen falsch koloriert
- ASCII-Art wird im Dark-Mode als Weiß-auf-Schwarz angezeigt
- Inline-Code ist im Dark-Mode schlecht lesbar

<br>

- Wie kann der Stil von Code-Feldern in der Config festgelegt werden?

<br>

- Lösungsansätze gibt's auch schon ;)

### Tricks

- Tooltips@tt(`Fancy Tooltip`)

```html
<!-- Macro im Header -->
@ttc: <a title='@0' href="#" class="lia-link"><sup><button aria-describedby='footnote-@1' class="lia-btn lia-btn--transparent text-highlight" id='footnote-key-@1' style="padding: 2px;">[@1]</button></sup></a>
@tt: @ttc(@0, ? )

<!-- Tooltip Macro nutzen -->
@tt(`Fancy Tooltip`)

<!-- Tooltip Markdown-Style nutzen -->
[[^?]](# 'Orginal Markdwon Tooltip')
```

- Hidden-Scripts für GitHub
  @hsse(`alert("script hidden in img tag of 1x1 transparent pixel");`, `width: 10px; height: 10px; overflow: hidden;`, onmouseover)

```html
<!-- Macro im Header -->
@hsse: <img src='img/hidden_pixel.png' @2='@0' style='@1'>
@hss: @hsse(@0, @1, onload)
@hse: @hsse(@0, '', @1)
@hs: @hss(@0, '')

<!-- Hidden-Script Macro nutzen -->
@hsse(`alert("script hidden in img tag of 1x1 transparent pixel`);`, `width: 10px; height: 10px; overflow: hidden;`, onmouseover)
@hs(`console.log("simple hidden scrip");`)
```

- Kommentare
  @com(`ein Kommentar`)

```html
<!-- Macro im Header -->
@com: <span title='@0'></span>

<!-- Kommentar Macro nutzen -->
@com(`Kommentartext`)
```

- Cookie-basierte Besucherzähler Badge
  <img id="b" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys&left_color=%235b5b5b&right_color=%230fb3ba&query_only" onload='function s(e,t,a=1,s="h`){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}function g(e){let o=e+"=",t=document.cookie.split(";`);for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}let u="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b`),p=window.location.search.split("/`).slice(-1)[0],c=g("v`);c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h`);'>

```html
<img
  id="b"
  src="https://visitor-badge.laobi.icu/badge?page_id=[PAGE_ID]&left_color=%235b5b5b&right_color=%230fb3ba&query_only"
  onload='
    function s(e,t,a=1,s="h`){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}
    function g(e){let o=e+"=",t=document.cookie.split(";`);for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}
    let u="https://visitor-badge.laobi.icu/badge?page_id=[PAGE_ID]&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b`),p=window.location.search.split("/`).slice(-1)[0],c=g("v`);
    c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h`);'
  '
>
<!-- hier [PAGE_ID] ersetzen -->
```
