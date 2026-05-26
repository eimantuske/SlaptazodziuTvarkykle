# Slaptažodžių Tvarkyklė

Tai saugi ir patogi slaptažodžių tvarkyklės programa, leidžianti vartotojams saugoti ir valdyti savo paskyrų prisijungimo duomenis. Programa sukurta taip, kad veiktų keliose operacinėse sistemose (angl. *cross-platform*), todėl ją galima sklandžiai paleisti tiek „Windows“, tiek „macOS“ aplinkose.

## Naudojamos technologijos

* **C++** – Pagrindinė programos logika, objektinis programavimas, failų valdymas ir vartotojo sąsajos (konsolės) veikimas.
* **C** – Naudojama integruojant šifravimo algoritmą.
* **CMake** – Naudojamas patogiam projekto kompiliavimui ir failų valdymui (minimali versija: 3.10).

## Saugumas

Visi jautrūs vartotojo duomenys yra užšifruojami siekiant užtikrinti maksimalų saugumą. Šiam tikslui projekte yra integruota **[tiny-AES-c](https://github.com/kokke/tiny-AES-c)** biblioteka, kuri naudoja AES (Advanced Encryption Standard) šifravimo algoritmą. 

## Kaip sukompiliuoti ir paleisti programą

Projektas naudoja `CMake` sistemą, kuri automatiškai nukopijuoja reikiamus duomenų failus (`paskyros.txt`, `config.cfg`) į kompiliavimo aplanką.

### Reikalavimai:
* Įdiegtas `CMake` (versija 3.10 ar naujesnė).
* C++ kompiliatorius (pvz., GCC/Clang skirta „Mac“/„Linux“, arba MSVC skirta „Windows“).

### Diegimo žingsniai (Terminal / Command Prompt)

1. **Atsisiųskite projektą ir atsidarykite jo aplanką per terminalą:**
```bash
   cd kelias/iki/SlaptazodziuTvarkykle
   ```

2. **Sukurkite kompiliavimo aplanką (angl. *build directory*) ir į jį pereikite:**
```bash
   mkdir build
   cd build
   ```

3. **Sukonfigūruokite projektą naudodami CMake:**
```bash
   cmake ..
   ```
   *(Pastaba: CMake automatiškai patikrins, ar egzistuoja `data/paskyros.txt` ir `config.cfg` failai, bei atitinkamai juos nukopijuos arba paruoš automatiškam sukūrimui paleidimo metu).*

4. **Sukompiliuokite programą:**
```bash
   cmake --build .
   ```

5. **Paleiskite programą:**

**„macOS“ / „Linux“ aplinkoje:**
```bash
   ./programa
   ```

   **„Windows“ aplinkoje (priklausomai nuo naudojamo kompiliatoriaus, failas gali būti aplanke `Debug` arba `Release`):**
```cmd
   Debug\programa.exe
   ```
*arba tiesiog:*
```cmd
   programa.exe
   ```

## Failų struktūra

* `src/` – Programos pradinio kodo failai (`.cpp`, `.c`).
* `include/` – Antraštiniai failai (`.h`, `.hpp`).
* `data/` – Vieta, kurioje saugomi informaciniai failai (pvz., `paskyros.txt`).
* `config.cfg` – Programos konfigūracinis failas.