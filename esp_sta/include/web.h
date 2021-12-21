const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <meta charset="utf-8">
    <title>Demo IOT</title>
    <body>
        <h1>Dieu khien thiet bi 1</h1>
        <button type="button" onclick="onoff()">ON/OFF</button>
        <br>
        <h1>Dieu khien thiet bi 2</h1>
        <input id="text"/>
        <button type="button" onclick="senddata()">Send Data</button>
    </body>
    <script>
        window.onload = UpdateData; 
        function UpdateData()
        {
            var xhttp = new XMLHttpRequest(); 
            xhttp.onreadystatechange = function()
            {
                if(this.readyState == 4 && this.status == 200)
                {
                    var data_mcu = xhttp.responseText; 
                    console.log("Data Mcu: " + data_mcu); 
                }
            }
            xhttp.open("GET", "/getdata", true); 
            xhttp.send(); 
            setTimeout(function() {UpdateData() }, 1000); 
        }
        function onoff()
        {
            //console.log("OnOfF "); 
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/onoff", true); 
            xhttp.send(); 
        }
        function senddata()
        {
            var text1 = "A" + document.getElementById("text").value + "B"; 
            var xhttp = new XMLHttpRequest(); 
            xhttp.open("GET","/adcvalue?adc=" + text1, true); 
            xhttp.send(); 
            
        }
        
    </script>
</html>
)====="; 