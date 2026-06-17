// iostream  - konsoles ivedimui/isvedimui
// fstream   - failu skaitymui ir rasymui
// vector    - dinaminiam masyvui (filmu sarasui)
// string    - teksto eiluciu darbui
// sstream   - eilutes dalijimui pagal ; (parsinimas)
// algorithm - rikiavimo funkcijai sort
// cstdlib   - bendros pagalbines funkcijos (exit ir pan.)
// limits    - cin srauto valymui esant netinkamai ivesciai

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

// Struktura, aprasanti viena filma
struct Filmas {
    string pavadinimas;
    string zanras;
    int metai;
    string rezisierius;
    double ivertinimas;
};

// Globalus filmu konteineris
vector<Filmas> filmai;

const string FAILO_VARDAS = "filmai.txt";

// Funkcija isvalo cin srauta po klaidingos ivesties
void isvalytiIvedima() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Sukuria pradini faila su 15 irasu, jei jo dar nera
void sukurtiPradiniFaila() {
    // --- Pradeda irasyma i faila (pradiniai duomenys) ---
    ofstream isvestis(FAILO_VARDAS);
    if (!isvestis.is_open()) {
        cout << "Klaida: nepavyko sukurti failo " << FAILO_VARDAS << endl;
        return;
    }
    // Iraso duomenis i faila
    isvestis << "Sauliuko nuotykiai;Komedija;2001;Jonas Jonaitis;7.5\n";
    isvestis << "Tamsos riteris;Veiksmas;2008;Christopher Nolan;9.0\n";
    isvestis << "Pradzia;Mokslines fantastikos;2010;Christopher Nolan;8.8\n";
    isvestis << "Matrica;Mokslines fantastikos;1999;Wachowski;8.7\n";
    isvestis << "Krestatevis;Drama;1972;Francis Ford Coppola;9.2\n";
    isvestis << "Pulp Fiction;Kriminalinis;1994;Quentin Tarantino;8.9\n";
    isvestis << "Forrest Gump;Drama;1994;Robert Zemeckis;8.8\n";
    isvestis << "Begantis skustuvo asmenimi;Mokslines fantastikos;1982;Ridley Scott;8.1\n";
    isvestis << "Gladiatorius;Veiksmas;2000;Ridley Scott;8.5\n";
    isvestis << "Titanikas;Drama;1997;James Cameron;7.9\n";
    isvestis << "Avataras;Mokslines fantastikos;2009;James Cameron;7.9\n";
    isvestis << "Begantis traukinys;Veiksmas;1985;Andrei Konchalovsky;7.2\n";
    isvestis << "Liutas karalius;Animacija;1994;Roger Allers;8.5\n";
    isvestis << "Ratatouille;Animacija;2007;Brad Bird;8.1\n";
    isvestis << "Tarp zvaigzdziu;Mokslines fantastikos;2014;Christopher Nolan;8.6\n";
    isvestis.close();
    // --- Baigia irasyma i faila ---
    cout << "Sukurtas naujas failas " << FAILO_VARDAS << " su pradiniais duomenimis." << endl;
}

// Nuskaito visus filmus is failo i globaluji vektoriu
void nuskaitytiIsFailo() {
    // --- Pradeda duomenu nuskaitymas is failo ---
    ifstream ivestis(FAILO_VARDAS);
    // Tikrina ar failas egzistuoja
    if (!ivestis.is_open()) {
        cout << "Failas " << FAILO_VARDAS << " nerastas. Kuriamas naujas..." << endl;
        sukurtiPradiniFaila();
        ivestis.open(FAILO_VARDAS);
        if (!ivestis.is_open()) {
            cout << "Klaida: nepavyko atidaryti failo." << endl;
            return;
        }
    }

    filmai.clear();
    string eilute;
    while (getline(ivestis, eilute)) {
        if (eilute.empty()) continue;
        stringstream ss(eilute);
        Filmas f;
        string metaiStr, ivertStr;

        getline(ss, f.pavadinimas, ';');
        getline(ss, f.zanras, ';');
        getline(ss, metaiStr, ';');
        getline(ss, f.rezisierius, ';');
        getline(ss, ivertStr, ';');

        // Tikrina ar laukai konvertuojami i skaicius
        try {
            f.metai = stoi(metaiStr);
            f.ivertinimas = stod(ivertStr);
            filmai.push_back(f);
        } catch (...) {
            // Praleidziama klaidinga eilute
        }
    }
    ivestis.close();
    // --- Baigia duomenu nuskaityma is failo ---
}

