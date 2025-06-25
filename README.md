# Final Project Sistem Operasi IT

## Peraturan
1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok B05

Nama 				| NRP
---				| ---
Muhammad Rakha Hananditya Rauf 	| 5027241015
Ivan Syarifuddin 		| 5027241045
Prabaswara Febrian Winandika 	| 5027241069
Mohammad Abyan Ranuaji 		| 5027241106

## Deskripsi Soal

<p align="justify">
&emsp;Program melakukan forking, di mana proses parent menerima satu baris input dari user dalam bentuk string yang nantinya akan di pipe ke proses child untuk diproses agar huruf kecil yang ada, diubah menjadi huruf besar. Setelah itu, proses child akan menampilkan hasil dalam bentuk output ke user.
</p>
  
### Catatan

![image](https://github.com/user-attachments/assets/5b7bd25d-9982-4d06-aff9-ea079797616f)

Struktur repository:
```
Sisop-FP-2025-IT-B05/
├─ soal_15_IPCToUpper.c
└─ README.md
```

## Pengerjaan

> Program menerima input dari user berupa message yang dimana message tersebut akan diproses agar diubah menjadi uppercase.

**Teori**

<p align="justify">
&emsp;Dalam Bahasa C, pengambilan input dari pengguna dapat dilakukan berbagai cara contohnya seperti scanf, sscanf, fgets, getch(), dimana masing-masing memiliki atribut kelebihan dan kekurangan masing-masing.
</p>
  
**Solusi**

<p align="justify">
&emsp;Menggunakan fungsi fgets untuk mendapatkan string message, yang mana fgets ini dapat membaca spasi dan membatasi jumlah karkter yang dibaca.
</p>
  
> Program menerima input dari user berupa message yang dimana message tersebut akan diproses agar diubah menjadi uppercase.

**Teori**

<p align="justify">
&emsp;Bagaimana caranya sebuah program bisa menjalankan dua tugas (proses induk dan anak) secara bersamaan? Di sinilah fungsi fork() berperan. Ketika fork() dipanggil, sistem operasi akan menduplikasi proses yang sedang berjalan. Hasilnya, kita punya dua proses yang identik: proses asli (induk) dan "kloningannya" (anak).
</p>

<p align="justify">
&emsp;Untuk berkomunikasi, mereka butuh jembatan. Fungsi pipe(fd) inilah yang menciptakan jembatan itu. pipe memberikan kita dua "file descriptor" (disimpan di array fd): fd[0] untuk membaca dan fd[1] untuk menulis.
</p>
  
**Solusi**

- pipe(fd): Pertama, kita buat dulu "pipa"-nya. Jika gagal, program akan berhenti.
- fork(): Kemudian, kita "kloning" prosesnya.
  - Di proses anak (case 0:), ia tidak perlu menulis ke pipa, jadi ia langsung menutup ujung untuk menulis (close(fd[1])). Tugasnya adalah menunggu dan membaca pesan dari induk.
  - Di proses induk (default:), ia tidak perlu membaca dari pipa, jadi ia menutup ujung untuk membaca (close(fd[0])). Tugasnya adalah mengirim pesan ke anak.

> Struktur switch(fork()) adalah cara yang umum untuk memisahkan logika antara proses induk dan anak setelah fork() dipanggil.

**Teori**

<p align="justify">
&emsp;Perubahan karakter huruf kecil ke huruf besar dalam bahasa pemrogramman C dapat dilakukan dengan fungsi toupper() dari pustaka <ctype.h> atau dalam beberapa konteks, secara manual dengan menggunakan pengecekan nilai ASCII suatu karakter. ASCII atau American Standard Code for Information Interchange adalah skema representasi karakter yang umum digunakan pada sistem komputer modern. Setiap karakter direpresentasikan oleh bilangan bulat 7-bit dengan rentang nilai dari 0 sampai 127. Huruf kecil 'a'-'z' direpresentasikan dengan nilai dari 97 hingga 122, sedangkan huruf besar 'A'–'Z' berkisar antara 65 hingga 90.
</p>

<p align="justify">
&emsp;Setiap huruf kecil dengan huruf besarnya memiliki selisih tetap sebesar 32 yang memungkinkan konversi sederhana dengan menggunakan operasi aritmatika. Metode manual dipilih karena memungkinkan eksekusi lebih cepat daripada pemanggilan fungsi pustaka, terutama pada loop besar, serta menyederhanakan dan meringankan program dengan tidak mengimpor pustaka.
</p>
  
**Solusi**

<p align="justify">
&emsp;Pesan yang diterima diproses satu per satu karakternya menggunakan loop, dan setiap karakter yang merupakan huruf kecil diubah menjadi huruf besar dengan mengurangi nilai ASCII tersebut dengan 32.
</p>

```c
for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] >= 'a' && buffer[i] <= 'z') {
        buffer[i] -= 32;
    }
}
```

**Teori**

Dalam sistem operasi modern, setiap program berjalan dalam prosesnya sendiri yang terisolasi. Setiap proses memiliki ruang memori (memory space) yang terpisah dan tidak bisa secara langsung mengakses memori proses lain. IPC adalah mekanisme yang disediakan oleh sistem operasi untuk memungkinkan proses-proses ini berkoordinasi dan berkomunikasi satu sama lain. Komunikasi ini penting untuk memungkinkan pembagian tugas, pertukaran data, dan sinkronisasi.

**Solusi**

Menggunakan IPC untuk mengirimkan pesan dari satu entitas ke entitas yang lain



**Video Menjalankan Program**

https://github.com/user-attachments/assets/a6a1f9ab-9900-42a5-9fbe-d6ec85160280

## Daftar Pustaka

"A mechanism that will allow [cooperating processes] to exchange data and information is required.... The pipe is one of the earliest and simplest channels of communication provided in UNIX systems."
— Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts. 10th Edition. John Wiley & Sons. (Chapter 3: Processes)
Sitasi 2
Sitasi 3
