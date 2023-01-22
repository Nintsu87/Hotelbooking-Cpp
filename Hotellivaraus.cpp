#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

/*-----------------------------------------------------*\
|	Nina Laaksosen touhuama harjoitustyö	22TietoB	|
|	TAMK: 5G00EI63-3009									|
|	C++-ohjelmoinnin perusteet -kurssi					|
|														|
|	Pyrin saamaan harjoitustyöstä arvosanan: 5 (1-5)	|
|														|
|	Jos luet tätä: Toivoisin saavani kehitysehdotuksia.	|
|														|
\*-----------------------------------------------------*/


// Luodaan structi yksittäisille huoneille
struct Huone {
	int id, // id tyyppinen juokseva numero, joka yksilöi huoneet
		yohinta, // joko 100e tai 150e
		varaus; // monta yötä
	double ale, yo_alen_jalkeen;// arvottu alennuskerroin
};

// Luodaan struckti varaukselle
struct Varaus {
	string varaajan_nimi = "";
	int id = 0, // varauksen id
		huoneid = 0, // varatun huoneen nro
		yomaara = 0, // montako yötä on varattu
		alemaara = 0, // ei prosentteina, vain kirjanpitoa varten
		loppusumma = 0; // loppusumma sis. ale
	double ale = 1.0; // alennuskerroin
};

// arpoo alennuksen 3 valmiista vaihtoehdosta randin avulla ja palauttaa sen
double Arvo_ale() {
	double ale = 0;
	int nro = rand() % 3 + 1;
	switch (nro) {
	case 1:
		return 1.0;
	case 2:
		return 0.9;
	case 3:
		return 0.8;
	}
}

// luo huoneen anetuilla tiedoilla ja palauttaa sen
Huone LuoHuone(int luku, int kaksiomaara) {
	Huone huone;
	int yksio = 100, 
		kaksio = 150;
	double ale = Arvo_ale();
	huone.ale = ale;
	huone.id = luku;
	huone.varaus = 0;

	// jos id on isompi on kyse 2h huoneesta
	if (luku > kaksiomaara) {
		huone.yohinta = kaksio;
		huone.yo_alen_jalkeen = kaksio * ale;
		return huone;
	}
	// muuten on 1h huone
	huone.yohinta = yksio;
	huone.yo_alen_jalkeen = yksio * ale;
	return huone;
}

// tarkistaa jakojäännöksen ja muokkaa mainin yksiöiden ja kaksioiden määriä
void Puolita_huonemaara(int maara, int *yksiomaara, int *kaksiomaara) {
	int p_yksio = 0, p_kaksio = 0;
	if (maara % 2 != 0) {
		maara = maara - 1;
		*kaksiomaara = maara / 2 + 1;
		*yksiomaara = maara / 2;
	}
	else {
		*yksiomaara = maara / 2;
		*kaksiomaara = maara / 2;
	}
}

// luo varauksen annetuilla tiedoilla
Varaus Luo_varaus(int varausnro, string nimi, int huoneid, int yomaara, double aleprosentti, int loppusumma, int alemaara) {
	Varaus varaus;
	
	varaus.id = varausnro;
	varaus.varaajan_nimi = nimi;
	varaus.huoneid = huoneid;
	varaus.yomaara = yomaara;
	varaus.ale = aleprosentti;
	varaus.alemaara = alemaara;
	varaus.loppusumma = loppusumma;
	return varaus;
}

// tarkistaa onko yksiöitä tai kaksioita vapaana ja ilmoittaa
// jos jompikumpi varattu
void Tulosta_menu(int vapaita1, int vapaita2) {
	cout << "Vapaita huoneita \tKoko \tMäärä";
	if (vapaita1 == 0 && vapaita2 > 0) {
		cout << "\n\t\t\t2hlö\t" << vapaita2;
		cout << "\n** Kaikki 1hlön huoneet on varattuina. **";
	} else if (vapaita1 > 0 && vapaita2 == 0) {
		cout << "\n\t\t\t1hlö\t" << vapaita1;
		cout << "\n** Kaikki 2hlön huoneet on varattuina. **";	
	} else if (vapaita1 == 0 && vapaita2 == 0) {
		cout << "\n** Kaikki huoneet ovat varattuina. **";
	} else {
		cout << "\n\t\t\t1hlö\t" << vapaita1;
		cout << "\n\t\t\t2hlö\t" << vapaita2;
	}
	
	cout << "\n\nToiminnot:\t\t\tKomento:\n";
	cout << "Varaa huone\t\t\t1\n";
	cout << "Etsi varauksia\t\t\t2\n";
	cout << "Muokkaa varausta\t\t3\n";
	cout << "Lista vapaista huoneista\t4\n";
	cout << "Lopeta\t\t\t\t11\n";
}


