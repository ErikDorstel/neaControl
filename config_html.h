const char *config_html=R"(

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
td     { text-align:right; padding:0.2em 0em; }
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
.left  { text-align:left; padding:0.2em 0em; }
</style>
<script>

function webUIinit() {
  ajaxObj=[]; red="#E09090"; green="#90E090"; yellow="#FFE460"; gray="#e0e0e0"; blue="#c2d5ed";
  peak1=0; rms1=0; freq1=0; cond1=0; time1=0; peak2=0; rms2=0; freq2=0; cond2=0; time2=0;
  peakCal1=0; rmsCal1=0; peakCal2=0; rmsCal2=0; changed=0; locked=1; doDisplay();
  setStatusTimer(1); setLogoutTimer(); }

function doDisplay() {
  if (cond1==0) { id("evu").style.backgroundColor=red; }
  else { if (time1>=30) { id("evu").style.backgroundColor=green; } else { id("evu").style.backgroundColor=yellow; } }

  if (cond2==0) { if (cond1==0) { id("nea").style.backgroundColor=red; } else { id("nea").style.backgroundColor=gray; } }
  else { if (time2>=30) { id("nea").style.backgroundColor=green; } else { id("nea").style.backgroundColor=yellow; } }

  id("peak1").innerHTML=peak1; id("rms1").innerHTML=rms1; id("freq1").innerHTML=freq1;
  id("peak2").innerHTML=peak2; id("rms2").innerHTML=rms2; id("freq2").innerHTML=freq2;

  if (time1>=63072000) { id("time1").innerHTML=Math.floor(time1/31536000); id("unit1").innerHTML="&nbsp;years"; }
  else if (time1>=172800) { id("time1").innerHTML=Math.floor(time1/86400); id("unit1").innerHTML="&nbsp;days"; }
  else if (time1>=7200) { id("time1").innerHTML=Math.floor(time1/3600); id("unit1").innerHTML="&nbsp;hours"; }
  else if (time1>=120) { id("time1").innerHTML=Math.floor(time1/60); id("unit1").innerHTML="&nbsp;min."; }
  else { id("time1").innerHTML=time1; id("unit1").innerHTML="&nbsp;sec."; }

  if (time2>=63072000) { id("time2").innerHTML=Math.floor(time2/31536000); id("unit2").innerHTML="&nbsp;years"; }
  else if (time2>=172800) { id("time2").innerHTML=Math.floor(time2/86400); id("unit2").innerHTML="&nbsp;days"; }
  else if (time2>=7200) { id("time2").innerHTML=Math.floor(time2/3600); id("unit2").innerHTML="&nbsp;hours"; }
  else if (time2>=120) { id("time2").innerHTML=Math.floor(time2/60); id("unit2").innerHTML="&nbsp;min."; }
  else { id("time2").innerHTML=time2; id("unit2").innerHTML="&nbsp;sec."; }

  if (locked==0) { id("locked").innerHTML="Unlocked"; id("locked").style.backgroundColor=gray; id("lock").innerHTML="Lock"; }
  else { id("locked").innerHTML="Locked"; id("locked").style.backgroundColor=blue; id("lock").innerHTML="Unlock"; }

  if (changed==0) { id("changed1").style.backgroundColor=gray; id("changed2").style.backgroundColor=gray; }
  else { id("changed1").style.backgroundColor=yellow; id("changed2").style.backgroundColor=yellow; } }

function getStatus() { requestAJAX("getStatus"); requestAJAX("getCalibration"); }

function doCalibrate(channel) { if (locked==0) { setLock(); clearStatusTimer();
  if (channel==1 && peak1>50 && rms1>50) { peakCal1=peakCal1/peak1*325; rmsCal1=rmsCal1/rms1*230; changed=1; peak1="325.0"; rms1="230.0"; doDisplay(); }
  if (channel==2 && peak2>50 && rms2>50) { peakCal2=peakCal2/peak2*325; rmsCal2=rmsCal2/rms2*230; changed=1; peak2="325.0"; rms2="230.0"; doDisplay(); }
  requestAJAX("setCalibration"+","+peakCal1+","+rmsCal1+","+peakCal2+","+rmsCal2+","+changed); setStatusTimer(0); } }

