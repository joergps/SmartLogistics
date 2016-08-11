# SmartLogistics
Code für das Sm@rtLogistics Projekt.

# Einführung
Das Projekt aus einem Sender und einem Empfänger. Der Sender ist ein Raspberry Pi mit angeschlossener Sensorik (z.B. Taster). Der Empfänger kann momentan ein beliebiger Computer sein, auf dem die Web-GUI läuft. Auf dem Sender laufen Python-Skripte (siehe "src/py"); auf dem Empfänger läuft die Java Spring-Boot Web-Applikation (siehe "src/java").

# Java Web-Gui
* Voraussetzung: Java 8
* Download des Binaries aus bin/java
* Start mit ``` java -jar smartlogistics-web-0.0.1.war```
* Adresse Web-GUI: http://localhost:8080
* Nachricht, dass ein Packstück da ist: http://localhost:8080?hasItem=true
