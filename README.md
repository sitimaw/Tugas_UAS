# Tugas_UAS

Nama : Siti Mawaddah
NPM  : 1908107010031

*compiler yang digunakan adalah gcc yang bersifat terbuka (open source/non-proprietary)

#Membaca data dari file
Jika file txt belum ada atau kosong, akan diberikan 5 data awal peserta.
Jika file sudah memiliki data, maka data dari file tersebut yang digunakan.
Format data dalam file yaitu:
nik;nama;jk;alamat;hafalan;target
Data dari file disimpan juga ke dalam struct agar mempermudah proses pengolahan data.

#Proses login
Jika file bin belum ada atau kosong, akan diberikan username dan password awal.
Jika file sudah memiliki data, maka data dari file tersebut yang digunakan.
Username awal: mawaddah
Password awal: mawmaw
Setelah login, user dapat mengganti username dan password sesuai yang diinginkan

#Menampilkan data
Data yang ditampilkan berasal dari struct yang sebelumnya diinput dari file

#Mencari data
Data dicari berdasarkan nik, kemudian ditampilkan data yang memiliki nik tersebut menggunakan fungsi find.

#Menambah data
Setiap atribut data memiliki syaratnya masing-masing.
Setelah proses input selesai, data akan disimpan ke struct menggunakan fungsi set dan disimpan ke file menggunakan fungsi save.

#Menghapus data
Terdapat satu variabel EmptyStruct bertipe struct data yang digunakan untuk menghapus data pada struct.
Setelah data dihapus, data yang tersisa di struct disave ulang ke dalam file menggunakan fungsi save.

#Mengubah data
Proses ubah data akan mengubah terlebih dahulu data pada struct, kemudian menyimpan hasilnya ke file.

#Ubah username dan password
User dapat mengubah username atau password.
Jika ingin mengubah password akan dimintai password lama sebagai autentikasi, jika terjadi 3 kali kesalahan dalam pengisian password maka akan diminta untuk kembali di lain waktu.
