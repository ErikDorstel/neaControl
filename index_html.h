const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>neaControl</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/neaControl">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1b   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:49%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
.but   { background-color:#f0f0f0; padding:0.1em 0.4em; }
</style>
<script>

function webUIinit() { ajaxObj=[];
  peak1=0; rms1=0; freq1=0; cond1=0; peak2=0; rms2=0; freq2=0; cond2=0; relay1=0; relay2=0; locked=1; doDisplay();
  requestAJAX("getVoltage"); requestAJAX("getRelay"); window.setInterval("getStatus();",10000); }

function doDisplay() {
  if (cond1==0) { id("evu").style.backgroundColor="#E09090"; } else { id("evu").style.backgroundColor="#90E090"; }
  if (cond2==0) { id("nea").style.backgroundColor="#E09090"; } else { id("nea").style.backgroundColor="#90E090"; }
  id("peak1").innerHTML=peak1+" Vpeak"; id("rms1").innerHTML=rms1+" Vrms"; id("freq1").innerHTML=freq1+" Hz";
  id("peak2").innerHTML=peak2+" Vpeak"; id("rms2").innerHTML=rms2+" Vrms"; id("freq2").innerHTML=freq2+" Hz";
  if (relay1==0) { id("relay1").innerHTML="Idle"; id("relay1").style.backgroundColor="#e0e0e0"; } else { id("relay1").innerHTML="Starting"; id("relay1").style.backgroundColor="#FFE460"; }
  if (relay2==0) { id("relay2").innerHTML="Idle"; id("relay2").style.backgroundColor="#e0e0e0"; } else { id("relay2").innerHTML="Active"; id("relay2").style.backgroundColor="#FFE460"; }
  if (locked==0) { id("locked").innerHTML="Unlocked"; id("locked").style.backgroundColor="#e0e0e0"; id("lock").innerHTML="Lock"; }
  else { id("locked").innerHTML="Locked"; id("locked").style.backgroundColor="#E09090"; id("lock").innerHTML="Unlock"; } }

function getStatus() { requestAJAX("getVoltage"); requestAJAX("getRelay"); }

function toggleRelay1() { if (locked==0) { setLock(); if (relay1==0) { requestAJAX("setRelay,0,1"); setRelay1Timer(); } else { requestAJAX("setRelay,0,0"); } } }
function setRelay1Timer() { if (typeof relay1Timer!=='undefined' ) { window.clearInterval(relay1Timer); } relay1Timer=window.setTimeout("unsetRelay1();",2000); }
function unsetRelay1() { requestAJAX("setRelay,0,0"); }
function toggleRelay2() { if (locked==0) { setLock(); if (relay2==0) { requestAJAX("setRelay,1,1"); } else { requestAJAX("setRelay,1,0"); } } }
function toggleLock() { if (locked==0) { locked=1; } else { locked=0; setLockTimer(); } doDisplay(); }
function setLockTimer() { if (typeof lockTimer!=='undefined' ) { window.clearInterval(lockTimer); } lockTimer=window.setTimeout("setLock();",5000); }
function setLock() { locked=1; doDisplay(); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getVoltage") {
      peak1=event.target.responseText.split(",")[0]; rms1=event.target.responseText.split(",")[1];
      freq1=event.target.responseText.split(",")[2]; cond1=event.target.responseText.split(",")[3];
      peak2=event.target.responseText.split(",")[4]; rms2=event.target.responseText.split(",")[5];
      freq2=event.target.responseText.split(",")[6]; cond2=event.target.responseText.split(",")[7]; doDisplay(); }
    else if (event.target.url=="getRelay" || event.target.url.startsWith("setRelay")) {
      relay1=event.target.responseText.split(",")[0]; relay2=event.target.responseText.split(",")[1]; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a">neaControl</div></div>
<div><div class="x0b">&nbsp;</div></div>

<div>
<div><div class="x1a">Voltages</div></div>
<div><div class="x2" id="evu">EVU</div>
     <div class="x2" id="nea">NEA</div><div>
<div><div class="x2" id="peak1"></div>
     <div class="x2" id="peak2"></div></div>
<div><div class="x2" id="rms1"></div>
     <div class="x2" id="rms2"></div></div>
<div><div class="x2" id="freq1"></div>
     <div class="x2" id="freq2"></div></div>
<div><div class="x1a">Remote Switches</div></div>
<div><div class="x2" id="relay1"></div>
     <div class="x2" id="relay2"></div></div>
<div><div class="x2" onclick="toggleRelay1();"><span class="but">Start Engine</span></div>
     <div class="x2" onclick="toggleRelay2();"><span class="but">Switchover</span></div></div>
<div><div class="x1b" id="locked"></div></div>
<div><div class="x1b" onclick="toggleLock();"><span class="but" id="lock"></span></div></div>
</div>

</body></html>

)";
