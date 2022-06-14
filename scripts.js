function setCookie(e,t,a=1,s="h"){const c=new Date;let i=1;switch(s){case"y":i=31557600;break;case"d":i=86400;break;case"m":i=60;break;case"s":i=1;break;case"h":default:i=3600}c.setTime(c.getTime()+a*i*1e3);let o="expires="+c.toUTCString();document.cookie=e+"="+t+";"+o+";path=/"}
function getCookie(t){let e=t+"=",n=document.cookie.split(";");for(let t=0;t<n.length;t++){let l=n[t];for(;" "==l.charAt(0);)l=l.substring(1);if(0==l.indexOf(e))return l.substring(e.length,l.length)}return null}

function createSession() {
	let page = window.location.search.split(".com")[1].slice(1);
	let hash = window.location.hash.slice(1);
	let hashes = getCookie("_vb");
	if (hashes != null) {
		if (!hashes.includes(hash)) {
			setCookie("_vb", hashes+","+hash, 1, "h");
		}
	} else {
		setCookie("_vb", page+":"+hash, 1, "h");
	}
}

displayVisitorBadge() {
	let url = "https://visitor-badge.laobi.icu/badge?page_id=fabianbartl/dsp-digsys-devlop&left_color=%235b5b5b&right_color=%230fb3ba";
	let badge = "visitor-badge";
	let page = window.location.search.split(".com")[1].slice(1);
	let hash = window.location.hash.slice(1);
	let hashes = getCookie("_vb");
	
	if (getCookie("_vb").includes(page)) {
		if (hashes != null) {
			if (!hashes.includes(hash)) {
				badge.src = url + "&query_only=true";
			}
		} else {
			badge.src = url;
		}
	}
}