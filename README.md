# 🕹️ Tugas Besar UTS Grafika Komputer: Claw Machine Simulator

**Mata Kuliah:** Grafika Komputer  
**Program Studi:** Teknik Informatika  
**Semester:** 4  
**Institusi:** Politeknik Negeri Bandung (POLBAN)  

---

## 👨‍🎓 Identitas Mahasiswa

* **Nama:** Afriza Choirie Saputra
* **NIM:** 241524002
* **Kelas:** D4-2A

---

## 📝 Deskripsi Proyek

**Claw Machine Simulator** adalah aplikasi simulasi mesin capit interaktif 2D yang dikembangkan menggunakan bahasa pemrograman **C** dan *framework* **Raylib**. Proyek ini dibuat secara khusus untuk memenuhi Tugas Besar Ujian Tengah Semester (UTS) mata kuliah Grafika Komputer.

Fokus utama dari proyek ini adalah **Procedural Rendering**. Aplikasi ini *tidak menggunakan asset gambar (sprite) eksternal* untuk menggambar objek utamanya. Seluruh elemen visual seperti capit, lengan mekanik, engsel, kabel penyangga yang melentur, hingga UI dirender menggunakan perhitungan matematis dan **Algoritma Primitif Grafika Komputer**.

## 🧠 Implementasi Algoritma Grafika

Proyek ini mendemonstrasikan penerapan langsung dari materi yang dipelajari di kelas:

1. **Digital Differential Analyzer (DDA)**
   * **Lokasi File:** `src/algo/dda.c`
   * **Penerapan:** Digunakan secara ekstensif (melalui fungsi modifikasi `DDA_ThickLine`) untuk menggambar garis tebal pada lengan mekanik (arm) capit, tali vertikal, dan elemen struktur dekoratif pada UI.
2. **Bresenham Line Algorithm**
   * **Lokasi File:** `src/algo/bresenham.c`
   * **Penerapan:** Diimplementasikan sebagai alternatif untuk rendering garis (seperti *dashed line* pada halaman About) yang bebas dari operasi *floating point*, memastikan efisiensi kalkulasi piksel.
3. **Midpoint Circle Algorithm (Midcircle)**
   * **Lokasi File:** `src/algo/midcircle.c`
   * **Penerapan:** Digunakan sebagai dasar pembentukan engsel persendian (joint) pada capit, roda penggerak mekanik, serta basis dari objek bola hadiah (prize).
4. **Quadratic Bezier Curve**
   * **Lokasi File:** `src/algo/kurvaBezierKuadratik.c`
   * **Penerapan:** Digunakan untuk mensimulasikan kelenturan (slack) pada kabel penyangga horizontal. Kurva akan secara dinamis menegang dan melentur berdasarkan jarak *claw* ke dinding mesin, memberikan efek fisika yang realistis.
5. **Transformasi 2D (Camera & Matrix)**
   * **Lokasi File:** Diimplementasikan pada `menu.c`, `claw.c`, dan `model.c`.
   * **Penerapan:** Menggunakan manipulasi *Viewport* dan *Camera2D* untuk memberikan efek perbesaran (*Zoom*), pergeseran (*Translation*), dan efek getaran layar (*Screen Shake VFX*) secara *real-time*.

## 📁 Struktur Direktori Proyek

Proyek ini menerapkan modularitas *Clean Code* untuk memisahkan antara logika algoritma, antarmuka, kontrol status, dan aset.

```text
mesinCapit/
├── src/
│   ├── algo/         # Inti dari algoritma primitif grafika (DDA, Bresenham, Midcircle, Bezier)
│   ├── effect/       # Efek visual tambahan (VFX Kamera getar)
│   ├── screens/      # State management antar layar (Menu, Claw, Model Showcase, About, Sound)
│   ├── ui/           # Penggambaran komponen UI, Capit (DrawClaw), Kabel, Hadiah, dan Tombol
│   └── asset/        # Aset Audio (BGM Menu, BGM Gameplay, dan SFX Arcade)
├── coords.c / .h     # Helper untuk manajemen koordinat
├── main.c            # Titik masuk program (Entry Point) & Game Loop utama
├── screen_type.h     # Definisi enum Screen (MENU, MODEL, ABOUT, CLAW) dan Konstanta Layar
├── Makefile          # Konfigurasi Build standar
└── Makefile.win      # Konfigurasi Build khusus untuk lingkungan Windows (MinGW/w64devkit)
