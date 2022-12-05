const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<div class="card">
  <h2>Update of the ESP32 ADC</h2>
  <h3>Chip Temp:<span id="Temp">0</span> <span class="units">&deg C;</span></h3>
  <h3>ADC#1 Value:<span id="ADC1">0</span> <span class="units">mV;</span></h3>
  <h3>ADC#2 Value:<span id="ADC2">0</span> <span class="units">mV;</span></h3>
  <h3>ADC#3 Value:<span id="ADC3">0</span> <span class="units">mV;</span></h3>
  <h3>ADC#4 Value:<span id="ADC4">0</span> <span class="units">mV;</span></h3>
  <h3>ADC#5 Value:<span id="ADC5">0</span> <span class="units">mV;</span></h3>
  <h3>ADC#6 Value:<span id="ADC6">0</span> <span class="units">mV;</span></h3>
<br>
</div>

<div id="chart-temperature" class="container"></div>
//<div id="chart-ADC1" class="container"></div>

<script>

setInterval(function() {
  // Call a function repetatively with 100 ms interval
  getData("Temp","handleTemp");
  getData("ADC1","handleADC1");
  getData("ADC2","handleADC2");
  getData("ADC3","handleADC3");
  getData("ADC4","handleADC4");
  getData("ADC5","handleADC5");
  getData("ADC6","handleADC6");

}, 100); //100mSeconds update rate

function getData(elementname,handlename) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById(elementname).innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", handlename, true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";