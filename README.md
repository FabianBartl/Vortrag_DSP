<!--
version:  0.0.6a

author: Fabian Bartl
email: fabian@informatic-freak.de

event: Praktikum Digitale Systeme
organization: Technische Universität Freiberg

comment: Funktionsweise des Digitalen Signalprozessors (DSP)

icon: https://upload.wikimedia.org/wikipedia/commons/d/de/Logo_TU_Bergakademie_Freiberg.svg

language: de
narrator: Deutsch Female

mode: Presentation
dark: false

@onload
function sc(e,t,n=1,i="h"){const o=new Date;let s=1;switch(i){case"y":s=31557600;break;case"d":s=86400;break;case"m":s=60;break;case"s":s=1;break;case"h":default:s=3600}o.setTime(o.getTime()+n*s*1e3);let r="expires="+o.toUTCString();document.cookie=e+"="+t+";"+r+";path=/"}
function gc(e){let t=e+"=",n=document.cookie.split(";");for(let e=0;e<n.length;e++){let i=n[e];for(;" "==i.charAt(0);)i=i.substring(1);if(0==i.indexOf(t))return i.substring(t.length,i.length)}return null}
function id(){return ([1e7]+-1e3+-4e3+-8e3+-1e11).replace(/[018]/g,e=>(e^crypto.getRandomValues(new Uint8Array(1))[0]&15>>e/4).toString(16))}
function cs() {
	let page = window.location.search.split(".com")[1].slice(1);
	let hash = window.location.hash.slice(1);
	hashes = gc("s");
	if (hashes != null) { if (!hashes.includes(hash)) { sc("s", page+":"+hashes+","+hash, 1, "h"); } }
	else { sc("s", page+":"+hash, 1, "h"); }
}
function lb(id="visitor-badge") {
	let badge = document.getElementById(id);
	let hash = window.location.hash.slice(1);
	let css = {};
	hashes = gc("s");
	if (hashes.includes(hash)) {
		css = { display: "none" };
		badge.src = "https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop";
	}
	else {
		css = { display: "block" };
		badge.src = "https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys";
	}
	Object.assign(badge.style, css);
}
cs();
lb();
@end

import:  https://raw.githubusercontent.com/liascript-templates/plantUML/master/README.md
         https://github.com/LiaTemplates/AVR8js/main/README.md

translation: English translations/English.md
-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://raw.githubusercontent.com/FabianBartl/DSP-DigSys/main/README.md)

# Digitaler Signalprozessor (DSP)

| Parameter             | Kursinformationen                                                                      |
| --------------------- | -------------------------------------------------------------------------------------- |
| **Veranstaltung:**    | @event                                                                                 |
| **Hochschule:**       | @organization                                                                          |
| **Inhalte:**          | @comment                                                                               |
| **Link auf GitHub:**  | [https://github.com/FabianBartl/DSP-DigSys](https://github.com/FabianBartl/DSP-DigSys) |
| **Autoren**           | @author                                                                                |

<img id="visitor-badge" src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop" style="display:block;" onload="cs();lb();">

<!-- <img src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop"> -->
<!-- <img src="https://img.shields.io/badge/visitors-3-blue"> -->
<!-- <img src="https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys"> -->

## Gliederung

| Kurze Übersicht |                                   |
| --------------- | --------------------------------- |
| Geschichte      |                                   |
| Funktionsweise  |                                   |
| Anwendungen     |                                   |
| Mein Beispiel   |                                   |
| Referenzen      |                                   |

## Geschichte

## Funktionsweise

## Anwendungen

## Mein Beispiel

## Referenzen

- https://www.elektroniknet.de/halbleiter/dsp-algorithmen-effizient-implementieren-teil-1.25937.html
- https://de.wikipedia.org/wiki/Digitaler_Signalprozessor
- https://www.ibr.cs.tu-bs.de/courses/ws9798/seminar/haverkamp/seminar.html#385
- http://www.krucker.ch/Skripten-Uebungen/DSPUeb/DSP%20Uebungen.html
- https://www.minidsp.de/anwendungsbeispiele/
- http://www.uibel.net/bauvor/bv_tutorials/dsp/dsp.html
- http://www.elektro-archiv.de/archiv/d/dsp/
- https://github.com/jgaeddert/liquid-dsp