// arpoo varauksen id:n
int Arvo_id() {
	int id = rand() % 89999 + 10000;
	return id;
}

// kevyt function loop tarkistaa onko käyttäjän antama komento oikein
int Kysy_kumpi_koko(int yksiovapaana, int kaksiovapaana) {
	bool tarkistusloop = true,
		tarkistusloop2 = true;
	string kumpi_koko_komento, 
		tuloste, 
		s_tarkiste;
	int tarkiste = 0;

	// tarkistaa, onko yksiöitä tai kaksioita ylipäänsä vapaana
	// ja rajaa vaihtoehdot
	if (yksiovapaana == 0 && kaksiovapaana == 0) { // kaikki varattuja
		cout << "Kaikki hotellin huoneet ovat varattuna.\nPalautuu päämenuun\n";
		return 3;
	}
	// yksiöt varattuja, voi joko palata päämenuun tai varata kaksion
	else if (yksiovapaana == 0) { 
		while (tarkistusloop) {
			cout << "Kaikki yksiöt on varattuna. Voit varata vain kaksioita."
				<< "Haluatko varata kaksion? \n(1 = kyllä, 2 = ei)\n";
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, s_tarkiste);
			if (s_tarkiste == "1") {
				return 2;
			}
			else if (s_tarkiste == "2") {
				cout << "\nPalautuu päämenuun.\n";
				return 3;
			}
			else {
				cout << "Vain joko 1 tai 2 käy syötteeksi.\n";
			}
		}
	}
	// kaksiot varattuja, voi joko palata päämenuun tai varata yksiön
	else if (kaksiovapaana == 0) {
		while (tarkistusloop) {
			cout << "Kaikki kaksiot on varattuna. Voit varata vain yksiöitä."
				<< "Haluatko varata yksiön? \n(1 = kyllä, 2 = ei)\n";
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, s_tarkiste);
			if (s_tarkiste == "1") {
				return 1;
			}
			else if (s_tarkiste == "2") {
				cout << "\nPalautuu päämenuun.\n";
				return 3;
			}
			else {
				cout << "Vain joko 1 tai 2 käy syötteeksi.\n";
			}

		}
	}
	// Jos kumpiakaan huonekoista ei ole kokonaan varattuna pyytää käyttäjältä 
	// kumpi huonekoko
	while (tarkistusloop2) {
		cout << "\nToiminnot:\t\t\tKomento:\n" << tuloste << "Yksiö\t\t\t\t1\n"
			<< "Kaksio\t\t\t\t2\nAnna komento: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, kumpi_koko_komento);

		if (kumpi_koko_komento == "1") {
			return 1;
		}
		else if (kumpi_koko_komento == "2") {
			return 2;
		}
		else {
			cout << "\nEn ymmärtänyt komentoa: \"" << kumpi_koko_komento
			<< "\", yritä uudestaan.\n";

		}
	}
}

// pyytää varausnumeron, kunnes se on syötetty oikein
int Pyyda_varausnumero(vector<Varaus>varauslista) {
	bool looppi = true;
	string syote;
	int varausnro, 
		muokattava_indx = -1;
	while (looppi) {
		cout << "Anna muokattavan varauksen varausnumero (Takaisin = 11)\n" 
			<< "Varausnumero: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, syote);
		
		if (syote == "11") {
			return -1;
		}
		else {
			// jos varausnumero on int ja 10000-99999 tai 
			// sillä ei ole varauksia -> antaa palautetta
			try {
				looppi = false;
				varausnro = stoi(syote);
				for (int i = 0; i < varauslista.size(); i++) {
					if (varauslista[i].id == varausnro) {
						muokattava_indx = i;
					}
				}
				if (varausnro > 99999 || varausnro < 10000) {
					cout << "Varausnumero on 10000 ja 99999 väliltä oleva numero. ";
					throw 505;
				}

				if (muokattava_indx == -1) {
					cout << "Syöttämälläsi varausnumerolla ei ole varauksia. ";
					throw 505;
				}
				return muokattava_indx;
			}
			catch (...) {
				looppi = true;
				cout << "Yritä uudelleen.\n";
			}
		}
	}
}

