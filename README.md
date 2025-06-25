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
&emsp;Bagaimana caranya sebuah program bisa menjalankan dua tugas secara bersamaan? Di sinilah fungsi fork() berperan. Ketika fork() dipanggil, sistem operasi akan menduplikasi proses yang sedang berjalan. Hasilnya, kita punya dua proses yang hampir identik: proses asli (induk) dan "kloningannya" (anak).
</p>

<p align="justify">
&emsp;Setelah forking, penting bagi proses induk untuk melakukan sinkronisasi dengan proses anak. Jika proses induk selesai lebih dulu tanpa menunggu proses anak, proses anak bisa menjadi "zombie"—sebuah proses yang telah selesai dieksekusi tetapi entri-nya masih ada di tabel proses. Untuk mencegah hal ini, proses induk harus menggunakan fungsi wait() yang akan menangguhkan eksekusinya sampai proses anak selesai.
</p>
  
**Solusi**

<p align="justify">
&emsp;Struktur switch(fork()) digunakan untuk memisahkan logika antara proses induk dan anak.
</p>

- Proses Anak (case 0): Menjalankan kode untuk menerima dan memproses pesan.
- Proses Induk (default): Menjalankan kode untuk meminta input dan mengirim pesan.
- Setelah mengirim pesan, proses induk memanggil wait(NULL). Ini memastikan induk menunggu sampai proses anak selesai, sehingga mencegah anak menjadi proses zombie dan program berakhir dengan bersih.

> Proses induk mengirimkan data (string) ke proses anak menggunakan IPC (Inter-Process Communication) berupa pipe.

**Teori**

<p align="justify">
&emsp;Dalam sistem operasi, setiap proses berjalan di ruang memorinya sendiri dan tidak bisa langsung mengakses memori proses lain. IPC adalah mekanisme yang memungkinkan proses-proses ini berkomunikasi. Salah satu bentuk IPC adalah pipe, yang menciptakan saluran komunikasi satu arah. Fungsi pipe(fd) membuat "pipa" ini dan memberikan dua file descriptor dalam sebuah array fd.
</p>

- fd[1] adalah ujung untuk menulis (write end). Data yang ditulis ke sini akan masuk ke dalam pipa.
- fd[0] adalah ujung untuk membaca (read end). Data yang ada di dalam pipa bisa dibaca dari sini.
  
**Solusi**

<p align="justify">
&emsp;Program ini menggunakan pipe agar proses induk dapat mengirimkan string input dari pengguna ke proses anak.
</p>

- Proses Induk (Penulis):
  - Menutup ujung pipa yang tidak digunakan: close(fd[0]);.
  - Mengirim data ke proses anak dengan menulis ke pipa: write(fd[1], buffer, len);.
- Proses Anak (Pembaca):
  - Menutup ujung pipa yang tidak digunakan: close(fd[1]);.
  - Menerima data dari proses induk dengan membaca dari pipa: read(fd[0], buffer, MSGBUFFER);.

> Pesan yang diterima oleh proses anak kemudian diubah menjadi huruf besar.

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

<p align="justify">
&emsp;Dalam sistem operasi modern, setiap program berjalan dalam prosesnya sendiri yang terisolasi. Setiap proses memiliki ruang memori (memory space) yang terpisah dan tidak bisa secara langsung mengakses memori proses lain. IPC adalah mekanisme yang disediakan oleh sistem operasi untuk memungkinkan proses-proses ini berkoordinasi dan berkomunikasi satu sama lain. Komunikasi ini penting untuk memungkinkan pembagian tugas, pertukaran data, dan sinkronisasi.
</p>

**Solusi**

<p align="justify">
&emsp;Menggunakan IPC untuk mengirimkan pesan dari satu entitas ke entitas yang lain.
</p>


**Video Menjalankan Program**

https://github.com/user-attachments/assets/a6a1f9ab-9900-42a5-9fbe-d6ec85160280

## Daftar Pustaka

<p align="justify">
&emsp;"A mechanism that will allow [cooperating processes] to exchange data and information is required.... The pipe is one of the earliest and simplest channels of communication provided in UNIX systems."
— Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts. 10th Edition. John Wiley & Sons. (Chapter 3: Processes)
</p>
<p align="justify">
&emsp;A pipe is an unnamed, one-way, first-in-first-out (FIFO) channel for communication between two related processes.... A pipe is created by the pipe system call, which returns a pair of file descriptors in an integer array. fd[0] is opened for reading and fd[1] is opened for writing."
— Kerrisk, M. (2010). The Linux Programming Interface. No Starch Press. (Chapter 44: Pipes and FIFOs)
</p>

<p align="justify">
&emsp;When a program wants to perform two tasks concurrently, it can use the fork() system call to create a duplicate of itself. This results in two nearly identical processes: the parent and the child. To enable communication between them, the pipe() system call is used, which provides two file descriptors: one for reading and one for writing. After the child process is created, the parent must wait for the child to finish using the wait() function. This prevents the child from becoming a zombie process — a process that has completed execution but still occupies an entry in the process table because its parent hasn’t retrieved its termination status.(Silberschatz, Galvin, & Gagne, 2018)
</p>
