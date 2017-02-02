# Algorytmy-Struktury

W tym krótkim dokumencie na temat algorytmów sortowania przedstawiam obrazowy opis poszczególnych metod sortowania. 
Cechy algorytmów, czyli klasy złożoności obliczeniowej: optymistycznej, typowej, pesymistycznej, złożonośd pamięciową, 
informację o tym, czy dany algorytm jest stabilny oraz czy jest algorytmem w miejscu. Następnie pokazuję graficzną 
reprezentację wykonania algorytmu w kolejnych krokach. Konkretyzuję specyfikacje problemu, czyli kolejno: dane wejściowe, 
dane wyjściowe oraz zmienne pomocnicze. W przedostatnim punkcie omawianego algorytmu przedstawiam listę kroków wykonania 
algorytmu czyli jego konkretny pseudokod, który później z drobnymi zmianami (ze względu na specyfikę języka programowania 
oraz dodatkowych funkcjonalności) implementuję w pliku sort.c. Na koocu znajdują się wyniki każdego testu przeprowadzonego 
na danym algorytmie oraz komentarze na temat zgodności wyników uzyskanych z powszechnie znanymi w środowisku informatycznym.
Na koocu dokumentu znajdują się wyniki zbiorcze wykonanych testów.

# Uwagi implementacyjne
Każda funkcja została zaimplementowana wg. konkretnego interfejsu:

<pre>
void functionSort( intptr_t *array, size_t size, int flag );
</pre>

Interfejs taki został przyjęty ze względu na naturę problemu sortowania. Można się domyślid, że array – to jest adres początku 
pamięci, w której przechowywane są dane, size to rozmiar danych. Z tego wynika, że możemy posortowad nie tylko całą tablicę 
danych typu intiger, ale także częśd danych umieszczonych w pamięci. Flaga flag jest parametrem pobieranym do funkcji, dzięki 
której możemy rozstrzygnąd o kierunku sortowania (rosnącym lub malejącym – SORTASC/SORTDESC). Miedzy innymi przez ten dodatkowy 
parametr - flag kody poszczególnych funkcji znacznie się rozrastają i duplikują (tylko po to by zmienid jeden krótki warunek 
na warunek przeciwny(zaprzeczony)). Taka strategia została przyjęta po to, by warunek dotyczący kierunku sortowania był 
sprawdzany tylko raz, zanim faktyczny algorytm zacznie się wykonywad, a nie wewnątrz pętli, gdzie byłby sprawdzany co najmniej 
size-razy. Mogłoby to mied systematyczny wpływ na czas wykonania algorytmu. Wygląda to następująco:

<pre>
if(flag == SORTASC)// sortuj rosnąco
{
// kod algorytmu sortowania w kierunku rosnącym
}
else if(flag == SORTDESC)// sortuj malejąco
{
// kod algorytmu sortowania w kierunku malejącym
}
</pre>

# Opis programu
Program automatycznie wykonuje testy dla odpowiednio dobranych danych. Rozmiar danych różni się dla różnych funkcji ze względu na ich 
różną złożonośd obliczeniową. Nie warto czekad 10 godzin w niektórych przypadkach… Dlatego utworzyłem dwa rodzaje testu: 
Test duży, tzn. test dla dużych rozmiarów danych. Taki test wykonywany jest tam gdzie złożonośd nie jest wyższego rzędu niż n lgn. Test mały wykonywany jest dla algorytmów, których złożonośd obliczeniowa jest wyższego rzędu niż liniowo-logarytmiczna. Z tego powodu program tworzy dwa pliki, jeden znacznie większy oraz plik mniejszy. Powodem takiego podejścia jest pewien fakt, który może wpłynąd na wyniki testu algorytmów o złożoności obliczeniowej kwadratowej. Gdy losujemy klika milionów liczb z małego przedziału np. <-100, 100>, 
to w takim zbiorze będziemy mieli duże podzbiory składające się z jednej i tej samej wartości np. {100, 100, …, 100}, 
takie zbiory mogą mied moc nawet kilku milionów. Wybierając z takiego pliku (w którym znajdują się liczby wcześniej posortowane) 
tylko np. 16000 liczb, może okazad się, że wybraliśmy liczby o tej samej wartości, co za skutkuję małym czasem sortowania w 
przypadku, gdy ten czas powinien byd znacznie większy, lub w nieco innym przypadku możemy stwierdzid, że dana funkcja dla 
podanych danych ma świetną złożonośd obliczeniową, rzędu dużo niższego niż czytaliśmy wcześniej w książkach.
Program dla każdej iteracji (liczby danych), pobiera dane z pliku, co znacznie wpływa na czas wykonania testu, ale nie 
wpływa na pomiary czasu sortowania. Jest to koszt oszczędzania pamięci lokowanej dynamicznie.