// Pyytää tietoja käyttäjältä varaus struktin luomista varten
Varaus Varauksen_tiedot(Huone huone, int id) {
	Varaus varaus;
	string varaajan_nimi, s_yomaara;
	int yomaara;
	bool apuboolean = true;
	double loppusumma = 0.0, alemaara = 0.0;


	cout << "\nNimi, jolla varaus tehdään: ";
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, varaajan_nimi);
	// while-loop, jossa tarkistetaan onko yösyöte oikean tyyppinen
	while (apuboolean) {
		cout << "Montako yötä huone varataan (1-30): ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, s_yomaara);
		try {
			yomaara = stoi(s_yomaara);
			// jos yli 30 tai alle 0, kehitetään error -> antaa palautetta
			// ja whileloop jatkuu
			if (yomaara > 30 || yomaara <=0) {
				cout << "\nEt voi varata yli 30 tai alle 1 yöksi. ";
				throw 505;
			}
			// lopettaa loopin
			apuboolean = false;
		}
		catch (...) {
			// palaute käyttäjälle
			cout << "Antamaasi syötettä \"" << s_yomaara << "\" ei hyväksytä.\n";
		}
	}
	// luo structin annetuilla tiedoilla ja palauttaa sen
	loppusumma = yomaara * huone.yo_alen_jalkeen;
	alemaara = (yomaara * huone.yohinta) - loppusumma;
	varaus = Luo_varaus(id, varaajan_nimi, huone.id, yomaara, huone.ale, loppusumma, alemaara);
	return varaus;
}

// testaa huonenumeron (kumpiprintti on valmiiksi,
// jos haluan lisätä enemmän printtejä tähän funktioon)
void Testaa_intti(int* intti, int eka_numero, int toka_numero, int kumpiprintti) {
	bool booleanmuuttuja = true;
	int huonenro;
	if (kumpiprintti == 1) {
		// pyydetään huonenumeroa, kunnes se on oikeanlainen
		while (booleanmuuttuja) {
			cout << "Anna huoneen numero (" << eka_numero << "-" << toka_numero << "): ";
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> huonenro;

			if (cin.fail()) {
				cout << "Huonenumeron pitää olla luku.\n\n";
			}
			else if (huonenro > toka_numero || huonenro < eka_numero) {
				cout << "Huonenumeron pitää olla " << eka_numero << " ja "
					<< toka_numero << " väliltä.\n";

			}
			else {
				*intti = huonenro;
				booleanmuuttuja = false;
			}
			cin.clear();
		}
	}
}

// Varauksen tuloste
void Varauksen_tulostus(Varaus varaus, int maara) {
	cout << "Varaajan nimi:\t\t\t" << varaus.varaajan_nimi
		<< "\nHuonenumero:\t\t\t" << varaus.huoneid
		<< "\nHuoneen koko:\t\t\t";
	if (varaus.huoneid < (maara - 1))
		cout << "1";
	else {
		cout << "2";
	}
	cout << " huonetta.\nVarattu aika:\t\t\t" << varaus.yomaara
		<< " yötä.\nLoppusumma:\t\t\t" << varaus.loppusumma << " Euroa.\n";
	if (varaus.ale != 1) {
		cout << "Alennusta:\t\t\t" << varaus.alemaara << " Euroa (" << (1 - varaus.ale) * 100 << " %).\n";
	}
}

