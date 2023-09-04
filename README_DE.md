# GradientDescent
Dieses Programm ermöglicht es, den Prozess der Nullstellenfindung zu beobachten. Die Koeffizienten werden für Gleichungen der Form \( k \sin(bx) \) angepasst.

1) Der ursprüngliche Graph wird oben in Blau mit Rauschen und den Koeffizienten \( k = 5, b = 7 \) dargestellt.
2) Der vom Programm erratene Graph ist in Rot.
3) Der in Grün dargestellte Graph basiert auf den von Ihnen gewählten Koeffizienten.

# Was ist das Diagramm unten?
Das untere Diagramm stellt die mittlere quadratische Abweichung der Funktion mit den Koeffizienten dar, die dem Punkt entsprechen, d.h., \( K \) ist auf der x-Achse, \( B \) auf der y-Achse. Die Farbe gibt die Abweichung an: Blau für das Minimum und Rot für das Maximum.

# Was ist die mittlere quadratische Abweichung?
Die mittlere quadratische Abweichung ist die Summe der Quadrate der Differenzen zwischen dem ursprünglichen Funktionswert und dem Funktionswert an dem Punkt mit den Koeffizienten.

# Wie interagiert man mit dem Programm?
Linksklick auf das untere Diagramm: Wählen Sie Koeffizienten, auf deren Grundlage ein Graph oben in Grün gezeichnet wird.
Rechtsklick auf das untere Diagramm: Gradientenabstieg vom Punkt zu den optimalen Koeffizienten.

# Beispiel:
![Bild](https://user-images.githubusercontent.com/64206443/233839716-fbb25ffc-4e41-42d0-b66f-404832f33996.png)

# Technische Merkmale
Läuft auf einer [eigenen Grafikbibliothek](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP).
Das Programm verwendet 4 Threads:
1) Der Hauptgrafik-Thread für die Fensternachrichtenverarbeitung
2) Ein Thread zum Zeichnen des oberen Graphen
3) Ein Thread zur Berechnung der Punkte der mittleren quadratischen Abweichung
4) Ein Gradientenabstiegs-Thread

------------------------------------------------------
# Installation
Um das Programm auszuführen, müssen Sie die kompilierte Version aus dem Reiter "Releases" [hier](https://github.com/quqveik1/GradientDescent/releases/latest) herunterladen.
Ignorieren Sie Antivirus-Warnungen, die besagen, dass die Datei einen Virus enthält.

In dem Dialogfenster klicken Sie auf "Weitere Informationen" und wählen dann "Trotzdem ausführen".

![Installationswarnung](https://user-images.githubusercontent.com/64206443/182945554-ed4d18c6-a25d-4d0d-a331-e268643b3031.png)
