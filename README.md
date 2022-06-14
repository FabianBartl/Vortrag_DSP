<!--
version:  0.0.11g

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

script: scripts.js
script: https://cdnjs.cloudflare.com/ajax/libs/crypto-js/4.1.1/crypto-js.min.js

import: https://raw.githubusercontent.com/liascript-templates/plantUML/master/README.md
import: https://github.com/LiaTemplates/AVR8js/main/README.md

translation: English translations/English.md

@onload
function setCookie(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}
function getCookie(t){let e=t+"=",n=document.cookie.split(";");for(let t=0;t<n.length;t++){let l=n[t];for(;" "==l.charAt(0);)l=l.substring(1);if(0==l.indexOf(e))return l.substring(e.length,l.length)}return null}

function createSession() {
	let page = window.location.search.split(".com")[1].slice(1);
	let hash = page;
	// let hash = CryptoJS.MD5(page).toString().slice(0, 3);
	let cookie = getCookie("_vb");
	
	if (cookie != null) {
		if (!cookie.includes(hash)) {
			setCookie("_vb", cookie+","+hash, 1, "h");
		}
	} else {
		setCookie("_vb", hash, 1, "h");
	}
}

displayVisitorBadge(id="visitor-badge") {
	let url = "https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba";
	let badge = document.getElementById(id);
	
	let page = window.location.search.split(".com")[1].slice(1);
	let hash = page;
	// let hash = CryptoJS.MD5(page).toString().slice(0, 3);
	let cookie = getCookie("_vb");
	
	if (cookie != null) {
		if (cookie.includes(hash)) {
			badge.src = url + "&query_only=true";
		} else {
			badge.src = url;
		}
	} else {
		badge.src = url;
	}
}

createSession();
displayVisitorBadge();
@end
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

<img id="visitor-badge" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba&query_only=true" onload="displayVisitorBadge();">
<!-- <img src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys&left_color=%235b5b5b&right_color=%230fb3ba&query_only=true"> -->

<!--
# %23
lighter:
	left:	#5b5b5b
	right:	#0fb3ba
darker:
	left:	#4b4b4b
	right:	#399193
-->


## Gliederung

<ol>
	<li>Geschichte</li>
	<li>Aufbau und Funktion</li>
	<li>Anwendungen</li>
	<li>Simulation</li>
	<li>Mein Beispiel</li>
	<li>Referenzen</li>
</ol>

## Geschichte

**Begriff *DSP***

| `digital signal processor`                            | `digital signal processing`                           |
| ----------------------------------------------------- | ----------------------------------------------------- |
| spezialisierter Mikroprozessor                        | algorithmische Verarbeitung digitaler Signale         |


                    {{1-2}}
********************************************************************************

**Einordnung**

********************************************************************************

## Aufbau und Funktion

* https://www.st.com/content/st_com/en/arm-32-bit-microcontrollers/arm-cortex-m4.html

## Anwendungen

## Simulation

* Simulink mit MathWorks (MATLAB)
	* Tutorials anschauen
	* 'Interaktives' Beispiel erstellen

>https://www.mathworks.com/matlabcentral/fileexchange/43155-dsp-system-toolbox-support-package-for-arm-cortex-m-processors

## Mein Beispiel

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
