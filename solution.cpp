#include <iostream>
#include <string>

using namespace std;

class Konto
{
protected:
	int login;
	string haslo;
	bool czyZalogowany;
};

class Notatka
{
	string tytul;
	string tresc;

public:
	Notatka(string tytul, string tresc)
	{
		this->tytul = tytul;
		this->tresc = tresc;
	}

	string zwrocTytul()
	{
		return this->tytul;
	}

	string zwrocTresc()
	{
		return this->tresc;
	}
	
	void nadajTytul(string tytul)
	{
		this->tytul = tytul;
	}

	void napiszTresc(string tresc)
	{
		this->tresc = tresc;
	}

};

class Folder
{
	Notatka* notatki[10];
	string nazwa;

public:
	Folder(string nazwa) : nazwa(nazwa){
		for (int i = 0; i < 10; i++)
		{
			notatki[i] = nullptr;
		}
	}

	string zwrocNazwe()
	{
		return this->nazwa;
	}

	Notatka** zwrocNotatki()
	{
		return this->notatki;
	}

	~Folder()
	{
		for (int i = 0; i < 10; i++)
		{
			if (notatki[i] != nullptr)
			{
				cout << "Usunieto notatke o tytule " << notatki[i]->zwrocTytul() << "." << endl;
				delete notatki[i];
				notatki[i] = nullptr;
			}
		}
	}
};

class KontoAdministratora : public Konto
{
public:
	KontoAdministratora(int login, string haslo)
	{
		this->login = login;
		this->haslo = haslo;
		this->czyZalogowany = false;
	}

	bool usunNotatke(Notatka* notatka)
	{
		int login;
		string haslo;
		cout << "Podaj login administratora:" << endl;
		cin >> login;
		if (login != this->login)
		{
			cout << "Podano z y login" << endl;
			return false;
		}
		else
		{
			cout << "Podaj haslo:" << endl;
			cin >> haslo;
			if (this->haslo == haslo)
				cout << "Przyznano uprawnienia" << endl;
			else
			{
				cout << "Podano zle haslo" << endl;
				return false;
			}

		}

		cout << "Czy jestes pewny ze chcesz usunac notatke? Proces jest nieodwracalny. (T/N)" << endl;
		char wybor;
		do
		{
			cin >> wybor;
			if (wybor != 'T' && wybor != 'N')
				cout << "Podaj odpowiednia opcje!" << endl;

		} while (wybor != 'T' && wybor != 'N');
		if (wybor == 'T')
		{
			delete notatka;
			notatka = nullptr;
			cout << "Usunieto notatke" << endl;
			return true;
		}
		else
		{
			cout << "Nie usunieto notatki" << endl;
			return false;
		}

	}
	bool usunFolder(Folder* folder)
	{
		int login;
		string haslo;
		cout << "Podaj login administratora:" << endl;
		cin >> login;
		if (login != this->login)
		{
			cout << "Podano z y login" << endl;
			return false;
		}
		else
		{
			cout << "Podaj haslo:" << endl;
			cin >> haslo;
			if (this->haslo == haslo)
				cout << "Przyznano uprawnienia" << endl;
			else
			{
				cout << "Podano zle haslo" << endl;
				return false;
			}

		}

		cout << "Czy jestes pewny ze chcesz usunac folder? Proces jest nieodwracalny, razem z nim usuna sie wszytskie zawarte w nim notatki. Chcesz kontynuowac? (T/N)" << endl;
		char wybor;
		do
		{
			cin >> wybor;
			if (wybor != 'T' && wybor != 'N')
				cout << "Podaj odpowiednia opcje!" << endl;

		} while (wybor != 'T' && wybor != 'N');
		if (wybor == 'T')
		{
			delete folder;
			folder = nullptr;
			cout << "Usunieto folder" << endl;
			return true;
		}
		else
		{
			cout << "Nie usunieto folderu" << endl;
			return false;

		}
	}



	friend class ManagerUzytkownikow;
};

class KontoUzytkownika : public Konto
{
	Folder* foldery[10];

public:
	KontoUzytkownika(int login, string haslo)
	{
		this->login = login;
		this->haslo = haslo;
		this->czyZalogowany = false;

		for (int i = 0; i < 10; i++)
		{
			foldery[i] = nullptr;
		}
	}

