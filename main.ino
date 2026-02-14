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
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(7, 0);
  digitalWrite(6, 0);
  digitalWrite(5, 0);
  digitalWrite(4, 0);
  Ethernet.begin(mac, ip);
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
        boolean off = false;
        
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
          if (line.indexOf("?go=O") >= 0) off = true;
          
          line = "";
          i = 0;
        }

        if (off) {
          digitalWrite(7, 0);
          digitalWrite(6, 0);   
          digitalWrite(5, 0);
          digitalWrite(4, 0);
        }

        if (left) {
          digitalWrite(7, 1);
          digitalWrite(4, 1);   
        }
        
        if (right) {
          digitalWrite(6, 1);
          digitalWrite(5, 1);
        }
        
        if (front) {
          digitalWrite(7, 1);
          digitalWrite(5, 1);
        }
        
        if (back) {
          digitalWrite(4, 1);
          digitalWrite(6, 1);
        }

        if (c == '\n' && currentLineIsBlank) {
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //client.println("<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>");
          //client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
          client.println("<head>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
          client.println("<title>Webservice - Robo Mordomo v0.9</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<p style='text-align: center;'>Webservice - Robo Mordomo v0.9");
          
          client.println("<br><br><br>");
          client.println("Camera:");
          client.println("<br>");
          
          client.println("<table style='margin: auto;'width: '95px;' border=0>");
          client.println("<tbody>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200:81/decoder_control.cgi?loginuse=admin&loginpas=1&command=0&onestep=1' target='null'>^</a>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200:81/decoder_control.cgi?loginuse=admin&loginpas=1&command=4&onestep=1' target='null'>&lt</a>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200:81/decoder_control.cgi?loginuse=admin&loginpas=1&command=6&onestep=1' target='null'>&gt</a>");
          client.println("</td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          client.println("<a href='http://192.168.1.200:81/decoder_control.cgi?loginuse=admin&loginpas=1&command=2&onestep=1' target='null'>v</a>");
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("</tbody>");
          client.println("</table>");
          
          client.println("<p style='text-align: center;'><iframe marginheight=0 marginwidth=0 width=400 height=300 frameborder=0 scrolling='no' name='main' id='main' src='http://192.168.1.200:81/videostream.cgi?loginuse=admin&loginpas=1'></iframe>");
          client.println("<iframe width=0 height=0 name='null' id='null'></iframe>");
          
          client.println("<p style='text-align: center;'>Movimentacao:");
          client.println("<br>");
          client.println("<table style='margin: auto;'width: '95px;' border=0>");
          client.println("<tbody>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          
          client.println("<input type='button' value='↑' onmousedown='up()' onmouseup='off()' ontouchstart='up()' ontouchend='off()'>");
          
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td>");
          
          client.println("<input type='button' value='←' onmousedown='left()' onmouseup='off()' ontouchstart='left()' ontouchend='off()'>");
          
          client.println("</td>");
          client.println("<td></td>");
          client.println("<td>");
          
          client.println("<input type='button' value='→' onmousedown='right()' onmouseup='off()' ontouchstart='right()' ontouchend='off()'>");
          
          client.println("</td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td></td>");
          client.println("<td>");
          
          client.println("<input type='button' value='↓' onmousedown='down()' onmouseup='off()' ontouchstart='down()' ontouchend='off()'>");
          
          client.println("</td>");
          client.println("<td></td>");
          client.println("</tr>");
          client.println("</tbody>");
          client.println("</table>");
          client.println("</p>");
          client.println("</body>");
          client.println("<script type='text/javascript'>");
          client.println("function up(){");
          client.println("window.location.href = '?go=F';");
          client.println("}");
          client.println("function down(){");
          client.println("window.location.href = '?go=T';");
          client.println("}");
          client.println("function left(){");
          client.println("window.location.href = '?go=E';");
          client.println("}");
          client.println("function right(){");
          client.println("window.location.href = '?go=D';");
          client.println("}");
          client.println("function off(){");
          client.println("window.location.href = '?go=O';");
          client.println("}");
          client.println("</script>");
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
