# INSTALLATION FHEM
1. FHEM installieren: http://fhem.de/fhem.html#Installation
2. Starten: perl fhem.pl fhem.cfg
3. Tablet UI installieren: http://www.fhemwiki.de/wiki/FHEM_Tablet_UI
   * Im FHEM-Eingabefeld: update all https://raw.githubusercontent.com/knowthelist/fhem-tablet-ui/master/controls_fhemtabletui.txt
(alternativ: komplettes Unterverzeichnis "www" von https://github.com/knowthelist/fhem-tablet-ui nach $FHEM_HOME entpacken
   * Im FHEM-Eingabefeld: define TABLETUI HTTPSRV ftui/ ./www/tablet Tablet-UI
   * Im Verzeichnis ./fhem/www/tablet die Datei index-example.html in index.html umbenennen oder eine neue index.html erzeugen
1. Widgets für Tablet UI installieren: https://github.com/nesges/Widgets-for-fhem-tablet-ui

Die Tablet-UI Oberfläche ist jetzt unter __http://localhost:8083/fhem/tablet/index.html__ erreichbar.

# Widgets für Tablet UI anpassen
Das Javascript *widget_iframe.js* produziert einen Fehler. Alle Aufrufe der Funktion `spinner.famultibutton` müssen entfernt werden.

# index.html
Die folgened `index.html` zeigt ein Video im Browser
```html
<html>
...
<body>
    <div class="gridster">
        <h1>Video</h1>
        <div data-type="iframe"
            data-src="http://www.youtube.com/embed/-WJYbJJNQyg?wmode=transparent"
            data-height="420"
            data-width="380">
        </div>
    </div>
</body>
</html>
```

# Chrome
Chrome so starten, dass ein "Cross-domain" request erlaubt ist
```
chrome.exe --user-data-dir="C:/Chrome dev session" --disable-web-security
```
Die Javascript-Console (fürs Debuggen) öffnet man mit `<CTRL>+<SHIFT>+J`.

# Troubleshooting

## FHEM

### Fehlermeldung über fehlende Rechte bei Raspberry Pi
Trage folgende Zeile in `/etc/sudoers` ein: 
```bash
fhem ALL=(ALL) NOPASSWD: ALL
```

## Kamera
/boot/config.txt: Zeile 'GPIO_MEM=128' zu 'GPIO_MEM=144' ersetzen
