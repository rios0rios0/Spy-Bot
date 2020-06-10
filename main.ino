//#include <enc28j60.h>
//#include <EtherCard.h>
//#include <net.h>

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//byte mac[] = {
  //0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
//};
IPAddress ip(192, 168, 1, 101);
EthernetServer server(80);
//byte Ethernet::buffer[700];

void setup() {
  //ether.begin(sizeof Ethernet::buffer, mac, 10);
  //ether.dhcpSetup();
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);
  Ethernet.begin(mac);
  //Serial.println("Erro");
  server.begin();
}

void loop() {
  //ether.packetLoop(ether.packetReceive());
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    String line = "";
    int i = 0;

    while (client.connected()) {
      if (client.available()) {
        boolean left = false;
        boolean right = false;
        boolean front = false;
        boolean back = false;
        boolean frist = false;
        
        char c = client.read();
        i = i + 1;
        if ((line.indexOf("G") >= 0) || (c == 'G')) {
          line = line + String(c);
        }

        if (i == 10) {
          if (line.indexOf("?go=E") >= 0) left = true;
          if (line.indexOf("?go=D") >= 0) right = true;
          if (line.indexOf("?go=F") >= 0) front = true;
          if (line.indexOf("?go=T") >= 0) back = true;
          
          line = "";
          i = 0;
        }

        if (left) {
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
        }
        
        if (right) {
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
          delay(200);
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
        }
        
        if (front) {
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
          delay(200);
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
          delay(200);
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
        }
        
        if (back) {
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
          delay(200);
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
          delay(200);
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
          delay(200);
          digitalWrite(12, 1);
          delay(200);
          digitalWrite(12, 0);
        }

        if (c == '\n' && currentLineIsBlank) {
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<script>");
          client.println("function setURL(url)");
          client.println("document.getElementById('teste').src = url;");
          client.println("}");
          client.println("</script>");
          //client.println("<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>");
          //client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
          client.println("<head>");
          //client.println("<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
          client.println("<title>SecurityBot v1.0</title>");
          client.println("<style type='text/css'>");
          client.println(".TitleName {");
	  client.println("font-size: 16pt;");
	  client.println("color: #F00;");
          client.println("}");
          client.println(".CamName {");
	  client.println("font-size: 14pt;");
	  client.println("color: #000;");
          client.println("}");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<p style='text-align: center;'><span class='TitleName'>SecurityBot v1.0</span><br><br>");
          client.println("<span class='CamName'>Cam: </span>");
          client.println("<table style='margin: auto;'width: '95px;' border=0>");
          client.println("<tbody>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          //client.println("<input value='^'; type='button' onclick=setURL(http://192.168.1.200/decoder_control.cgi?loginuse=visit&loginpas=1&command=0&onestep=1)>");
          client.println("<a href='http://192.168.1.200/decoder_control.cgi?loginuse=visit&loginpas=1&command=0&onestep=1' target='teste'>^</a>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200/decoder_control.cgi?loginuse=visit&loginpas=1&command=4&onestep=1' target='teste'>&lt</a>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200/decoder_control.cgi?loginuse=visit&loginpas=1&command=6&onestep=1' target='teste'>&gt</a>");
          client.println("</td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200/decoder_control.cgi?loginuse=visit&loginpas=1&command=2&onestep=1' target='teste'>v</a>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("</tbody>");
          client.println("</table>");
          
          client.println("<p style='text-align: center;'><iframe marginheight=0 marginwidth=0 width=400 height=300 frameborder=0 scrolling='no' name='main' id='main' src='http://192.168.1.200/videostream.cgi?loginuse=visit&loginpas=1'></iframe>");
          client.println("<iframe width=0 height=0 name='teste' id='teste'></iframe>");
          client.println("<p style='text-align: center; font-size: 14pt; color: #000;'>Mov:");
          client.println("<br>");
          client.println("<table style='margin: auto;'width: '95px;' border=0>");
          client.println("<tbody>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<form method=get action=''>");
          client.println("<input type=hidden name=go value=F />");
          client.println("<input value=^ type=submit>");
          client.println("</form>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td>");
          client.println("<form method=get action=''>");
          client.println("<input type=hidden name=go value=E />");
          client.println("<input value=&lt; type=submit>");
          client.println("</form>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<form method=get action=''>");
          client.println("<input type=hidden name=go value=D />");
          client.println("<input value=&gt; type=submit>");
          client.println("</form>");
          client.println("</td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<form method=get action=''>");
          client.println("<input type=hidden name=go value=T />");
          client.println("<input value=v type=submit>");
          client.println("</form>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("</tbody>");
          client.println("</table>");
          client.println("</p>");
          client.println("</body>");
          client.println("</html>");

          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    client.stop();
  }
}