	void utworzNowaNotatke(string nazwaFolderu, string tytulNotatki, string trescNotatki)
{
    Folder* doUzupelnienia = nullptr;
    Folder* nowyStworzony = nullptr;
    bool czyNowyFolder = true;
    bool czyMiejsceNaNotatke = false;
    bool czyMiejsceNaFolder = false;

    if (this->czyZalogowany == true)
    {
        for (int i = 0; i < 10; i++)
        {
            if (this->foldery[i] == nullptr)
                continue;

            if (this->foldery[i]->zwrocNazwe() == nazwaFolderu)
            {
                czyNowyFolder = false;
                doUzupelnienia = this->foldery[i];
            }
        }

        if (czyNowyFolder)
        {
            cout << "Nie odnaleziono folderu o wskazanej nazwie, proba stworzenia folderu..." << endl;

            for (int i = 0; i < 10; i++)
            {
                if (this->foldery[i] == nullptr)
                {
                    czyMiejsceNaFolder = true;
                    nowyStworzony = new Folder(nazwaFolderu); // Poprawiono inicjalizacj 
                    this->foldery[i] = nowyStworzony;
                    break;
                }
            }

            if (czyMiejsceNaFolder == false)
            {
                cout << "Nie ma juz miejsca na nowy folder. Sprobuj usunac jednen z nich." << endl;
                return;
            }
            else
            {
                cout << "Stworzono folder" << endl;
                Notatka** zbiorNowychNotatek = nowyStworzony->zwrocNotatki();
                zbiorNowychNotatek[0] = new Notatka(tytulNotatki, trescNotatki);
                cout << "Stworzono notatke." << endl;
            }
        }
        else
        {
            Notatka** zbiorNotatek = doUzupelnienia->zwrocNotatki();
            for (int i = 0; i < 10; i++)
            {
                if (zbiorNotatek[i] == nullptr)
                {
                    czyMiejsceNaNotatke = true;
                    zbiorNotatek[i] = new Notatka(tytulNotatki, trescNotatki);
                    break;
                }
            }

            if (czyMiejsceNaNotatke == false)
            {
                cout << "Nie ma juz miejsca na nowa notatke w tym folderze, sprobuj utoworzyc nowy folder." << endl;
                return;
            }
            else
                cout << "Stworzono notatke." << endl;
        }
    }
    else
        cout << "Musisz sie zalogowac" << endl;
}

	void edytujNotatke(string nazwaFolderu, string nazwaNotatki)
	{
		Folder* gdzieNotatka = nullptr;
		Notatka* jakaNotatka = nullptr;
		bool czyIstniejeFolder = false;
		bool czyIstniejeNotatka = false;
		int wybor;

		if (this->czyZalogowany == true)
		{
			for (int i = 0; i < 10; i++)
			{
				if (this->foldery[i] == nullptr)
					break;

				if (this->foldery[i]->zwrocNazwe() == nazwaFolderu)
				{
					czyIstniejeFolder = true;
					gdzieNotatka = this->foldery[i];
				}
			}
			if (czyIstniejeFolder)
			{
				Notatka** zbiorNotatek = gdzieNotatka->zwrocNotatki();
				for (int i = 0; i < 10; i++)
				{
					if (zbiorNotatek[i] == nullptr)
						break;

					if (zbiorNotatek[i]->zwrocTytul() == nazwaNotatki)
					{
						czyIstniejeNotatka = true;
						jakaNotatka = zbiorNotatek[i];
					}
				}
				if (czyIstniejeNotatka)
				{
					cout << "Co chcesz edytowac w notatce?" << endl << "1) Tytul" << endl << "2) Tresc" << endl;
					do
					{
						cin >> wybor;

						if (wybor != 1 && wybor != 2)
							cout << "Wybierz odpowiednia opcje" << endl;

					} while (wybor != 1 && wybor != 2);

					if (wybor == 1)
					{
						string nowyTytul;
						cout << "Podaj nowy tytul" << endl;
						cin >> nowyTytul;
						jakaNotatka->nadajTytul(nowyTytul);
						cout << "Zmieniono tytul." << endl;

					}
					else
					{
						string nowaTresc;
						cout << "Podaj nowa tresc" << endl;
						cin >> nowaTresc;
						jakaNotatka->napiszTresc(nowaTresc);
						cout << "Zmieniono tresc." << endl;
					}

				}
				else
				{
					cout << "Notatka nie istnieje" << endl;
					return;
				}

			}
			else
			{
				cout << "Folder nie istnieje" << endl;
				return;
			}

		}
		else
			cout << "Musisz sie zalogowac" << endl;
		
	}