function doDefault() { if (locked==0) { setLock(); clearStatusTimer(); requestAJAX("defaultCalibration"); changed=1;
  peak1="- - -"; rms1="- - -"; freq1="- - -"; peak2="- - -"; rms2="- - -"; freq2="- - -"; doDisplay(); setStatusTimer(0); } }

function doUndo() { if (locked==0) { setLock(); clearStatusTimer(); requestAJAX("readCalibration"); changed=0;
  peak1="- - -"; rms1="- - -"; freq1="- - -"; peak2="- - -"; rms2="- - -"; freq2="- - -"; doDisplay(); setStatusTimer(0); } }

function doSave() { if (locked==0) { setLock(); clearStatusTimer(); requestAJAX("writeCalibration"); changed=0; doDisplay(); setStatusTimer(0); } }

function setStatusTimer(now) { clearStatusTimer(); statusTimer=window.setInterval("getStatus();",10000); if (now==1) { getStatus(); } }
function clearStatusTimer() { if (typeof statusTimer!=='undefined' ) { window.clearInterval(statusTimer); ajaxObj["getCalibration"].abort(); } }
function toggleLock() { if (locked==0) { setLock(); } else { unsetLock(); } }
function setLockTimer() { if (typeof lockTimer!=='undefined' ) { window.clearTimeout(lockTimer); } lockTimer=window.setTimeout("setLock();",2000); }
function unsetLock() { locked=0; doDisplay(); setLockTimer(); setLogoutTimer(); }
function setLock() { locked=1; doDisplay(); }
function setLogoutTimer() { if (typeof logoutTimer!=='undefined' ) { window.clearTimeout(logoutTimer); } logoutTimer=window.setTimeout("doLogout();",5*60000); }
function doLogout() { location.reload(); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getStatus") {
      peak1=event.target.responseText.split(",")[0]; rms1=event.target.responseText.split(",")[1];
      freq1=event.target.responseText.split(",")[2]; cond1=event.target.responseText.split(",")[3];
      time1=event.target.responseText.split(",")[4]; peak2=event.target.responseText.split(",")[5];
      rms2=event.target.responseText.split(",")[6]; freq2=event.target.responseText.split(",")[7];
      cond2=event.target.responseText.split(",")[8]; time2=event.target.responseText.split(",")[9]; doDisplay(); }
    else if (event.target.url=="getCalibration") {
      peakCal1=event.target.responseText.split(",")[0]; rmsCal1=event.target.responseText.split(",")[1];
      peakCal2=event.target.responseText.split(",")[2]; rmsCal2=event.target.responseText.split(",")[3];
      changed=event.target.responseText.split(",")[4]; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a">neaControl</div></div>
<div><div class="x0b">Emergency power system</div></div>

<div>
<div><div class="x1a">Voltages</div></div>
<div><div class="x2" id="evu">EVU</div>
     <div class="x2" id="nea">NEA</div></div>
<div><div class="x2"><table>
     <tr><td id="peak1"></td><td class="left">&nbsp;Vpeak</td></tr>
     <tr><td id="rms1"></td><td class="left">&nbsp;Vrms</td></tr>
     <tr><td id="freq1"></td><td class="left">&nbsp;Hz</td></tr>
     <tr><td id="time1"></td><td class="left" id="unit1"></td></tr>
     </table></div>
     <div class="x2"><table>
     <tr><td id="peak2"></td><td class="left">&nbsp;Vpeak</td></tr>
     <tr><td id="rms2"></td><td class="left">&nbsp;Vrms</td></tr>
     <tr><td id="freq2"></td><td class="left">&nbsp;Hz</td></tr>
     <tr><td id="time2"></td><td class="left" id="unit2"></td></tr>
     </table></div></div>
<div><div class="x2" onclick="doCalibrate(1);"><span class="but">Calibrate</span></div>
     <div class="x2" onclick="doCalibrate(2);"><span class="but">Calibrate</span></div></div>
<div><div class="x1b" id="locked"></div></div>
<div><div class="x1b" onclick="toggleLock();"><span class="but" id="lock"></span></div></div>
<div><div class="x1a">Configuration</div></div>
<div><div class="x3" onclick="doDefault();"><span class="but">Default</span></div>
     <div class="x3" onclick="doUndo();" id="changed1"><span class="but">Undo</span></div>
     <div class="x3" onclick="doSave();" id="changed2"><span class="but">Save</span></div></div>
</div>

</body></html>

)";
