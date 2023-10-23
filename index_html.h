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
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function webUIinit() { ajaxObj=[];
  peak1=0; rms1=0; freq1=0; peak2=0; rms2=0; freq2=0; relay1=0; relay2=0; doDisplay();
  requestAJAX("getVoltage"); requestAJAX("getRelay"); window.setInterval("getStatus();",10000); }

function doDisplay() {
  id("peak1").innerHTML=peak1; id("rms1").innerHTML=rms1; id("freq1").innerHTML=freq1;
  id("peak2").innerHTML=peak2; id("rms2").innerHTML=rms2; id("freq2").innerHTML=freq2;
  if (relay1==0) { id("relay1").innerHTML="not Active"; } else { id("relay1").innerHTML="Active"; }
  if (relay2==0) { id("relay2").innerHTML="not Starting"; } else { id("relay2").innerHTML="Starting"; } }

function getStatus() { requestAJAX("getVoltage"); requestAJAX("getRelay"); }

function setRelay1() { if (relay1==0) { requestAJAX("setRelay,0,1"); } else { requestAJAX("setRelay,0,0"); } }
function setRelay2() { if (relay2==0) { requestAJAX("setRelay,1,1"); } else { requestAJAX("setRelay,1,0"); } }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getVoltage") {
      peak1=event.target.responseText.split(",")[0]; rms1=event.target.responseText.split(",")[1]; freq1=event.target.responseText.split(",")[2];
      peak2=event.target.responseText.split(",")[3]; rms2=event.target.responseText.split(",")[4]; freq2=event.target.responseText.split(",")[5]; doDisplay(); }
    else if (event.target.url=="getRelay" || event.target.url.startsWith("setRelay")) {
      relay1=event.target.responseText.split(",")[0]; relay2=event.target.responseText.split(",")[1]; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a">neaControl</div></div>
<div><div class="x0b">&nbsp;</div></div>

<div>
<div><div class="x1a">Voltages</div></div>
<div><div class="x2">EVU</div>
     <div class="x2">NEA</div><div>
<div><div class="x4" id="peak1"></div>
     <div class="x4">Volt Peak</div>
     <div class="x4" id="peak2"></div>
     <div class="x4">Volt Peak</div></div>
<div><div class="x4" id="rms1"></div>
     <div class="x4">Volt RMS</div>
     <div class="x4" id="rms2"></div>
     <div class="x4">Volt RMS</div></div>
<div><div class="x4" id="freq1"></div>
     <div class="x4">Hertz</div>
     <div class="x4" id="freq2"></div>
     <div class="x4">Hertz</div></div>
<div><div class="x1a">Remote Switches</div></div>
<div><div class="x3">NEA switchover</div>
     <div class="x3" id="relay1"></div>
     <div class="x3" onclick="setRelay1();">Switch</div></div>
<div><div class="x3">Start NEA Engine</div>
     <div class="x3" id="relay2"></div>
     <div class="x3" onclick="setRelay2();">Start</div></div>
</div>

</body></html>

)";
