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
.x5    { background-color:#e0e0e0; padding:0.3em 0em; width:19%; font-size:1.4em; }
.but   { background-color:#f0f0f0; padding:0.1em 0.4em; }
</style>
<script>

function webUIinit() {
  ajaxObj=[]; red="#E09090"; green="#90E090"; yellow="#FFE460"; gray="#e0e0e0"; blue="#c2d5ed";
  secret=""; challenge=""; getChallenge(); window.setInterval("getChallenge();",9000); doDisplay(); }

function doDisplay() {
  id("secret").innerHTML="Secret: "+"X".repeat(secret.length); }

function getChallenge() { requestAJAX("getChallenge"); }

function doClear() { secret=""; doDisplay(); }
function doLogin() { location.replace('/'+String(secret^challenge)+"/"); }
function setChar(value) { secret+=value; if (secret.length>10) { secret=""; } doDisplay(); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getChallenge") { challenge=event.target.responseText.split(",")[0]; } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a">neaControl</div></div>
<div><div class="x0b">Emergency power system</div></div>

<div>
<div><div class="x1a" id="secret"></div></div>
<div><div class="x5" onclick="setChar('0');"><span class="but">0</span></div>
     <div class="x5" onclick="setChar('1');"><span class="but">1</span></div>
     <div class="x5" onclick="setChar('2');"><span class="but">2</span></div>
     <div class="x5" onclick="setChar('3');"><span class="but">3</span></div>
     <div class="x5" onclick="setChar('4');"><span class="but">4</span></div></div>
<div><div class="x5" onclick="setChar('5');"><span class="but">5</span></div>
     <div class="x5" onclick="setChar('6');"><span class="but">6</span></div>
     <div class="x5" onclick="setChar('7');"><span class="but">7</span></div>
     <div class="x5" onclick="setChar('8');"><span class="but">8</span></div>
     <div class="x5" onclick="setChar('9');"><span class="but">9</span></div></div>
<div><div class="x1a"">&nbsp;</div></div>
<div><div class="x2" onclick="doClear();"><span class="but">Clear</span></div>
     <div class="x2" onclick="doLogin();"><span class="but">Login</span></div></div>
</div>

</body></html>

)";
