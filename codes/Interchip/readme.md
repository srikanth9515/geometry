
This directory contains **(.cpp)** files which are an extension of code designed to support Vaman Esp32 Board.
<h2>Steps to Follow:</h2>
<h3>Setting up Directory in Ubuntu</h3>
<ol>
  <li>Creating Directory</li>
  <pre>mkdir interchip</pre>
  <li>Changing Directory</li>
  <pre>cd interchip</pre>
  <li>Creating src file</li>
  <pre>mkdir src</pre>
  <li>Changing to src directory</li>
  <pre>cd src</pre>
  <li>Download required <b>.cpp</b> file, along with <b>libs</b> folder and paste it in here.</li>
  <li>Modify <b>.cpp</b> file</li>
  Give your respective ssid, password. Save and exit.
  <pre>
const char* ssid = "Redmi";
const char* password = "987654321";</pre>
  <li>Returning Back to interchip</li>
  <pre>cd ..</pre>
  <li>Download the <b>platformio.ini</b> file and paste it in here</li>
</ol>
<h3>Generating .bin file</h3>
<ol>
  <li>Open Terminal, Goto geohard Directory</li>
  <li>Installing AsyncTCP</li>
  <pre>pio pkg install --library "me-no-dev/AsyncTCP@^1.1.1"</pre>
  <li>Installing ESP Async WebServer</li>
  <pre>pio pkg install --library "me-no-dev/ESP Async WebServer@^1.2.3"</pre>
  <li>Building bin file</li>
  <pre>pio run</pre>
</ol>
<h3>Flash vaman-ESP32 using Arduino</h3>
Click the <a href="https://github.com/gadepall/digital-design/blob/main/main.pdf">URL</a> to find out circuit Diagram between Arduino and Vaman.<br>
After Succesfully connecting both Vaman and Arduino, Connect Mobile to Arduino using Otg cable.<br>Then proceed to Uploading bin to vaman.

<h3>Uploading bin to Vaman</h3>
<ol>
  <li>Open Arduino Droid</li>
  <li>Select Board Type</li>
  <pre>Menu --> Settings --> Board type --> ESP32 --> DOIT ESP32 DEVKIT V1</pre>
  Flash Frequency: 80MHz<br>
  Upload Speed: 115200<br>
  Click ok
  <li>Upload <b>.bin</b> file</li>
  <pre>Menu --> Upload --> Upload precompiled --> location of bin</pre>
  <p>Or</p>  
</ol>
<h3>Uploading .cpp via UART:</h3>
<ol>
  <li>Using Arduino IDE to compile and upload <b>(.cpp)</b> file and installing necessary packages.</li>
</ol><br><br>

<h3>After sucessfully uploading esp32 code into vaman, Now we can move onto fpga</h3>
<ol>
  <li>Download the fpga folder present above</li>
  <li>Move to fpga folder</li>
  <pre>cd fpga</pre>
  <li>Link bin path to QORC_SDK_PATH</li>
  <pre>export QORC_SDK_PATH=/home/user/pygmy-dev/pygmy-sdk</pre>
  <li>Generate .bin file</li>
  <pre>make</pre>
  <li><h4>Uploading <b>(.bin)</b> to vaman</h4></li>
  <ol>
    <li>Connect ESP32 to PYGMY using the reference diagram <a href="https://github.com/gadepall/embedded-system/blob/main/main.pdf">here</a> in section 3.1.1.2 .
    </li>
    <li>Flashing Vaman</li>
    <pre>sudo python3 /path/to/TinyFPGA-Programmer-Application/tinyfpga-programmer-gui.py --port /dev/ttyACM0  --appfpga /path/to/AL4S3B_FPGA_Top.bin --mode m4-fpga --reset
</pre>
  </ol>
    <li>After succesfull uploading, The Vaman connects to the Network whose credentials are provided in the <b>.cpp</b> file.</li>
  <li>Now find out the Ip address assigned to vaman.</li>
  <pre>ifconfig
nmap -sn 192.168.xx.xx/24</pre>
  <li>After finding the IP, type this in browser.</li>
  <pre>http://IP_ADDRESS/form_name</pre>
  </ol>