// Iraso visus globalaus vektoriaus filmus i faila (perrasoma)
void issaugotiIFaila() {
    // --- Pradeda irasyma i faila ---
    ofstream isvestis(FAILO_VARDAS);
    if (!isvestis.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo rasymui." << endl;
        return;
    }
    // Iraso duomenis i faila
    for (size_t i = 0; i < filmai.size(); i++) {
        isvestis << filmai[i].pavadinimas << ";"
                 << filmai[i].zanras << ";"
                 << filmai[i].metai << ";"
                 << filmai[i].rezisierius << ";"
                 << filmai[i].ivertinimas << "\n";
    }
    isvestis.close();
    // --- Baigia irasyma i faila ---
}

// Atvaizduoja viena filma su jo indeksu
void rodytiFilma(const Filmas& f, int indeksas) {
    cout << "[" << indeksas << "] "
         << f.pavadinimas << " | "
         << f.zanras << " | "
         << f.metai << " | "
         << f.rezisierius << " | "
         << f.ivertinimas << endl;
}

// Read: parodo visus filmus konsoleje
void rodytiVisus(const vector<Filmas>& sarasas) {
    if (sarasas.empty()) {
        cout << "Sarasas tuscias." << endl;
        return;
    }
    cout << "\n--- Filmu sarasas ---" << endl;
    for (size_t i = 0; i < sarasas.size(); i++) {
        rodytiFilma(sarasas[i], (int)i);
    }
}

// Read: ieskoma pagal indeksa arba pavadinima ir parodomas vienas filmas
void rodytiVienaFilma(const vector<Filmas>& sarasas) {
    cout << "Pasirinkite: 1 - pagal indeksa, 2 - pagal pavadinima: ";
    int pasirinkimas;
    cin >> pasirinkimas;
    // Tikrina ar ivestis sekminga
    if (cin.fail()) {
        isvalytiIvedima();
        cout << "Netinkama ivestis." << endl;
        return;
    }
    isvalytiIvedima();

    if (pasirinkimas == 1) {
        cout << "Iveskite indeksa: ";
        int idx;
        cin >> idx;
        if (cin.fail()) { isvalytiIvedima(); cout << "Netinkama ivestis." << endl; return; }
        isvalytiIvedima();
        // Tikrina ar indeksas teisingas
        if (idx < 0 || idx >= (int)sarasas.size()) {
            cout << "Neegzistuojantis indeksas." << endl;
            return;
        }
        rodytiFilma(sarasas[idx], idx);
    } else if (pasirinkimas == 2) {
        cout << "Iveskite pavadinima: ";
        string pav;
        getline(cin, pav);
        bool rasta = false;
        for (size_t i = 0; i < sarasas.size(); i++) {
            if (sarasas[i].pavadinimas == pav) {
                rodytiFilma(sarasas[i], (int)i);
                rasta = true;
            }
        }
        if (!rasta) cout << "Filmas nerastas." << endl;
    } else {
        cout << "Netinkamas pasirinkimas." << endl;
    }
}

