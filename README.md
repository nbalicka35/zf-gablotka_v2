# Aplikacja mobilna sterująca Arduino Uno R4 WiFi

Repozytorium zawiera aplikację mobilną napisaną w **React Native**, służącą do sterowania urządzeniem **Arduino Uno R4 WiFi**. Aplikacja pozwala na włączanie i wyłączanie poszczególnych sektorów szafy oraz zarządzanie stanem urządzenia. Dzięki komunikacji z Arduino, użytkownik może sterować różnymi komponentami podłączonymi do płytki.

## Wymagania

Aby uruchomić aplikację, wymagane są następujące wersje narzędzi:

- **npm**: 10.9.2+
- **node**: 22.13.0+

## Struktura plików:

    /app
      ├── /assets          # Komponenty plikowe (np. zdjęcia)
      ├── /components      # Komponenty UI (Cabinet, Buttons, Background)
      ├── /constants       # Stałe wartości (np. kolory)
      ├── /fonts           # Czcionki (Prometo)
      ├── /screens         # Ekrany aplikacji
      ├── /toggleObjects   # Logika zmiany stanów
    App.js           # Główna aplikacja

## Sposób uruchamiania:
1. **Zainstaluj wymagane narzędzia** (jeśli jeszcze nie masz) <br><br>
2. Zainstaluj zależności projektu:
   ```
   npm install
   ```
3. Przejdź do lokalizacji projektu:
   ```
   cd C:/path/to/your/project
   ```
4. Uruchom aplikację:
   ```
   npm start
   ```
   
## Dokumentacja kodu:
App.js – Główna nawigacja aplikacji

Plik główny aplikacji, który obsługuje nawigację między ekranami. Używa React Navigation (Stack Navigator) do przełączania między ekranami: Home, Blank, i Main.
MainScreen.js – Ekran główny

Główny ekran aplikacji. Zawiera:

    Tło (Background)
    Logo
    Sterowanie szafą (Cabinet)
    Przycisk "Włącz/Wyłącz" (BigButton)

Cabinet.js – Logika sterowania szafą

Komponent szafy, który umożliwia włączanie i wyłączanie sektorów szafy. Stan sektora zmienia się po kliknięciu. Każdy sektor może być włączony lub wyłączony, a cała szafa jest włączona tylko wtedy, gdy chociaż jeden sektor jest aktywny.
toggleCabinet.js – Logika zmiany stanów szafy

Klasa ToggleCabinet zarządza stanami szafy i jej sektorów:

    swapValue(key) – zmienia stan sektora.
    countTurnedOn() – liczy włączone sektory i aktualizuje stan cabinetOn.

Technologie

    React Native - Do budowy aplikacji mobilnej.
    React Navigation - Do nawigacji między ekranami.
    Expo - Środowisko do budowy aplikacji.
    Arduino Uno R4 WiFi - Główne urządzenie, którym steruje aplikacja.

## Stan aplikacji i koncept docelowy:
Na chwilę obecną aplikacja nie ma zaimplementowanego modelu BLE (Bluetooth Low Energy) oraz nie ma skończonego UI.
Koncept aplikacji można znaleźć [tutaj](https://www.figma.com/design/iZmbK1VegNtcDiAbvrVDdF/ZF-Gablotka-V3?m=auto&t=xKcmbQK0f2CaXZeO-1).
