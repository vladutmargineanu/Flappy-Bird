`My Flappy Bird`

In cadrul temei 1 veti implementa propria versiune de Flappy Bird. Tot ce nu este specificat ramane la creativitatea voastra.

`Pasarea`

Pasarea va fi creata prin combinarea mai multor figuri geometrice pline (GL_FILL) generate de voi. Minim 2 primitive geometrice (e.g. triunghi, patrat, cerc, etc.) Trebuie sa creati cel putin corpul pasarii, capul si ciocul).

`Exemplu de pasare:`

Doua discuri de cerc si un triunghi (figura din stanga)
Un dreptunghi, un disc de cerc si un triunghi (figura din centru)
Un dreptunghi, un disc de cerc si mai multe triunghiuri (figura din dreapta)

`Mediul in care se deplaseaza pasarea`

Mediul inconjurator va fi creat din perechi de dreptunghiuri, de aceeasi latime dar de inaltime diferita, unul ancorat sus, si celalalt
ancorat jos (similar cu stalactitele si stalagmitele din pesteri), ca in figura urmatoare. Inaltimea dreptunghiurilor se poate stabili 
procedural, aleator sau hardcodat, dar trebuie sa se respecte regula ca distanta intre doua perechi de dreptunghiuri sa fie suficient 
de mare, astfel incat pasarea sa poata trece printre ele.


`Gameplay`

Jocul va fi un endless runner, care va crea impresia ca pasarea se deplaseaza de la stanga la dreapta printre perechile de dreptunghiuri.
In realitate, nu se deplaseaza pasarea de la stanga la dreapta, ci scena se deplaseaza de la dreapta spre stanga. Pasarea este afectata
de gravitatie. Ea va avea intotdeauna tendinta sa se incline in jos si sa cada. Daca se apasa tasta SPACE, pasarea se va ridica ,
inclinandu-se in sus. Daca pasarea se loveste de dreptunghiuri, moare. Pe masura ce timpul de supravietuire al pasarii trece, creste 
si punctajul jucatorului. In consola se va afisa periodic punctajul jucatorului. Atunci cand pasarea moare, se va afisa in consola un
mesaj, impreuna cu punctajul final.

`Detalii de implementare`

Caderea sau ridicarea pasarii se vor implementa prin translatie pe axa Oy.
Inclinarea pasarii in jos va fi implementata printr-o rotatie (fata de centrul de greutate al pasarii) in sens orar, iar inclinarea 
pasarii in sus, printr-o rotatie in sens trigonometric
Perechile de dreptunghiuri se vor translata incontinuu pe axa Ox (de la dreapta la stanga). De fiecare data cand o pereche de
dreptunghiuri dispare (s-a deplasat spre stanga pana cand a iesit din spatiul de desenare), apare o alta pereche de dreptunghiuri
in partea dreapta. Crearea mediului inconjurator trebuie sa se realizeze in asa fel incat consumul de memorie si timpul de redare 
sa fie optime. Nu creati incontinuu obiecte care sa reprezinte perechile de dreptunghiuri care apar si dispar din spatiul de 
desenare!!!! O implementare eleganta este sa creati un singur dreptunghi in functia init(), iar in functia Update() sa dati 
comanda de desenare pentru acel dreptunghi de mai multe ori, de fiecare data la alta pozitie si cu alt factor de scalare pe OY, 
astfel incat dreptunghiurile desenate sa aiba inaltimi diferite. La fel, in functia Update() nu trimiteti spre desenare dreptunghiuri
care au disparut din ecran!!
Toate animatiile trebuie sa fie independente de platforma.
Coliziunea dintre pasare si dreptunghiuri se poate simplifica prin verificarea unei coliziuni intre un cerc si dreptunghiuri 
(daca pasarea este destul de mica in raport cu dreptunghiurile, ea poata fi aproximata prin cercul care o incadreaza)
Mai multe informatii despre ce reprezinta coliziunea si cum se poate implementa:
https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
https://www.youtube.com/watch?v=aTbw71EpamY
https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

`Bonus`

(5p) Animatie de scalare pentru perechile de dreptunghiuri (o pereche de dreptunghiuri sa se comporte ca un set de usi glisante de
la un lift modern), astfel incat sa se apropie si sa se departeze incontinuu, pastrand totusi o distanta suficient de mare intre 
ele astfel incat pasarea sa treaca printre ele)
(5p-10p) Scena cat mai realista (perechile de stalactite si stalagmite sa fie in mai multe culori, din forme mai complexe, pasarea
sa arate ca o pasare)
Stalactitele si stalagmitele sa nu fie numai verticale (look up 2D GJK)
Sa creasca dificultatea jocului pe masura ce creste punctajul jucatorului
Animatie care sa simuleze modul prin care pasarea da din aripi
Exemplu (doar pentru orientare): https://www.youtube.com/watch?v=I69adfEqwC0
Functionalitati obligatorii
Barem orientativ pentru realizarea functionalitatilor (din 150 puncte):

desenare pasare (25p)
desenare mediu si animatie, cu utilizarea optima a resurselor (40p)
animatii fluide pasare (35p)
coliziuni (35p)
printare statistici in consola (10p)
readme (5p)
Intrebari si raspunsuri
Pentru intrebari vom folosi forumurile de pe moodle.

`Indicatii suplimentare`

Tema va fi implementata in OpenGL si C++. Este indicat sa folositi framework-ul si Visual Studio.

Pentru implementarea temei, in folderul Source/Laboratoare/ puteti crea un nou folder, de exemplu Tema1, cu fisierele Tema1.cpp si 
Tema1.h (pentru implementare POO, este indicat sa aveti si alte fisiere). Pentru a vedea fisierele nou create in Visual Studio in 
Solution Explorer, apasati click dreapta pe filtrul Laboratoare si selectati Add→New Filter. Dupa ce creati un nou filtru, de exemplu 
Tema1, dati click dreapta si selectati Add→Existing Item. Astfel adaugati toate fisierele din folderul nou creat. In fisierul LabList.h 
trebuie adaugata si calea catre header-ul temei. De exemplu: #include <Laboratoare/Tema1/Tema1.h>

`Arhivarea proiectului`

in mod normal arhiva trebuie sa contina toate resursele necesare compilarii si rularii
inainte de a face arhiva asigurati-va ca ati dat clean la proiect
click dreapta pe proiect in Solution Explorer → Clean Solution, sau
stergeti folderul /Visual Studio/obj
stergeti fisierul /Visual Studio/Framework_EGC.sdf (in caz ca exista)
stergeti fisierul /Visual Studio/Framework_EGC.VC.db (in caz ca exista)
stergeti folderul /.vs (in caz ca exista)
stergeti folderul /x64 sau /x86 (in caz ca exista)
executabilul final este generat in folderul /x86 sau /x64 la finalul link-editarii in functie de arhitectura aleasa la compilare 
(32/64 biti) in cazul in care arhiva tot depaseste limita de 20MB (nu ar trebui), puteti sa stergeti si folderul /libs sau /Resources 
intrucat se pot adauga la testare. Nu este recomandat sa faceti acest lucru intrucat ingreuneaza mult testarea in cazul in care 
versiunea curenta a librariilor/resurselor difera de versiunea utilizata la momentul scrierii temei.