	void wyswietlFolderyZnotatkami()
{
    bool czyPuste = true;
    if (this->czyZalogowany == true)
    {
        cout << "LISTA FOLDEROW" << endl << endl;
        for (int i = 0; i < 10; i++)
        {
            if (foldery[i] == nullptr)
                continue;

            czyPuste = false;
            cout << foldery[i]->zwrocNazwe() << endl;

            Notatka** zbiorNotatek = foldery[i]->zwrocNotatki();
            if (zbiorNotatek != nullptr)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (zbiorNotatek[j] == nullptr)
                        continue;
                    cout << "   - " << zbiorNotatek[j]->zwrocTytul() << endl;
                }
            }
        }

        if (czyPuste)
            cout << "Lista jest pusta" << endl;
    }
    else
        cout << "Musisz sie zalogowac" << endl;
}

	void usunFolder(KontoAdministratora* admin, string nazwaFolderu)
	{
		Folder* doUsuniecia = nullptr;
		int indeks = 0;
		bool czyZnaleziony = false;
		if (this->czyZalogowany == true)
		{
			for (int i = 0; i < 10; i++)
			{
				if (nazwaFolderu == foldery[i]->zwrocNazwe())
				{
					indeks = i;
					czyZnaleziony = true;
					doUsuniecia = foldery[i];
					break;
				}
			}
			if (czyZnaleziony)
			{
				 bool czyUdaloSieZalogowac = admin->usunFolder(doUsuniecia);
				 if (czyUdaloSieZalogowac == true)
					 foldery[indeks] = nullptr;
			}
			else
				cout << "Nie znaleziono folderu o takiej nazwie" << endl;
		}
		else
			cout << "Musisz sie zalogowac" << endl;
	}

	void usunNotatke(KontoAdministratora* admin, string tytulNotatki)
	{
		Notatka* doUsuniecia = nullptr;
		int indeksI = 0;
		int indeksJ = 0;
		Notatka** zbiorNotatek = nullptr;
		bool czyZnaleziony = false;
		if (this->czyZalogowany == true)
		{
			for (int j = 0; j < 10; j++)
			{
				if (foldery[j] == nullptr)
					continue;

				zbiorNotatek = foldery[j]->zwrocNotatki();
				for (int i = 0; i < 10; i++)
				{
					if (zbiorNotatek[i] == nullptr)
						continue;

					if (tytulNotatki == zbiorNotatek[i]->zwrocTytul())
					{
						indeksI = i;
						indeksJ = j;
						czyZnaleziony = true;
						doUsuniecia = zbiorNotatek[i];
						break;
					}
				}

			}
			if (czyZnaleziony)
			{
				bool czySieUdalo = admin->usunNotatke(doUsuniecia);
				if (czySieUdalo)
				{
					zbiorNotatek = foldery[indeksJ]->zwrocNotatki();
					zbiorNotatek[indeksI] = nullptr;
				}

			}
			else
				cout << "Nie znaleziono notatki o takim tytule" << endl;
		}
		else
			cout << "Musisz sie zalogowac" << endl;
	}

	~KontoUzytkownika()
	{
		for (int i = 0; i < 10; i++)
		{
			if (foldery[i] != nullptr)
			{
				cout << "Usunieto folder o nazwie " << foldery[i]->zwrocNazwe() << "." << endl;
				delete foldery[i];
				foldery[i] = nullptr;
			}

		}
	}

	friend class ManagerUzytkownikow;
};

