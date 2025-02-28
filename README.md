# Aplikacja mobilna sterująca Arduino Uno R4 WiFi

Repozytorium zawiera aplikację mobilną napisaną w **React Native**, służącą do sterowania urządzeniem **Arduino Uno R4 WiFi**. Aplikacja pozwala na włączanie i wyłączanie poszczególnych sektorów szafy oraz zarządzanie stanem urządzenia. Dzięki komunikacji z Arduino, użytkownik może sterować różnymi komponentami podłączonymi do płytki.

## Wymagania

Aby uruchomić aplikację, wymagane są następujące wersje narzędzi:

- **npm**: 10.9.2+
- **node**: 22.13.0+

## Struktura plików:

    /app
      ├── /components      # Komponenty UI (Cabinet, Buttons, Background)
      ├── /screens         # Ekrany aplikacji (WelcomeScreen, MainScreen)
      ├── /constants       # Stałe wartości (np. kolory)
      ├── /toggleObjects   # Logika zmiany stanów
      └── App.js           # Główna aplikacja

## Sposób uruchamiania:
1. **Zainstaluj Expo CLI** (jeśli jeszcze nie masz):
   ```
   npm install -g expo-cli
2. Zainstaluj zależności projektu:
   ```
   npm install 
4. Uruchom aplikację:
   ```
   npm start

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