// Luo printit ja pyytää käyttäjältä tietoja ja luo varauksia niiden mukaan
bool Huone_printit(Huone varattava_huone, bool Onko_alennusta, int varausnumero, int yksiomaara, vector<Varaus>& varauslista, vector<Huone>& huonelista) {
	bool looppiapuri = true;
	string jatkuuko, onko1vai2 = "Yhden";
	Varaus kasiteltava_varaus;
	int huone_id, yomaara;
	cout << "\nHuoneen nro:\t\t\t" << varattava_huone.id;

	// tarkistaa onko alennusta ja valitsee tulosteen sen mukaan
	if (Onko_alennusta)
		cout << "\nHuoneen alennus: \t\t" << (1 - varattava_huone.ale) * 100 << "%" << endl;
	else
		cout << "\nHuoneen hinta: \t\t\tNormaalihintainen\n";

	// looppi jossa kysytään oliko kyseessä se huone joka haluttiin vai perutaanko
	while (looppiapuri) {
		cout << "\nHaluatko jatkaa vai aloittaa alusta (palata menuun)?\n"
			<< "Jatka:\t\t\t\ty\nAloita alusta:\t\t\tn\n\nAnna komento: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, jatkuuko);
		// jos haluaa jatkaa
		if (jatkuuko == "y") {
			// tallentaa varaus-structiksi funktiosta palaavan varaus strucktin
			kasiteltava_varaus = Varauksen_tiedot(varattava_huone, varausnumero);
			// lisää varauksen varauslistaan
			varauslista.push_back(kasiteltava_varaus);
			yomaara = kasiteltava_varaus.yomaara;
			huone_id = varattava_huone.id;
			
			// tallentaa huonelistassa olevaan huoneeseen joka juuri varattiin 
			// varattujen öiden määrän, jota käytetään tarkistamaan onko huone
			// vielä vapaana
			huonelista[huone_id -1].varaus = yomaara;
			if (huone_id > (yksiomaara))
				onko1vai2 = "Kahden";
			// tulostaa yhteenvedon talletetusta varauksesta
			cout << "\nVaraus on tehty nimellä: " << kasiteltava_varaus.varaajan_nimi
				<< endl << onko1vai2 << " hengen huone " << varattava_huone.id << " on varattu " 
				<< yomaara << " yöksi.\nVarauksen loppusumma on "
				<< kasiteltava_varaus.loppusumma;
			// tarkistaa onko alea ja printtaa sen mukaisesti.
			if (kasiteltava_varaus.ale != 1) {
				cout << "Euroa, josta on otettu " << kasiteltava_varaus.alemaara
					<< " Euroa eli " << (1 - kasiteltava_varaus.ale) * 100
					<< "% alennus pois.\n";
			}
			else
				cout << "Euroa.\n";
			cout << "HUOM! Voit muokata varausta varausnumerolla: \n\t" << varausnumero
				<< "\nPidä se tallessa.\n\n";
			looppiapuri = false;
			return looppiapuri;

		}
		else if (jatkuuko == "n") {
			looppiapuri = false;
			return looppiapuri;
		}
		else
			cout << "\nEn ymmärtänyt komentoa: \"" << jatkuuko
			<< "\", yritä uudestaan.\n";
	}
	jatkuuko.clear();
}

// tarkistaa onko huone vapaana varauksen (yömäärä) tarkistaen
bool Onko_vapaa(int id, vector<Huone>huonelista) {
	if (huonelista[id].varaus == 0)
		return true;
	return false;
}

// tarkistaa onko alennusta printtejä varten
bool Onko_alennusta(double kerroin) {
	if (kerroin != 1.0)
		return true;
	return false;
}