class ManagerUzytkownikow
{
	KontoUzytkownika* listaUzytkownikow[100];
	KontoAdministratora* listaAdministratorow[10];

public:
	ManagerUzytkownikow()
	{
		for (int i = 0; i < 100; i++)
		{
			this->listaUzytkownikow[i] = nullptr;
		}
		for (int i = 0; i < 10; i++)
		{
			this->listaAdministratorow[i] = nullptr;
		}
	}

	void dodajUzytkownika(int login, string haslo)
	{
		bool czyJestMiejsce = false;
		for (int i = 0; i < 100; i++)
		{
			if (this->listaUzytkownikow[i] == nullptr)
			{
				czyJestMiejsce = true;
				listaUzytkownikow[i] = new KontoUzytkownika(login, haslo);
				cout << "Dodano uzytkownika." << endl;
				break;
			}

		}
		if (!czyJestMiejsce)
			cout << "Nie ma miejsca na kolejnego uzytkownika." << endl;
	}

	void dodajAdmina(int login, string haslo)
	{
		bool czyJestMiejsce = false;
		for (int i = 0; i < 10; i++)
		{
			if (this->listaAdministratorow[i] == nullptr)
			{
				czyJestMiejsce = true;
				listaAdministratorow[i] = new KontoAdministratora(login, haslo);
				cout << "Dodano administratora." << endl;
				break;
			}

		}
		if (!czyJestMiejsce)
			cout << "Nie ma miejsca na kolejnego administratora." << endl;
	}

	KontoUzytkownika* zalogujUzytkownika()
	{
		KontoUzytkownika* uzytkownik = nullptr;
		int szanse = 1;
		bool czyZnaleziono = false;
		int login;
		string haslo;
		char wybor = 'T';

		while (wybor == 'T')
		{
			cout << "Podaj login uzytkownika:" << endl;
			cin >> login;

			for (int i = 0; i < 100; i++)
			{
				if (listaUzytkownikow[i] == nullptr)
					break;
				if (listaUzytkownikow[i]->login == login)
				{
					czyZnaleziono = true;
					cout << "Znaleziono uzytkownika o podanym loginie" << endl;
					uzytkownik = listaUzytkownikow[i];
					break;
				}
			}
			if (!czyZnaleziono)
			{
				cout << "Nie znaleziono uzytkownika o podanym loginie, chcesz sprobowac ponownie? (T/N)" << endl;
				char wybor;
				do
				{
					cin >> wybor;
					if (wybor != 'T' && wybor != 'N')
						cout << "Podaj odpowiednia opcje!" << endl;

				} while (wybor != 'T' && wybor != 'N');
				if (wybor == 'N')
					return nullptr;
			}
			else
				break;
		}

		if (czyZnaleziono)
		{
			while (szanse != 4)
			{
				cout <<"Szansa " << szanse << " : Podaj haslo do uzytkownika:" << endl;
				cin >> haslo;
				if (uzytkownik->haslo == haslo)
				{
					cout << "Haslo prawidlowe, zalogowano" << endl;
					uzytkownik->czyZalogowany = true;
					return uzytkownik;
				}
				else
				{
					cout << "Bledne haslo" << endl;
					szanse++;
				}
			}
			cout << "Wykorzystano wszytskie szanse." << endl;
			return nullptr;


		}
	}

