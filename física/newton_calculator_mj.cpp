#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>

// ── Colores ANSI para consola ─────────────────────────────
const std::string RESET  = "\033[0m";
const std::string BOLD   = "\033[1m";
const std::string CYAN   = "\033[96m";
const std::string YELLOW = "\033[93m";
const std::string GREEN  = "\033[92m";
const std::string RED    = "\033[91m";
const std::string MAGENTA= "\033[95m";
const std::string WHITE  = "\033[97m";
const std::string DIM    = "\033[2m";

// ── Constante gravitacional ───────────────────────────────
const double G = 9.8;  // m/s²

// ── Estructura de resultados ──────────────────────────────
struct Resultado2daLey {
    double masa;        // kg
    double fuerza;      // N
    double mu;          // coef. fricción cinética
    double normal;      // N
    double friccion;    // N
    double fuerzaNeta;  // N
    double aceleracion; // m/s²
};

struct Resultado3raLey {
    double fuerzaAccion;   // N
    double fuerzaReaccion; // N  (igual magnitud, sentido opuesto)
    std::string cuerpo1;
    std::string cuerpo2;
};

// ── Utilidades de pantalla ────────────────────────────────
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void separador(char c = '=', int n = 60) {
    std::cout << CYAN;
    for (int i = 0; i < n; i++) std::cout << c;
    std::cout << RESET << "\n";
}

void titulo(const std::string& txt) {
    separador();
    std::cout << BOLD << YELLOW
              << "  " << txt << "\n"
              << RESET;
    separador();
}

