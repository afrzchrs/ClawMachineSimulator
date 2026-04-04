# 🕹️ Claw Machine Simulator (Raylib)

Sebuah simulator mesin capit (claw machine) interaktif berbasis 2D yang dikembangkan menggunakan bahasa **C** dan *framework* **Raylib**. 

Proyek ini bukan sekadar *game* biasa, melainkan implementasi praktis dari berbagai **Algoritma Grafika Komputer** tingkat dasar hingga menengah untuk merender objek secara prosedural (tanpa menggunakan *asset* gambar/sprite eksternal untuk elemen utamanya).

## ✨ Fitur Utama

* **Procedural Rendering:** Hampir seluruh elemen visual (capit, kabel, UI, latar belakang) digambar menggunakan algoritma matematis murni:
    * *Digital Differential Analyzer (DDA)* dan *Bresenham* untuk rendering garis lurus.
    * *Midcircle Algorithm* untuk engsel dan roda.
    * *Quadratic Bezier Curves* untuk simulasi kelenturan kabel penyangga secara dinamis.
* **State Machine Logic:** Menggunakan *Finite State Machine* (Idle, Dropping, Grabbing, Returning, dll) untuk mengatur siklus animasi dan fisika capit yang mulus.
* **Efek Visual Interaktif:**
    * Animasi *idle* bergoyang (hovering) dengan kalkulasi sinus/cosinus.
    * Sistem partikel sederhana (energy orb, debu bercahaya).
    * Efek getaran layar (Screen Shake) saat capit berhasil menangkap hadiah tertentu.
* **Multi-Screen Architecture:** Navigasi mulus antara Main Menu, Model Showcase, Simulasi Utama, dan About Page.
* **Audio Integration:** Dilengkapi dengan BGM yang dinamis dan efek suara (SFX) rel, tombol, dan capit untuk pengalaman *arcade* yang nyata.

## 🛠️ Teknologi yang Digunakan
* **Bahasa:** C
* **Library:** Raylib 5.5
* **Compiler:** GCC (MinGW-w64)
* **Build System:** Makefile

## 📁 Struktur Proyek
```text
mesinCapit/
├── src/
│   ├── algo/      # Implementasi algoritma grafika (DDA, Bresenham, Bezier, Midcircle)
│   ├── effect/    # Efek visual khusus (Screen shake, dll)
│   ├── screens/   # Logika per-layar (Menu, Claw, Model, About, Sound)
│   ├── ui/        # Komponen antarmuka & penggambaran objek (Claw, Cable, Buttons, Prizes)
│   └── asset/     # File audio (BGM & SFX)
├── main.c         # Entry point & State Manager utama
├── screen_type.h  # Definisi enum layar & resolusi
└── Makefile.win   # Konfigurasi build untuk Windows