	KontoAdministratora* zalogujAdmina()
	{
		KontoAdministratora* uzytkownik = nullptr;
		int szanse = 1;
		bool czyZnaleziono = false;
		int login;
		string haslo;
		char wybor = 'T';

		while (wybor == 'T')
		{
			cout << "Podaj login admina:" << endl;
			cin >> login;

			for (int i = 0; i < 100; i++)
			{
				if (listaAdministratorow[i] == nullptr)
					continue;
				if (listaAdministratorow[i]->login == login)
				{
					czyZnaleziono = true;
					cout << "Znaleziono admina o podanym loginie" << endl;
					uzytkownik = listaAdministratorow[i];
					break;
				}
			}
			if (!czyZnaleziono)
			{
				cout << "Nie znaleziono admina o podanym loginie, chcesz sprobowac ponownie? (T/N)" << endl;
				char wybor;
				do
				{
					cin >> wybor;
					if (wybor != 'T' && wybor != 'N')
						cout << "Podaj odpowiednia opcje!" << endl;

				} while (wybor != 'T' && wybor != 'N');
				if (wybor == 'N')
					return nullptr;
			}
			else
				break;
		}

		if (czyZnaleziono)
		{
			while (szanse != 4)
			{
				cout << "Szansa " << szanse << " : Podaj haslo do admina:" << endl;
				cin >> haslo;
				if (uzytkownik->haslo == haslo)
				{
					cout << "Haslo prawidlowe, zalogowano" << endl;
					uzytkownik->czyZalogowany = true;
					return uzytkownik;
				}
				else
				{
					cout << "Bledne haslo" << endl;
					szanse++;
				}
			}
			cout << "Wykorzystano wszytskie szanse." << endl;
			return nullptr;


		}
	}
	
	void wylogujUzytkownika(KontoUzytkownika* uzytkownik)
	{
		uzytkownik->czyZalogowany = false;
	}

	void wylogujAdmina(KontoAdministratora* admin)
	{
		admin->czyZalogowany = false;
	}

	~ManagerUzytkownikow()
	{
		for (int i = 0; i < 100; i++)
		{
			if (listaUzytkownikow[i] != nullptr)
			{
				cout << "Usunieto uzytkownika o loginie " << listaUzytkownikow[i]->login << "." << endl;
				delete listaUzytkownikow[i];
				listaUzytkownikow[i] = nullptr;

			}

		}
		for (int i = 0; i < 10; i++)
		{
			if (listaAdministratorow[i] != nullptr)
			{
				cout << "Usunieto admina o loginie " << listaAdministratorow[i]->login << "." << endl;
				delete listaAdministratorow[i];
				listaAdministratorow[i] = nullptr;
			}

		}
	}
};


int main(void)
{
ManagerUzytkownikow manager;
    KontoUzytkownika* zalogowanyUzytkownik = nullptr;
    KontoAdministratora* zalogowanyAdmin = nullptr;

    while(true) {
        int wybor;
        cout << "\nmenu\n";
        cout << "1. stworz konto uzykownika\n";
        cout << "2. stworz konto administratora\n";
        cout << "3. zaloguj uzytkownika\n";
        cout << "4. zaloguj administratora\n";
        cout << "5. wyloguj uzykownika\n";
        cout << "6. wyloguj administratora\n";
        cout << "7. dodaj notatke\n";
        cout << "8. wyswietl notatki\n";
        cout << "0. wyjscie\n";
        cout << "wybierz opcje: ";
        cin >> wybor;
		int login;
		string haslo, folder, tytul,tresc;

        switch(wybor) {
            case 1: {
                cout << "podaj login: ";
                cin >> login;
                cout << "podaj haslo: ";
                cin >> haslo;
                manager.dodajUzytkownika(login, haslo);
                break;
            }
            case 2: {
                cout << "podaj login: ";
                cin >> login;
                cout << "podaj haslo: ";
                cin >> haslo;
                manager.dodajAdmina(login, haslo);
                break;
            }
            case 3: {
                zalogowanyUzytkownik = manager.zalogujUzytkownika();
                break;
            }
            case 4: {
                zalogowanyAdmin = manager.zalogujAdmina();
                break;
            }
            case 5: {
                manager.wylogujUzytkownika(zalogowanyUzytkownik);
                break;
            }
            case 6: {
                manager.wylogujAdmina(zalogowanyAdmin);
                break;
            }
            case 7: {
                cout << "podaj nazwe folderu: ";
                cin >> folder;
                cout << "podaj tytul notatki: ";
                cin >> tytul;
				cout << "podaj tresc notatki: ";
				cin >> tresc;
                zalogowanyUzytkownik->utworzNowaNotatke(folder, tytul,tresc);
                break;
            }
            case 8: {
                zalogowanyUzytkownik->wyswietlFolderyZnotatkami();
                break;
            }
            case 0:
                return 0;
            default:
                cout << "niepoprawna opcja\n";
        }
    }

    return 0;
}