double leerDouble(const std::string& prompt, double minVal = 0.0001) {
    double val;
    while (true) {
        std::cout << CYAN << "  → " << WHITE << prompt << ": " << RESET;
        if (std::cin >> val && val > minVal - 0.0001) {
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << RED << "  ✗ Valor inválido. Intente de nuevo.\n" << RESET;
    }
}

std::string leerTexto(const std::string& prompt) {
    std::string val;
    std::cout << CYAN << "  → " << WHITE << prompt << ": " << RESET;
    std::cin.ignore();
    std::getline(std::cin, val);
    return val.empty() ? "Objeto" : val;
}

// ── Calculo 2da Ley ───────────────────────────────────────
Resultado2daLey calcular2daLey(double m, double F, double mu) {
    Resultado2daLey r;
    r.masa        = m;
    r.fuerza      = F;
    r.mu          = mu;
    r.normal      = m * G;
    r.friccion    = mu * r.normal;
    r.fuerzaNeta  = F - r.friccion;
    r.aceleracion = r.fuerzaNeta / m;
    return r;
}

// ── Calculo 3ra Ley ───────────────────────────────────────
Resultado3raLey calcular3raLey(double fAccion,
                                const std::string& c1,
                                const std::string& c2) {
    Resultado3raLey r;
    r.fuerzaAccion   =  fAccion;
    r.fuerzaReaccion = -fAccion;
    r.cuerpo1 = c1;
    r.cuerpo2 = c2;
    return r;
}

// ── Mostrar resultados 2da Ley ────────────────────────────
void mostrar2daLey(const Resultado2daLey& r) {
    separador('-');
    std::cout << BOLD << GREEN << "  DATOS DE ENTRADA\n" << RESET;
    separador('-');
    std::cout << std::fixed << std::setprecision(4);
    std::cout << WHITE  << "  Masa          m  = " << YELLOW << r.masa    << " kg\n"  << RESET;
    std::cout << WHITE  << "  Fuerza aplic. F  = " << YELLOW << r.fuerza  << " N\n"   << RESET;
    std::cout << WHITE  << "  Coef. fricción μ = " << YELLOW << r.mu      << "\n"     << RESET;
    std::cout << WHITE  << "  Gravedad       g  = " << YELLOW << G         << " m/s²\n"<< RESET;

    separador('-');
    std::cout << BOLD << GREEN << "  RESULTADOS — 2DA LEY (F = m·a)\n" << RESET;
    separador('-');

    std::cout << WHITE << "  Fuerza Normal     N  = m·g = "
              << CYAN  << r.masa << "×" << G << " = "
              << BOLD  << r.normal << " N ↑\n" << RESET;

    std::cout << WHITE << "  Fricción cinética f  = μ·N = "
              << CYAN  << r.mu << "×" << r.normal << " = "
              << BOLD  << r.friccion << " N ←\n" << RESET;

    std::cout << WHITE << "  Fuerza Neta      Fn  = F-f = "
              << CYAN  << r.fuerza << "-" << r.friccion << " = "
              << BOLD  << r.fuerzaNeta << " N\n" << RESET;

    if (r.fuerzaNeta <= 0) {
        std::cout << RED << BOLD
                  << "\n  ⚠  La fricción supera la fuerza aplicada.\n"
                  << "     El objeto NO se mueve (a = 0).\n" << RESET;
    } else {
        std::cout << WHITE << "  Aceleración       a  = Fn/m = "
                  << CYAN  << r.fuerzaNeta << "/" << r.masa << " = "
                  << BOLD  << YELLOW << r.aceleracion << " m/s² →\n" << RESET;
    }

    // Par 3ra ley implícito
    separador('-');
    std::cout << BOLD << MAGENTA << "  PAR ACCIÓN-REACCIÓN (3RA LEY)\n" << RESET;
    separador('-');
    std::cout << WHITE << "  Bloque → Suelo   W  = " << BOLD << -r.normal << " N (↓ acción)\n"   << RESET;
    std::cout << WHITE << "  Suelo  → Bloque  N  = " << BOLD <<  r.normal << " N (↑ reacción)\n" << RESET;
    std::cout << DIM   << "  Ambas fuerzas: igual magnitud, sentido opuesto.\n" << RESET;
    separador();
}

// ── Mostrar resultados 3ra Ley ────────────────────────────
void mostrar3raLey(const Resultado3raLey& r) {
    separador('-');
    std::cout << BOLD << MAGENTA << "  RESULTADOS — 3RA LEY (F₁ = −F₂)\n" << RESET;
    separador('-');
    std::cout << std::fixed << std::setprecision(4);

    std::cout << WHITE  << "  Cuerpo 1 : " << CYAN  << r.cuerpo1 << "\n" << RESET;
    std::cout << WHITE  << "  Cuerpo 2 : " << CYAN  << r.cuerpo2 << "\n" << RESET;
    separador('-');

    std::cout << WHITE  << "  Fuerza de ACCIÓN   F₁ = " << BOLD << YELLOW
              << r.fuerzaAccion   << " N → (ejerce " << r.cuerpo1 << " sobre " << r.cuerpo2 << ")\n" << RESET;

    std::cout << WHITE  << "  Fuerza de REACCIÓN F₂ = " << BOLD << YELLOW
              << r.fuerzaReaccion << " N ← (ejerce " << r.cuerpo2 << " sobre " << r.cuerpo1 << ")\n" << RESET;

    std::cout << "\n" << DIM
              << "  |F₁| = |F₂| = " << std::abs(r.fuerzaAccion) << " N\n"
              << "  Misma línea de acción, sentidos opuestos,\n"
              << "  actúan sobre cuerpos DISTINTOS.\n" << RESET;
    separador();
}

// ── Menú principal ────────────────────────────────────────
void menuPrincipal() {
    titulo("CALCULADORA — LEYES DE NEWTON  |  C++");
    std::cout << YELLOW << "  Selecciona una opción:\n\n" << RESET;
    std::cout << WHITE  << "  [1]  2da Ley de Newton  (F = m·a con fricción)\n";
    std::cout          << "  [2]  3ra Ley de Newton  (Acción = Reacción)\n";
    std::cout          << "  [3]  Ambas leyes combinadas\n";
    std::cout          << "  [0]  Salir\n\n" << RESET;
    std::cout << CYAN  << "  Opción: " << RESET;
}

// ── Modo 2da Ley ──────────────────────────────────────────
void modo2daLey() {
    titulo("2DA LEY DE NEWTON  —  F = m · a");
    std::cout << DIM << "  Calcula aceleración, fricción y fuerza neta.\n\n" << RESET;

    double m  = leerDouble("Masa del objeto (kg)");
    double F  = leerDouble("Fuerza aplicada (N)", 0.0);
    double mu = leerDouble("Coef. fricción cinética μ (0 = sin fricción)", 0.0);

    std::cout << "\n";
    Resultado2daLey r = calcular2daLey(m, F, mu);
    mostrar2daLey(r);
}

// ── Modo 3ra Ley ──────────────────────────────────────────
void modo3raLey() {
    titulo("3RA LEY DE NEWTON  —  F₁ = −F₂");
    std::cout << DIM << "  Calcula el par acción-reacción entre dos cuerpos.\n\n" << RESET;

    double fA = leerDouble("Fuerza de acción (N)", 0.0001);
    std::string c1 = leerTexto("Nombre del cuerpo 1 (quien ejerce la acción)");
    std::string c2 = leerTexto("Nombre del cuerpo 2 (quien recibe la acción)");

    std::cout << "\n";
    Resultado3raLey r = calcular3raLey(fA, c1, c2);
    mostrar3raLey(r);
}

// ── Modo Combinado ────────────────────────────────────────
void modoCombinado() {
    titulo("ANÁLISIS COMPLETO — 2DA + 3RA LEY");
    std::cout << DIM << "  Ingresa los datos del sistema.\n\n" << RESET;

    double m  = leerDouble("Masa del objeto (kg)");
    double F  = leerDouble("Fuerza aplicada (N)", 0.0);
    double mu = leerDouble("Coeficiente de fricción μ", 0.0);

    std::cout << "\n";
    Resultado2daLey r2 = calcular2daLey(m, F, mu);
    mostrar2daLey(r2);

    // Par acción-reacción de la fuerza aplicada
    Resultado3raLey r3 = calcular3raLey(F, "Agente externo", "Bloque");
    mostrar3raLey(r3);
}

// ── Main ──────────────────────────────────────────────────
int main() {
    int opcion = -1;

    while (opcion != 0) {
        limpiarPantalla();
        menuPrincipal();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                limpiarPantalla();
                modo2daLey();
                break;
            case 2:
                limpiarPantalla();
                modo3raLey();
                break;
            case 3:
                limpiarPantalla();
                modoCombinado();
                break;
            case 0:
                std::cout << "\n" << GREEN << BOLD
                          << "  ¡Hasta luego! — Ciencia aplicada.\n\n"
                          << RESET;
                return 0;
            default:
                std::cout << RED << "  Opción no válida.\n" << RESET;
        }

        std::cout << YELLOW << "\n  Presiona ENTER para continuar..." << RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    return 0;
}
