# Linux---file-manager
Functia touch:
        - Avand o lista de fisiere am luat toate cele trei cazuri in 
        considerare(lista goala, lista cu un element si lista cu mai multe elemente) 
        si am adaugat elementul de tip fisier la sfarsitul listei;
        - Mai multc verificam daca elementul dorit sa il adaug exista deja in lista, in 
        acest caz afisam mesajul corespunzator;

Functia rmdir:
        - Am utilizat exact acelasi principiu de adaugare ca la functia touch;

Functia rm:
        - Am luat in considearre tot cele trei cazuri de mai sus, am iterat 
        prin lista iar la momentul gasirii elementului cu numele respectiv, il 
        eliminam din lista, daca nu il gaseam afisam mesajul corespunzator;

Functia removeFiles:
        - stergerea fisierelor dintr un directorul;

Functia removeDirs:
        -stergerea directoarelor dintr un director;

Functia removeAll:
        - sterge tot ceea ce este intr un director;

Functia rmdir:
        - Am utilizat acelasi principiu ca la functia rm;

Functia cd:
        - In cadrul acestei functii iterez prin lista de directoare din directorul curent
        si cand gasesc directorul in care vreau sa ma mut chimb valoarea lui target;

Functia mv:
        - In aceasta functie imi iau niste variabile auxiliare care ma ajuta sa verific daca 
        exista sau nu old name in lista respectiv new name;
        - Dupa care in functie de aceste conditii implementez niste if-uri in cadrul carora 
        sterg directorul cu numele old name si adaug la finalul listei pe cel cu new name;
        - De asemenea in cazurile speciale afisez mesajele corespunzatoare;

Functia pwd:
        - Imi formez un string care pleaca de la directorul curent si merge din parinte in 
        parinte pana la directorul radacina (home), acesta este calea in forma inversa;
        - Dupa aceea inversez acest string, impartindu-l in tokeni si adaugand fiecare token
        intr-un vector pentru a putea creea calea finala;

Main:
    - Primesc un sir de la tatatura si in impart in 3 siruri: comanda si posibilele argumente;
    - Verific ce comanda a introdus si dupa aceea o apelez;