// Create: prideda nauja filma (modifikuoja perduota vektoriu per nuoroda)
void pridetiFilma(vector<Filmas>& sarasas) {
    // --- PRIDEDAMA: naujas filmas ---
    Filmas f;
    cout << "Iveskite pavadinima: ";
    getline(cin, f.pavadinimas);
    cout << "Iveskite zanra: ";
    getline(cin, f.zanras);

    cout << "Iveskite metus: ";
    cin >> f.metai;
    // Tikrina ar metai - skaicius
    if (cin.fail()) {
        isvalytiIvedima();
        cout << "Netinkami metai. Pridejimas nutrauktas." << endl;
        return;
    }
    isvalytiIvedima();

    cout << "Iveskite rezisieriu: ";
    getline(cin, f.rezisierius);

    cout << "Iveskite ivertinima (0.0 - 10.0): ";
    cin >> f.ivertinimas;
    // Tikrina ar ivertinimas tinkamas
    if (cin.fail() || f.ivertinimas < 0.0 || f.ivertinimas > 10.0) {
        isvalytiIvedima();
        cout << "Netinkamas ivertinimas. Pridejimas nutrauktas." << endl;
        return;
    }
    isvalytiIvedima();

    sarasas.push_back(f);
    issaugotiIFaila();
    cout << "Filmas pridetas." << endl;
}

// Update: leidzia redaguoti pasirinkto filmo laukus
void redaguotiFilma(vector<Filmas>& sarasas) {
    if (sarasas.empty()) { cout << "Sarasas tuscias." << endl; return; }
    cout << "Iveskite redaguojamo filmo indeksa: ";
    int idx;
    cin >> idx;
    if (cin.fail()) { isvalytiIvedima(); cout << "Netinkama ivestis." << endl; return; }
    isvalytiIvedima();

    // Tikrina ar indeksas teisingas
    if (idx < 0 || idx >= (int)sarasas.size()) {
        cout << "Neegzistuojantis indeksas." << endl;
        return;
    }

    // --- KEICIAMA: iraso laukai ---
    Filmas& f = sarasas[idx];
    string laikinas;

    cout << "Naujas pavadinimas (Enter - palikti '" << f.pavadinimas << "'): ";
    getline(cin, laikinas);
    if (!laikinas.empty()) f.pavadinimas = laikinas;

    cout << "Naujas zanras (Enter - palikti '" << f.zanras << "'): ";
    getline(cin, laikinas);
    if (!laikinas.empty()) f.zanras = laikinas;

    cout << "Nauji metai (0 - palikti " << f.metai << "): ";
    int n;
    cin >> n;
    if (cin.fail()) { isvalytiIvedima(); }
    else { isvalytiIvedima(); if (n > 0) f.metai = n; }

    cout << "Naujas rezisierius (Enter - palikti '" << f.rezisierius << "'): ";
    getline(cin, laikinas);
    if (!laikinas.empty()) f.rezisierius = laikinas;

    cout << "Naujas ivertinimas (-1 - palikti " << f.ivertinimas << "): ";
    double iv;
    cin >> iv;
    if (cin.fail()) { isvalytiIvedima(); }
    else {
        isvalytiIvedima();
        // Tikrina ar ivertinimas teisingas
        if (iv >= 0.0 && iv <= 10.0) f.ivertinimas = iv;
    }

    issaugotiIFaila();
    cout << "Filmas atnaujintas." << endl;
}

// Delete: pasalina filma is saraso pagal indeksa
void salintiFilma(vector<Filmas>& sarasas) {
    if (sarasas.empty()) { cout << "Sarasas tuscias." << endl; return; }
    cout << "Iveskite salinamo filmo indeksa: ";
    int idx;
    cin >> idx;
    if (cin.fail()) { isvalytiIvedima(); cout << "Netinkama ivestis." << endl; return; }
    isvalytiIvedima();

    // Tikrina ar indeksas teisingas
    if (idx < 0 || idx >= (int)sarasas.size()) {
        cout << "Neegzistuojantis indeksas." << endl;
        return;
    }
    // --- KEICIAMA: irasas salinamas ---
    sarasas.erase(sarasas.begin() + idx);
    issaugotiIFaila();
    cout << "Filmas pasalintas." << endl;
}

