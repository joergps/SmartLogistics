# SmartLogistics
Code f�r das Sm@rtLogistics Projekt.

# Einf�hrung
Das Projekt aus einem Sender und einem Empf�nger. Der Sender ist ein Raspberry Pi mit angeschlossener Sensorik (z.B. Taster). Der Empf�nger kann momentan ein beliebiger Computer sein, auf dem die Web-GUI l�uft. Auf dem Sender laufen Python-Skripte (siehe "src/py"); auf dem Empf�nger l�uft die Java Spring-Boot Web-Applikation (siehe "src/java").

# Java Web-Gui
* Voraussetzung: Java 8
* Download des Binaries aus bin/java
* Start mit ``` java -jar smartlogistics-web-0.0.1.war```
* Adresse Web-GUI: http://localhost:8080
* Nachricht, dass ein Packst�ck da ist: http://localhost:8080?hasItem=true
