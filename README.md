<!--
version: 1.2

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

@vb: <img id="b" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/vortrag_dsp&left_color=%235b5b5b&right_color=%230fb3ba&query_only" onload='function s(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}function g(e){let o=e+"=",t=document.cookie.split(";");for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}let u="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/vortrag_dsp&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b"),p=window.location.search.split("/").slice(-1)[0],c=g("v");c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h");'>
-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://raw.githubusercontent.com/FabianBartl/Vortrag_DSP/main/README.md)

# Digitaler Signalprozessor (DSP)

| Parameter            | Kursinformationen                                                                                  |
| -------------------- | -------------------------------------------------------------------------------------------------- |
| **Veranstaltung**    | Praktikum Digitale Systeme                                                                         |
| **Hochschule**       | Technische Universit??t Bergakademie Freiberg                                                       |
| **Inhalte**          | @comment                                                                                           |
| **Link auf GitHub**  | [https://github.com/FabianBartl/Vortrag_DSP](https://github.com/FabianBartl/Vortrag_DSP/tree/main) |
| **Autoren**          | @author                                                                                            |
| **Version**          | V @version                                                                                         |

@vb

## Motivation

  {{0-4}}
********************************************************************************

**Mittelwert-Filter**

- Durchschnitt der z.B. letzten drei Werte:
  $$A=\frac{x_{i-2}+x_{i-1}+x_i}3$$

********************************************************************************

  {{1-4}}
********************************************************************************

```c C-Code
#define SIZE 6

int main()
{
    int x[SIZE] = {4, 1, 3, 2, 3, 3};
    int A;

    int i = SIZE; // size of x[]
    A = (x[i-2] + x[i-1] + x[i]) / 3;
    
    return A;
}
```

********************************************************************************

  {{2-3}}
********************************************************************************

```asm AVR-Assembly
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
.LC0:
  .word 4
  .word 1
  .word 3
  .word 2
  .word 3
  .word 3
main:
  push r28
  push r29
  in r28,__SP_L__
  in r29,__SP_H__
  sbiw r28,16
  in __tmp_reg__,__SREG__
  cli
  out __SP_H__,r29
  out __SREG__,__tmp_reg__
  out __SP_L__,r28
  ldi r24,lo8(12)
  ldi r30,lo8(.LC0)
  ldi r31,hi8(.LC0)
  movw r26,r28
  adiw r26,5
  0:
  ld r0,Z+
  st X+,r0
  dec r24
  brne 0b
  ldi r24,lo8(6)
  ldi r25,0
  std Y+2,r25
  std Y+1,r24
  ldd r24,Y+1      ;
  ldd r25,Y+2      ;
  sbiw r24,2       ;
  lsl r24          ;   
  rol r25          ;   
  movw r18,r28     ; 
  subi r18,-1      ;
  sbci r19,-1      ;
  add r24,r18      ;
  adc r25,r19      ;
  adiw r24,4       ;
  movw r30,r24     ; 
  ld r18,Z         ;    
  ldd r19,Z+1      ;
  ldd r24,Y+1      ;
  ldd r25,Y+2      ;
  sbiw r24,1       ;      
  lsl r24          ;   
  rol r25          ;   
  movw r20,r28     ; 
  subi r20,-1      ;
  sbci r21,-1      ;
  add r24,r20      ;
  adc r25,r21      ;
  adiw r24,4       ;
  movw r30,r24     ; 
  ld r24,Z         ;    
  ldd r25,Z+1      ;
  add r18,r24      ;
  adc r19,r25      ;
  ldd r24,Y+1      ;    
  ldd r25,Y+2      ;
  lsl r24          ;   
  rol r25          ;   
  movw r20,r28     ; 
  subi r20,-1      ;
  sbci r21,-1      ;
  add r24,r20      ;
  adc r25,r21      ;
  adiw r24,4       ;
  movw r30,r24     ; 
  ld r24,Z         ;    
  ldd r25,Z+1      ;      
  add r24,r18      ;
  adc r25,r19      ;
  ldi r18,lo8(3)   ;   
  ldi r19,0        ;
  movw r22,r18     ; 
  call __divmodhi4 ;     
  movw r24,r22     ; 
  std Y+4,r25      ;
  std Y+3,r24      ;
  ldd r24,Y+3
  ldd r25,Y+4
  adiw r28,16
  in __tmp_reg__,__SREG__
  cli
  out __SP_H__,r29
  out __SREG__,__tmp_reg__
  out __SP_L__,r28
  pop r29
  pop r28
  ret
```

********************************************************************************

  {{3-4}}
********************************************************************************

```asm ARMv7-Assembly
main:
  push {r4, r5, r6, r10, r11, lr}
  add r11, sp, #16
  sub sp, sp, #36
  mov r0, #0
  str r0, [r11, #-20]
  ldr r2, .LCPI0_1
.LPC0_0:
  add r2, pc, r2
  add r1, sp, #8
  mov r0, r1
  ldm r2, {r3, r4, r5, r6, r12, lr}
  stm r0, {r3, r4, r5, r6, r12, lr}
  mov r0, #6
  str r0, [sp]
  ldr r2, [sp]                ;
  add r3, r1, r2, lsl #2      ;
  ldr r0, [r3, #-8]           ;
  ldr r3, [r3, #-4]           ;
  add r0, r0, r3              ;
  ldr r1, [r1, r2, lsl #2]    ;
  add r2, r0, r1              ;
  ldr r3, .LCPI0_0            ;
  smull r1, r0, r2, r3        ;
  add r0, r0, r0, lsr #31     ;
  str r0, [sp, #4]            ;
  ldr r0, [sp, #4]
  sub sp, r11, #16
  pop {r4, r5, r6, r10, r11, lr}
  bx lr
.LCPI0_0:
  .long 1431655766 @ 0x55555556
.LCPI0_1:
  .long .L__const.main.x-(.LPC0_0+8)
.L__const.main.x:
  .long 4 @ 0x4
  .long 1 @ 0x1
  .long 3 @ 0x3
  .long 2 @ 0x2
  .long 3 @ 0x3
  .long 3 @ 0x3
```

********************************************************************************

  {{4}}
********************************************************************************

1. DSP?
2. Entwicklung
3. Aufbau & Funktion
4. Anwendung auf dem Nucleo-64 Board
5. Referenzen
6. Tools, Issues & Tricks

********************************************************************************

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

- st??ndige Umwandlung von Signalen von analog in digital und umgekehrt
- schnelle digitale Manipulation der Daten
- harte Echtzeitf??higkeit (sehr geringe Latenz)

********************************************************************************

  {{3}}
********************************************************************************

- die meisten Allzweck-Mikroprozessoren und Betriebssysteme k??nnen DSP-Algorithmen erfolgreich ausf??hren
- aber ein spezialisierter DSP bietet tendenziell eine kosteng??nstigere L??sung mit besserer Leistung
@com(`geringere Latenz, kleinerer Energieverbrauch`)

********************************************************************************

### Vor- & Nachteile und Anwendungen

  {{0}}
********************************************************************************

**Vorteile**

- Fehlererkennung und -korrektur ist m??glich
- einfachere Verarbeitung und Speicherung der Daten
- Verschl??sselung
- einfachere Modifikation / Programmierung

********************************************************************************

  {{1}}
********************************************************************************

**Nachteile gegen??ber analoger Verarbeitung**

- h??herer Stromverbrauch, da DSP aus aktiven Komponenten besteht
- Verlust von Informationen durch Quantisierung der Daten

********************************************************************************

  {{2}}
********************************************************************************

**Anwendungen**

- Regeltechnik @com(`Motosteuerung`)
- Digitale Bild-, Ton- und Videoverarbeitung @com(`Soundkarten, JPEG-/MP3-Komprimierung`)
- Telekommunikation @com(`Digital Radio, Telefonieren`)
- Ersatz f??r aufwendigere analoge Filtertechnik

********************************************************************************

### Kategorien

  {{0}}
********************************************************************************

**Floating-Point DSP**

- gro??er Zahlenbereich, h??here Genauigkeit (`IEEE 754`-Format)
- `FPU`@tt(`Floating-Point Unit`) erh??ht Stromverbrauch und Kosten

********************************************************************************

  {{1}}
********************************************************************************

**Geeignet f??r Produkte**

 - in niedriger St??ckzahl
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

**Geeignet f??r Produkte**

- in gro??er Str??ckzahl
- mit festem Zahlenbereich
- besser f??r Eingebettete Systeme geeignet, da g??nstiger und stromsparender

********************************************************************************

## Entwicklung

  {{0}}
********************************************************************************

**Anf??nge in den 1970er**

- TI@tt(`Texas Instruments`) entwickelte von 1976-78 den ersten *Speak & Spell*[^1], der einen `TMS5100` enthielt - der erste DSP der Branche
- AMI@tt(`American Microsystems`) brachte 1978 den DSP `S2811` auf den Markt, dieser verf??gte bereits ??ber einen Hardware-Multiplikator
@com(`Wurde als Peripherieger??t f??r Motorola 6800 entwickelt, musste aber vom Host initialisiert werden. War auf dem Markt nicht erfolgreich.`)
- Intel brachte 1979 den `2920` als "analogen Signalprozessor" auf den Markt, mit On-Chip- `ADC` / `DAC`, aber ohne Hardware-Multiplikator
@com(`War auf dem Markt nicht erfolgreich.`)

********************************************************************************

  {{1}}
********************************************************************************

**1. Generation in den 1980er**

- 1980 stellten AT&T und NEC@tt(`Nippon Electric Corporation`) die ersten eigenst??ndigen und vollst??ndigen DSPs auf der ISSCC@tt(`International Solid-State Circuits Conference`) vor, den `DSP1` und `NEC ??PD7720`[^2]
- der `NEC ??PD7720` wurde f??r Sprachband-Anwendungen eingef??hrt und war einer der kommerziell erfolgreichsten fr??hen DSPs
@com(`Anwendungen, die Frequenzen der gesprochenen Sprache ??bermitteln`)
- 1983 stellte TI den DSP `TMS32010` vor, dieser basierte auf der Harward-Architektur, verf??gte u.a. ??ber `MAC`@tt(`Multiply-Accumulate Operation`)-Anweisungen und konnte mit 16-Bit-Zahlen arbeiten
- ca. 390 ns Ausf??hrungsdauer f??r eine `MAC`-Operation

********************************************************************************

  {{2}}
********************************************************************************

**2. Generation ab ca. 1985**

- Hardwarebeschleunigung von Schleifen mittels `AGU`@tt(`Address Generation Unit`)
- teilweise mit 24-Bit-Variablen
- ca. 21 ns Ausf??hrungsdauer f??r eine `MAC`-Operation
- Bsp.: `AT&T DSP16A`, `Motorola 56000`

********************************************************************************

  {{3}}
********************************************************************************

**3. Generation in den 1990er**

- Anwendungsspezifische DSPs erm??glichten als Coprozessoren direkte Hardwarebeschleunigung sehr spezifischer und komplexer mathematischer Probleme 
@com(`Bsp.: Fourier-Transformation, Matrixoperationen`)
- einige Chips, wie der `Motorola MC68356`, nutzten mehrere Prozessorkerne zur Parallelisierung
- Bsp.: `TI TMS320C541`, `TMS 320C80`

********************************************************************************

  {{4}}
********************************************************************************

**4. Generation**

- `SIMD`[^3]-Erweiterungen wurden hinzugef??gt, diese dienen der echten parallelen Ausf??hrung von vielen gleichen Operationen auf Hardware-Ebene
  @com(`VLIW: Very long instruction word`)
- h??here Taktraten
- ca. 3 ns Ausf??hrungsdauer f??r eine `MAC`-Operation

********************************************************************************

[^1]: **Speak & Spell** war eine Lernspielzeugserie von elektronische Kindercomputern von TI, die aus einem linearen pr??diktiv kodierenden Sprachsynthesizer, einer Tastatur und einem Steckplatz f??r ROMs bestanden. Es war eines der fr??hesten tragbaren elektronischen Ger??te mit Display, dass austauschbare ROMs verwendete.<br><br>
  ![](img/Speak-and-Spell.jpg)
  **Der Speak & Spell Wurde 2009 zum IEEE Milestone ernannt.**

  -- [Wikipedia](https://en.wikipedia.org/wiki/Speak_%26_Spell_(toy)

[^2]: ![](img/ST010_01.jpg)
  Der von NEC 1980 entwickelte DSP `NEC ??PD7720` war einer der popul??rsten DSPs dieser Zeit.

  -- [Wikipedia](https://en.wikipedia.org/wiki/NEC_%C2%B5PD7720)

[^3]: `SIMD` steht f??r **Single instruction, multiple data**, dieser Befehlssatz implementiert eine echte parallele Ausf??hrung von gleichartigen Rechenoperationen auf Hardware-Ebene, die mit einem Befehlsaufruf mehrere Daten parallel verarbeiten.<br>
  `SIMD` eignet sich besonders gut f??r die Verarbeitung von Bild-, Ton- und Videodaten, da identische Operationen f??r zum Beispiel viele einzelne Bildpunkte ausgef??hrt werden m??ssen.

  -- [Wikipedia](https://de.wikipedia.org/wiki/Flynnsche_Klassifikation#SIMD_(Single_Instruction,_Multiple_Data)

### Moderne DSPs

  {{0}}
********************************************************************************

- liefern h??here Leistung, u.a. durch schnellen Cache, ein breites Bussystem, und `DMA`@tt(`Direct Memory Access`)
- viele verschiedene Arten, jeder f??r bestimmte Aufgaben besser geeignet
- DSPs kosten zwischen 1,50 ??? bis hin zu 300 ???
- TI ist heute Marktf??hrer bei Allzweck DSPs

********************************************************************************

  {{1}}
********************************************************************************

**`C6000`-DSP-Serie von TI**

- 1,2 GHz Taktrate
- 8 MB 2nd Level Cache
- 64 `DMA`-Kan??le
- teilweise bis zu 8000 MIPS@tt(`Mio. Instruktionen pro Sekunde`)
- 8 Operationen pro Taktzyklus
- kompatibel und vielen Peripherieger??ten und Bussen
- unterst??tzen in der neuesten Generation Floating-Point und Fixed-Point Verarbeitung
{{2}}- der Chip `TMS320C6474` enth??lt drei solcher DSPs und kostet ca. 250 ???

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
5. analoger Low-Pass-Filter, um Hochfrequenzkomponenten zu entfernen @com(`Gl??ttungsfilter`)

********************************************************************************

@com(`??????????????????????????????`)

  {{1-2}}
********************************************************************************

```ascii
 ???   ??????      ????????????     +-----+     +-----*-------*-*     +-------------+     +-------------*-*     +-----+     ???           ???????????? 
 ???   ??????  ???????????????        |     |     |-----|---*-* | |     |             |     |---------*-* | |     |     |     ???       ???????????????    
 ???   ???????????????        --> | ADC | --> |-----|-* | | | | --> | Algorithmus | --> |-----*-* | | | | --> | DAC | --> ???   ???????????????        
 ???????????????                |     |     |-*-* | | | | | |     |             |     |-*-* | | | | | |     |     |     ???????????????            
 ????????????????????????????????????????????????     +-----+     +-+-+-+-+-+-+-+-+     +-------------+     +-+-+-+-+-+-+-+-+     +-----+     ???????????????????????????????????????????????? 
```

********************************************************************************

  {{2}}
********************************************************************************

```ascii
 ???   ??????      ????????????     +-----+     +-----*-------*-*     +-------------+     +-------------*-*     +-----+     ???           ???????????? 
 ???   ??????  ???????????????        |     |     |-----|---*-* | |     |             |     |---------*-* | |     |     |     ???       ???????????????    
 ???   ???????????????        --> | ADC | --> |-----|-* | | | | --> | Algorithmus | --> |-----*-* | | | | --> | DAC | --> ???   ???????????????        
 ???????????????             A  |     |     |-*-* | | | | | |     |             |     |-*-* | | | | | |     |     |  A  ???????????????            
 ????????????????????????????????????????????????  |  +-----+     +-+-+-+-+-+-+-+-+     +-------------+     +-+-+-+-+-+-+-+-+     +-----+  |  ???????????????????????????????????????????????? 
                   |                                                                                       |
                   ??                                                                                       ??
            Anti-Aliasing Filter                                                                     Gl??ttungsfilter
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

  - Rechenwerk f??r Accumulate-Operationen wie `MAC`
  - `FPU`@tt(`Floating-Point Unit`) f??r Floating-Point Operationen
  - Hardware-Multiplizierer und -Dividierer
  - weitere `ALU`'s zur parallelen Ausf??hrung von Berechnungen

********************************************************************************

  {{2}}
********************************************************************************

- `PLU`@tt(`Parallel Logic Unit`) dient der von der `ALU` unabh??ngigen logischen Datenmanipulation

********************************************************************************

  {{3}}
********************************************************************************

- `AGU`@tt(`Address Generation Unit`) dient der von der `ALU` unabh??ngigen Berechnungen von Adressen f??r Schleifen und Spr??nge mittels programmierbarer Counter und Shifter, etc.

********************************************************************************

  {{4}}
********************************************************************************

>Alle Komponenten k??nnen parallel verwendet werden.

********************************************************************************

### Ausgew??hlte Assembly-Direktiven

-> [STM32 Cortex??-M4 MCUs and MPUs programming manual](docs/stm32-cortex-m4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)

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
???40 to 85 ??C -------------------------------------.
```

<br>

- ARMv7E-M[10] Architektur
- ARM Cortex-M4F-Kern

<br>

- 1-Zyklus Hardware-Multiplizierer
- Hardware-Dividierer
- DSP-Erweiterung
- S??ttigungsarithmetik
- FPU

  {{1}}
********************************************************************************

**Mini-Projekt DSP**

1. Entfernung messen und digitalisieren -> `ADC`
2. DSP-Algorithmus anwenden -> Noise-Reduction, Frequenzanpassung f??r Tonausgabe
3. Ton ausgeben -> `DAC`

<br>

- *Fertigstellung bis zur n??chsten ??bung, am 8. Juli*

********************************************************************************

## Referenzen

### Literatur

  {{0}}
********************************************************************************

- Dr. Yifeng Zhu. *Embedded Systems with ARM Cortex-M Microcontrollers in Assembly Language and C* (3. Aufl.).<br>
  E-Man Press LLC, 2017. ISBN 978-0-9826926-6-0

- Edmund Weitz. *Konkrete Mathematik (nicht nur) f??r Informatiker* (1. Aufl.).<br>
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
- Links ??ber Einblendungen sind nicht m??glich
- Im Dark-Mode ist die Liste der Editor-Stile in den Einstellungen falsch koloriert
- ASCII-Art wird im Dark-Mode als Wei??-auf-Schwarz angezeigt
- Inline-Code ist im Dark-Mode schlecht lesbar

<br>

- Wie kann der Stil von Code-Feldern in der Config festgelegt werden?

<br>

- L??sungsans??tze gibt's auch schon ;)

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

- Hidden-Scripts f??r GitHub
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

- Cookie-basierte Besucherz??hler Badge
  @vb

```html
<img
  id="b"
  src="https://visitor-badge.laobi.icu/badge?page_id=[PAGE_ID]&left_color=%235b5b5b&right_color=%230fb3ba&query_only"
  onload='
    function s(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}
    function g(e){let o=e+"=",t=document.cookie.split(";");for(let e=0;e<t.length;e++){let i=t[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(o))return i.substring(o.length,i.length)}return null}
    let u="https://visitor-badge.laobi.icu/badge?page_id=[PAGE_ID]&left_color=%235b5b5b&right_color=%230fb3ba",b=document.getElementById("b"),p=window.location.search.split("/").slice(-1)[0],c=g("v");
    c&&c.includes(p)?b.src=u+"&query_only":b.src=u;s("v",p,2,"h");'
  '
>
<!-- hier [PAGE_ID] ersetzen -->
```
