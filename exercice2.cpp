
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ===============================
// CLASSE MATIERE
// ===============================
class Matiere {
private:
    string codeMatiere;
    string nomMatiere;
    double coefficient;

public:
    Matiere(string code, string nom, double coef) {
        codeMatiere = code;
        nomMatiere = nom;
        coefficient = coef;
    }

    string getCode() const {
        return codeMatiere;
    }

    string getNom() const {
        return nomMatiere;
    }

    double getCoefficient() const {
        return coefficient;
    }

    void afficher() const {
        cout << nomMatiere
             << " | Coefficient : " << coefficient << endl;
    }
};


// ===============================
// CLASSE UE
// ===============================
class UE {
private:
    string codeUE;
    string nomUE;
    int credit;
    vector<Matiere> matieres;

public:
    UE(string code, string nom, int c) {
        codeUE = code;
        nomUE = nom;
        credit = c;
    }

    void ajouterMatiere(Matiere m) {
        matieres.push_back(m);
    }

    string getNom() const {
        return nomUE;
    }

    int getCredit() const {
        return credit;
    }

    const vector<Matiere>& getMatieres() const {
        return matieres;
    }

    void afficher() const {
        cout << "UE : " << nomUE
             << " | Credits : " << credit << endl;

        for (const Matiere& m : matieres) {
            m.afficher();
        }
    }
};


// ===============================
// CLASSE FILIERE
// ===============================
class Filiere {
private:
    string codeFiliere;
    string nomFiliere;
    vector<UE> listeUE;

public:
    Filiere(string code, string nom) {
        codeFiliere = code;
        nomFiliere = nom;
    }

    void ajouterUE(UE ue) {
        listeUE.push_back(ue);
    }

    string getNom() const {
        return nomFiliere;
    }

    const vector<UE>& getUE() const {
        return listeUE;
    }

    void afficherUE() const {
        cout << "\nFiliere : " << nomFiliere << endl;

        for (const UE& ue : listeUE) {
            ue.afficher();
        }
    }
};


// ===============================
// CLASSE NOTE
// ===============================
class Note {
private:
    string codeMatiere;
    double valeur;

public:
    Note(string code, double v) {
        codeMatiere = code;
        valeur = v;
    }

    string getCodeMatiere() const {
        return codeMatiere;
    }

    double getValeur() const {
        return valeur;
    }

    void afficher() const {
        cout << codeMatiere << " : "
             << valeur << "/20" << endl;
    }
};


// ===============================
// CLASSE ETUDIANT
// ===============================
class Etudiant {
private:
    string matricule;
    string nom;
    string prenom;
    string niveau;
    Filiere* filiere;
    vector<Note> notes;

public:
    Etudiant(string mat, string n, string p,
             string niv, Filiere* f) {
        matricule = mat;
        nom = n;
        prenom = p;
        niveau = niv;
        filiere = f;
    }

    void ajouterNote(Note n) {
        notes.push_back(n);
    }

    double chercherNote(string code) const {
        for (const Note& n : notes) {
            if (n.getCodeMatiere() == code) {
                return n.getValeur();
            }
        }

        return -1;
    }

    // Calcul de la moyenne generale
    double calculerMoyenne() const {
        double somme = 0;
        double totalCoef = 0;

        if (filiere == nullptr)
            return 0;

        for (const UE& ue : filiere->getUE()) {
            for (const Matiere& m : ue.getMatieres()) {

                double note = chercherNote(m.getCode());

                if (note >= 0) {
                    somme += note * m.getCoefficient();
                    totalCoef += m.getCoefficient();
                }
            }
        }

        if (totalCoef == 0)
            return 0;

        return somme / totalCoef;
    }

    // Verification de la validation d'une UE
    bool validerUE(const UE& ue) const {
        double somme = 0;
        double totalCoef = 0;

        for (const Matiere& m : ue.getMatieres()) {
            double note = chercherNote(m.getCode());

            if (note < 0)
                return false;

            somme += note * m.getCoefficient();
            totalCoef += m.getCoefficient();
        }

        if (totalCoef == 0)
            return false;

        return (somme / totalCoef) >= 10;
    }

    // Affichage du releve de notes
    void afficherReleve() const {

        cout << "\n====================================\n";
        cout << "          RELEVE DE NOTES\n";
        cout << "====================================\n";

        cout << "Matricule : " << matricule << endl;
        cout << "Nom       : " << nom << endl;
        cout << "Prenom    : " << prenom << endl;
        cout << "Niveau    : " << niveau << endl;

        if (filiere == nullptr) {
            cout << "Aucune filiere associee.\n";
            return;
        }

        cout << "Filiere   : " << filiere->getNom() << endl;

        for (const UE& ue : filiere->getUE()) {

            cout << "\n------------------------------------\n";
            cout << "UE : " << ue.getNom() << endl;
            cout << "Credits : " << ue.getCredit() << endl;

            for (const Matiere& m : ue.getMatieres()) {

                double note = chercherNote(m.getCode());

                cout << m.getNom() << " : ";

                if (note < 0)
                    cout << "Non disponible" << endl;
                else
                    cout << note << "/20" << endl;
            }

            cout << "Validation : ";

            if (validerUE(ue))
                cout << "VALIDEE" << endl;
            else
                cout << "NON VALIDEE" << endl;
        }

        cout << "\n------------------------------------\n";

        cout << "Moyenne generale : "
             << fixed << setprecision(2)
             << calculerMoyenne() << "/20" << endl;

        cout << "====================================\n";
    }
};


// ===============================
// PROGRAMME PRINCIPAL
// ===============================
int main() {

    // Creation des matieres
    Matiere m1("M01", "Mathematiques", 2);
    Matiere m2("M02", "Informatique", 3);
    Matiere m3("M03", "Algorithmique", 2);

    // Creation des UE
    UE ue1("UE01", "Mathematiques", 5);
    UE ue2("UE02", "Algorithmique", 4);

    // Ajout des matieres dans les UE
    ue1.ajouterMatiere(m1);
    ue1.ajouterMatiere(m2);

    ue2.ajouterMatiere(m3);

    // Creation de la filiere
    Filiere f1("F01", "Informatique");

    // Ajout des UE dans la filiere
    f1.ajouterUE(ue1);
    f1.ajouterUE(ue2);

    // Creation de l'etudiant
    Etudiant e1("ET001", "DANSOU", "Brigitte",
                "L1", &f1);

    // Ajout des notes de l'etudiant
    e1.ajouterNote(Note("M01", 12));
    e1.ajouterNote(Note("M02", 14));
    e1.ajouterNote(Note("M03", 15));

    // Affichage du releve
    e1.afficherReleve();

    return 0;
}

