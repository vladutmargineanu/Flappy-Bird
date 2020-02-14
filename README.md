# Flappy-Bird
Homework for the Computer Graphics Elements course @ ACS, UPB 2019

# Algorithm

Implementare: OpenGL si C++.

 1. `Pasarea - desenare pasare:`
 - pasarea este creata dintr-un dreptunghi (corpul), cerc (capul), triunghi (ciocul, 
 un cerc pentru ochi si un triunghi pentru aripa.
 Pentru fiecare figura geometrica am implementat cate o functie in fisierul
 Object2D si anume: CreateRectangles, CreateCircle (metoda "the triangle fan method"), 
 CreateTriangle.

 2. `Mediul in care se deplaseaza pasarea` - desenare mediu si animatie, cu
  utilizarea optima a resurselor:
 - am creat o pereche de dreptunghiuri, unul jos si altul sus. Pe acestea le-am
 desenat de NUMBER_RECTANGLES ori in scena in funcia Update cu factor de scalare si
 translatie diferit, in functie de starea jocului (dificultatea creste in timp).

 3. `Gameplay:`
 
 a) animatii fluide pasare:
 - Pasarea se inclina in sus pe apasarea tastei SPACE, iar la caderea libera se
 inclin in jos.Pentru aceasta m-am ajutat de functiile OnKeyPress si OnKeyRelease
 pentru a determina directia.
 - La urcare, pasarea (toate componentele) se roteste cu angularStep pe care il
 crestem in timp, iar la coborare unghiul va fi negativul de la urcare.

 b) coliziuni:
 - pentru a determina daca exista coliziune, am creat o clasa Collision, in care
 exista metoda CheckCollision. Pentru fiecare dreptunghi desenat in Update, verific
 daca exista coliziune intre pasare si acesta, fiecare dreptunchi va avea
 dimensiuni diferite. Lungimea unui dreptunghi la un moment dat va fi
 scaleFactor * initalLength. Metoda CheckCollision verifica coliziunea dintre un 
 cerc (care aproximeaza pasarea) si un dreptunghi la un moment dat. Verific
 distanta dintre centrul cercului si un punct al dreptunghiului (cel mai aproape 
 de cerc), aceasta trebuie sa fie mai mica decat raza cercului. Pentru a afla cel
 mai aproape punct de cerc, am folosit formulele:

 NearestX = Max(RectangleX, Min(CircleX, RectangleX + RectangleWidth));
 NearestY = Max(RectangleY, Min(CircleY, RectangleY + RectangleHeight));

 c) printare statistici in consola
 - La fiecare coliziune realizata, afisez numarul de coliziuni realizate pana in
 acel moment, scorul
 si numarul maxim de coliziuni pe care avem voie sa le facem.
 - Cand se ajunge la maxim Level, se afiseaza in consola scorul realizat pana in
 acel moment.
 - Scorul este incrementat cu 1 la fiecare trecere de un triunghi in scena.

 `Bonus:`
 
 1. Animatie de scalare pentru perechile de dreptunghiuri:
 - Dreptunghiurile se comporta ca un set de usi glisante de la un lift modern. 
 - In functia Update, in bucla for in care construiesc dreptunghiurile, calculez
 valori diferite pentru factorul de scalare. In acest mod, dreptunghiul isi modifica
 lungimea constant, factorul de scalare fiind difert de fiecare data.

 2. Dificultatea jocului creste pe masura ce creste punctajul jucatorului:
 - jocul are 3 stari, fiecare stare are cate o metoda diferita de calculare a
 factorului de scalare, si anume (vor avea dimensiuni diferite fata de Oy):
 1) prin folosirea lui rand() 
 scaleX = scaleX +/- ( Timp / (rand() % 10 + variabila));
 2) doar prin Timp
 scaleX = ScaleX +/-Timp;
 3) in functie de numarul dreptunghiului de desenare
 scaleX = scaleX +/- (Timp / (i + 1));

 Fiecare stare a jocului are o dificultate diferita. Miscarea dreptunghiurilor pe
 Ox creste in functie de timp in fiecare stare, factorul de translatie are cate
 o un mod diferit de calcul pentru starea respectiva.

 3. Animatie care sa simuleze modul prin care pasarea da din aripi
 - Aripa pasarii este un triunghi. Aceasta se misca doar in momentul apasarii
 tastei SPACE.
 - Pentru aceasta, m-am folosit de functiile OnKeyPress si OnKeyRelease, pentru a
 stii cand trebuie sa modific unghiul de rotatie angularWingStep. Aripa se roteste
 in intervalul [-PI / 6, PI/7].


 Sursa informatii coliziuni folosita:
 `https://yal.cc/rectangle-circle-intersection-test/?fbclid=IwAR3eGj5E_OoGnTNxhSpGa
  0hif-TIvrwhKabstNTYbaeQtXhgnLmXJiieSw`