// Pääkoodi
int main() {
	setlocale(LC_ALL, "fi_FI"); // avataan tulostukseen ääkköset
	srand(time(NULL));
	bool jatketaan = true; // while-loopin hallitsijaboolean
	string komento; // stringiin otetaan käyttäjältä komento
	vector<Huone>huonelista; // huoneita varten 
	vector<Varaus>varauslista; // varauksia varten
	
	// Luo huonemäärän randomisti ja tarkistetaan montako huonetta on puolet
	int huonemaara = rand() % 300 + 40;
	int yksiomaara, kaksiomaara;
	
	Puolita_huonemaara(huonemaara, &yksiomaara, &kaksiomaara);
	
	// luo huoneet huone tyyppiseen vectoriin
	for (int id = 1; id <= huonemaara; id++) {
		huonelista.push_back(LuoHuone(id,kaksiomaara));
	}

	// while-silmukka, jonka käyttäjä voi sulkea määrätyllä komennolla.
	while (jatketaan) {
		int vapaat_yksiot = 0, vapaat_kaksiot = 0; // montako vapaata yksiöö/kaksioo 
		// lasketaan, montako vapaata huonetta on koottain
		for (int i = 0; i < huonemaara; i++) {
			int varaus = huonelista[i].varaus;
			if (huonelista[i].id <= yksiomaara) {
				if (varaus == 0)
					vapaat_yksiot++;
			}
			else {
				if (varaus == 0)
					vapaat_kaksiot++;
			}
		}

		// kutsuu funktioo varausten määrien kanssa
		Tulosta_menu(vapaat_yksiot, vapaat_kaksiot);

		// pyytää käyttäjältä komentoa 
		cout << "\nAnna komento: ";

		// resettaa cinin niin, ettei tule ylimääräistä tyhjää komentoa välissä
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, komento);

		// tarkistaa komennon ja toimii sen mukaisesti.
		if (komento == "11") { // komento 11 katkaisee ohjelman käytön
			jatketaan = false;
			cout << "\nKiitos ohjelman käytöstä!\n";
		}
		else if (komento == "1") { // varaa huone
			komento.clear();
			bool varauskomentoloop = true;
			string varauskomento = "0";
			int varauksien_maara = varauslista.size();
			int varausnumero = 0;
			// luo varausnumeron
			varausnumero = Arvo_id();

			// tarkistaa, onko arvottu varausnumero jo käytössä
			if (!varauslista.empty()) {
				for (int i = 0; i < varauksien_maara; i++) {
					if (varauslista[i].id == varausnumero) {
						varausnumero = Arvo_id();
						i = 0;
					}
				}
			}

			while (varauskomentoloop) {
				string jatkuuko;
				int yomaara = 0;
				int varaus_id = 0;
				// kysyy käyttäjältä valitseeko hän vai arpooko ohjelma huoneen
				cout << "\nToiminnot:\t\t\tKomento:\nValitse huone\t\t\t1\n"
					<< "Arvo huone\t\t\t2\nPalaa päävalikkoon\t\t11\n" << "\nAnna komento: ";
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, varauskomento);

				// käyttäjä valitsee huoneen
				if (varauskomento == "1") { 
					Huone varattava_huone;
					Varaus kasiteltava_varaus;
					bool kayttajan_valinta_apuri = true;
					int annettu_huonenumero = 0;
					int kumpi_koko_komento = Kysy_kumpi_koko(vapaat_yksiot, vapaat_kaksiot);
					// jos käyttäjä valitsee yksiön kokoisen, pyytää loopissa tiedot
					if (kumpi_koko_komento == 1) {
						
						while (kayttajan_valinta_apuri) {
							// pyytää huonenumeroa
							Testaa_intti(&annettu_huonenumero, 1, yksiomaara, 1);
							// jos vapaa, pääsee antamaan tiedot ja tekemään varauksen ja pois loopista
							if (Onko_vapaa(annettu_huonenumero - 1, huonelista)) {
								kayttajan_valinta_apuri = false;
								varattava_huone = huonelista[annettu_huonenumero - 1];

								varauskomentoloop = Huone_printit(varattava_huone, Onko_alennusta(varattava_huone.ale), varausnumero, yksiomaara, varauslista, huonelista);
							}
							else
								cout << "Antamasi huone on valitettavasti varattu.\n";
						}
					}
					// jos käyttäjä valitsee kaksion kokoisen, pyytää loopissa tiedot
					else if (kumpi_koko_komento == 2) {

						while (kayttajan_valinta_apuri) {
							// pyytää huonenumeroa
							Testaa_intti(&annettu_huonenumero, (yksiomaara + 1), huonemaara, 1);
							// jos vapaa, pääsee antamaan tiedot ja tekemään varauksen ja pois loopista
							if (Onko_vapaa(annettu_huonenumero - 1, huonelista)) {
								kayttajan_valinta_apuri = false;
								varattava_huone = huonelista[annettu_huonenumero - 1];

								varauskomentoloop = Huone_printit(varattava_huone, Onko_alennusta(varattava_huone.ale), varausnumero, yksiomaara, varauslista, huonelista);
							}
							else
								cout << "Antamasi huone on valitettavasti varattu.\n";
						}
					}
					
					
				}
				// käyttäjä valitsee ohjelman arpoman huoneen
				else if (varauskomento == "2") {
					int kumpi_koko_komento = Kysy_kumpi_koko(vapaat_yksiot, vapaat_kaksiot);
					bool kayttajan_valinta_apuri2 = true;
					// jos käyttäjä valitsee yksiön kokoisen, pyytää loopissa tiedot
					if (kumpi_koko_komento == 1) {
						Huone randomhuone;
						Varaus kasiteltava_varaus;
						// arpoo uuden huoneID niin kauan, kunnes huone on vapaa
						while (kayttajan_valinta_apuri2) {
							int random_huone_id = rand() % (yksiomaara - 1) + 1;

							if (Onko_vapaa(random_huone_id - 1, huonelista)) {
								kayttajan_valinta_apuri2 = false;
								randomhuone = huonelista[random_huone_id];
								varauskomentoloop = Huone_printit(randomhuone, Onko_alennusta(randomhuone.ale), varausnumero, yksiomaara, varauslista, huonelista);
							}
						}
					}
					// jos käyttäjä valitsee kaksion kokoisen, pyytää loopissa tiedot
					else if (kumpi_koko_komento == 2) {
						Huone randomhuone;
						Varaus kasiteltava_varaus;
						int random_huone_id = -1;

						// arpoo uuden huoneID niin kauan, kunnes huone on vapaa
						while (kayttajan_valinta_apuri2) {
							random_huone_id = rand() % (huonemaara - yksiomaara) + yksiomaara;
							
							if (Onko_vapaa(random_huone_id - 1, huonelista)) {
								kayttajan_valinta_apuri2 = false;
								randomhuone = huonelista[random_huone_id];
								varauskomentoloop = Huone_printit(randomhuone, Onko_alennusta(randomhuone.ale), varausnumero, yksiomaara, varauslista, huonelista);
							}
						}
					}
					else if (kumpi_koko_komento == 3) {
						varauskomentoloop = false;
					}
				}
				// palauttaa takaisin päävalikkoon
				else if (varauskomento == "11") {
					varauskomentoloop = false;

				}
				else {
					cout << "\nEn ymmärtänyt komentoa: \"" << varauskomento
						<< "\", yritä uudestaan.\n";
				}
				varauskomento.clear();
			}

		}

		// 2 -> etsii varauksia
		else if (komento == "2") {
			vector<int>loydetyt_indxit;
			bool etsintabool = true;
			string etsinta_komento,
				s_etsinta,
				alkuperainen;
			int varauslista_max;
			// tarkistaa onko varauksia ylipäänsä
			if (varauslista.size() == 0) {
				etsintabool = false;
				cout << "\nHotellissa ei ole varauksia.\n\n";
			}
			// jos varauksia on, aloittaa whileloopin
			while (etsintabool) {
				// ottaa varauslistasta muokattavan varauksen indeksin
				int muokattava_indx = -1; 
				varauslista_max = varauslista.size();
				// tulostaa käyttäjälle pienen menun ja pyytää mitä haluaa tehdä
				cout << "\nEtsi:\nVaraajan nimellä \t\t1"
					<< "\nVarausnumerolla\t\t\t2\nPalaa päämenuun\t\t\t11\nAnna komento: ";
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, etsinta_komento);

				// 1 -> etsi nimellä
				if (etsinta_komento == "1") {
					string pieni_syotetty, pieni_alkuperainen;
					// pyytää nimeä tai sen osaa s_etsintämuuttujaan
					cout << "Syötä nimi tai sen osa: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, s_etsinta);

					// käy varauslistan läpi
					for (int i = 0; i < varauslista_max; i++) {
						alkuperainen = varauslista[i].varaajan_nimi;
						pieni_alkuperainen = alkuperainen;
						pieni_syotetty = s_etsinta;
						// muutetaan jokainen kirjain pieniksi, jotta vertailu ignooraa isot kirjaimet
						transform(pieni_alkuperainen.begin(), pieni_alkuperainen.end(), pieni_alkuperainen.begin(), ::tolower);
						transform(pieni_syotetty.begin(), pieni_syotetty.end(), pieni_syotetty.begin(), ::tolower);

						// jos etsinnällä ei ole positioo (eli jos löytyy) lisää indeksin listaan
						if (pieni_alkuperainen.find(pieni_syotetty) != string::npos) {
							loydetyt_indxit.push_back(i);
						}
						
						// jos ei ole tyhjä indeksilista (johon tallennettiin löydetyt indeksit)
						if (!loydetyt_indxit.empty()) {
							cout << "\nOsuvia varauksia nimellä \"" << s_etsinta
								<< "\" löytyi " << loydetyt_indxit.size() << " kpl.\n";

							// tulostaa indeksi kerrallaan listasta löydetyt
							for (int i = 0; i < loydetyt_indxit.size(); i++) {
								Varaus kasiteltava_varaus = varauslista[i];
								Varauksen_tulostus(varauslista[i], kaksiomaara);
							}
						}
						else {
							cout << "Nimellä \"" << s_etsinta << "\" ei löytynyt varausta.\n";

						}
						loydetyt_indxit.clear();
						s_etsinta.clear();
					}
					
				}
				// 2 -> etsi varausnumerolla,
				else if (etsinta_komento == "2") {
					
					// pyytää käyttäjältä stringiin varausnumeron
					cout << "Syötä varausnumero: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, s_etsinta);

					// käy varauslistan määrän verran läpi 0->
					for (int i = 0; i < varauslista_max; i++) {
						int etsintavarausnro, apunro = 0;
						
						// jos voi muokata intiksi ja jos 10000 < nro < 99999 tekee tarkastuksen
						try {
							etsintavarausnro = stoi(s_etsinta);

							for (Varaus v : varauslista) {

								if (v.id == etsintavarausnro) {
									loydetyt_indxit.push_back(apunro);
								}

								if (!loydetyt_indxit.empty()) {
									cout << "\nVarausnumerolla " << etsintavarausnro << " löytyi:\n";
									for (int i = 0; i < loydetyt_indxit.size(); i++) {
										Varaus kasiteltava_varaus = varauslista[i];
										Varauksen_tulostus(varauslista[i], kaksiomaara);
									}
									loydetyt_indxit.clear();
								}
								else if (etsintavarausnro > 99999 || etsintavarausnro < 10000) {
									throw 505;
								}
								else {
									cout << "\nVarausnumerolla " << etsintavarausnro << " ei löytynyt mitään.";
								}
							}
						}
						catch (...) {
							cout << s_etsinta << " ei ole numero tai se ylittää arvot 10000 - 99999.\n";
						}
					}
					s_etsinta.clear();
				}
				else if (etsinta_komento == "11") {
					etsintabool = false;
				}
				else {
					cout << "Komento \"" << etsinta_komento << "\" ei kelpaa.\n";
				}
				
			}
		}
		// 3 -> muokkaa varauksia
		else if (komento == "3") {
			
			bool muokataanko_bool = true, 
				muokkausbool = true;
			int muokattava_indx = -1, 
				rundi = 1;
			vector<int>loydetyt_indxit;
			string etsinta_komento, 
				muokkaus_komento, 
				muokattava_nimi;

			// tarkistaa onko varauksia
			if (varauslista.empty()) {
				cout << "\nHotellissa ei ole varauksia.\n\n";
				muokataanko_bool = false;
			}
			// aloittaa pienen menu tyyppisen whileloopin
			while (muokataanko_bool) {
				if (rundi > 1) {
					cout << "\nJatka muokkaukseen? (1 = kyllä, 2 = ei)\nAnna komento: ";
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, etsinta_komento);
					cout << endl;
				}
				else {
					etsinta_komento = "1";
					rundi++;
				}
			
				if (etsinta_komento == "1") {
					muokattava_indx = Pyyda_varausnumero(varauslista);

					if (muokattava_indx == -1)
						muokkausbool = false;

					while (muokkausbool) {
						cout << "\nMitä haluat muokata?\nPoista koko varaus\t\t1\n"
							<< "Nimeä\t\t\t\t2\nAikaa\t\t\t\t3\nPalaa takaisin päämenuun\t11\n"
							<< "Anna komento: ";
						cin.ignore(cin.rdbuf()->in_avail());
						getline(cin, muokkaus_komento);


						if (muokkaus_komento == "1") {
							int varmistus,
								poistetun_varausnumero = varauslista[muokattava_indx].id,
								poistetun_huoneid = varauslista[muokattava_indx].huoneid;
							bool varmistusbool = true;
							while (varmistusbool) {

							
								cout << "\nOletko aivan varma? (1 = kyllä, 2 = ei)\nAnna komento: ";
								cin.ignore(cin.rdbuf()->in_avail());
								cin >> varmistus;
								if (cin.fail()) {
									cout << "\nVain 1 tai 2 komento käy.\n";

								}
								else if (varmistus == 2) {
									muokataanko_bool = false;
									varmistusbool = false;
								}
								else if (varmistus == 1) {
									for (int i = 0; i < loydetyt_indxit.size(); i++) {
										if (loydetyt_indxit[i] == muokattava_indx)
											loydetyt_indxit.erase(loydetyt_indxit.begin() + i);

									}

									varauslista.erase(varauslista.begin() + muokattava_indx);
								
									for (int i = 0; i < huonelista.size(); i++) {
										if (huonelista[i].id == poistetun_huoneid) {
											huonelista[i].varaus = 0;
										}
									}
									cout << "Varaus varausnumerolla: " << poistetun_varausnumero << " poistettu.\n";
									if (varauslista.size() == 0) {
										muokkausbool = false;
										muokataanko_bool = false;
										cout << "Hotellissa ei ole varauksia.\n\n";
										break;

									}
									muokkausbool = false;
								}
							}
						}
						else if (muokkaus_komento == "2") {
							cout << "\nUusi nimi: ";
							cin.ignore(cin.rdbuf()->in_avail());
							getline(cin, muokattava_nimi);
							varauslista[muokattava_indx].varaajan_nimi = muokattava_nimi;
							muokkausbool = false;
							cout << endl << "Muokattu:" << endl;
							Varauksen_tulostus(varauslista[muokattava_indx], kaksiomaara);
							cout << endl;

						}
						else if (muokkaus_komento == "3") {
							int oidenmaara;
							bool onko_nro = true;
							while (onko_nro) {
								cout << "\nUusi öiden määrä: ";
								cin.ignore(cin.rdbuf()->in_avail());
								cin >> oidenmaara;
								if (cin.fail()) {
									cout << "\nAnna öiden määrä numerona.\n";
									
								} else if (oidenmaara > 30 || oidenmaara < 1) {
									cout << "\nEt voi varata yli 30 tai alle 1 yöksi.\n";
								
								} else {
									varauslista[muokattava_indx].yomaara = oidenmaara;
									for (Huone h : huonelista) {
										if (h.id == varauslista[muokattava_indx].huoneid) {
											h.varaus = oidenmaara;
											varauslista[muokattava_indx].loppusumma = (h.yohinta * oidenmaara) * h.ale;
											varauslista[muokattava_indx].alemaara = (h.yohinta * oidenmaara) - varauslista[muokattava_indx].loppusumma;
										}
									}
									muokkausbool = false;
									onko_nro = false;
									cout << endl << "Muokattu:" << endl;
								}
								cin.clear();
								
							}
							Varauksen_tulostus(varauslista[muokattava_indx], kaksiomaara);
						}

						else if (muokkaus_komento == "11") {
							muokkausbool = false;
							muokataanko_bool = false;
						}

					}
				}
				else if (etsinta_komento == "2") {
					muokataanko_bool = false;
					muokkausbool = false;

				}
				else {
					cout << "Syötä 1 tai 2.";
				}
				
				muokkausbool = true;
				
			}
		}

		// tulostaa vapaista huoneista listan
		else if (komento == "4") { 

			int apunumero = 0;
			cout << "\n\t**YKSIÖT**\n\nHuone:\t" << "Ale:\tHuone:\t"
				<< "Ale:\tHuone:\t" << "Ale:\n";

			// iteroi vectorin yksiöt läpi ja tulostaa huoneista tarvittavat tiedot
			// 3 huonetta samalle riville apunumeron avulla
			for (int i = 0; i < vapaat_yksiot; i++) {
				int varaus = huonelista[i].varaus;
				if (varaus == 0) {

					cout << huonelista[i].id << "\t";
					if (huonelista[i].ale == 1) {

						cout << " ";
						apunumero++;
					}
					else {
						// laskutoimituksessa luodaan alekertoimesta helpommin 
						// ymmärrettävä
						cout << "-" << (1 - huonelista[i].ale) * 100 << "%";
						apunumero++;
					}
					if (apunumero == 3) {
						cout << endl;
						apunumero = 0;
					}
					else
						cout << "\t";
				}
			}
			cout << "\n\n\t**KAKSIOT**\n\nHuone:\t" << "Ale:\tHuone:\t"
				<< "Ale:\tHuone:\t" << "Ale:\n";
			apunumero = 0;
			// iteroi vectorin kaksiot läpi ja tulostaa huoneista tarvittavat tiedot
			// 3 huonetta samalle riville apunumeron avulla
			for (int i = kaksiomaara; i < huonemaara; i++) {
				int varaus = huonelista[i].varaus;
				if (varaus == 0) {

					cout << huonelista[i].id << "\t";
					if (huonelista[i].ale == 1) {

						cout << " ";
						apunumero++;
					}
					else {
						// laskutoimituksessa luodaan alekertoimesta helpommin 
						// ymmärrettävä
						cout << "-" << (1 - huonelista[i].ale) * 100 << "%";
						apunumero++;
					}
					if (apunumero == 3) {
						cout << endl;
						apunumero = 0;
					}
					else
						cout << "\t";
				}
			}
			cout << "\n\n";
		}
		else { // jos komentoa ei ole koodiin määritelty siitä annetaan palautetta
			cout << "\nEn ymmärtänyt komentoa: \"" << komento
				<< "\", yritä uudestaan.\n";
		}
	}
	return 0;
}