// Paieska pagal zanra arba rezisieriu
void paieska(const vector<Filmas>& sarasas) {
    cout << "Pasirinkite: 1 - pagal zanra, 2 - pagal rezisieriu: ";
    int p;
    cin >> p;
    if (cin.fail()) { isvalytiIvedima(); cout << "Netinkama ivestis." << endl; return; }
    isvalytiIvedima();

    cout << "Iveskite kriteriju: ";
    string krit;
    getline(cin, krit);

    bool rasta = false;
    for (size_t i = 0; i < sarasas.size(); i++) {
        // Tikrina ar atitinka pasirinkta kriteriju
        if ((p == 1 && sarasas[i].zanras == krit) ||
            (p == 2 && sarasas[i].rezisierius == krit)) {
            rodytiFilma(sarasas[i], (int)i);
            rasta = true;
        }
    }
    if (!rasta) cout << "Atitikmenu nerasta." << endl;
}

// Rikiavimas pagal ivertinima arba metus (nemodifikuoja originalaus saraso)
void rikiavimas(vector<Filmas> sarasas) {
    cout << "1 - pagal ivertinima mazejanciai\n"
            "2 - pagal ivertinima didejanciai\n"
            "3 - pagal metus mazejanciai\n"
            "4 - pagal metus didejanciai\n"
            "Pasirinkimas: ";
    int p;
    cin >> p;
    if (cin.fail()) { isvalytiIvedima(); cout << "Netinkama ivestis." << endl; return; }
    isvalytiIvedima();

    switch (p) {
        case 1: sort(sarasas.begin(), sarasas.end(), [](const Filmas& a, const Filmas& b){ return a.ivertinimas > b.ivertinimas; }); break;
        case 2: sort(sarasas.begin(), sarasas.end(), [](const Filmas& a, const Filmas& b){ return a.ivertinimas < b.ivertinimas; }); break;
        case 3: sort(sarasas.begin(), sarasas.end(), [](const Filmas& a, const Filmas& b){ return a.metai > b.metai; }); break;
        case 4: sort(sarasas.begin(), sarasas.end(), [](const Filmas& a, const Filmas& b){ return a.metai < b.metai; }); break;
        default: cout << "Netinkamas pasirinkimas." << endl; return;
    }
    rodytiVisus(sarasas);
}

// Isspausdina meniu vartotojui
void rodytiMeniu() {
    cout << "\n=== FILMU KATALOGAS ===\n"
            "1. Rodyti visus filmus\n"
            "2. Rodyti viena filma\n"
            "3. Prideti nauja filma\n"
            "4. Redaguoti filma\n"
            "5. Salinti filma\n"
            "6. Paieska pagal zanra/rezisieriu\n"
            "7. Rikiavimas\n"
            "0. Iseiti\n"
            "Pasirinkimas: ";
}

// --- PRADEDA PAGRINDINE PROGRAMOS DALIS (main) ---
int main() {
    nuskaitytiIsFailo();

    int pasirinkimas = -1;
    while (pasirinkimas != 0) {
        rodytiMeniu();
        cin >> pasirinkimas;
        // Tikrina ar ivestis sveikasis skaicius
        if (cin.fail()) {
            isvalytiIvedima();
            cout << "Netinkama ivestis, bandykite dar karta." << endl;
            continue;
        }
        isvalytiIvedima();

        switch (pasirinkimas) {
            case 1: rodytiVisus(filmai); break;
            case 2: rodytiVienaFilma(filmai); break;
            case 3: pridetiFilma(filmai); break;
            case 4: redaguotiFilma(filmai); break;
            case 5: salintiFilma(filmai); break;
            case 6: paieska(filmai); break;
            case 7: rikiavimas(filmai); break;
            case 0: cout << "Iki!" << endl; break;
            default: cout << "Tokio pasirinkimo nera." << endl;
        }
    }
    return 0;
}
// --- BAIGIA PAGRINDINE PROGRAMOS DALIS ---
