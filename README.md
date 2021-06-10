# DistanceCalculation
Program obliczający odległość między dwoma miejscowościami pomijając krzywiznę Ziemi

# Opis 
Zadaniem było zaprojektowanie sieci dróg łączących miasta w pewnym państwie. Koszt budowy połączenia był wprost proporcjonalny do odległości pomiędzy dwoma miastami. Skorzystałem tutaj ze wzoru na odległość dwóch punktów na Ziemi pomijając jej krzywiznę:

![alt text](https://github.com/BartekWMII/DistanceCalculation/blob/main/1.png)

# O kodzie
W kodzie stworzyłem dwie klasy, jedna- Data do przechowywania danych o miejscowości, a druga- Data Connect do przechowywania danych o dwóch miastach i o odległości między nimi. Z pliku pobieram miasta w formacie „x1 x2 nazwa”. Ważne aby na końcu dokumentu oraz jego początku nie było pustej linii, ponieważ powoduje ona błąd przy pobieraniu tekstu przez program. Również na górze pliku z kodem zdefiniowałem zmienną M, która oznacza ilość miejscowości w pliku tekstowym. W obu przypadkach jest to 17. Do projektu jest załączony plik z miastami (miasta.txt) oraz plik z miastami stworzony przeze mnie (miasta2.txt). Współrzędne miast brałem ze strony http://astronomia.zagan.pl/art/wspolrzedne.html . Wracając do kodu – kolejna funkcja Graph służy za utworzenie macierzy sąsiedztwa, która jest drukowana w pliku o nazwie wynik.txt po zakończeniu programu. Dalej znajduje się funkcja wspomagająca do algorytmu Prima i sam algorytm oraz funkcja drukująca.

# Opis algorytmu Prima
Algorytm prima wyznacza minimalne drzewo rozpinające dla grafu nieskierowanego ważonego, czyli znajduje drzewo zawierające wszystkie wierzchołki grafu, którego
waga jest jak najmniejsza. Jest to algorytm zachłanny.
Funkcja MinKey służy do znalezienia wierzchołka z minimalną wartością klucza.
Tworzy się zestaw mstSet, który w pewien sposób „śledzi” wierzchołki w MST(Minimum Spanning Tree). Następnie wartości kluczów w wierzchołkach oznaczamy jako nieskończoność. Do pierwszego klucza przypisujemy 0, aby to on był wybrany jako pierwszy. Następnie wybiera się wierzchołek, którego nie ma w zestawie i go tam dołączamy. Potem aktualizujemy wartość wszystkich wierzchołków ze sąsiadującym wierzchołkiem.
Z racji mało estetycznego wyglądu(z powodu dużej ilości miast) w jaki wypisują się wyniki w pliku tekstowym, pozwoliłem je sobie skopiować do Excela dzięki czemu świetnie widać ich wyniki dla każdego z miast. Odsyłam do pliku excel „PLIK”.
Liczba wypisana w konsoli na samym dole jest sumą wszystkich odległości między połączonymi miastami widocznymi w konsoli.
